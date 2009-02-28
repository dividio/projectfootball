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

#include "CScreenMatchResult.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../utils/CLog.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../db/bean/CPfMatches.h"
#include "../event/CEventsQueue.h"
#include "../event/CEventConsumer.h"
#include "../event/match/CEndMatchEvent.h"
#include "../event/match/CGoalMatchEvent.h"
#include "../event/match/CStartMatchEvent.h"
#include "../option/CSinglePlayerOptionManager.h"


CScreenMatchResult::CScreenMatchResult(CSinglePlayerGame *game)
 :CScreen("matchResult.layout")
{
    CLog::getInstance()->debug("CScreenMatchResult()");

    m_game			= game;
    m_loadMatchInfo = true;

    m_competitionName		= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/Competition"));
    m_competitionPhaseName	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/CompetitionPhase"));
    m_homeName				= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/HomeName"));
    m_awayName				= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/AwayName"));
    m_homeScore            	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/HomeScore"));
    m_awayScore            	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/AwayScore"));
    m_homeEventsList       	= static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/HomeTeamEventsList"));
    m_awayEventsList       	= static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/AwayTeamEventsList"));
    m_homeLogo             	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/HomeTeamLogo"));
    m_awayLogo             	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/AwayTeamLogo"));
    m_continueButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MatchResult/ContinueButton"));

    // Event handle
    m_continueButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMatchResult::continueButtonClicked, this));

    // i18n support
    m_continueButton->setText((CEGUI::utf8*)gettext("Continue"));

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
}

CScreenMatchResult::~CScreenMatchResult()
{
    CLog::getInstance()->debug("~CScreenMatchResult()");
}

void CScreenMatchResult::enter()
{
    CScreen::enter();
}

void CScreenMatchResult::leave()
{
    m_homeEventsList->resetList();
    m_awayEventsList->resetList();

    m_loadMatchInfo = true;
}

void CScreenMatchResult::update()
{
	CScreen::update();

	if( m_loadMatchInfo ){
		m_game->getEventConsumer()->consumeCurrentDayEvents();
		loadMatchInfo();

		m_loadMatchInfo = false;
	}
}

void CScreenMatchResult::loadMatchInfo()
{
    IDAOFactory				*daoFactory				= m_game->getIDAOFactory();
    IPfMatchesDAO			*matchesDAO				= daoFactory->getIPfMatchesDAO();
    IPfGoalsDAO				*goalsDAO				= daoFactory->getIPfGoalsDAO();
    IPfTeamPlayersDAO		*playersDAO      		= daoFactory->getIPfTeamPlayersDAO();
    IPfCompetitionsDAO		*competitionsDAO		= daoFactory->getIPfCompetitionsDAO();
    IPfCompetitionPhasesDAO	*competitionPhasesDAO	= daoFactory->getIPfCompetitionPhasesDAO();
    IPfTeamsDAO				*teamsDAO				= daoFactory->getIPfTeamsDAO();

    CPfMatches				*match				= matchesDAO->findLastTeamMatch(m_game->getOptionManager()->getGamePlayerTeam());
    CPfTeams				*homeTeam			= teamsDAO->findByXTeam(match->getXFkTeamHome());
    CPfTeams				*awayTeam			= teamsDAO->findByXTeam(match->getXFkTeamAway());
    CPfCompetitionPhases	*competitionPhase	= competitionPhasesDAO->findByXCompetitionPhase(match->getXFkCompetitionPhase());
    CPfCompetitions			*competition		= competitionsDAO->findByXCompetition(competitionPhase->getXFkCompetition());
    std::vector<CPfGoals*>	*homeGoalsList		= goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), homeTeam->getXTeam());
    std::vector<CPfGoals*>	*awayGoalsList		= goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), awayTeam->getXTeam());

    std::ostringstream nHomeGoals;
    nHomeGoals << homeGoalsList->size();
    std::ostringstream nAwayGoals;
    nAwayGoals << awayGoalsList->size();

    std::string homeName = homeTeam->getSTeam();
    std::string awayName = awayTeam->getSTeam();
    m_competitionName     ->setProperty("Text", (CEGUI::utf8*)competition->getSCompetition().c_str());
    m_competitionPhaseName->setProperty("Text", (CEGUI::utf8*)competitionPhase->getSCompetitionPhase().c_str());
    m_homeName            ->setProperty("Text", (CEGUI::utf8*)homeName.c_str());
    m_awayName            ->setProperty("Text", (CEGUI::utf8*)awayName.c_str());
    m_homeScore           ->setProperty("Text", (CEGUI::utf8*)nHomeGoals.str().c_str());
    m_awayScore           ->setProperty("Text", (CEGUI::utf8*)nAwayGoals.str().c_str());

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
    delete awayTeam;
    delete homeTeam;
    delete match;
}

bool CScreenMatchResult::continueButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->nextScreen(m_game->getGameScreen());
    return true;
}
