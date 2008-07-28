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

#include <libintl.h>

#include "CStateRanking.h"
#include "../engine/CGameEngine.h"
#include "../utils/CLog.h"

CStateRanking::CStateRanking()
    :CState()
{
    CLog::getInstance()->debug("CStateRanking()");

    CEGUI::WindowManager *ceguiWM = &(CEGUI::WindowManager::getSingleton());
    m_sheet = ceguiWM->loadWindowLayout((CEGUI::utf8*)"ranking.layout");

    m_rankingList = static_cast<CEGUI::MultiColumnList*>(ceguiWM->getWindow((CEGUI::utf8*)"Ranking/RankingList"));

    m_rankingList->setUserColumnDraggingEnabled(false);
    m_rankingList->setUserColumnSizingEnabled(false);
    m_rankingList->setUserSortControlEnabled(false);

    // i18n support
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Ranking/BackButton"))->setText((CEGUI::utf8*)gettext("Back"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Ranking/RankingLabel"))->setText((CEGUI::utf8*)gettext("Ranking:"));

    m_rankingList->addColumn((CEGUI::utf8*)gettext("Team"), 0, CEGUI::UDim(0.65,0));
    m_rankingList->addColumn("PT",   1, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("PM",   2, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("WM",   3, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("DM",   4, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("LM",   5, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("GF",   6, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("GA",   7, CEGUI::UDim(0.05,0));

}

CStateRanking* CStateRanking::getInstance()
{
    static CStateRanking instance;
    return &instance;
}

CStateRanking::~CStateRanking()
{
    CLog::getInstance()->debug("~CStateRanking()");
}

void CStateRanking::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    loadRanking();
}

void CStateRanking::forcedLeave()
{

}

bool CStateRanking::leave()
{
    return true;
}

void CStateRanking::update()
{
}

void CStateRanking::loadRanking()
{
    m_rankingList->resetList();

    IPfRankingDAO                       *rankingDAO     = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfRankingDAO();
    std::vector<CPfRanking*>            *rankingList    = rankingDAO->findRanking();
    std::vector<CPfRanking*>::iterator  it;

    for( it=rankingList->begin(); it!=rankingList->end(); it++ ){
        CPfRanking *ranking = (*it);

        int row_idx = m_rankingList->addRow();
        m_rankingList->setItem(new CEGUI::ListboxTextItem(ranking->getSTeam()),             0, row_idx);
        m_rankingList->setItem(new CEGUI::ListboxTextItem(ranking->getNPoints_str()),       1, row_idx);
        m_rankingList->setItem(new CEGUI::ListboxTextItem(ranking->getNPlayed_str()),       2, row_idx);
        m_rankingList->setItem(new CEGUI::ListboxTextItem(ranking->getNWins_str()),         3, row_idx);
        m_rankingList->setItem(new CEGUI::ListboxTextItem(ranking->getNDraws_str()),        4, row_idx);
        m_rankingList->setItem(new CEGUI::ListboxTextItem(ranking->getNLosses_str()),       5, row_idx);
        m_rankingList->setItem(new CEGUI::ListboxTextItem(ranking->getNGoalsFor_str()),     6, row_idx);
        m_rankingList->setItem(new CEGUI::ListboxTextItem(ranking->getNGoalsAgainst_str()), 7, row_idx);
    }
    rankingDAO->freeVector(rankingList);

    m_rankingList->getHorzScrollbar()->setVisible(false);
}
