/*******************************************************************************
 * Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
 *                                                                             *
 * This program is free software; you can redistribute it and/or               *
 * modify it under the terms of the GNU General Public License                 *
 * as published by the Free Software Foundation; either version 2              *
 * of the License, or (at your option) any later version.                      *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with this program; if not, write to the Free Software                 *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. *
 *                                                                             *
 *                                                                             *
 ******************************************************************************/

#include "CEventProcessorVisitor.h"

#include <stdlib.h>
#include <time.h>

#include "../../engine/event/CEventsQueue.h"

#include "season/CStartSeasonEvent.h"
#include "season/CEndSeasonEvent.h"

#include "competition/CStartCompetitionEvent.h"
#include "competition/CEndCompetitionEvent.h"

#include "match/CMatchEvent.h"
#include "match/CStartMatchEvent.h"
#include "match/CGoalMatchEvent.h"
#include "match/CEndMatchEvent.h"

#include "../CSinglePlayerGame.h"
#include "../CSeasonGenerator.h"
#include "../db/bean/CPfGoals.h"
#include "../db/bean/CPfMatches.h"
#include "../db/bean/CPfTeamAverages.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"

CEventProcessorVisitor::CEventProcessorVisitor(CSinglePlayerGame *game)
: IEventVisitor(), m_matchesMap()
{
	m_game = game;

	// Set the seed for the pseudo-random number generator
    srand(time(NULL));
}

CEventProcessorVisitor::~CEventProcessorVisitor()
{
	std::map<int, std::vector<CPfGoals *>*>::iterator itMatches;
	for( itMatches=m_matchesMap.begin(); itMatches!=m_matchesMap.end(); itMatches++){
		int							xMatch			= itMatches->first;
		std::vector<CPfGoals *>		*goalsVector	= itMatches->second;

		std::vector<CPfGoals*>::iterator itGoals;
		for( itGoals=goalsVector->begin(); itGoals!=goalsVector->end(); itGoals++){
			delete (*itGoals);
		}
		delete goalsVector;
	}
	m_matchesMap.clear();
}

void CEventProcessorVisitor::startSeasonEventVisitor(const CStartSeasonEvent &event)
{
	// Nothing to do
}

void CEventProcessorVisitor::endSeasonEventVisitor(const CEndSeasonEvent &event)
{
	CSeasonGenerator::generateSeason(m_game);
}

void CEventProcessorVisitor::startCompetitionEventVisitor(const CStartCompetitionEvent &event)
{
	// Nothing to do
}

void CEventProcessorVisitor::endCompetitionEventVisitor(const CEndCompetitionEvent &event)
{
	// Nothing to do
}

void CEventProcessorVisitor::matchEventVisitor(const CMatchEvent &event)
{
	IPfMatchesDAO 	*matchesDAO 	= m_game->getIDAOFactory()->getIPfMatchesDAO();
	CPfMatches 		*match			= matchesDAO->findByXMatch(event.getXMatch());
	int				 xPlayerTeam	= m_game->getOptionManager()->getGamePlayerTeam();

	if( match->getXFkTeamAway()==xPlayerTeam || match->getXFkTeamHome()==xPlayerTeam ){
		if( m_game->getOptionManager()->getMatchResultMode() ){
			simulateMatch(match);
			CGameEngine::getInstance()->getWindowManager()->nextScreen("MatchResult");
//			m_game->nextScreen(m_game->getMatchResultScreen());
		}else{
			CGameEngine::getInstance()->getWindowManager()->nextScreen("Simulator");
//			m_game->nextScreen(m_game->getSimulatorScreen());
		}
	}else{
		simulateMatch(match);
	}

	delete match;
}

void CEventProcessorVisitor::simulateMatch(CPfMatches *match)
{
	IDAOFactory        *daoFactory     = m_game->getIDAOFactory();
    IPfTeamPlayersDAO  *teamPlayersDAO = daoFactory->getIPfTeamPlayersDAO();
    IPfTeamAveragesDAO *teamsAvgDAO    = daoFactory->getIPfTeamAveragesDAO();

    m_game->getEventsQueue()->push(new CStartMatchEvent(match->getDMatch(), match->getXMatch()));

    int xHomeTeam  = match->getXFkTeamHome();
    int xAwayTeam  = match->getXFkTeamAway();
    CPfTeamAverages *homeTeamAvg = teamsAvgDAO->findByXTeam(xHomeTeam);
    CPfTeamAverages *awayTeamAvg = teamsAvgDAO->findByXTeam(xAwayTeam);
    int nHomeGoals = getRandomNGoals(homeTeamAvg, awayTeamAvg);
    int nAwayGoals = getRandomNGoals(awayTeamAvg, homeTeamAvg);

    delete homeTeamAvg;
    delete awayTeamAvg;

    if( nHomeGoals>0 ){
        std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findLineUpByXFkTeam(xHomeTeam);
        while( nHomeGoals>0 ){
            int numPlayer = rand()%teamPlayesList->size();
            if(numPlayer == 0) { //Goalie don't score
                numPlayer = 10;
            }
            CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](numPlayer);

            int minute = rand()%90;
            CDate eventDate = match->getDMatch();
            eventDate.setMin(eventDate.getMin()+minute);

            m_game->getEventsQueue()->push(new CGoalMatchEvent(eventDate, match->getXMatch(), xHomeTeam, teamPlayer->getXTeamPlayer(), minute, false));

            nHomeGoals--;
        }
        teamPlayersDAO->freeVector(teamPlayesList);
    }
    if( nAwayGoals>0 ){
        std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findLineUpByXFkTeam(xAwayTeam);
        while( nAwayGoals>0 ){
            int numPlayer = rand()%teamPlayesList->size();
            if(numPlayer == 0) { //Goalie don't score
                numPlayer = 10;
            }
            CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](numPlayer);

            int minute = rand()%90;
            CDate eventDate = match->getDMatch();
            eventDate.setMin(eventDate.getMin()+minute);

            m_game->getEventsQueue()->push(new CGoalMatchEvent(eventDate, match->getXMatch(), xAwayTeam, teamPlayer->getXTeamPlayer(), minute, false));

            nAwayGoals--;
        }
        teamPlayersDAO->freeVector(teamPlayesList);
    }

    CDate eventDate = match->getDMatch();
    eventDate.setMin(eventDate.getMin()+90);

    m_game->getEventsQueue()->push(new CEndMatchEvent(eventDate, match->getXMatch()));
}

int CEventProcessorVisitor::getRandomNGoals(CPfTeamAverages *attackTeam, CPfTeamAverages *defenseTeam)
{
    int goals = 0;
    int teamFactor = attackTeam->getNTotal() - defenseTeam->getNTotal();

    int n = rand()%100 + teamFactor;

         if( n<25  )         { goals = 0; }
    else if( n>=25 && n<55  ){ goals = 1; }
    else if( n>=55 && n<80  ){ goals = 2; }
    else if( n>=80 && n<96  ){ goals = 3; }
    else if( n>=96 && n<100 ){ goals = 4; }
    else if( n>=100 )        { goals = 5; }
    return goals;
}

void CEventProcessorVisitor::startMatchEventVisitor(const CStartMatchEvent &event)
{
	int xMatch = event.getXMatch();
	if( m_matchesMap.find(xMatch)==m_matchesMap.end() ){
		// if the match is not registered
		m_matchesMap[xMatch] = new std::vector<CPfGoals*>();
	}
}

void CEventProcessorVisitor::goalMatchEventVisitor(const CGoalMatchEvent &event)
{
	int xMatch = event.getXMatch();
	if( m_matchesMap.find(xMatch)!=m_matchesMap.end() ){
		// if the match is registered
		CPfGoals *goal = new CPfGoals();
        goal->setLOwnGoal(event.getLOwnGoal());
        goal->setNMinute(event.getNMinute());
        goal->setXFkMatch(event.getXMatch());
        goal->setXFkTeamScorer(event.getXTeamScorer());
        goal->setXFkTeamPlayerScorer(event.getXTeamPlayerScorer());

		m_matchesMap[xMatch]->push_back(goal);
	}
}

void CEventProcessorVisitor::endMatchEventVisitor(const CEndMatchEvent &event)
{
	int xMatch = event.getXMatch();
	if( m_matchesMap.find(xMatch)!=m_matchesMap.end() ){
		// if the match is registered
		std::vector<CPfGoals*>	*goalsList = m_matchesMap[xMatch];

        IPfGoalsDAO *goalsDAO = m_game->getIDAOFactory()->getIPfGoalsDAO();
        std::vector<CPfGoals*>::iterator itGoals;
        for( itGoals=goalsList->begin(); itGoals!=goalsList->end(); itGoals++ ){
            goalsDAO->insertReg(*itGoals);
        }

        IPfMatchesDAO *matchesDAO = m_game->getIDAOFactory()->getIPfMatchesDAO();
        CPfMatches *match = matchesDAO->findByXMatch(xMatch);
        match->setLPlayed(true);
        matchesDAO->updateReg(match);
        delete match;

        // Remove data of the match from the map
        for( itGoals=goalsList->begin(); itGoals!=goalsList->end(); itGoals++ ){
            delete (*itGoals);
        }
        delete goalsList;
        m_matchesMap.erase(xMatch);
	}
}
