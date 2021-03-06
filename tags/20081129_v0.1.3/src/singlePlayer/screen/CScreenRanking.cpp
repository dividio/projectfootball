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
#include "../utils/CLog.h"
#include "../db/dao/factory/IDAOFactory.h"


CScreenRanking::CScreenRanking(CSinglePlayerGame *game)
    :CScreen("ranking.layout")
{
    CLog::getInstance()->debug("CScreenRanking()");

    m_game = game;

    m_rankingList 	= static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/RankingList"));
    m_backButton	= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/BackButton"));

    m_rankingList->setUserColumnDraggingEnabled(false);
    m_rankingList->setUserColumnSizingEnabled(false);
    m_rankingList->setUserSortControlEnabled(false);

    // i18n support
    m_backButton->setText((CEGUI::utf8*)gettext("Back"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/RankingLabel"))->setText((CEGUI::utf8*)gettext("Ranking:"));

    // Event handle
    m_backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::backButtonClicked, this));

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
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("MultiListSelectionBrush");

    IDAOFactory                         *daoFactory		= m_game->getIDAOFactory();
    IPfRankingDAO                       *rankingDAO     = daoFactory->getIPfRankingDAO();
    std::vector<CPfRanking*>            *rankingList    = rankingDAO->findRanking();
    std::vector<CPfRanking*>::iterator  it;
    CEGUI::ListboxTextItem *item;
    char position[4];
    int cont = 1;

    // TODO Ranking for all competitions
    CPfTeams *playerTeam = daoFactory->getIPfTeamsDAO()->findPlayerTeam();
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

            item = new CEGUI::ListboxTextItem(ranking->getSTeam());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 1, row_idx);

            item = new CEGUI::ListboxTextItem(ranking->getNPoints_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 2, row_idx);

            item = new CEGUI::ListboxTextItem(ranking->getNPlayed_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 3, row_idx);

            item = new CEGUI::ListboxTextItem(ranking->getNWins_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 4, row_idx);

            item = new CEGUI::ListboxTextItem(ranking->getNDraws_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 5, row_idx);

            item = new CEGUI::ListboxTextItem(ranking->getNLosses_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 6, row_idx);

            item = new CEGUI::ListboxTextItem(ranking->getNGoalsFor_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 7, row_idx);

            item = new CEGUI::ListboxTextItem(ranking->getNGoalsAgainst_str());
            item->setSelectionBrushImage(sel_img);
            m_rankingList->setItem(item, 8, row_idx);

            cont++;
        }
    }
    rankingDAO->freeVector(rankingList);

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
