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

#include <iostream>
#include <fstream>
#include <stdio.h>

#include "CSinglePlayerGameState.h"
#include "CGameEngine.h"
#include "event/strategy/CSingleMatchEventStrategy.h"
#include "../utils/CLog.h"

CSinglePlayerGameState::CSinglePlayerGameState(int xGame)
{
    IPfGamesDAO *gamesDAO   = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    m_game                  = gamesDAO->findByXGame(xGame);

    m_database_filepath     = m_game->getSConnectionString();
    m_database_tmp_filepath = m_game->getSConnectionString();
    m_database_tmp_filepath+= ".tmp";
    copyFile(m_database_filepath, m_database_tmp_filepath);
    m_daoFactory            = new CDAOFactorySQLite(m_database_tmp_filepath);

    m_eventStrategy         = new CSingleMatchEventStrategy();
    m_reportRegister        = new CGameReportRegister();
    m_optionManager         = new CGameOptionManager(m_daoFactory->getIPfGameOptionsDAO());
    setGameOptionsDefaultValues();
}

CSinglePlayerGameState::~CSinglePlayerGameState()
{
    delete m_optionManager;
    delete m_reportRegister;
    delete m_eventStrategy;
    delete m_daoFactory;
    delete m_game;

    remove(m_database_tmp_filepath.c_str());
}

void CSinglePlayerGameState::save()
{
    CDate nowDate;
    m_game->setDLastSaved(nowDate);
    IPfGamesDAO *gamesDAO = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    gamesDAO->updateReg(m_game);

    m_daoFactory->closeSQLite();
    copyFile(m_database_tmp_filepath, m_database_filepath);
    m_daoFactory->openSQLite(m_database_tmp_filepath);
}

IDAOFactory* CSinglePlayerGameState::getIDAOFactory()
{
    return m_daoFactory;
}

IGameEventStrategy* CSinglePlayerGameState::getIGameEventStrategy()
{
    return m_eventStrategy;
}

CGameReportRegister* CSinglePlayerGameState::getCGameReportRegister()
{
    return m_reportRegister;
}

CGameOptionManager* CSinglePlayerGameState::getCGameOptionManager()
{
    return m_optionManager;
}

void CSinglePlayerGameState::setGameOptionsDefaultValues()
{
    // nothing at the moment
}

void CSinglePlayerGameState::copyFile(const std::string &origin, const std::string &destination)
{
    std::ifstream  is(origin.c_str(),       std::ifstream::in|std::ifstream::binary);
    std::ofstream  os(destination.c_str(),  std::ofstream::out|std::ofstream::binary|std::ofstream::trunc);
    if( !is.is_open() || !os.is_open() ){
        CLog::getInstance()->exception("[CSinglePlayerGameState::copyFile] Error opening the files: is:'%s' os:'%s'", origin.c_str(), destination.c_str());
    }

    char buffer[4096]; // 4KBytes
    int  nBytes;
    while( !is.eof() ){
        is.read(buffer, sizeof(buffer));
        nBytes = is.gcount();
        os.write(buffer, nBytes);
    }

    is.close();
    os.close();
}
