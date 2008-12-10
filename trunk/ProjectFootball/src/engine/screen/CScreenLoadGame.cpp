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

#include "CScreenLoadGame.h"
#include "../CGameEngine.h"
#include "../../singlePlayer/CSinglePlayerGame.h"
#include "../../utils/CLog.h"

CScreenLoadGame::CScreenLoadGame()
    :CScreen("loadGame.layout")
{
    CLog::getInstance()->debug("CScreenLoadGame()");

    m_mainWindow           = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/MainWindow"));
    m_backButton		   = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/BackButton"));
    m_loadGameButton       = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/LoadGameButton"));
    m_deleteGameButton     = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/DeleteGameButton"));
    m_newGameButton        = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/NewGameButton"));
    m_newGameEditbox       = static_cast<CEGUI::Editbox*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/NewGameEdit"));
    m_confirmRemoveWindow  = static_cast<CEGUI::FrameWindow*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/RemoveConfirmationWindow"));
    m_confirmRemoveNote    = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/RemoveConfirmationWindow/Note"));
    m_removeConfirmButton  = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/RemoveConfirmationWindow/YesButton"));
    m_removeCancelButton   = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/RemoveConfirmationWindow/NoButton"));



    m_gamesList = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"LoadGame/GamesList"));
    m_gamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
    m_gamesList->setUserColumnDraggingEnabled(false);
    m_gamesList->setUserColumnSizingEnabled(false);
    m_gamesList->setUserSortControlEnabled(false);
    m_gamesList->setWantsMultiClickEvents(true);

    // i18n support
    m_gamesList->addColumn((CEGUI::utf8*)gettext("Name"), 0, CEGUI::UDim(0.7,0));
    m_gamesList->addColumn((CEGUI::utf8*)gettext("Date"), 1, CEGUI::UDim(0.3,0));

    m_newGameButton       ->setText((CEGUI::utf8*)gettext("New Game"));
    m_deleteGameButton    ->setText((CEGUI::utf8*)gettext("Delete Game"));
    m_loadGameButton      ->setText((CEGUI::utf8*)gettext("Load Game"));
    m_backButton          ->setText((CEGUI::utf8*)gettext("Back"));
    m_confirmRemoveNote   ->setText((CEGUI::utf8*)gettext("Are you sure you want to remove this game?"));
    m_removeConfirmButton ->setText((CEGUI::utf8*)gettext("Yes"));
    m_removeCancelButton  ->setText((CEGUI::utf8*)gettext("No"));

    // Event handle
    m_backButton         ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenLoadGame::backButtonClicked, this));
    m_newGameButton      ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenLoadGame::newGameButtonClicked, this));
    m_loadGameButton     ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenLoadGame::loadGameButtonClicked, this));
    m_deleteGameButton   ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenLoadGame::deleteGameButtonClicked, this));
    m_gamesList          ->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenLoadGame::gamesListSelectChanged, this));
    m_gamesList          ->subscribeEvent(CEGUI::MultiColumnList::EventMouseDoubleClick, CEGUI::Event::Subscriber(&CScreenLoadGame::gamesListDoubleClick, this));
    m_newGameEditbox     ->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&CScreenLoadGame::newGameEditboxTextChanged, this));
    m_removeConfirmButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenLoadGame::removeConfirmButtonClicked, this));
    m_removeCancelButton ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenLoadGame::removeCancelButtonClicked, this));

}

CScreenLoadGame::~CScreenLoadGame()
{
    CLog::getInstance()->debug("~CScreenLoadGame()");
}

void CScreenLoadGame::enter()
{
    CScreen::enter();

    loadGameList();

    m_loadGameButton->setEnabled(false);
    m_deleteGameButton->setEnabled(false);
    m_newGameButton->setEnabled(false);
    m_newGameEditbox->setText("");
}

void CScreenLoadGame::loadGameList()
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

        CEGUI::ListboxTextItem* itm_0 = new CEGUI::ListboxTextItem(game->getSGameName());
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

bool CScreenLoadGame::gamesListDoubleClick(const CEGUI::EventArgs& e)
{
    if( m_gamesList->getFirstSelectedItem()!=NULL ){
        loadGameButtonClicked(e);
    }
    return true;
}

bool CScreenLoadGame::gamesListSelectChanged(const CEGUI::EventArgs& e)
{
    m_loadGameButton->setEnabled(m_gamesList->getFirstSelectedItem()!=NULL);
    m_deleteGameButton->setEnabled(m_gamesList->getFirstSelectedItem()!=NULL);

    return true;
}

bool CScreenLoadGame::newGameEditboxTextChanged(const CEGUI::EventArgs& e)
{
    if( m_newGameEditbox->getText().compare("")!=0 ){
        m_newGameButton->setEnabled(true);
    }else{
        m_newGameButton->setEnabled(false);
    }
}

bool CScreenLoadGame::backButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->previousScreen();
    return true;
}

bool CScreenLoadGame::newGameButtonClicked(const CEGUI::EventArgs& e)
{
    IMasterDAOFactory *masterDatabase = CGameEngine::getInstance()->getCMasterDAOFactory();
    const CPfUsers *user = CGameEngine::getInstance()->getCurrentUser();

    if( user==NULL || user->getXUser()==0 ){
        CLog::getInstance()->exception("[CScreenLoadGame::newGameButtonClicked] User not defined");
    }

    CGameEngine::getInstance()->loadGame(new CSinglePlayerGame(user, m_newGameEditbox->getText().c_str()));
    CGameEngine::getInstance()->save();

    m_newGameEditbox->setText("");

    return true;
}

bool CScreenLoadGame::loadGameButtonClicked(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem* itm = m_gamesList->getFirstSelectedItem();
    CPfGames *game = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO()->findByXGame(itm->getID());
    CGameEngine::getInstance()->loadGame(new CSinglePlayerGame(game));
    delete game;

    return true;
}

bool CScreenLoadGame::deleteGameButtonClicked(const CEGUI::EventArgs& e)
{
    m_mainWindow->disable();
    m_confirmRemoveWindow->setVisible(true);
    m_confirmRemoveWindow->activate();
    m_confirmRemoveWindow->enable();

    return true;
}

bool CScreenLoadGame::removeConfirmButtonClicked(const CEGUI::EventArgs& e)
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

    m_confirmRemoveWindow->setVisible(false);
    m_confirmRemoveWindow->deactivate();
    m_confirmRemoveWindow->disable();
    m_mainWindow->enable();

    return true;
}

bool CScreenLoadGame::removeCancelButtonClicked(const CEGUI::EventArgs& e)
{
    m_confirmRemoveWindow->setVisible(false);
    m_confirmRemoveWindow->deactivate();
    m_confirmRemoveWindow->disable();
    m_mainWindow->enable();

    return true;
}
