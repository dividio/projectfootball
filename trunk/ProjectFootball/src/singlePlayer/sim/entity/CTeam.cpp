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

#include <boost/filesystem/operations.hpp>

#include "projectfootball_config.h"
#include "CTeam.h"

#include "CField.h"
#include "CReferee.h"
#include "CFootballPlayer.h"
#include "../CSimulationManager.h"
#include "../tactic/CFormation.h"
#include "../tactic/CStrategicPosition.h"
#include "../../db/bean/CPfTeams.h"
#include "../../db/bean/CPfTeamPlayers.h"

std::string CTeam::m_pCtorName = "CTeam_p_ctor";

extern std::string dataPath;

CTeam* CTeam::getTeam(CBaseGameEntity *team)
{
    return (CTeam*) team;
}

CTeam::CTeam(CSimulationManager *simulationManager, const CPfTeams *team, bool sideLeft)
{
    LOG_DEBUG("CTeam()");

    m_simulationManager = simulationManager;

    CLuaManager::getInstance()->runScript(CONCAT_PATH(dataPath, "scripts/team.lua"));
    m_team = new CPfTeams(*team);
    m_sideLeft = sideLeft;
    m_currentFormation = NULL;

}


CTeam::~CTeam()
{
    LOG_DEBUG("~CTeam()");
    delete m_stateMachine;
    delete m_team;
}


CSimulationManager* CTeam::getSimulationManager()
{
	return m_simulationManager;
}


void CTeam::setOpponentTeam(CTeam *team)
{
    m_opponentTeam = team;
}


void CTeam::setControllingPlayer(CFootballPlayer *player)
{
    m_controllingPlayer = player;
}


void CTeam::setPlayers(std::vector<CFootballPlayer*>* playersVector)
{
    m_players = playersVector;
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
    return m_players;
}


bool CTeam::handleMessage(const CMessage &msg)
{
    return m_stateMachine->handleMessage(msg);
}


void CTeam::update()
{
    std::vector<CFootballPlayer*>::iterator it;
    for(it = m_players->begin(); it!=m_players->end(); it++) {
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
    m_sideLeft = !m_sideLeft;
    int idLeft = m_currentFormation->getRightCornerKickPlayerId();
    int idRight = m_currentFormation->getLeftCornerKickPlayerId();
    m_currentFormation->setLeftCornerKickPlayerId(idLeft);
    m_currentFormation->setRightCornerKickPlayerId(idRight);

    idLeft = m_currentFormation->getRightTrowInPlayerId();
    idRight = m_currentFormation->getLeftTrowInPlayerId();
    m_currentFormation->setLeftTrowInPlayerId(idLeft);
    m_currentFormation->setRightTrowInPlayerId(idRight);

    std::vector<CFootballPlayer*>::iterator it;
    for(it = m_players->begin(); it!=m_players->end(); it++) {
        (*it)->changeSide();
    }
}

void CTeam::setNearestPlayerToBall(CFootballPlayer *player)
{
    m_nearestPlayerToBall = player;
}


CFootballPlayer* CTeam::getNearestPlayerToBall() const
{
    return m_nearestPlayerToBall;
}


CFootballPlayer* CTeam::getControllingPlayer() const
{
    return m_controllingPlayer;
}


int CTeam::getKickPlayerID() const
{
    int formationPos;
    int playerId;
    int aux;
    GameMode mode = m_simulationManager->getReferee()->getGameMode();
    switch(mode) {
        case KICK_OFF:
            formationPos = m_currentFormation->getKickOffPlayerId();
            playerId = m_players->at(formationPos)->getID();
            break;
        case KICK_IN:
            aux = (int)m_simulationManager->getBallPosition().z();
            if(aux < -25) {
                formationPos = m_currentFormation->getLeftTrowInPlayerId();
            } else if(aux > 25) {
                formationPos = m_currentFormation->getRightTrowInPlayerId();
            } else {
                formationPos = m_currentFormation->getKickInPlayerId();
            }
            playerId = m_players->at(formationPos)->getID();
            break;
        case CORNER_KICK:
            aux = (int)m_simulationManager->getBallPosition().z();
            if(aux < 0) {
                formationPos = m_currentFormation->getLeftCornerKickPlayerId();
            } else if(aux > 0) {
                formationPos = m_currentFormation->getRightCornerKickPlayerId();
            }
            playerId = m_players->at(formationPos)->getID();
            break;
        case GOAL_KICK:
            formationPos = m_currentFormation->getGoalKickPlayerId();
            playerId = m_players->at(formationPos)->getID();
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

void CTeam::setFormation(CFormation *formation)
{
	if(m_currentFormation != NULL) {
		FormationType currentType = m_currentFormation->getCurrentFormationType();
		m_currentFormation = formation;
		m_currentFormation->setCurrentFormationType(currentType);
	} else {
		m_currentFormation = formation;
	}
}

CStrategicPosition* CTeam::getPlayerStrategicPosition(int formationPos) const
{
	if(formationPos >= 0 && formationPos <= 11) {
		return m_currentFormation->getPlayerStrategicPosition(formationPos-1);
	} else {
		LOG_ERROR("Invalid formation position.");
	}
}


bool CTeam::isKickForUs() const
{
    bool us = false;
    if(m_simulationManager->getReferee()->getKickTeam()->getID() == getID()) {
        us = true;
    }
    return us;
}


bool CTeam::inControl() const
{
    bool control = false;
    if(m_controllingPlayer) {
        control = true;
    }
    return control;
}


bool CTeam::isNearestPlayerToBall(CFootballPlayer* player) const
{
    bool nearest = true;
    int id = player->getID();
    if(m_nearestPlayerToBall->getID() == id) {
        btVector3 ballPos = m_simulationManager->getBallPosition();
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
    int id = player->getID();
    if(m_nearestPlayerToBall->getID() == id) {
        nearest = true;
    }

    return nearest;
}


bool CTeam::isBallInOwnPenaltyArea() const
{
    bool isIn = false;
    btVector3 posBall = m_simulationManager->getBallPosition();
    if(m_sideLeft) {
        isIn = m_simulationManager->getField()->isInLeftArea(posBall);
    } else {
        isIn = m_simulationManager->getField()->isInRightArea(posBall);
    }
    return isIn;
}


bool CTeam::isBallInOpponentPenaltyArea() const
{
    bool isIn = false;
    btVector3 posBall = m_simulationManager->getBallPosition();
    if(m_sideLeft) {
        isIn = m_simulationManager->getField()->isInRightArea(posBall);
    } else {
        isIn = m_simulationManager->getField()->isInLeftArea(posBall);
    }
    return isIn;
}


bool CTeam::isSideLeft() const
{
    return m_sideLeft;
}

void CTeam::assignSide(bool side) {
	m_sideLeft = side;
    if(!m_sideLeft) {
        m_currentFormation->setRightCornerKickPlayerId(7);
        m_currentFormation->setLeftCornerKickPlayerId(6);
        m_currentFormation->setRightTrowInPlayerId(7);
        m_currentFormation->setLeftTrowInPlayerId(6);
    }
    m_stateMachine = new CStateMachine<CTeam>(this);
    m_stateMachine->setGlobalState("STm_Global");
    m_stateMachine->changeState("STm_BeforeStart");
}
