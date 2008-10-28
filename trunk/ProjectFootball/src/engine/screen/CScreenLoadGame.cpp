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

// TODO: Remove singlePlayer dependency
#include "CScreenLoadGame.h"
#include "../../singlePlayer/screen/CScreenGame.h"
#include "../CScreenManager.h"
#include "../../singlePlayer/screen/CScreenSelectTeam.h"
#include "../../utils/CLog.h"
#include "../CGameEngine.h"
#include "../singlePlayer/db/sqlite/dao/factory/CDAOFactorySQLite.h"
#include "../../singlePlayer/CDataGenerator.h"
#include "../../utils/CDate.h"

CScreenLoadGame::CScreenLoadGame()
    :CScreen()
{
    CLog::getInstance()->debug("CScreenLoadGame()");

    CEGUI::WindowManager *ceguiWM = &(CEGUI::WindowManager::getSingleton());
    m_sheet = ceguiWM->loadWindowLayout((CEGUI::utf8*)"loadGame.layout");

    m_loadGameButton    = static_cast<CEGUI::PushButton*>(ceguiWM->getWindow((CEGUI::utf8*)"LoadGame/LoadGameButton"));
    m_deleteGameButton  = static_cast<CEGUI::PushButton*>(ceguiWM->getWindow((CEGUI::utf8*)"LoadGame/DeleteGameButton"));
    m_newGameButton     = static_cast<CEGUI::PushButton*>(ceguiWM->getWindow((CEGUI::utf8*)"LoadGame/NewGameButton"));

    m_newGameEditbox    = static_cast<CEGUI::Editbox*>(ceguiWM->getWindow((CEGUI::utf8*)"LoadGame/NewGameEdit"));
    m_newGameEditbox->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&CScreenLoadGame::handleTextChanged, this));

    m_gamesList = static_cast<CEGUI::MultiColumnList*>(ceguiWM->getWindow((CEGUI::utf8*)"LoadGame/GamesList"));
    m_gamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
    m_gamesList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenLoadGame::handleSelectChanged, this));
    m_gamesList->subscribeEvent(CEGUI::MultiColumnList::EventMouseDoubleClick, CEGUI::Event::Subscriber(&CScreenLoadGame::handleDoubleClick, this));
    m_gamesList->setUserColumnDraggingEnabled(false);
    m_gamesList->setUserColumnSizingEnabled(false);
    m_gamesList->setUserSortControlEnabled(false);
    m_gamesList->setWantsMultiClickEvents(true);

    // i18n support
    m_gamesList->addColumn((CEGUI::utf8*)gettext("Name"), 0, CEGUI::UDim(0.7,0));
    m_gamesList->addColumn((CEGUI::utf8*)gettext("Date"), 1, CEGUI::UDim(0.3,0));
    m_newGameButton->setText((CEGUI::utf8*)gettext("New Game"));
    m_deleteGameButton->setText((CEGUI::utf8*)gettext("Delete Game"));
    m_loadGameButton->setText((CEGUI::utf8*)gettext("Load Game"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"LoadGame/BackButton"))->setText((CEGUI::utf8*)gettext("Back"));
}

CScreenLoadGame* CScreenLoadGame::getInstance()
{
    static CScreenLoadGame instance;
    return &instance;
}

CScreenLoadGame::~CScreenLoadGame()
{
    CLog::getInstance()->debug("~CScreenLoadGame()");
}

void CScreenLoadGame::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    loadGameList();

    m_loadGameButton->setEnabled(false);
    m_deleteGameButton->setEnabled(false);
    m_newGameButton->setEnabled(false);
    m_newGameEditbox->setText("");
}

void CScreenLoadGame::forcedLeave()
{

}

bool CScreenLoadGame::leave()
{
    return true;
}

void CScreenLoadGame::update()
{
}

void CScreenLoadGame::newGame()
{
    IMasterDAOFactory *masterDatabase = CGameEngine::getInstance()->getCMasterDAOFactory();
    const CPfUsers *user = CGameEngine::getInstance()->getCurrentUser();

    if( user==NULL || user->getXUser()==0 ){
        CLog::getInstance()->exception("[CScreenLoadGame::newGame] User not defined");
    }

    const char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string filename = "data/database/savedgames/";

    srand(time(NULL));
    for( int i=0; i<8; i++ ){
        filename += str[rand()%52];
    }
    filename += ".sql3";

    CDate nowDate;
    CPfGames game;
    game.setDLastSaved(nowDate);
    game.setSDriverName("SQLite");
    game.setSConnectionString(filename);
    game.setSGameName(m_newGameEditbox->getText().c_str());
    game.setSGameType(S_GAME_TYPE_SINGLEPLAYER);
    game.setXFkUser(user->getXUser());
    masterDatabase->getIPfGamesDAO()->insertReg(&game);

    CDAOFactorySQLite *daoFactory = new CDAOFactorySQLite(filename);
    daoFactory->beginTransaction();
    daoFactory->executeScriptFile("data/database/scripts/tables.sql");
    daoFactory->executeScriptFile("data/database/scripts/view_ranking.sql");
    daoFactory->executeScriptFile("data/database/scripts/indexes.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_countries.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_teams.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_teamplayers.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_competitions.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_registeredteams.sql");
    std::vector<CPfCompetitions*> *competitions = daoFactory->getIPfCompetitionsDAO()->findCompetitions();
    std::vector<CPfCompetitions*>::iterator it;
    CDate date(31, 8, 2008, 17, 0, 0);
    CDataGenerator generator;
    for(it = competitions->begin(); it != competitions->end(); it++) {
        generator.generateCompetitionMatches(daoFactory, (*it), date);
    }
    daoFactory->executeScriptFile("data/database/scripts/inserts_gameoptions.sql");
    daoFactory->commit();

    CPfGameStates newGameState;
    newGameState.setSState(S_STATE_NEWGAME);
    newGameState.setSValue("true");
    daoFactory->getIPfGameStatesDAO()->insertReg(&newGameState);

    delete daoFactory;

    loadGameList();
    m_newGameEditbox->setText("");
}

void CScreenLoadGame::loadGame()
{
    CEGUI::ListboxItem* itm = m_gamesList->getFirstSelectedItem();
    int xGame = itm->getID();
    CGameEngine::getInstance()->loadGame(xGame);

    // Test if this game is a new game
    IPfGameStatesDAO *gameStateDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfGameStatesDAO();
    CPfGameStates *newGameState = gameStateDAO->findBySState(S_STATE_NEWGAME);
    if( newGameState->getSValue()=="true" ){
        CScreenManager::getInstance()->pushState(CScreenSelectTeam::getInstance());
    }else{
        CScreenManager::getInstance()->popState();
        CScreenManager::getInstance()->pushState(CScreenGame::getInstance());
    }
    delete newGameState;
}

void CScreenLoadGame::deleteGame()
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
}

void CScreenLoadGame::loadGameList()
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("MultiListSelectionBrush");

    m_gamesList->resetList();
    m_gamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);

    IPfGamesDAO*                        gamesDAO    = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    std::vector<CPfGames*>*             gamesList   = gamesDAO->findByXFkUser(CGameEngine::getInstance()->getCurrentUser()->getXUser());
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

bool CScreenLoadGame::handleDoubleClick(const CEGUI::EventArgs& e)
{
    if( m_gamesList->getFirstSelectedItem()!=NULL ){
        loadGame();
    }
    return true;
}

bool CScreenLoadGame::handleSelectChanged(const CEGUI::EventArgs& e)
{
    m_loadGameButton->setEnabled(m_gamesList->getFirstSelectedItem()!=NULL);
    m_deleteGameButton->setEnabled(m_gamesList->getFirstSelectedItem()!=NULL);

    return true;
}

bool CScreenLoadGame::handleTextChanged(const CEGUI::EventArgs& e)
{
    if( m_newGameEditbox->getText().compare("")!=0 ){
        m_newGameButton->setEnabled(true);
    }else{
        m_newGameButton->setEnabled(false);
    }
}
