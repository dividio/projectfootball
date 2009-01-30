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
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Name (Line Up)"), 0, CEGUI::UDim(0.55,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Speed"), 1, CEGUI::UDim(0.15,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Shot power"), 2, CEGUI::UDim(0.15,0));
    m_lineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Average"), 3, CEGUI::UDim(0.15,0));
    m_lineUpTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_lineUpTeamPlayersList->setUserColumnSizingEnabled(false);
    m_lineUpTeamPlayersList->setUserSortControlEnabled(false);
    m_lineUpTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);
    m_lineUpTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenTeamPlayers::lineUpTeamPlayersListboxSelectionChanged, this));

    m_alternateTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/AlternateTeamPlayersList"));
    m_alternateTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Name (Alternate)"), 0, CEGUI::UDim(0.55,0));
    m_alternateTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Speed"), 1, CEGUI::UDim(0.15,0));
    m_alternateTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Shot power"), 2, CEGUI::UDim(0.15,0));
    m_alternateTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Average"), 3, CEGUI::UDim(0.15,0));
    m_alternateTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_alternateTeamPlayersList->setUserColumnSizingEnabled(false);
    m_alternateTeamPlayersList->setUserSortControlEnabled(false);
    m_alternateTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);
    m_alternateTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenTeamPlayers::alternateTeamPlayersListboxSelectionChanged, this));

    m_notLineUpTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/NotLineUpTeamPlayersList"));
    m_notLineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Name (Not Line Up)"), 0, CEGUI::UDim(0.55,0));
    m_notLineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Speed"), 1, CEGUI::UDim(0.15,0));
    m_notLineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Shot power"), 2, CEGUI::UDim(0.15,0));
    m_notLineUpTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Average"), 3, CEGUI::UDim(0.15,0));
    m_notLineUpTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_notLineUpTeamPlayersList->setUserColumnSizingEnabled(false);
    m_notLineUpTeamPlayersList->setUserSortControlEnabled(false);
    m_notLineUpTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);
    m_notLineUpTeamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenTeamPlayers::notLineUpTeamPlayersListboxSelectionChanged, this));

    m_backButton = static_cast<CEGUI::PushButton *>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/BackButton"));
    m_backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenTeamPlayers::backButtonClicked, this));

    m_changePlayersButton = static_cast<CEGUI::PushButton *>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/ChangeButton"));
    m_changePlayersButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenTeamPlayers::changePlayersButtonClicked, this));

    m_teamName    = static_cast<CEGUI::Window *>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/TeamName"));
    m_teamAverage = static_cast<CEGUI::Window *>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/TeamAverage"));
    m_teamShield  = static_cast<CEGUI::Window *>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/TeamShield"));

    // i18n support
    m_backButton->setText((CEGUI::utf8*)gettext("Back"));
    m_changePlayersButton->setText((CEGUI::utf8*)gettext("Change"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/TeamPlayersLabel"))->setText((CEGUI::utf8*)gettext("Team Players:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"TeamPlayers/TeamAverageLabel"))->setText((CEGUI::utf8*)gettext("Average:"));
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
    m_selectedPlayer1 = NULL;
    m_selectedPlayer2 = NULL;
}


void CScreenTeamPlayers::leave()
{
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
    changeRows(m_selectedPlayer1List, m_selectedPlayer1Row, m_selectedPlayer2List, m_selectedPlayer2Row);

    m_selectedPlayer1List->getHorzScrollbar()->setVisible(false);
    m_selectedPlayer2List->getHorzScrollbar()->setVisible(false);
    delete m_selectedPlayer1;
    delete m_selectedPlayer2;
    m_selectedPlayers = NONE;
    m_selectedPlayer1List->clearAllSelections();
    m_selectedPlayer2List->clearAllSelections();
}


void CScreenTeamPlayers::loadTeamPlayersList()
{
    m_lineUpTeamPlayersList   ->resetList();
    m_alternateTeamPlayersList->resetList();
    m_notLineUpTeamPlayersList->resetList();

    CPfTeams                        *team                       = m_game->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayersDAO               *teamPlayersDAO             = m_game->getIDAOFactory()->getIPfTeamPlayersDAO();
    IPfTeamAveragesDAO              *teamAveragesDAO            = m_game->getIDAOFactory()->getIPfTeamAveragesDAO();
    std::vector<CPfTeamPlayers*>    *lineUpTeamPlayersList      = teamPlayersDAO->findLineUpByXFkTeam(team->getXTeam());
    std::vector<CPfTeamPlayers*>    *alternateTeamPlayersList   = teamPlayersDAO->findAlternateByXFkTeam(team->getXTeam());
    std::vector<CPfTeamPlayers*>    *notLineUpTeamPlayersList   = teamPlayersDAO->findNotLineUpByXFkTeam(team->getXTeam());

    std::vector<CPfTeamPlayers*>::iterator it;
    for( it=lineUpTeamPlayersList->begin(); it!=lineUpTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);
        addPlayerToList(teamPlayer, m_lineUpTeamPlayersList);
    }
    for( it=alternateTeamPlayersList->begin(); it!=alternateTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);
        addPlayerToList(teamPlayer, m_alternateTeamPlayersList);
    }
    for( it=notLineUpTeamPlayersList->begin(); it!=notLineUpTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);
        addPlayerToList(teamPlayer, m_notLineUpTeamPlayersList);
    }

    CPfTeamAverages *teamAverage = teamAveragesDAO->findByXTeam(team->getXTeam_str());
    m_teamName   ->setText((CEGUI::utf8*)team->getSTeam().c_str());
    std::ostringstream average;
    average << teamAverage->getNTotal();
    m_teamAverage->setText((CEGUI::utf8*)average.str().c_str());
    delete teamAverage;

    //Loading Shield
    m_teamShield->setProperty("Image", "set:"+ team->getSLogo() +" image:"+team->getSLogo()+"_b");

    teamPlayersDAO->freeVector(lineUpTeamPlayersList);
    teamPlayersDAO->freeVector(alternateTeamPlayersList);
    teamPlayersDAO->freeVector(notLineUpTeamPlayersList);
    delete team;

    m_lineUpTeamPlayersList   ->getHorzScrollbar()->setVisible(false);
    m_alternateTeamPlayersList->getHorzScrollbar()->setVisible(false);
    m_notLineUpTeamPlayersList->getHorzScrollbar()->setVisible(false);

    m_lineUpTeamPlayersList   ->getVertScrollbar()->setVisible(false);
    m_alternateTeamPlayersList->getVertScrollbar()->setVisible(false);
}


void CScreenTeamPlayers::addPlayerToList(CPfTeamPlayers *player, CEGUI::MultiColumnList *list)
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    int row_idx = list->addRow();
    int XTeamPlayer = player->getXTeamPlayer();
    CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getSName().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 0, row_idx);

    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNVelocity_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 1, row_idx);

    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNKickPower_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 2, row_idx);

    CPfTeamPlayerAverages *playerAverage = m_game->getIDAOFactory()->getIPfTeamPlayerAveragesDAO()->findByXTeamPlayer(player->getXTeamPlayer_str());
    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)playerAverage->getNTotal_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 3, row_idx);
    delete playerAverage;
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
        int currentRow  = list->getItemRowIndex(currentItem);
        list->clearAllSelections();
        IPfTeamPlayersDAO *teamPlayersDAO = m_game->getIDAOFactory()->getIPfTeamPlayersDAO();
        int xTeamPlayer = currentItem->getID();
        switch (m_selectedPlayers) {
            case NONE:
                m_selectedPlayer1 = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
                m_selectedPlayers = PLAYER1;
                m_selectedPlayer1Row = currentRow;
                m_selectedPlayer1List = list;
                changeRowSelection(m_selectedPlayer1List, m_selectedPlayer1Row, true);
                break;
            case PLAYER1:
                if(xTeamPlayer == m_selectedPlayer1->getXTeamPlayer()) {
                    delete m_selectedPlayer1;
                    m_selectedPlayers = NONE;
                } else {
                    m_selectedPlayer2 = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
                    m_selectedPlayers = BOTH;
                    m_selectedPlayer2Row = currentRow;
                    m_selectedPlayer2List = list;
                    changeRowSelection(m_selectedPlayer1List, m_selectedPlayer1Row, true);
                    changeRowSelection(m_selectedPlayer2List, m_selectedPlayer2Row, true);
                }
                break;
            case PLAYER2:
                if(xTeamPlayer == m_selectedPlayer2->getXTeamPlayer()) {
                    delete m_selectedPlayer2;
                    m_selectedPlayers = NONE;
                } else {
                    m_selectedPlayer1 = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
                    m_selectedPlayers = BOTH;
                    m_selectedPlayer1Row = currentRow;
                    m_selectedPlayer1List = list;
                    changeRowSelection(m_selectedPlayer1List, m_selectedPlayer1Row, true);
                    changeRowSelection(m_selectedPlayer2List, m_selectedPlayer2Row, true);
                }
                break;
            case BOTH:
                if(xTeamPlayer == m_selectedPlayer1->getXTeamPlayer()) {
                    delete m_selectedPlayer1;
                    m_selectedPlayers = PLAYER2;
                    changeRowSelection(m_selectedPlayer2List, m_selectedPlayer2Row, true);
                } else if(xTeamPlayer == m_selectedPlayer2->getXTeamPlayer()) {
                    delete m_selectedPlayer2;
                    m_selectedPlayers = PLAYER1;
                    changeRowSelection(m_selectedPlayer1List, m_selectedPlayer1Row, true);
                } else {
                    changeRowSelection(m_selectedPlayer1List, m_selectedPlayer1Row, true);
                    changeRowSelection(m_selectedPlayer2List, m_selectedPlayer2Row, true);
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
        saveTeamPlayersList();

        IPfTeamAveragesDAO *teamAveragesDAO = m_game->getIDAOFactory()->getIPfTeamAveragesDAO();
        CPfTeams           *team            = m_game->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
        CPfTeamAverages    *teamAverage     = teamAveragesDAO->findByXTeam(team->getXTeam_str());
        std::ostringstream average;
        average << teamAverage->getNTotal();
        m_teamAverage->setText((CEGUI::utf8*)average.str().c_str());
        delete teamAverage;
        delete team;
    }
    return true;
}


bool CScreenTeamPlayers::backButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->previousScreen();
    return true;
}

void CScreenTeamPlayers::changeRows(CEGUI::MultiColumnList *list1, int row1, CEGUI::MultiColumnList *list2, int row2)
{
    CEGUI::ListboxItem *item1;
    CEGUI::ListboxItem *item2;
    int columns = list1->getColumnCount();
    for( int i = 0; i < columns; i++) {
        CEGUI::ListboxItem *itemAux;
        CEGUI::MCLGridRef reference1 = CEGUI::MCLGridRef(row1, i);
        CEGUI::MCLGridRef reference2 = CEGUI::MCLGridRef(row2, i);
        item1 = list1->getItemAtGridReference(reference1);
        item2 = list2->getItemAtGridReference(reference2);
        item1->setAutoDeleted(false);
        item2->setAutoDeleted(false);
        list1->setItem(item2, reference1);
        list2->setItem(item1, reference2);
        itemAux = item1;
        item1 = item2;
        item2 = itemAux;
        item1->setAutoDeleted(true);
        item2->setAutoDeleted(true);
    }

    IPfTeamPlayerAveragesDAO *teamPlayerAveragesDAO = m_game->getIDAOFactory()->getIPfTeamPlayerAveragesDAO();
    CPfTeamPlayerAverages *playerAverage = teamPlayerAveragesDAO->findByXTeamPlayer(item1->getID());
    item1->setText((CEGUI::utf8*)playerAverage->getNTotal_str().c_str());
    delete playerAverage;

    playerAverage = teamPlayerAveragesDAO->findByXTeamPlayer(item2->getID());
    item2->setText((CEGUI::utf8*)playerAverage->getNTotal_str().c_str());
    delete playerAverage;
}

void CScreenTeamPlayers::changeRowSelection(CEGUI::MultiColumnList *list, int row, bool newSelectionState)
{
    int columns = list->getColumnCount();
    for( int i = 0; i < columns; i++) {
        CEGUI::ListboxItem *item = list->getItemAtGridReference(CEGUI::MCLGridRef(row, i));
        item->setSelected(newSelectionState);
    }
}
