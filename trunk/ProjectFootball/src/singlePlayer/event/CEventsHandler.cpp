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

#include "CEventsHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../CSeasonGenerator.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "season/CEndSeasonEvent.h"
#include "match/CMatchEvent.h"
#include "match/CStartMatchEvent.h"
#include "match/CGoalMatchEvent.h"
#include "match/CEndMatchEvent.h"

#include "../../engine/CGameEngine.h"
#include "../../engine/event/IGameEvent.h"
#include "../../engine/event/CEventManager.h"
#include "../../engine/event/slot/CSlotConnection.h"
#include "../../engine/event/system/CEndDayEvent.h"
#include "../../engine/event/system/CTimeStartEvent.h"
#include "../../engine/event/system/CTimeStopEvent.h"
#include "../../engine/time/CTimeManager.h"

CEventsHandler::CEventsHandler(CSinglePlayerGame &game) :
	m_game(game),
	m_matchesMap(),
	m_slotsList()
{
	CEventManager *eventMngr = CGameEngine::getInstance()->getEventManager();

	m_slotsList.push_back(eventMngr->subscribeEvent(CEndDayEvent::type, &CEventsHandler::endDayEventHandler, this));
	m_slotsList.push_back(eventMngr->subscribeEvent(CTimeStartEvent::type, &CEventsHandler::timeStartEventHandler, this));
	m_slotsList.push_back(eventMngr->subscribeEvent(CTimeStopEvent::type, &CEventsHandler::timeStopEventHandler, this));
	m_slotsList.push_back(eventMngr->subscribeEvent(CEndSeasonEvent::type, &CEventsHandler::endSeasonEventHandler, this));
	m_slotsList.push_back(eventMngr->subscribeEvent(CMatchEvent::type, &CEventsHandler::matchEventHandler, this));
	m_slotsList.push_back(eventMngr->subscribeEvent(CStartMatchEvent::type, &CEventsHandler::startMatchEventHandler, this));
	m_slotsList.push_back(eventMngr->subscribeEvent(CGoalMatchEvent::type, &CEventsHandler::goalMatchEventHandler, this));
	m_slotsList.push_back(eventMngr->subscribeEvent(CEndMatchEvent::type, &CEventsHandler::endMatchEventHandler, this));
}

CEventsHandler::~CEventsHandler()
{
	CEventManager *eventMngr = CGameEngine::getInstance()->getEventManager();

	TSlotConnectionsList::iterator it;
	for( it=m_slotsList.begin(); it!=m_slotsList.end(); it++ ){
		eventMngr->disconnectSlot(*it);
	}

	TMatchesMap::iterator itMatches;
	for( itMatches=m_matchesMap.begin(); itMatches!=m_matchesMap.end(); itMatches++){
		TGoalsList *goalsVector	= itMatches->second;
		TGoalsList::iterator itGoals;
		for( itGoals=goalsVector->begin(); itGoals!=goalsVector->end(); itGoals++){
			delete (*itGoals);
		}
		delete goalsVector;
	}
	m_matchesMap.clear();
}

void CEventsHandler::matchEventHandler(const IGameEvent &event)
{
	const CMatchEvent &matchEvent = static_cast<const CMatchEvent&>(event);

	IPfMatchesDAO 	*matchesDAO 	= m_game.getIDAOFactory()->getIPfMatchesDAO();
	CPfMatches 		*match			= matchesDAO->findByXMatch(matchEvent.getXMatch());
	int				 xPlayerTeam	= m_game.getOptionManager()->getGamePlayerTeam();

	if( match->getXFkTeamAway()==xPlayerTeam || match->getXFkTeamHome()==xPlayerTeam ){
		m_game.setCurrentMatch(match);
		CGameEngine::getInstance()->getTimeManager()->stop();
		CGameEngine::getInstance()->getWindowManager()->nextScreen("Game");
		CGameEngine::getInstance()->getWindowManager()->clearHistory();
	}
	else{
		m_game.simulateMatch(*match);
	}
	delete match;
}

void CEventsHandler::startMatchEventHandler(const IGameEvent &event)
{
	const CStartMatchEvent &startMatchEvent = static_cast<const CStartMatchEvent&>(event);

	int xMatch = startMatchEvent.getXMatch();
	if( m_matchesMap.find(xMatch)==m_matchesMap.end() ){
		// if the match is not registered
		m_matchesMap[xMatch] = new TGoalsList();
	}
}

void CEventsHandler::goalMatchEventHandler(const IGameEvent &event)
{
	const CGoalMatchEvent &goalMatchEvent = static_cast<const CGoalMatchEvent&>(event);

	int xMatch = goalMatchEvent.getXMatch();
	if( m_matchesMap.find(xMatch)!=m_matchesMap.end() ){
		// if the match is registered
		CPfGoals *goal = new CPfGoals();
        goal->setLOwnGoal(goalMatchEvent.getLOwnGoal());
        goal->setNMinute(goalMatchEvent.getNMinute());
        goal->setXFkMatch(goalMatchEvent.getXMatch());
        goal->setXFkTeamScorer(goalMatchEvent.getXTeamScorer());
        goal->setXFkTeamPlayerScorer(goalMatchEvent.getXTeamPlayerScorer());

		m_matchesMap[xMatch]->push_back(goal);
	}
}

void CEventsHandler::endMatchEventHandler(const IGameEvent &event)
{
	const CEndMatchEvent &endMatchEvent = static_cast<const CEndMatchEvent&>(event);

	int xMatch = endMatchEvent.getXMatch();
	if( m_matchesMap.find(xMatch)!=m_matchesMap.end() ){
		// if the match is registered
        IPfGoalsDAO 	          *goalsDAO	    = m_game.getIDAOFactory()->getIPfGoalsDAO();
        IPfMatchesDAO	          *matchesDAO   = m_game.getIDAOFactory()->getIPfMatchesDAO();
        IPfTeamPlayersDAO         *playersDAO   = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();

        CPfMatches *match = matchesDAO->findByXMatch(xMatch);
        int homeTeam = match->getXFkTeamHome();
        int awayTeam = match->getXFkTeamAway();
        std::string timestamp = match->getDMatch().getTimestamp();
        std::vector<CPfTeamPlayers*> *homeTeamPlayers = playersDAO->findLineUpByXFkTeam(homeTeam, timestamp);
        std::vector<CPfTeamPlayers*> *awayTeamPlayers = playersDAO->findLineUpByXFkTeam(awayTeam, timestamp);
        std::vector<CPfTeamPlayers*> *homeAlternatePlayers = playersDAO->findAlternateByXFkTeam(homeTeam, timestamp);
		std::vector<CPfTeamPlayers*> *awayAlternatePlayers = playersDAO->findAlternateByXFkTeam(awayTeam, timestamp);
        std::vector<CPfTeamPlayers*> *homeNotLineUpPlayers = playersDAO->findNotLineUpByXFkTeam(homeTeam, timestamp);
		std::vector<CPfTeamPlayers*> *awayNotLineUpPlayers = playersDAO->findNotLineUpByXFkTeam(awayTeam, timestamp);

        TGoalsList	*goalsList = m_matchesMap[xMatch];
        TGoalsList::iterator itGoals;
        int homeGoals = 0;
        int awayGoals = 0;
        for( itGoals=goalsList->begin(); itGoals!=goalsList->end(); itGoals++ ){
            CPfGoals *goal = *itGoals;
            if(goal->getXFkTeamScorer() == homeTeam) {
                homeGoals++;
            } else {
                awayGoals++;
            }
            goalsDAO->insertReg(goal);
            delete (goal);
        }
        delete goalsList;

        std::ostringstream message;
        message << gettext("Simulating match: ") << homeGoals << " - " << awayGoals;

        CGameEngine::getInstance()->getWindowManager()->loadingUpdate(message.str(), false);

        match->setLPlayed(true);
        matchesDAO->updateReg(match);
        delete match;

        updateLineUpPlayersStats(homeTeamPlayers, homeGoals, awayGoals);
        updateLineUpPlayersStats(homeAlternatePlayers, homeGoals, awayGoals);
        updateNotLineUpPlayersStats(homeNotLineUpPlayers, homeGoals, awayGoals);

        updateLineUpPlayersStats(awayTeamPlayers, awayGoals, homeGoals);
        updateLineUpPlayersStats(awayAlternatePlayers, awayGoals, homeGoals);
        updateNotLineUpPlayersStats(awayNotLineUpPlayers, awayGoals, homeGoals);

        playersDAO->freeVector(homeTeamPlayers);
        playersDAO->freeVector(awayTeamPlayers);
        playersDAO->freeVector(homeAlternatePlayers);
		playersDAO->freeVector(awayAlternatePlayers);
		playersDAO->freeVector(homeNotLineUpPlayers);
		playersDAO->freeVector(awayNotLineUpPlayers);

        // Remove data of the match from the map
        m_matchesMap.erase(xMatch);
	}
}

void CEventsHandler::endSeasonEventHandler(const IGameEvent &event)
{
	CSeasonGenerator::generateSeason(m_game);
}

void CEventsHandler::endDayEventHandler(const IGameEvent &event)
{
	switch( m_game.getGameState() ){
	case CSinglePlayerGame::SimulatingUntilTheNextDay:
		CGameEngine::getInstance()->getTimeManager()->stop();
		break;
	case CSinglePlayerGame::PlayingMatch:
		CGameEngine::getInstance()->getTimeManager()->stop();
        CGameEngine::getInstance()->getWindowManager()->nextScreen("MatchResult");
		break;
	}
}

void CEventsHandler::timeStartEventHandler(const IGameEvent &event)
{
	m_game.getIDAOFactory()->beginTransaction();
}

void CEventsHandler::timeStopEventHandler(const IGameEvent &event)
{
	m_game.getIDAOFactory()->commit();
	m_game.setGameState(CSinglePlayerGame::Stopped);
}

void CEventsHandler::updateLineUpPlayersStats(std::vector<CPfTeamPlayers*> *players, int teamGoals, int opponentGoals) {
    IPfTeamPlayersDAO *playersDAO   = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();

    std::vector<CPfTeamPlayers*>::iterator itPlayers;
    // Update team players attributes
    for( itPlayers=players->begin(); itPlayers!=players->end(); itPlayers++ ){
        CPfTeamPlayers *player = *itPlayers;
        int fortitude = player->getNFortitude();
        int moral = player->getNMoral();
        int currentMoral = moral;

        if(teamGoals > opponentGoals && fortitude > 30) {
                    moral++;
        } else if(teamGoals < opponentGoals && fortitude < 70) {
                    moral--;
        }

        if(player==players->front()) {
        	// if goalie
			if(opponentGoals == 0) {
				moral++;
			} else if(opponentGoals >= 5 && fortitude < 80) {
				moral--;
			}
        }

        // Apply max and min values for moral
        if(moral > 99) {
            moral = 99;
        } else if(moral < 30) {
            moral = 30;
        }

        // update if moral changes
        if(moral != currentMoral) {
            player->setNMoral(moral);
            playersDAO->updateReg(player);
        }
    }
}

void CEventsHandler::updateNotLineUpPlayersStats(std::vector<CPfTeamPlayers*> *players, int teamGoals, int opponentGoals) {
    IPfTeamPlayersDAO *playersDAO   = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();

    std::vector<CPfTeamPlayers*>::iterator itPlayers;
    // Update not line up players attributes
    for( itPlayers=players->begin(); itPlayers!=players->end(); itPlayers++ ){
        CPfTeamPlayers *player = *itPlayers;
        int fortitude = player->getNFortitude();
        int moral = player->getNMoral();
        int currentMoral = moral;

        if(teamGoals > opponentGoals && fortitude > 30) {
                    moral++;
        } else if(teamGoals < opponentGoals && fortitude < 70) {
                    moral--;
        }

        if(fortitude < 50) {
			// not line up and not alternate
			moral--;
		}

        // Apply max and min values for moral
        if(moral > 99) {
            moral = 99;
        } else if(moral < 30) {
            moral = 30;
        }

        // update if moral changes
        if(moral != currentMoral) {
            player->setNMoral(moral);
            playersDAO->updateReg(player);
        }
    }
}
