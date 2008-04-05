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
#include "../state/CStateMonitor.h"
#include "../audio/CAudioSystem.h"
#include "../engine/option/CSystemOptionManager.h"
#include "../db/dao/IPfMatchesDAO.h"
#include "../engine/CGameEngine.h"
#include "../engine/event/strategy/IGameEventStrategy.h"
#include "../engine/event/match/CStartMatchEvent.h"
#include "../engine/event/match/CEndMatchEvent.h"
#include "../engine/event/match/CGoalMatchEvent.h"



CSimulationManager::CSimulationManager(int xMatch)
{
    CLog::getInstance()->debug("CSimulationManager()");
    CSystemOptionManager* optionManager = CSystemOptionManager::getInstance();
    int hz = optionManager->getIntOption("Simulation", "LogicFrequency");
    m_logicTimer = new CTimer(hz);
    hz = optionManager->getIntOption("Simulation", "PhysicsFrequency");
    m_physicsTimer = new CTimer(hz);
    m_simWorld = new CSimulationWorld();

    m_field = new CField();
    m_simWorld->addObject(m_field);

    m_referee = new CReferee();
    m_simWorld->addObject(m_referee);

    m_ball = new CBall();
    m_simWorld->addObject(m_ball);

    IPfMatchesDAO *matchesDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfMatchesDAO();
    m_match = matchesDAO->findByXMatch(xMatch);

    m_homeTeam = new CTeam(m_match->getXFkTeamHome(), true);
    m_awayTeam = new CTeam(m_match->getXFkTeamAway(), false);
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

    while(!m_goalEvents.empty()) {
        delete m_goalEvents.back();
        m_goalEvents.pop_back();
    }
    delete m_match;
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


CField* CSimulationManager::getField()
{
    return m_field;
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


void CSimulationManager::goalMatchEvent(CTeam *teamScorer, CFootballPlayer *playerScorer, int minute, bool ownGoal)
{
    CGoalMatchEvent *event = new CGoalMatchEvent(m_match->getXMatch(), teamScorer->getXTeam(),
                                                 playerScorer->getXTeamPlayer(), minute, ownGoal);
    m_goalEvents.push_back(event);
    CStateMonitor::getInstance()->updateScore();
}


void CSimulationManager::endMatchEvent()
{
    IGameEventStrategy *eventStrategy = CGameEngine::getInstance()->getCurrentGame()->getIGameEventStrategy();
    CStartMatchEvent startMatchEvent(m_match->getXMatch());
    CEndMatchEvent endMatchEvent(m_match->getXMatch());
    eventStrategy->process(startMatchEvent);
    std::vector<CGoalMatchEvent*>::iterator it;
    for(it = m_goalEvents.begin(); it!=m_goalEvents.end(); it++) {
        eventStrategy->process(*(*it));
    }
    eventStrategy->process(endMatchEvent);
}


void CSimulationManager::changeFormationEvent(int pos)
{
    CPfTeams *team = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    int xTeam = team->getXTeam();
    if(xTeam == m_homeTeam->getXTeam()) {
        m_homeTeam->changeFormation(pos);
    } else if(xTeam == m_awayTeam->getXTeam()) {
        m_awayTeam->changeFormation(pos);
    } else {
        CLog::getInstance()->error("Can't switch formation, team %d is not playing the match.", xTeam);
    }
}


const std::string& CSimulationManager::getHomeTeamName()
{
    return m_homeTeam->getName();
}


const std::string& CSimulationManager::getAwayTeamName()
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
    CSystemOptionManager* optionManager = CSystemOptionManager::getInstance();
    int maxBallVelocity = optionManager->getIntOption("Simulation", "MaxBallVelocity");
    int maxKickPower = optionManager->getIntOption("Simulation", "MaxKickPower");
    btRigidBody *ballBody = m_ball->getBody();
    btRigidBody *body = player->getBody();
    btVector3 velocity;
    btVector3 direction = power.normalized();
    direction = direction / 4;
    if(player->canKickBall(m_referee->getCycle()) && player->canDoActions()) {
        truncateVector(&power, maxKickPower);
        ballBody->applyImpulse(power, -direction);
        velocity = ballBody->getLinearVelocity();
        truncateVector(&velocity, maxBallVelocity);
        ballBody->setLinearVelocity(velocity);
        CMessageDispatcher::getInstance()->dispatchMsg(0, player->getID(), m_referee->getID(), Msg_TouchBall, 0);
        CAudioSystem::LOW_KICK->play();
    }
}


void CSimulationManager::truncateVector(btVector3 *v, double max)
{
    if (v->length() > max) {
        v->normalize();
        v->operator *=(max);
    }
}
