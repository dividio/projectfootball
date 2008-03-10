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


#include "CTeam.h"
#include "CFootballPlayer.h"
#include "../../state/CStateMonitor.h"
#include "../CSimulationManager.h"


char* CTeam::m_pCtorName = "CTeam_p_ctor";

CTeam* CTeam::getTeam(CBaseGameEntity *team)
{
    return (CTeam*) team;
}

CTeam::CTeam(std::string name, bool sideLeft)
{
    CLog::getInstance()->debug("CTeam()");
    CLuaManager::getInstance()->runScript("data/scripts/team.lua");
    m_name = name;
    m_stateMachine = new CStateMachine<CTeam>(this);
    m_stateMachine->setGlobalState("STm_Global");
    m_stateMachine->changeState("STm_BeforeStart");

    CFootballPlayer *player = new CFootballPlayer(1, this, -54, 0, 0, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(2, this, -30, 0, 25, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(3, this, -30, 0, -25, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(4, this, -35, 0, 5, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(5, this, -35, 0, -5, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(6, this, -20, 0, 0, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(7, this, -20, 0, 20, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(8, this, -20, 0, -20, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(9, this, -10, 0, 0, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(10, this, -5, 0, 20, sideLeft);
    m_players.push_back(player);

    player = new CFootballPlayer(11, this, -5, 0, -20, sideLeft);
    m_players.push_back(player);
}


CTeam::~CTeam()
{
    CLog::getInstance()->debug("~CTeam()");
    // TODO
}


void CTeam::setOpponentTeam(CTeam *team)
{
    m_opponentTeam = team;
}


CTeam* CTeam::getOpponentTeam()
{
    return m_opponentTeam;
}


std::string* CTeam::getName()
{
    return &m_name;
}


std::vector<CFootballPlayer*>* CTeam::getPlayers()
{
    return &m_players;
}


bool CTeam::handleMessage(const CMessage &msg)
{
    return m_stateMachine->handleMessage(msg);
}


void CTeam::update()
{
    setNearestPlayersToBall();
    std::vector<CFootballPlayer*>::iterator it;
    for(it = m_players.begin(); it!=m_players.end(); it++) {
        (*it)->update();
    }
}


CStateMachine<CTeam>* CTeam::getFSM()
{
    return m_stateMachine;
}


void CTeam::changeSide()
{
    std::vector<CFootballPlayer*>::iterator it;
    for(it = m_players.begin(); it!=m_players.end(); it++) {
        (*it)->changeSide();
    }
}


void CTeam::setNearestPlayersToBall()
{
    CSimulationManager *sim = CStateMonitor::getInstance()->getSimulationManager();
    btScalar minDist = 1000;
    btScalar auxDist;
    btVector3 playerPos;
    btVector3 ballPos = sim->getBallPosition();
    std::vector<CFootballPlayer*>::iterator it;
    for(it = m_players.begin(); it!=m_players.end(); it++) {
        playerPos = (*it)->getPosition();
        auxDist = playerPos.distance(ballPos);
        if(auxDist < minDist) {
            minDist = auxDist;
            m_nearestPlayerToBall = (*it);
        }
    }
}


CFootballPlayer* CTeam::getNearestPlayerToBall() const
{
    return m_nearestPlayerToBall;
}


bool CTeam::isKickForUs() const
{
    bool us = false;
    CSimulationManager *sim = CStateMonitor::getInstance()->getSimulationManager();
    if(sim->getReferee()->getKickTeam()->getID() == getID()) {
        us = true;
    }
    return us;
}

bool CTeam::isNearestPlayerToBall(CFootballPlayer* player) const
{
    bool nearest = true;
    std::string id = player->getIdent();
    if(m_nearestPlayerToBall->getIdent() == id) {
        CSimulationManager *sim = CStateMonitor::getInstance()->getSimulationManager();
        btVector3 ballPos = sim->getBallPosition();
        btVector3 playerPos = player->getPosition();
        btVector3 opponentPos = m_opponentTeam->getNearestPlayerToBall()->getPosition();
        btScalar playerDist = playerPos.distance(ballPos);
        btScalar opponentDist = opponentPos.distance(ballPos);
        if(playerDist > opponentDist) {
            nearest = false;
        }
    } else {
        nearest = false;
    }

    return nearest;
}


bool CTeam::isNearestTeamMatePlayerToBall(CFootballPlayer* player) const
{
    bool nearest = false;
    std::string id = player->getIdent();
    if(m_nearestPlayerToBall->getIdent() == id) {
        nearest = true;
    }

    return nearest;
}
