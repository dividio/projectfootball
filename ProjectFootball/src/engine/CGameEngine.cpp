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

#include <time.h>
#include <stdlib.h>

#include "CGameEngine.h"
#include "CGameStateAbstractFactory.h"
#include "option/CSystemOptionManager.h"
#include "../db/sqlite/dao/factory/CDAOFactorySQLite.h"
#include "../utils/CLog.h"

CGameEngine::CGameEngine()
{
    m_gameState = NULL;

    const char *masterDatabasePath = CSystemOptionManager::getInstance()->getStringOption("General", "MasterDatabasePath");
    m_masterDatabase = new CMasterDAOFactorySQLite(masterDatabasePath);

    m_user = NULL;
    setUser(DEFAULT_USER);
}

CGameEngine::~CGameEngine()
{
    if( m_gameState!=NULL ){
        unloadCurrentGame();
    }

    if( m_user!=NULL ){
        delete m_user;
    }

    delete m_masterDatabase;
}

CGameEngine* CGameEngine::getInstance()
{
    static CGameEngine instance;
    return &instance;
}

void CGameEngine::setUser(int xUser)
{
    if( m_user!=NULL ){
        delete m_user;
        m_user = NULL;
    }
    m_user = m_masterDatabase->getIPfUsersDAO()->findByXUser(xUser);
}

const CPfUsers* CGameEngine::getCurrentUser()
{
    return m_user;
}

IGameState* CGameEngine::getCurrentGame()
{
    return m_gameState;
}

IMasterDAOFactory* CGameEngine::getCMasterDAOFactory()
{
    return m_masterDatabase;
}

void CGameEngine::newSinglePlayerGame(const std::string &gameName)
{
    if( m_user==NULL || m_user->getXUser_str()=="" ){
        CLog::getInstance()->exception("[CGameEngine::newSinglePlayerGame] User not defined");
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
    game.setSGameName(gameName);
    game.setSGameType(S_GAME_TYPE_SINGLEPLAYER);
    game.setXFkUser(m_user->getXUser());
    m_masterDatabase->getIPfGamesDAO()->insertReg(&game);

    CDAOFactorySQLite *daoFactory = new CDAOFactorySQLite(filename);
    daoFactory->executeScriptFile("data/database/scripts/tables.sql");
    daoFactory->executeScriptFile("data/database/scripts/view_ranking.sql");
    daoFactory->executeScriptFile("data/database/scripts/indexes.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts.sql");

    CPfGameStates newGameState;
    newGameState.setSState(S_STATE_NEWGAME);
    newGameState.setSValue("true");
    daoFactory->getIPfGameStatesDAO()->insertReg(&newGameState);

    delete daoFactory;
}

void CGameEngine::loadGame(int xGame)
{
    unloadCurrentGame();
    m_gameState = CGameStateAbstractFactory::getIGameState(xGame);
}

void CGameEngine::saveCurrentGame()
{
    if(m_gameState!=NULL){
        m_gameState->save();
    }
}

void CGameEngine::unloadCurrentGame()
{
    if(m_gameState!=NULL){
        delete m_gameState;
        m_gameState = NULL;
    }
}
