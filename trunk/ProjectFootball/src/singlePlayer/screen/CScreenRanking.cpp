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

#include "CScreenRanking.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeams.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"
#include "../utils/CLog.h"


CScreenRanking::CScreenRanking(CSinglePlayerGame *game)
    :CScreen("ranking.layout")
{
    CLog::getInstance()->debug("CScreenRanking()");

    m_game = game;

    m_rankingList    = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/RankingList"));
    m_backButton     = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/BackButton"));
    m_gameMenuButton = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/GameMenuButton"));
    m_rankingButton      = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/RankingButton"));
    m_teamPlayersButton	 = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/TeamPlayersButton"));
    m_resultsButton	     = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/ResultsButton"));

    m_rankingList->setUserColumnDraggingEnabled(false);
    m_rankingList->setUserColumnSizingEnabled(false);
    m_rankingList->setUserSortControlEnabled(false);

    // i18n support
    m_backButton    ->setTooltipText((CEGUI::utf8*)gettext("Back"));
    m_gameMenuButton->setTooltipText((CEGUI::utf8*)gettext("Game Menu"));
    m_rankingButton     ->setText((CEGUI::utf8*)gettext("Ranking"));
    m_teamPlayersButton ->setText((CEGUI::utf8*)gettext("Team Players"));
    m_resultsButton     ->setText((CEGUI::utf8*)gettext("Results"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/RankingLabel"))->setText((CEGUI::utf8*)gettext("Ranking:"));

    // Event handle
    m_backButton    ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::backButtonClicked, this));
    m_gameMenuButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::gameMenuButtonClicked, this));
    m_rankingButton     ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::rankingButtonClicked, this));
    m_teamPlayersButton ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::teamPlayersButtonClicked, this));
    m_resultsButton     ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::resultsButtonClicked, this));

    m_rankingList->addColumn("",     0, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn((CEGUI::utf8*)gettext("Team"), 1, CEGUI::UDim(0.60,0));
    m_rankingList->addColumn("PT",   2, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("PM",   3, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("WM",   4, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("DM",   5, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("LM",   6, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("GF",   7, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("GA",   8, CEGUI::UDim(0.05,0));

}

CScreenRanking::~CScreenRanking()
{
    CLog::getInstance()->debug("~CScreenRanking()");
}

void CScreenRanking::enter()
{
	CScreen::enter();

    loadRanking();
}

void CScreenRanking::loadRanking()
{
    m_rankingList->resetList();
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    IDAOFactory                         *daoFactory		= m_game->getIDAOFactory();
    IPfRankingDAO                       *rankingDAO     = daoFactory->getIPfRankingDAO();
    std::vector<CPfRanking*>            *rankingList    = rankingDAO->findRanking();
    std::vector<CPfRanking*>::iterator  it;
    CEGUI::ListboxTextItem *item;
    char position[4];
    int cont = 1;

    // TODO Ranking for all competitions
    CPfTeams *playerTeam = daoFactory->getIPfTeamsDAO()->findByXTeam(m_game->getOptionManager()->getGamePlayerTeam());
    CPfRegisteredTeams *registeredTeam = daoFactory->getIPfRegisteredTeamsDAO()->findByXFkTeam(playerTeam->getXTeam());
    std::vector<CPfTeams*> *teams = daoFactory->getIPfTeamsDAO()->findTeamsByXCompetition(registeredTeam->getXFkCompetition());

    for( it=rankingList->begin(); it!=rankingList->end(); it++ ){
        CPfRanking *ranking = (*it);
        if(isInSameCompetition(teams, ranking->getSTeam())) {
            sprintf(position, "%d", cont);

            int row_idx = m_rankingList->addRow();

            item = new CEGUI::ListboxTextItem(position);
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 0, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getSTeam().c_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 1, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNPoints_str().c_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 2, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNPlayed_str().c_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 3, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNWins_str().c_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 4, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNDraws_str().c_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 5, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNLosses_str().c_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 6, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNGoalsFor_str().c_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 7, row_idx);

            item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNGoalsAgainst_str().c_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 8, row_idx);

            cont++;
        }
    }
    rankingDAO->freeVector(rankingList);
    daoFactory->getIPfTeamsDAO()->freeVector(teams);
    delete registeredTeam;
    delete playerTeam;

    m_rankingList->getHorzScrollbar()->setVisible(false);
}

bool CScreenRanking::isInSameCompetition(std::vector<CPfTeams*> *teams, std::string STeam)
{
    std::vector<CPfTeams*>::iterator it;
    bool finded = false;
    it=teams->begin();
    while(it!=teams->end() && !finded){
        if((*it)->getSTeam() == STeam) {
            finded = true;
        }
        it++;
    }
    return finded;
}

bool CScreenRanking::backButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->previousScreen();
	return true;
}

bool CScreenRanking::gameMenuButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->nextScreen(m_game->getGameScreen());
    return true;
}

bool CScreenRanking::rankingButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getRankingScreen());
	return true;
}

bool CScreenRanking::teamPlayersButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getTeamPlayersScreen());
	return true;
}

bool CScreenRanking::resultsButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getResultsScreen());
	return true;
}