/******************************************************************************
* Copyright (C) 2008 - Ikaro Games   www.ikarogames.com                       *
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

#include "CMatchResultWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../db/bean/CPfMatches.h"
#include "../../engine/event/CEventsQueue.h"
#include "../event/match/CEndMatchEvent.h"
#include "../event/match/CGoalMatchEvent.h"
#include "../event/match/CStartMatchEvent.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"


CMatchResultWindowHandler::CMatchResultWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("matchResult.layout"),
	m_game(game),
	m_initiated(false)
{
    LOG_DEBUG("CMatchResultWindowHandler()");
}

CMatchResultWindowHandler::~CMatchResultWindowHandler()
{
    LOG_DEBUG("~CMatchResultWindowHandler()");

    if( m_initiated ){
		m_homeEventsList->removeColumnWithID(0);
		m_homeEventsList->removeColumnWithID(1);
		m_awayEventsList->removeColumnWithID(0);
		m_awayEventsList->removeColumnWithID(1);
    }
}

void CMatchResultWindowHandler::enter()
{
	loadMatchInfo();
}

void CMatchResultWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

    m_competitionName		= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/Competition"));
    m_competitionPhaseName	= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/CompetitionPhase"));
    m_homeName				= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/HomeName"));
    m_awayName				= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/AwayName"));
    m_homeScore            	= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/HomeScore"));
    m_awayScore            	= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/AwayScore"));
    m_stadiumName           = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/StadiumName"));
    m_homeEventsList       	= static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/HomeTeamEventsList"));
    m_awayEventsList       	= static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/AwayTeamEventsList"));
    m_homeLogo             	= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/HomeTeamLogo"));
    m_awayLogo             	= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/AwayTeamLogo"));
    m_continueButton		= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/ContinueButton"));

    // Event handle
    registerEventConnection(m_continueButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMatchResultWindowHandler::continueButtonClicked, this)));

    // i18n support
    m_continueButton->setText((CEGUI::utf8*)gettext("Continue"));
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchResult/StadiumLabel"))->setText((CEGUI::utf8*)gettext("Stadium:"));

    m_homeEventsList->addColumn((CEGUI::utf8*)gettext("min"), 0, CEGUI::UDim(0.2,0));
    m_homeEventsList->addColumn((CEGUI::utf8*)gettext("Event"), 1, CEGUI::UDim(0.8,0));
    m_awayEventsList->addColumn((CEGUI::utf8*)gettext("min"), 0, CEGUI::UDim(0.2,0));
    m_awayEventsList->addColumn((CEGUI::utf8*)gettext("Event"), 1, CEGUI::UDim(0.8,0));

    m_homeEventsList->setUserColumnDraggingEnabled(false);
    m_homeEventsList->setUserColumnSizingEnabled(false);
    m_homeEventsList->setUserSortControlEnabled(true);
    m_awayEventsList->setUserColumnDraggingEnabled(false);
    m_awayEventsList->setUserColumnSizingEnabled(false);
    m_awayEventsList->setUserSortControlEnabled(true);
    m_homeEventsList->getHorzScrollbar()->setVisible(false);
    m_awayEventsList->getHorzScrollbar()->setVisible(false);

    m_initiated = true;
}

void CMatchResultWindowHandler::leave()
{
    m_homeEventsList->resetList();
    m_awayEventsList->resetList();
}

void CMatchResultWindowHandler::loadMatchInfo()
{
    IDAOFactory				*daoFactory				= m_game.getIDAOFactory();
    IPfGoalsDAO				*goalsDAO				= daoFactory->getIPfGoalsDAO();
    IPfTeamPlayersDAO		*playersDAO      		= daoFactory->getIPfTeamPlayersDAO();
    IPfCompetitionsDAO		*competitionsDAO		= daoFactory->getIPfCompetitionsDAO();
    IPfCompetitionPhasesDAO	*competitionPhasesDAO	= daoFactory->getIPfCompetitionPhasesDAO();
    IPfPhaseRoundsDAO		*phaseRoundsDAO			= daoFactory->getIPfPhaseRoundsDAO();
    IPfTeamsDAO				*teamsDAO				= daoFactory->getIPfTeamsDAO();
    IPfStadiumsDAO          *stadiumsDAO            = daoFactory->getIPfStadiumsDAO();

    const CPfMatches		*match				= m_game.getCurrentMatch();
    CPfTeams				*homeTeam			= teamsDAO->findByXTeam(match->getXFkTeamHome());
    CPfTeams				*awayTeam			= teamsDAO->findByXTeam(match->getXFkTeamAway());
    CPfStadiums             *stadium            = stadiumsDAO->findByXStadium(homeTeam->getXFkStadium_str());
    CPfPhaseRounds			*phaseRound			= phaseRoundsDAO->findByXPhaseRound(match->getXFkPhaseRound());
    CPfCompetitionPhases	*competitionPhase	= competitionPhasesDAO->findByXCompetitionPhase(phaseRound->getXFkCompetitionPhase());
    CPfCompetitions			*competition		= competitionsDAO->findByXCompetition(competitionPhase->getXFkCompetition());
    std::vector<CPfGoals*>	*homeGoalsList		= goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), homeTeam->getXTeam());
    std::vector<CPfGoals*>	*awayGoalsList		= goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), awayTeam->getXTeam());

    std::ostringstream nHomeGoals;
    nHomeGoals << homeGoalsList->size();
    std::ostringstream nAwayGoals;
    nAwayGoals << awayGoalsList->size();

    std::string homeName = homeTeam->getSTeam();
    std::string awayName = awayTeam->getSTeam();
    m_competitionName     ->setText((CEGUI::utf8*)competition->getSCompetition().c_str());
    m_competitionPhaseName->setText((CEGUI::utf8*)phaseRound->getSPhaseRound().c_str());
    m_homeName            ->setText((CEGUI::utf8*)homeName.c_str());
    m_awayName            ->setText((CEGUI::utf8*)awayName.c_str());
    m_homeScore           ->setText((CEGUI::utf8*)nHomeGoals.str().c_str());
    m_awayScore           ->setText((CEGUI::utf8*)nAwayGoals.str().c_str());
    m_stadiumName         ->setText((CEGUI::utf8*)stadium->getSName().c_str());

    //Loading Home Shield
    m_homeLogo->setProperty("Image", "set:"+ homeTeam->getSLogo() +" image:"+homeTeam->getSLogo()+"_b");

    //Loading Away Shield
    m_awayLogo->setProperty("Image", "set:"+ awayTeam->getSLogo() +" image:"+awayTeam->getSLogo()+"_b");

    std::vector<CPfGoals*>::iterator it;
    CEGUI::ListboxTextItem *item;
    CPfTeamPlayers *player;
    std::ostringstream event;

    for( it=homeGoalsList->begin(); it!=homeGoalsList->end(); it++ ){
        CPfGoals *goal = (*it);

        int row_idx = m_homeEventsList->addRow();

        item = new CEGUI::ListboxTextItem(goal->getNMinute_str());
        m_homeEventsList->setItem(item, 0, row_idx);

        player = playersDAO->findByXTeamPlayer(goal->getXFkTeamPlayerScorer());
        event << gettext("Goal by ") << player->getSName().c_str();
        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)event.str().c_str());
        m_homeEventsList->setItem(item, 1, row_idx);
        delete player;
        event.str("");
    }
    goalsDAO->freeVector(homeGoalsList);

    for( it=awayGoalsList->begin(); it!=awayGoalsList->end(); it++ ){
        CPfGoals *goal = (*it);

        int row_idx = m_awayEventsList->addRow();

        item = new CEGUI::ListboxTextItem(goal->getNMinute_str());
        m_awayEventsList->setItem(item, 0, row_idx);

        player = playersDAO->findByXTeamPlayer(goal->getXFkTeamPlayerScorer());
        event << gettext("Goal by ") << player->getSName().c_str();
        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)event.str().c_str());
        m_awayEventsList->setItem(item, 1, row_idx);
        delete player;
        event.str("");
    }
    goalsDAO->freeVector(awayGoalsList);

    m_homeEventsList->setSortColumn(0);
    m_awayEventsList->setSortColumn(0);
    m_homeEventsList->setSortDirection(CEGUI::ListHeaderSegment::Descending);
    m_awayEventsList->setSortDirection(CEGUI::ListHeaderSegment::Descending);
    m_homeEventsList->handleUpdatedItemData();
    m_awayEventsList->handleUpdatedItemData();
    m_homeEventsList->getHorzScrollbar()->setVisible(false);
    m_awayEventsList->getHorzScrollbar()->setVisible(false);

    delete competition;
    delete competitionPhase;
    delete phaseRound;
    delete stadium;
    delete awayTeam;
    delete homeTeam;
}

bool CMatchResultWindowHandler::continueButtonClicked(const CEGUI::EventArgs& e)
{
	m_game.setCurrentMatch(NULL);
	m_game.setGameState(CSinglePlayerGame::SimulatingUntilTheNextEvent);
	CGameEngine::getInstance()->getTimeManager()->start();

    return true;
}
