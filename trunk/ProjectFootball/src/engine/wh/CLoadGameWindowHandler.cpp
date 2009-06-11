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

#include <stdio.h>
#include <libintl.h>

#include "CLoadGameWindowHandler.h"
#include "../CGameEngine.h"
#include "../../singlePlayer/CSinglePlayerGame.h"
#include "../../utils/CLog.h"

CLoadGameWindowHandler::CLoadGameWindowHandler()
: CWindowHandler("loadGame.layout")
{
    LOG_DEBUG("CLoadGameWindowHandler()");
}

CLoadGameWindowHandler::~CLoadGameWindowHandler()
{
    LOG_DEBUG("~CLoadGameWindowHandler()");
}

void CLoadGameWindowHandler::enter()
{
    loadGameList();

    m_loadGameButton->setEnabled(false);
    m_deleteGameButton->setEnabled(false);
}

void CLoadGameWindowHandler::init()
{
	CEGUI::WindowManager *windowMngr = CEGUI::WindowManager::getSingletonPtr();

    m_mainWindow           = static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"LoadGame/MainWindow"));
    m_backButton		   = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"LoadGame/BackButton"));
    m_loadGameButton       = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"LoadGame/LoadGameButton"));
    m_deleteGameButton     = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"LoadGame/DeleteGameButton"));

    m_gamesList = static_cast<CEGUI::MultiColumnList*>(windowMngr->getWindow((CEGUI::utf8*)"LoadGame/GamesList"));
    m_gamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
    m_gamesList->setUserColumnDraggingEnabled(false);
    m_gamesList->setUserColumnSizingEnabled(false);
    m_gamesList->setUserSortControlEnabled(false);
    m_gamesList->setWantsMultiClickEvents(true);

    // i18n support
    m_gamesList->addColumn((CEGUI::utf8*)gettext("Name"), 0, CEGUI::UDim(0.7,0));
    m_gamesList->addColumn((CEGUI::utf8*)gettext("Date"), 1, CEGUI::UDim(0.3,0));

    m_deleteGameButton    ->setText((CEGUI::utf8*)gettext("Delete Game"));
    m_loadGameButton      ->setText((CEGUI::utf8*)gettext("Load Game"));
    m_backButton          ->setText((CEGUI::utf8*)gettext("Back"));

    // Event handle
    registerEventConnection(m_backButton         ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CLoadGameWindowHandler::backButtonClicked, this)));
    registerEventConnection(m_loadGameButton     ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CLoadGameWindowHandler::loadGameButtonClicked, this)));
    registerEventConnection(m_deleteGameButton   ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CLoadGameWindowHandler::deleteGameButtonClicked, this)));
    registerEventConnection(m_gamesList          ->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CLoadGameWindowHandler::gamesListSelectChanged, this)));
    registerEventConnection(m_gamesList          ->subscribeEvent(CEGUI::MultiColumnList::EventMouseDoubleClick, CEGUI::Event::Subscriber(&CLoadGameWindowHandler::gamesListDoubleClick, this)));
}

void CLoadGameWindowHandler::loadGameList()
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    m_gamesList->resetList();
    m_gamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);

    IPfGamesDAO*                        gamesDAO    = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    std::vector<CPfGames*>*             gamesList   = gamesDAO->findByXFkUserAndSGameType(CGameEngine::getInstance()->getCurrentUser()->getXUser(), S_GAME_TYPE_SINGLEPLAYER);
    std::vector<CPfGames*>::iterator    it;
    for( it=gamesList->begin(); it!=gamesList->end(); it++ ){
        CPfGames *game = (*it);

        int row_idx = m_gamesList->addRow();
        m_gamesList->setRowID(row_idx, game->getXGame());

        CEGUI::ListboxTextItem* itm_0 = new CEGUI::ListboxTextItem((CEGUI::utf8*)game->getSGameName().c_str());
        itm_0->setSelectionBrushImage(sel_img);
        itm_0->setID(game->getXGame());

        CEGUI::ListboxTextItem* itm_1 = new CEGUI::ListboxTextItem(game->getDLastSaved().format("%Y/%m/%d %H:%M:%S"));
        itm_1->setSelectionBrushImage(sel_img);
        itm_1->setID(game->getXGame());

        m_gamesList->setItem(itm_0, 0, row_idx);
        m_gamesList->setItem(itm_1, 1, row_idx);
    }
    gamesDAO->freeVector(gamesList);

    m_gamesList->getHorzScrollbar()->setVisible(false);

    m_loadGameButton->setEnabled(false);
    m_deleteGameButton->setEnabled(false);
}

bool CLoadGameWindowHandler::gamesListDoubleClick(const CEGUI::EventArgs& e)
{
    if( m_gamesList->getFirstSelectedItem()!=NULL ){
        loadGameButtonClicked(e);
    }
    return true;
}

bool CLoadGameWindowHandler::gamesListSelectChanged(const CEGUI::EventArgs& e)
{
    m_loadGameButton->setEnabled(m_gamesList->getFirstSelectedItem()!=NULL);
    m_deleteGameButton->setEnabled(m_gamesList->getFirstSelectedItem()!=NULL);

    return true;
}

bool CLoadGameWindowHandler::backButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->getWindowManager()->previousScreen();
    return true;
}

bool CLoadGameWindowHandler::loadGameButtonClicked(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem* itm = m_gamesList->getFirstSelectedItem();
    CPfGames *game = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO()->findByXGame(itm->getID());
    CGameEngine::getInstance()->loadGame(CSinglePlayerGame::load(*game));
    delete game;

    return true;
}

bool CLoadGameWindowHandler::deleteGameButtonClicked(const CEGUI::EventArgs& e)
{
	CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to remove this game?"), CEGUI::Event::Subscriber(&CLoadGameWindowHandler::deleteGameConfirmed, this));
    return true;
}

bool CLoadGameWindowHandler::deleteGameConfirmed(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem* itm = m_gamesList->getFirstSelectedItem();
    int xGame = itm->getID();

    IPfGamesDAO *gamesDAO   = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    CPfGames    *game       = gamesDAO->findByXGame(xGame);
    if( game->getSDriverName()=="SQLite" ){
        remove(game->getSConnectionString().c_str());
    }
    gamesDAO->deleteReg(game);
    delete game;

    loadGameList();
    return true;
}
