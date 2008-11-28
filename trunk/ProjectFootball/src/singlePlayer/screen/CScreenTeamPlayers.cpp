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

#include "CScreenTeamPlayers.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeamPlayers.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../utils/CLog.h"


CScreenTeamPlayers::CScreenTeamPlayers(CSinglePlayerGame *game)
    :CScreen("teamPlayers.layout")
{
    CLog::getInstance()->debug("CScreenTeamPlayers()");

    m_game = game;

    m_lineUpTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/LineUpTeamPlayersList"));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Name (Line Up)"), 0, CEGUI::UDim(1.0,0));
    m_lineUpTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_lineUpTeamPlayersList->setUserColumnSizingEnabled(false);
    m_lineUpTeamPlayersList->setUserSortControlEnabled(false);
    m_lineUpTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);
    m_lineUpTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenTeamPlayers::lineUpTeamPlayersListboxSelectionChanged, this));

    m_alternateTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/AlternateTeamPlayersList"));
    m_alternateTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Name (Alternate)"), 0, CEGUI::UDim(1.0,0));
    m_alternateTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_alternateTeamPlayersList->setUserColumnSizingEnabled(false);
    m_alternateTeamPlayersList->setUserSortControlEnabled(false);
    m_alternateTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);
    m_alternateTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenTeamPlayers::alternateTeamPlayersListboxSelectionChanged, this));

    m_notLineUpTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/NotLineUpTeamPlayersList"));
    m_notLineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Name (Not Line Up)"), 0, CEGUI::UDim(1.0,0));
    m_notLineUpTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_notLineUpTeamPlayersList->setUserColumnSizingEnabled(false);
    m_notLineUpTeamPlayersList->setUserSortControlEnabled(false);
    m_notLineUpTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);
    m_notLineUpTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenTeamPlayers::notLineUpTeamPlayersListboxSelectionChanged, this));

    m_backButton = static_cast<CEGUI::PushButton *>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/BackButton"));
    m_backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenTeamPlayers::backButtonClicked, this));

    m_changePlayersButton = static_cast<CEGUI::PushButton *>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/ChangeButton"));
    m_changePlayersButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenTeamPlayers::changePlayersButtonClicked, this));

    // i18n support
    m_backButton->setText((CEGUI::utf8*)gettext("Back"));
    m_changePlayersButton->setText((CEGUI::utf8*)gettext("Change"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/TeamPlayersLabel"))->setText((CEGUI::utf8*)gettext("Team Players:"));
}


CScreenTeamPlayers::~CScreenTeamPlayers()
{
    CLog::getInstance()->debug("~CScreenTeamPlayers()");
}


void CScreenTeamPlayers::enter()
{
  CScreen::enter();

    loadTeamPlayersList();
    m_selectedPlayers = NONE;
    m_selectedPlayer1 = 0;
    m_selectedPlayer2 = 0;
}


void CScreenTeamPlayers::leave()
{
    saveTeamPlayersList();
    switch (m_selectedPlayers) {
        case NONE:
            break;
        case PLAYER1:
            delete m_selectedPlayer1;
            break;
        case PLAYER2:
            delete m_selectedPlayer2;
            break;
        case BOTH:
            delete m_selectedPlayer1;
            delete m_selectedPlayer2;
            break;
        default:
            break;
    }
    m_selectedPlayers = NONE;
}


void CScreenTeamPlayers::changePlayers()
{
    CEGUI::ListboxItem *itemAux = m_item1;
    m_item1->setAutoDeleted(false);
    m_item2->setAutoDeleted(false);
    CEGUI::MCLGridRef reference1 = m_selectedPlayer1List->getItemGridReference(m_item1);
    CEGUI::MCLGridRef reference2 = m_selectedPlayer2List->getItemGridReference(m_item2);
    m_selectedPlayer1List->setItem(m_item2, reference1);
    m_selectedPlayer2List->setItem(m_item1, reference2);
    m_item1 = m_item2;
    m_item2 = itemAux;
    m_item1->setAutoDeleted(true);
    m_item2->setAutoDeleted(true);
    m_selectedPlayer1List->getHorzScrollbar()->setVisible(false);
    m_selectedPlayer1List->getVertScrollbar()->setVisible(false);
    m_selectedPlayer2List->getHorzScrollbar()->setVisible(false);
    m_selectedPlayer2List->getVertScrollbar()->setVisible(false);
    m_selectedPlayers = NONE;
    m_selectedPlayer1List->clearAllSelections();
    m_selectedPlayer2List->clearAllSelections();
}


void CScreenTeamPlayers::loadTeamPlayersList()
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("MultiListSelectionBrush");

    m_lineUpTeamPlayersList->resetList();
    m_alternateTeamPlayersList->resetList();
    m_notLineUpTeamPlayersList->resetList();

    CPfTeams                        *team                       = m_game->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayersDAO               *teamPlayersDAO             = m_game->getIDAOFactory()->getIPfTeamPlayersDAO();
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


void CScreenTeamPlayers::saveTeamPlayersList()
{
    m_game->getIDAOFactory()->beginTransaction();
    CPfTeams                    *team                   = m_game->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayerContractsDAO   *teamPlayerContractsDAO = m_game->getIDAOFactory()->getIPfTeamPlayerContractsDAO();

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
    m_game->getIDAOFactory()->commit();
}


void CScreenTeamPlayers::selectChanged(CEGUI::MultiColumnList *list)
{
    CEGUI::ListboxItem *currentItem = list->getFirstSelectedItem();

    if( currentItem != NULL ) {
        list->clearAllSelections();
        IPfTeamPlayersDAO *teamPlayersDAO = m_game->getIDAOFactory()->getIPfTeamPlayersDAO();
        int xTeamPlayer = currentItem->getID();
        switch (m_selectedPlayers) {
            case NONE:
                m_selectedPlayer1 = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
                m_selectedPlayers = PLAYER1;
                m_item1 = currentItem;
                m_selectedPlayer1List = list;
                m_item1->setSelected(true);
                break;
            case PLAYER1:
                if(xTeamPlayer == m_selectedPlayer1->getXTeamPlayer()) {
                    delete m_selectedPlayer1;
                    m_selectedPlayers = NONE;
                } else {
                    m_selectedPlayer2 = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
                    m_selectedPlayers = BOTH;
                    m_item2 = currentItem;
                    m_selectedPlayer2List = list;
                    m_item1->setSelected(true);
                    m_item2->setSelected(true);
                }
                break;
            case PLAYER2:
                if(xTeamPlayer == m_selectedPlayer2->getXTeamPlayer()) {
                    delete m_selectedPlayer2;
                    m_selectedPlayers = NONE;
                } else {
                    m_selectedPlayer1 = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
                    m_selectedPlayers = BOTH;
                    m_item1 = currentItem;
                    m_selectedPlayer1List = list;
                    m_item1->setSelected(true);
                    m_item2->setSelected(true);
                }
                break;
            case BOTH:
                if(xTeamPlayer == m_selectedPlayer1->getXTeamPlayer()) {
                    delete m_selectedPlayer1;
                    m_selectedPlayers = PLAYER2;
                    m_item2->setSelected(true);
                } else if(xTeamPlayer == m_selectedPlayer2->getXTeamPlayer()) {
                    delete m_selectedPlayer2;
                    m_selectedPlayers = PLAYER1;
                    m_item1->setSelected(true);
                } else {
                    m_item1->setSelected(true);
                    m_item2->setSelected(true);
                }
                break;
            default:
                break;
        }
    }
}


bool CScreenTeamPlayers::lineUpTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e)
{
    selectChanged(m_lineUpTeamPlayersList);
    return true;
}


bool CScreenTeamPlayers::alternateTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e)
{
    selectChanged(m_alternateTeamPlayersList);
    return true;
}


bool CScreenTeamPlayers::notLineUpTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e)
{
    selectChanged(m_notLineUpTeamPlayersList);
    return true;
}


bool CScreenTeamPlayers::changePlayersButtonClicked(const CEGUI::EventArgs& e)
{
    if(m_selectedPlayers == BOTH) {
        changePlayers();
    }
    return true;
}


bool CScreenTeamPlayers::backButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->previousScreen();
    return true;
}
