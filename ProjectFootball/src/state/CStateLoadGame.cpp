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

#include "CStateLoadGame.h"

#include "CStateGame.h"
#include "CStateManager.h"
#include "CStateSelectTeam.h"
#include "../utils/CLog.h"
#include "../engine/CGameEngine.h"

CStateLoadGame::CStateLoadGame()
    :CState()
{
    CLog::getInstance()->debug("CStateLoadGame()");
    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"loadGame.layout");

    m_loadGameButton    = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/LoadGameButton"));
    m_newGameButton     = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameButton"));

    m_newGameEditbox    = static_cast<CEGUI::Editbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameEdit"));
    m_newGameEditbox->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&CStateLoadGame::handleTextChanged, this));

    m_gamesList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/GamesList"));
    m_gamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
    m_gamesList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CStateLoadGame::handleSelectChanged, this));
    m_gamesList->setUserColumnDraggingEnabled(false);
    m_gamesList->setUserColumnSizingEnabled(false);
    m_gamesList->setUserSortControlEnabled(false);

    m_gamesList->addColumn("Name", 0, CEGUI::UDim(0.7,0));
    m_gamesList->addColumn("Date", 1, CEGUI::UDim(0.3,0));
}

CStateLoadGame* CStateLoadGame::getInstance()
{
    static CStateLoadGame instance;
    return &instance;
}

CStateLoadGame::~CStateLoadGame()
{
    CLog::getInstance()->debug("~CStateLoadGame()");
}

void CStateLoadGame::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    loadGameList();

    m_loadGameButton->setEnabled(false);
    m_newGameButton->setEnabled(false);
    m_newGameEditbox->setText("");
}

void CStateLoadGame::forcedLeave()
{

}

bool CStateLoadGame::leave()
{
    return true;
}

void CStateLoadGame::update()
{
}

void CStateLoadGame::createNewGame()
{
    CGameEngine::getInstance()->newSinglePlayerGame(m_newGameEditbox->getText().c_str());
    loadGameList();
    m_newGameEditbox->setText("");
}

void CStateLoadGame::loadGame()
{
    CEGUI::ListboxItem* itm = m_gamesList->getFirstSelectedItem();
    int xGame = itm->getID();
    CGameEngine::getInstance()->loadGame(xGame);

    // Test if this game is a new game
    IPfGameStatesDAO *gameStateDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfGameStatesDAO();
    CPfGameStates *newGameState = gameStateDAO->findBySState(S_STATE_NEWGAME);
    if( newGameState->getSValue()=="true" ){
        CStateManager::getInstance()->popState();
        CStateManager::getInstance()->pushState(CStateSelectTeam::getInstance());
    }else{
        CStateManager::getInstance()->popState();
        CStateManager::getInstance()->pushState(CStateGame::getInstance());
    }
    delete newGameState;
}

void CStateLoadGame::loadGameList()
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("MultiListSelectionBrush");

    m_gamesList->resetList();
    m_gamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);

    IPfGamesDAO*                        gamesDAO = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    std::vector<CPfGames*>*             gamesList = gamesDAO->findByXFkUser(DEFAULT_USER);
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
}

bool CStateLoadGame::handleSelectChanged(const CEGUI::EventArgs& e)
{
    m_loadGameButton->setEnabled(m_gamesList->getFirstSelectedItem()!=NULL);

    return true;
}

bool CStateLoadGame::handleTextChanged(const CEGUI::EventArgs& e)
{
    if( m_newGameEditbox->getText().compare("")!=0 ){
        m_newGameButton->setEnabled(true);
    }else{
        m_newGameButton->setEnabled(false);
    }
}
