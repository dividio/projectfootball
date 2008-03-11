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

#include "CGameState.h"
#include "CGameEngine.h"
#include "../db/CDAOAbstractFactory.h"
#include "event/strategy/CSingleMatchEventStrategy.h"

CGameState::CGameState(int xGame)
{
    IPfGamesDAO *gamesDAO   = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    m_game                  = gamesDAO->findByXGame(xGame);
    m_daoFactory            = CDAOAbstractFactory::getIDAOFactory(m_game->getSDriverName(), m_game->getSConnectionString());
    m_eventStrategy         = new CSingleMatchEventStrategy();
    m_reportRegister        = new CGameReportRegister();
    m_optionManager         = new CGameOptionManager(m_daoFactory->getIPfGameOptionsDAO());
    setGameOptionsDefaultValues();

    m_daoFactory->beginTransaction();
}

CGameState::~CGameState()
{
    m_daoFactory->rollback();

    delete m_optionManager;
    delete m_reportRegister;
    delete m_eventStrategy;
    delete m_daoFactory;
    delete m_game;
}

void CGameState::save()
{
    CDate nowDate;
    m_game->setDLastSaved(nowDate);
    IPfGamesDAO *gamesDAO = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    gamesDAO->updateReg(m_game);

    m_daoFactory->commit();
    m_daoFactory->beginTransaction();
}

IDAOFactory* CGameState::getIDAOFactory()
{
    return m_daoFactory;
}

IGameEventStrategy* CGameState::getIGameEventStrategy()
{
    return m_eventStrategy;
}

CGameReportRegister* CGameState::getCGameReportRegister()
{
    return m_reportRegister;
}

CGameOptionManager* CGameState::getCGameOptionManager()
{
    return m_optionManager;
}

void CGameState::setGameOptionsDefaultValues()
{
    // nothing at the moment
}
