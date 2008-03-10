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

#include <stdlib.h>
#include <cmath>

#include "CSimulationManager.h"
#include "message/CMessageDispatcher.h"
#include "message/MessageTypes.h"
#include "entity/CField.h"
#include "entity/CEntityManager.h"
#include "../utils/CLog.h"
#include "../audio/CAudioSystem.h"
#include "../engine/option/CSystemOptionManager.h"



CSimulationManager::CSimulationManager()
{
    CLog::getInstance()->debug("CSimulationManager()");
    int hz = CSystemOptionManager::getInstance()->getIntOption("Simulation", "LogicFrequency", 30);
    m_logicTimer = new CTimer(hz);
    hz = CSystemOptionManager::getInstance()->getIntOption("Simulation", "PhysicsFrequency", 60);
    m_physicsTimer = new CTimer(hz);
    m_simWorld = new CSimulationWorld();

    CField *field = new CField();
    m_simWorld->addObject(field);

    m_referee = new CReferee();
    m_simWorld->addObject(m_referee);

    m_ball = new CBall();
    m_simWorld->addObject(m_ball);

    m_homeTeam = new CTeam("Lui TM", true);
    m_awayTeam = new CTeam("Aceitunas Pacheco", false);
    m_homeTeam->setOpponentTeam(m_awayTeam);
    m_awayTeam->setOpponentTeam(m_homeTeam);

    std::vector<CFootballPlayer*>::iterator it;
    std::vector<CFootballPlayer*>* players = m_homeTeam->getPlayers();
    for(it = players->begin(); it!=players->end(); it++) {
        m_simWorld->addObject((*it));
    }
    players = m_awayTeam->getPlayers();
    for(it = players->begin(); it!=players->end(); it++) {
        m_simWorld->addObject((*it));
    }
}


CSimulationManager::~CSimulationManager()
{
    CLog::getInstance()->debug("~CSimulationManager()");

    CMessageDispatcher::getInstance()->reset();
    CEntityManager::getInstance()->reset();
    if(m_simWorld != NULL) {
        delete m_simWorld;
    }
    if(m_logicTimer != NULL) {
        delete m_logicTimer;
    }
    if(m_physicsTimer != NULL) {
        delete m_physicsTimer;
    }
    if(m_homeTeam != NULL) {
        delete m_homeTeam;
    }
    if(m_awayTeam != NULL) {
        delete m_awayTeam;
    }
}


void CSimulationManager::update()
{
    if(m_logicTimer->nextTick()) {
        m_referee->update();
        m_homeTeam->update();
        m_awayTeam->update();
    }

    if(m_physicsTimer->nextTick()) {
        m_simWorld->update();
    }
    CMessageDispatcher::getInstance()->dispatchDelayedMessages();
}


CSimulationWorld* CSimulationManager::getSimulationWorld()
{
    return m_simWorld;
}


CReferee* CSimulationManager::getReferee()
{
    return m_referee;
}


CBall* CSimulationManager::getBall()
{
    return m_ball;
}


CTeam* CSimulationManager::getHomeTeam()
{
    return m_homeTeam;
}


CTeam* CSimulationManager::getAwayTeam()
{
    return m_awayTeam;
}


void CSimulationManager::changePlayersSide()
{
    m_homeTeam->changeSide();
    m_awayTeam->changeSide();
}


void CSimulationManager::startMatch()
{
    CMessageDispatcher::getInstance()->dispatchMsg(0, -1, m_referee->getID(), Msg_StartMatch, 0);
}


std::string* CSimulationManager::getHomeTeamName()
{
    return m_homeTeam->getName();
}


std::string* CSimulationManager::getAwayTeamName()
{
    return m_awayTeam->getName();
}


btVector3 CSimulationManager::getBallPosition() const
{
    return m_ball->getPosition();
}


void CSimulationManager::dash(CFootballPlayer *player, btVector3 power)
{
    btVector3 impulse;
    double maxDash = 10.0;
    btRigidBody *body = player->getBody();
    btVector3 currentVelocity = body->getLinearVelocity();
    btVector3 newVelocity = currentVelocity;
    if(player->canDoActions()) {
        newVelocity += power;
        truncateVector(&newVelocity, maxDash);
        //printf("Cycle: %d Player: %s Power: %f Mass: %f NewVelocity: %f\n", m_referee->getCycle(), player->getIdent().c_str(), power.length(), 1.0/body->getInvMass(), newVelocity.length());
        body->setLinearVelocity(newVelocity);
    }
}


void CSimulationManager::move(CFootballPlayer *player, int x, int z)
{
    if(m_referee->isMoveLegal()) {
        btRigidBody *body = player->getBody();
        body->clearForces();
        body->setLinearVelocity(btVector3(0,0,0));
        body->setAngularVelocity(btVector3(0,0,0));
        player->setPosition(x,0,z);
    }
}


void CSimulationManager::kick(CFootballPlayer *player, btVector3 power)
{
    btVector3 impulse;
    int maxBallVelocity = CSystemOptionManager::getInstance()->getIntOption("Simulation", "MaxBallVelocity", 25);
    int maxKickPower = CSystemOptionManager::getInstance()->getIntOption("Simulation", "MaxKickPower", 25);
    btRigidBody *ballBody = m_ball->getBody();
    btRigidBody *body = player->getBody();
    btVector3 currentVelocity = ballBody->getLinearVelocity();
    btVector3 newVelocity = currentVelocity;
    if(player->canKickBall(m_referee->getCycle()) && player->canDoActions()) {
        truncateVector(&power, maxKickPower);
        newVelocity += power;
        truncateVector(&newVelocity, maxBallVelocity);
        ballBody->setLinearVelocity(newVelocity);
        //m_referee->playerKickEvent(player);
        CMessageDispatcher::getInstance()->dispatchMsg(0, player->getID(), m_referee->getID(), Msg_TouchBall, 0);
        CAudioSystem::LOW_KICK->play();
    }
}


void CSimulationManager::turn(CFootballPlayer *player, int moment)
{
//    if(player->canDoActions()) {
//        btRigidBody *body = player->getBody();
//        body->setAngularVelocity(btVector3(0,moment,0));
//    }

//    double maxDash = 10.0;
//    btRigidBody *body = player->getBody();
//    btVector3 currentAngVelocity = body->getAngularVelocity();
//    btVector3 newAngVelocity = currentAngVelocity;
//    double cos = player->m_steeringBehavior->sideComponent();
//    double rad = acos(cos);
//    double rot = cos*(player->m_steeringBehavior->force().length());
//    if(     (currentAngVelocity.y() < 0 && rot < 0) ||
//            (currentAngVelocity.y() > 0 && rot > 0)) {
//        newAngVelocity = currentAngVelocity + btVector3(0,rot,0);
//    } else{
//        newAngVelocity = btVector3(0,rot,0);
//    }
//    truncateVector(&newAngVelocity, maxDash);
//    if(player->getID() == 11)
//        printf("Cycle: %d angle: %f  sideComponent(cos): %f  rot: %f\n", m_referee->getCycle(), rad*(360/(2*3.14)), cos, rot);
//    body->setAngularVelocity(newAngVelocity);


}


void CSimulationManager::truncateVector(btVector3 *v, double max)
{
    if (v->length() > max) {
        v->normalize();
        v->operator *=(max);
    }
}
