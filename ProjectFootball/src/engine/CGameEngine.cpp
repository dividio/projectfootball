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

#include "option/CSystemOptionManager.h"
#include "CGameEngine.h"

#include "../db/sqlite/dao/factory/CDAOFactorySQLite.h"

CGameEngine::CGameEngine()
{
    m_gameState = NULL;

    const char *masterDatabasePath = CSystemOptionManager::getInstance()->getStringOption("General", "MasterDatabasePath", "data/database/master.sql3");
    m_masterDatabase = new CMasterDAOFactorySQLite(masterDatabasePath);
}

CGameEngine::~CGameEngine()
{
    if( m_gameState!=NULL ){
        unloadCurrentGame();
    }

    delete m_masterDatabase;
}

CGameEngine* CGameEngine::getInstance()
{
    static CGameEngine instance;
    return &instance;
}

CGameState* CGameEngine::getCurrentGame()
{
    return m_gameState;
}

CMasterDAOFactorySQLite* CGameEngine::getCMasterDAOFactory()
{
    return m_masterDatabase;
}

void CGameEngine::newGame(int xFkUser, const std::string &gameName)
{
    const char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string filename = "data/database/";

    srand(time(NULL));
    for( int i=0; i<8; i++ ){
        filename += str[rand()%52];
    }
    filename += ".sql3";

    CPfGames game;
    game.setSDriverName("SQLite");
    game.setSConnectionString(filename);
    game.setSGameName(gameName);
    game.setXFkUser(xFkUser);
    m_masterDatabase->getIPfGamesDAO()->insertReg(&game);

    CDAOFactorySQLite *daoFactory = new CDAOFactorySQLite(filename);
    daoFactory->createSchema();
    delete daoFactory;
}

void CGameEngine::loadGame(const std::string &xGame)
{
    unloadCurrentGame();
    m_gameState = new CGameState(xGame);
}

void CGameEngine::saveGame()
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
