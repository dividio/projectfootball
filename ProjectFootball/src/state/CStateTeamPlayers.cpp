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

#include "CStateTeamPlayers.h"
#include "../engine/CGameEngine.h"
#include "../utils/CLog.h"

CStateTeamPlayers::CStateTeamPlayers()
    :CState()
{
    CLog::getInstance()->debug("CStateTeamPlayers()");
    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"teamPlayers.layout");

    m_lineUpTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"TeamPlayers/LineUpTeamPlayersList"));
    m_lineUpTeamPlayersList->addColumn("Name (Line Up)", 0, CEGUI::UDim(1.0,0));
    m_lineUpTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_lineUpTeamPlayersList->setUserColumnSizingEnabled(false);
    m_lineUpTeamPlayersList->setUserSortControlEnabled(false);
    m_lineUpTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
    m_lineUpTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CStateTeamPlayers::handleLineUpSelectChanged, this));

    m_alternateTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"TeamPlayers/AlternateTeamPlayersList"));
    m_alternateTeamPlayersList->addColumn("Name (Alternate)", 0, CEGUI::UDim(1.0,0));
    m_alternateTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_alternateTeamPlayersList->setUserColumnSizingEnabled(false);
    m_alternateTeamPlayersList->setUserSortControlEnabled(false);
    m_alternateTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
    m_alternateTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CStateTeamPlayers::handleAlternateSelectChanged, this));

    m_notLineUpTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"TeamPlayers/NotLineUpTeamPlayersList"));
    m_notLineUpTeamPlayersList->addColumn("Name (Not Line Up)", 0, CEGUI::UDim(1.0,0));
    m_notLineUpTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_notLineUpTeamPlayersList->setUserColumnSizingEnabled(false);
    m_notLineUpTeamPlayersList->setUserSortControlEnabled(false);
    m_notLineUpTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
    m_notLineUpTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CStateTeamPlayers::handleNotLineUpSelectChanged, this));
}

CStateTeamPlayers* CStateTeamPlayers::getInstance()
{
    static CStateTeamPlayers instance;
    return &instance;
}

CStateTeamPlayers::~CStateTeamPlayers()
{
    CLog::getInstance()->debug("~CStateTeamPlayers()");
}

void CStateTeamPlayers::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    loadTeamPlayersList();
}

void CStateTeamPlayers::forcedLeave()
{
    saveTeamPlayersList();
}

bool CStateTeamPlayers::leave()
{
    saveTeamPlayersList();
    return true;
}

void CStateTeamPlayers::update()
{
}

void CStateTeamPlayers::teamPlayerUp()
{
    if( m_lineUpTeamPlayersList->getFirstSelectedItem()!=NULL ){
        CEGUI::ListboxItem  *item   = m_lineUpTeamPlayersList->getFirstSelectedItem();
        int                 row_idx = m_lineUpTeamPlayersList->getItemRowIndex(item);

        if( row_idx>0 ){
            item->setAutoDeleted(false);
            m_lineUpTeamPlayersList->removeRow(row_idx);
            item->setAutoDeleted(true);
            m_lineUpTeamPlayersList->insertRow(item, 0, (row_idx-1));

            m_lineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_lineUpTeamPlayersList->getVertScrollbar()->setVisible(false);
        }
    }else if( m_alternateTeamPlayersList->getFirstSelectedItem()!=NULL ){
        CEGUI::ListboxItem  *item   = m_alternateTeamPlayersList->getFirstSelectedItem();
        int                 row_idx = m_alternateTeamPlayersList->getItemRowIndex(item);

        if( row_idx>0 ){
            item->setAutoDeleted(false);
            m_alternateTeamPlayersList->removeRow(row_idx);
            item->setAutoDeleted(true);
            m_alternateTeamPlayersList->insertRow(item, 0, (row_idx-1));

            m_alternateTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_alternateTeamPlayersList->getVertScrollbar()->setVisible(false);
        }else if( row_idx==0 ){
            item->setAutoDeleted(false);
            m_alternateTeamPlayersList->removeRow(0);
            item->setAutoDeleted(true);
            m_lineUpTeamPlayersList->insertRow(item, 0, m_lineUpTeamPlayersList->getRowCount());

            if( m_lineUpTeamPlayersList->getRowCount()==12 ){
                item = m_lineUpTeamPlayersList->getItemAtGridReference(CEGUI::MCLGridRef(10, 0));
                item->setAutoDeleted(false);
                m_lineUpTeamPlayersList->removeRow(10);
                item->setAutoDeleted(true);
                m_alternateTeamPlayersList->insertRow(item, 0, 0);
            }

            m_lineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_lineUpTeamPlayersList->getVertScrollbar()->setVisible(false);
            m_alternateTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_alternateTeamPlayersList->getVertScrollbar()->setVisible(false);
        }
    }else if( m_notLineUpTeamPlayersList->getFirstSelectedItem()!=NULL ){
        CEGUI::ListboxItem  *item   = m_notLineUpTeamPlayersList->getFirstSelectedItem();
        int                 row_idx = m_notLineUpTeamPlayersList->getItemRowIndex(item);

        if( row_idx>0 ){
            item->setAutoDeleted(false);
            m_notLineUpTeamPlayersList->removeRow(row_idx);
            item->setAutoDeleted(true);
            m_notLineUpTeamPlayersList->insertRow(item, 0, (row_idx-1));

            m_notLineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
        }else if( row_idx==0 ){
            item->setAutoDeleted(false);
            m_notLineUpTeamPlayersList->removeRow(0);
            item->setAutoDeleted(true);
            m_alternateTeamPlayersList->insertRow(item, 0, m_lineUpTeamPlayersList->getRowCount());

            if( m_alternateTeamPlayersList->getRowCount()==7 ){
                item = m_alternateTeamPlayersList->getItemAtGridReference(CEGUI::MCLGridRef(5, 0));
                item->setAutoDeleted(false);
                m_alternateTeamPlayersList->removeRow(5);
                item->setAutoDeleted(true);
                m_notLineUpTeamPlayersList->insertRow(item, 0, 0);
            }

            m_alternateTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_alternateTeamPlayersList->getVertScrollbar()->setVisible(false);
            m_notLineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
        }
    }
}

void CStateTeamPlayers::teamPlayerDown()
{
    if( m_lineUpTeamPlayersList->getFirstSelectedItem()!=NULL ){
        CEGUI::ListboxItem  *item   = m_lineUpTeamPlayersList->getFirstSelectedItem();
        int                 row_idx = m_lineUpTeamPlayersList->getItemRowIndex(item);

        if( row_idx<(m_lineUpTeamPlayersList->getRowCount()-1) ){
            item->setAutoDeleted(false);
            m_lineUpTeamPlayersList->removeRow(row_idx);
            item->setAutoDeleted(true);
            m_lineUpTeamPlayersList->insertRow(item, 0, (row_idx+1));

            m_lineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_lineUpTeamPlayersList->getVertScrollbar()->setVisible(false);
        }else if( row_idx==(m_lineUpTeamPlayersList->getRowCount()-1) ){
            item->setAutoDeleted(false);
            m_lineUpTeamPlayersList->removeRow(row_idx);
            item->setAutoDeleted(true);
            m_alternateTeamPlayersList->insertRow(item, 0, 0);

            if( m_alternateTeamPlayersList->getRowCount()==7 ){
                item = m_alternateTeamPlayersList->getItemAtGridReference(CEGUI::MCLGridRef(1,0));
                item->setAutoDeleted(false);
                m_alternateTeamPlayersList->removeRow(1);
                item->setAutoDeleted(true);
                m_lineUpTeamPlayersList->insertRow(item, 0, 10);
            }

            m_lineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_lineUpTeamPlayersList->getVertScrollbar()->setVisible(false);
            m_alternateTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_alternateTeamPlayersList->getVertScrollbar()->setVisible(false);
        }
    }else if( m_alternateTeamPlayersList->getFirstSelectedItem()!=NULL ){
        CEGUI::ListboxItem  *item   = m_alternateTeamPlayersList->getFirstSelectedItem();
        int                 row_idx = m_alternateTeamPlayersList->getItemRowIndex(item);

        if( row_idx<(m_alternateTeamPlayersList->getRowCount()-1) ){
            item->setAutoDeleted(false);
            m_alternateTeamPlayersList->removeRow(row_idx);
            item->setAutoDeleted(true);
            m_alternateTeamPlayersList->insertRow(item, 0, (row_idx+1));

            m_alternateTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_alternateTeamPlayersList->getVertScrollbar()->setVisible(false);
        }else if( row_idx==(m_alternateTeamPlayersList->getRowCount()-1) ){
            item->setAutoDeleted(false);
            m_alternateTeamPlayersList->removeRow(row_idx);
            item->setAutoDeleted(true);
            m_notLineUpTeamPlayersList->insertRow(item, 0, 0);

            m_alternateTeamPlayersList->getHorzScrollbar()->setVisible(false);
            m_alternateTeamPlayersList->getVertScrollbar()->setVisible(false);
            m_notLineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
        }
    }else if( m_notLineUpTeamPlayersList->getFirstSelectedItem()!=NULL ){
        CEGUI::ListboxItem  *item   = m_notLineUpTeamPlayersList->getFirstSelectedItem();
        int                 row_idx = m_notLineUpTeamPlayersList->getItemRowIndex(item);

        if( row_idx<(m_notLineUpTeamPlayersList->getRowCount()-1) ){
            item->setAutoDeleted(false);
            m_notLineUpTeamPlayersList->removeRow(row_idx);
            item->setAutoDeleted(true);
            m_notLineUpTeamPlayersList->insertRow(item, 0, (row_idx+1));

            m_notLineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
        }
    }
}

void CStateTeamPlayers::loadTeamPlayersList()
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("MultiListSelectionBrush");

    m_lineUpTeamPlayersList->resetList();
    m_alternateTeamPlayersList->resetList();
    m_notLineUpTeamPlayersList->resetList();

    CPfTeams                        *team                       = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayersDAO               *teamPlayersDAO             = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamPlayersDAO();
    std::vector<CPfTeamPlayers*>    *lineUpTeamPlayersList      = teamPlayersDAO->findLineUpByXFkTeam(team->getXTeam());
    std::vector<CPfTeamPlayers*>    *alternateTeamPlayersList   = teamPlayersDAO->findAlternateByXFkTeam(team->getXTeam());
    std::vector<CPfTeamPlayers*>    *notLineUpTeamPlayersList   = teamPlayersDAO->findNotLineUpByXFkTeam(team->getXTeam());

    std::vector<CPfTeamPlayers*>::iterator it;
    for( it=lineUpTeamPlayersList->begin(); it!=lineUpTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);

        int row_idx = m_lineUpTeamPlayersList->addRow();
        CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(teamPlayer->getSName(), teamPlayer->getXTeamPlayer());
        item->setSelectionBrushImage(sel_img);
        m_lineUpTeamPlayersList->setItem(item, 0, row_idx);
    }
    for( it=alternateTeamPlayersList->begin(); it!=alternateTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);

        int row_idx = m_alternateTeamPlayersList->addRow();
        CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(teamPlayer->getSName(), teamPlayer->getXTeamPlayer());
        item->setSelectionBrushImage(sel_img);
        m_alternateTeamPlayersList->setItem(item, 0, row_idx);
    }
    for( it=notLineUpTeamPlayersList->begin(); it!=notLineUpTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);

        int row_idx = m_notLineUpTeamPlayersList->addRow();
        CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(teamPlayer->getSName(), teamPlayer->getXTeamPlayer());
        item->setSelectionBrushImage(sel_img);
        m_notLineUpTeamPlayersList->setItem(item, 0, row_idx);
    }

    teamPlayersDAO->freeVector(lineUpTeamPlayersList);
    teamPlayersDAO->freeVector(alternateTeamPlayersList);
    teamPlayersDAO->freeVector(notLineUpTeamPlayersList);
    delete team;

    m_lineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);
    m_alternateTeamPlayersList->getHorzScrollbar()->setVisible(false);
    m_notLineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);

    m_lineUpTeamPlayersList->getVertScrollbar()->setVisible(false);
    m_alternateTeamPlayersList->getVertScrollbar()->setVisible(false);
}

void CStateTeamPlayers::saveTeamPlayersList()
{
    CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->beginTransaction();
    CPfTeams                    *team                   = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayerContractsDAO   *teamPlayerContractsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamPlayerContractsDAO();

    int i;
    int lineUpOrder = 1;

    for( i=0; i<m_lineUpTeamPlayersList->getRowCount(); i++ ){

        CEGUI::ListboxItem  *item           = m_lineUpTeamPlayersList->getItemAtGridReference(CEGUI::MCLGridRef(i, 0));
        int                 xFkTeamPlayer   = item->getID();

        CPfTeamPlayerContracts *teamPlayerContract = teamPlayerContractsDAO->findActiveByXFkTeamAndXFkTeamPlayer(team->getXTeam(), xFkTeamPlayer);
        teamPlayerContract->setNLineupOrder(lineUpOrder);
        teamPlayerContractsDAO->updateReg(teamPlayerContract);
        delete teamPlayerContract;

        lineUpOrder++;
    }

    if( lineUpOrder<12 ){ lineUpOrder=12; }
    for( i=0; i<m_alternateTeamPlayersList->getRowCount(); i++ ){

        CEGUI::ListboxItem  *item           = m_alternateTeamPlayersList->getItemAtGridReference(CEGUI::MCLGridRef(i, 0));
        int                 xFkTeamPlayer   = item->getID();

        CPfTeamPlayerContracts *teamPlayerContract = teamPlayerContractsDAO->findActiveByXFkTeamAndXFkTeamPlayer(team->getXTeam(), xFkTeamPlayer);
        teamPlayerContract->setNLineupOrder(lineUpOrder);
        teamPlayerContractsDAO->updateReg(teamPlayerContract);
        delete teamPlayerContract;

        lineUpOrder++;
    }

    if( lineUpOrder<18 ){ lineUpOrder=18; }
    for( i=0; i<m_notLineUpTeamPlayersList->getRowCount(); i++ ){

        CEGUI::ListboxItem  *item           = m_notLineUpTeamPlayersList->getItemAtGridReference(CEGUI::MCLGridRef(i, 0));
        int                 xFkTeamPlayer   = item->getID();

        CPfTeamPlayerContracts *teamPlayerContract = teamPlayerContractsDAO->findActiveByXFkTeamAndXFkTeamPlayer(team->getXTeam(), xFkTeamPlayer);
        teamPlayerContract->setNLineupOrder(lineUpOrder);
        teamPlayerContractsDAO->updateReg(teamPlayerContract);
        delete teamPlayerContract;

        lineUpOrder++;
    }

    delete team;
    CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->commit();
}

bool CStateTeamPlayers::handleLineUpSelectChanged(const CEGUI::EventArgs& e)
{
    if( m_lineUpTeamPlayersList->getFirstSelectedItem()!=NULL ){
        m_alternateTeamPlayersList->clearAllSelections();
        m_notLineUpTeamPlayersList->clearAllSelections();
    }

    return true;
}

bool CStateTeamPlayers::handleAlternateSelectChanged(const CEGUI::EventArgs& e)
{
    if( m_alternateTeamPlayersList->getFirstSelectedItem()!=NULL ){
        m_lineUpTeamPlayersList->clearAllSelections();
        m_notLineUpTeamPlayersList->clearAllSelections();
    }

    return true;
}

bool CStateTeamPlayers::handleNotLineUpSelectChanged(const CEGUI::EventArgs& e)
{
    if( m_notLineUpTeamPlayersList->getFirstSelectedItem()!=NULL ){
        m_lineUpTeamPlayersList->clearAllSelections();
        m_alternateTeamPlayersList->clearAllSelections();
    }

    return true;
}
