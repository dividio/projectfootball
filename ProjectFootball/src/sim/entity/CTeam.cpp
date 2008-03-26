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
#include "../db/dao/IPfTeamsDAO.h"
#include "../db/dao/IPfTeamPlayersDAO.h"
#include "../engine/CGameEngine.h"


char* CTeam::m_pCtorName = "CTeam_p_ctor";

CTeam* CTeam::getTeam(CBaseGameEntity *team)
{
    return (CTeam*) team;
}

CTeam::CTeam(int XTeam, bool sideLeft)
{
    CLog::getInstance()->debug("CTeam()");
    CLuaManager::getInstance()->runScript("data/scripts/team.lua");
    IDAOFactory *daoFactory = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory();
    IPfTeamsDAO *teamsDAO = daoFactory->getIPfTeamsDAO();
    IPfTeamPlayersDAO *teamPlayersDAO = daoFactory->getIPfTeamPlayersDAO();
    m_team = teamsDAO->findByXTeam(XTeam);
    std::vector<CPfTeamPlayers*> *playersVector = teamPlayersDAO->findActiveTeamPlayersByXFkTeam(XTeam);


    setFormations();
    if(!sideLeft) {
        m_currentFormation->setRightCornerKickPlayerId(7);
        m_currentFormation->setLeftCornerKickPlayerId(6);
        m_currentFormation->setRightTrowInPlayerId(7);
        m_currentFormation->setLeftTrowInPlayerId(6);
    }
    m_stateMachine = new CStateMachine<CTeam>(this);
    m_stateMachine->setGlobalState("STm_Global");
    m_stateMachine->changeState("STm_BeforeStart");

    CFootballPlayer *player = new CFootballPlayer(playersVector->at(0)->getXTepl(), 1, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/goalie.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(1)->getXTepl(), 2, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(2)->getXTepl(), 3, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(3)->getXTepl(), 4, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(4)->getXTepl(), 5, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(5)->getXTepl(), 6, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(6)->getXTepl(), 7, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(7)->getXTepl(), 8, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(8)->getXTepl(), 9, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(9)->getXTepl(), 10, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    player = new CFootballPlayer(playersVector->at(10)->getXTepl(), 11, this, sideLeft);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    m_players.push_back(player);

    teamPlayersDAO->freeVector(playersVector);
}


CTeam::~CTeam()
{
    CLog::getInstance()->debug("~CTeam()");
    // TODO
    while(!m_formations.empty()) {
        delete m_formations.back();
        m_formations.pop_back();
    }
    delete m_team;
}


void CTeam::setOpponentTeam(CTeam *team)
{
    m_opponentTeam = team;
}


CTeam* CTeam::getOpponentTeam()
{
    return m_opponentTeam;
}


const std::string& CTeam::getName()
{
    return m_team->getSTeam();
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


int CTeam::getXTeam()
{
    return m_team->getXTeam();
}


void CTeam::changeSide()
{
    int idLeft = m_currentFormation->getRightCornerKickPlayerId();
    int idRight = m_currentFormation->getLeftCornerKickPlayerId();
    m_currentFormation->setLeftCornerKickPlayerId(idLeft);
    m_currentFormation->setRightCornerKickPlayerId(idRight);

    idLeft = m_currentFormation->getRightTrowInPlayerId();
    idRight = m_currentFormation->getLeftTrowInPlayerId();
    m_currentFormation->setLeftTrowInPlayerId(idLeft);
    m_currentFormation->setRightTrowInPlayerId(idRight);

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


int CTeam::getKickPlayerID() const
{
    int formationPos;
    int playerId;
    int aux;
    CSimulationManager *sim = CStateMonitor::getInstance()->getSimulationManager();
    GameMode mode = sim->getReferee()->getGameMode();
    switch(mode) {
        case KICK_OFF:
            formationPos = m_currentFormation->getKickOffPlayerId();
            playerId = m_players[formationPos]->getID();
            break;
        case KICK_IN:
            aux = (int)sim->getBallPosition().z();
            if(aux < -25) {
                formationPos = m_currentFormation->getLeftTrowInPlayerId();
            } else if(aux > 25) {
                formationPos = m_currentFormation->getRightTrowInPlayerId();
            } else {
                formationPos = m_currentFormation->getKickInPlayerId();
            }
            playerId = m_players[formationPos]->getID();
            break;
        case CORNER_KICK:
            aux = (int)sim->getBallPosition().z();
            if(aux < 0) {
                formationPos = m_currentFormation->getLeftCornerKickPlayerId();
            } else if(aux > 0) {
                formationPos = m_currentFormation->getRightCornerKickPlayerId();
            }
            playerId = m_players[formationPos]->getID();
            break;
        case GOAL_KICK:
            formationPos = m_currentFormation->getGoalKickPlayerId();
            playerId = m_players[formationPos]->getID();
            break;
        default:
            playerId = m_nearestPlayerToBall->getID();
            break;
    }
    return playerId;
}


CFormation* CTeam::getCurrentFormation() const
{
    return m_currentFormation;
}


std::vector<CFormation*>* CTeam::getFormations()
{
    return &m_formations;
}


CStrategicPosition* CTeam::getPlayerStrategicPosition(int formationPos) const
{
    //TODO Verify formationPos
    return m_currentFormation->getPlayerStrategicPosition(formationPos-1);
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


void CTeam::setFormations()
{
    int i;
    btVector3 point;
    CFormation *formation = new CFormation("4-3-3");
    CStrategicPosition *pos;

    //Goalie
    pos = formation->getPlayerStrategicPosition(0);
    point.setValue(-54,0,0);
    pos->setInitialPosition(&point);
    point.setValue(-54,0,0);
    pos->setDefensivePosition(&point);
    point.setValue(-52,0,0);
    pos->setOffensivePosition(&point);

    //DF
    pos = formation->getPlayerStrategicPosition(1);
    point.setValue(-30,0,25);
    pos->setInitialPosition(&point);
    point.setValue(-30,0,25);
    pos->setDefensivePosition(&point);
    point.setValue(-10,0,25);
    pos->setOffensivePosition(&point);

    pos = formation->getPlayerStrategicPosition(2);
    point.setValue(-30,0,-25);
    pos->setInitialPosition(&point);
    point.setValue(-30,0,-25);
    pos->setDefensivePosition(&point);
    point.setValue(-10,0,-25);
    pos->setOffensivePosition(&point);

    pos = formation->getPlayerStrategicPosition(3);
    point.setValue(-30,0,5);
    pos->setInitialPosition(&point);
    point.setValue(-30,0,5);
    pos->setDefensivePosition(&point);
    point.setValue(-10,0,5);
    pos->setOffensivePosition(&point);

    pos = formation->getPlayerStrategicPosition(4);
    point.setValue(-30,0,-5);
    pos->setInitialPosition(&point);
    point.setValue(-30,0,-5);
    pos->setDefensivePosition(&point);
    point.setValue(-10,0,-5);
    pos->setOffensivePosition(&point);

    //MD

    pos = formation->getPlayerStrategicPosition(5);
    point.setValue(-20,0,0);
    pos->setInitialPosition(&point);
    point.setValue(-20,0,0);
    pos->setDefensivePosition(&point);
    point.setValue(0,0,0);
    pos->setOffensivePosition(&point);

    pos = formation->getPlayerStrategicPosition(6);
    point.setValue(-20,0,20);
    pos->setInitialPosition(&point);
    point.setValue(-20,0,20);
    pos->setDefensivePosition(&point);
    point.setValue(0,0,25);
    pos->setOffensivePosition(&point);

    pos = formation->getPlayerStrategicPosition(7);
    point.setValue(-20,0,-20);
    pos->setInitialPosition(&point);
    point.setValue(-20,0,-20);
    pos->setDefensivePosition(&point);
    point.setValue(0,0,-25);
    pos->setOffensivePosition(&point);

    //

    pos = formation->getPlayerStrategicPosition(8);
    point.setValue(-10,0,0);
    pos->setInitialPosition(&point);
    point.setValue(10,0,0);
    pos->setDefensivePosition(&point);
    point.setValue(30,0,0);
    pos->setOffensivePosition(&point);

    pos = formation->getPlayerStrategicPosition(9);
    point.setValue(-5,0,20);
    pos->setInitialPosition(&point);
    point.setValue(15,0,20);
    pos->setDefensivePosition(&point);
    point.setValue(25,0,20);
    pos->setOffensivePosition(&point);

    pos = formation->getPlayerStrategicPosition(10);
    point.setValue(-5,0,-20);
    pos->setInitialPosition(&point);
    point.setValue(15,0,-20);
    pos->setDefensivePosition(&point);
    point.setValue(25,0,-20);
    pos->setOffensivePosition(&point);

    formation->setKickOffPlayerId(8);
    formation->setKickInPlayerId(5);
    formation->setRightCornerKickPlayerId(6);
    formation->setLeftCornerKickPlayerId(7);
    formation->setRightTrowInPlayerId(6);
    formation->setLeftTrowInPlayerId(7);
    formation->setGoalKickPlayerId(0);

    m_formations.push_back(formation);
    m_currentFormation = formation;
}
