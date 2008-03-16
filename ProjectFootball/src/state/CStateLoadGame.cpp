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

    CEGUI::MultiColumnList* ceguiGamesList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/GamesList"));
    ceguiGamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
    ceguiGamesList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CStateLoadGame::handleSelectChanged, this));
    ceguiGamesList->addColumn("Name", 0, CEGUI::UDim(0.77,0));
    ceguiGamesList->addColumn("Date", 1, CEGUI::UDim(0.2,0));

    CEGUI::Editbox* ceguiNewEdit = static_cast<CEGUI::Editbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameEdit"));
    ceguiNewEdit->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&CStateLoadGame::handleTextChanged, this));
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

    CEGUI::PushButton* ceguiLoadButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/LoadGameButton"));
    ceguiLoadButton->setEnabled(false);

    CEGUI::PushButton* ceguiNewButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameButton"));
    ceguiNewButton->setEnabled(false);

    CEGUI::Editbox* editBox = static_cast<CEGUI::Editbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameEdit"));
    editBox->setText("");
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
    CEGUI::Editbox* editBox = static_cast<CEGUI::Editbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameEdit"));
    CGameEngine::getInstance()->newGame(DEFAULT_USER, editBox->getText().c_str());
    loadGameList();
    editBox->setText("");
}

void CStateLoadGame::loadGame()
{
    CEGUI::MultiColumnList* ceguiGamesList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/GamesList"));
    CEGUI::ListboxItem* itm = ceguiGamesList->getFirstSelectedItem();
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

    CEGUI::MultiColumnList* ceguiGamesList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/GamesList"));
    ceguiGamesList->resetList();
    ceguiGamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);

    IPfGamesDAO*                        gamesDAO = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    std::vector<CPfGames*>*             gamesList = gamesDAO->findByXFkUser(DEFAULT_USER);
    std::vector<CPfGames*>::iterator    it;
    for( it=gamesList->begin(); it!=gamesList->end(); it++ ){
        CPfGames *game = (*it);

        int row_idx = ceguiGamesList->addRow();
        ceguiGamesList->setRowID(row_idx, game->getXGame());
        CEGUI::ListboxTextItem* itm_0 = new CEGUI::ListboxTextItem(game->getSGameName());
        itm_0->setSelectionBrushImage(sel_img);
        itm_0->setID(game->getXGame());
        CEGUI::ListboxTextItem* itm_1 = new CEGUI::ListboxTextItem(game->getDLastSaved().format("%Y/%m/%d %H:%M:%S"));
        itm_1->setSelectionBrushImage(sel_img);
        itm_1->setID(game->getXGame());
        ceguiGamesList->setItem(itm_0, 0, row_idx);
        ceguiGamesList->setItem(itm_1, 1, row_idx);
    }
    gamesDAO->freeVector(gamesList);
}

bool CStateLoadGame::handleSelectChanged(const CEGUI::EventArgs& e)
{
    CEGUI::PushButton* ceguiLoadButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/LoadGameButton"));
    ceguiLoadButton->setEnabled(true);

    return true;
}

bool CStateLoadGame::handleTextChanged(const CEGUI::EventArgs& e)
{
    CEGUI::Editbox* editBox = static_cast<CEGUI::Editbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameEdit"));
    if( editBox->getText().compare("")!=0 ){
        CEGUI::PushButton* ceguiNewButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameButton"));
        ceguiNewButton->setEnabled(true);
    }else{
        CEGUI::PushButton* ceguiNewButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadGame/NewGameButton"));
        ceguiNewButton->setEnabled(false);
    }
}
