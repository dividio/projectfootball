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

#include "CSimulationManager.h"

#include <stdlib.h>
#include <cmath>

#include "CSimulationWorld.h"
#include "message/CMessageDispatcher.h"
#include "message/MessageTypes.h"
#include "entity/CEntityManager.h"
#include "entity/CFootballPlayer.h"
#include "entity/CReferee.h"
#include "entity/CTeam.h"
#include "entity/CField.h"
#include "entity/CBall.h"

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfMatches.h"
#include "../db/bean/CPfTeams.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../event/match/CStartMatchEvent.h"
#include "../event/match/CEndMatchEvent.h"
#include "../event/match/CGoalMatchEvent.h"
#include "../option/CSinglePlayerOptionManager.h"
#include "../wh/CSimulatorWindowHandler.h"

#include "../../audio/CAudioSystem.h"
#include "../../bullet/LinearMath/btVector3.h"
#include "../../bullet/BulletDynamics/Dynamics/btRigidBody.h"
#include "../../engine/CGameEngine.h"
#include "../../engine/event/CEventManager.h"
#include "../../engine/option/CSystemOptionManager.h"
#include "../../engine/utils/CTimer.h"
#include "../../utils/CLog.h"
#include "../../utils/CDate.h"


CSimulationManager::CSimulationManager(int xMatch, CSinglePlayerGame &game, CSimulatorWindowHandler &simulatorWH) :
	m_goalEvents(),
	m_game(game),
	m_simulatorWindowHandler(simulatorWH)
{
    LOG_DEBUG("CSimulationManager()");

    CSystemOptionManager* optionManager = CSystemOptionManager::getInstance();

    m_maxBallVelocity           = optionManager->getSimulationMaxBallVelocity();
    m_maxPlayerVelocity         = optionManager->getSimulationMaxPlayerVelocity();
    m_maxKickPower              = optionManager->getSimulationMaxKickPower();
    m_maxKickDistance           = optionManager->getSimulationMaxKickDistance();
    m_nearestPlayerToBallCycles = optionManager->getSimulationNearestPlayerToBallCycles();
    m_nearestPlayerToBallTime   = optionManager->getSimulationNearestPlayerToBallTime() * 0.01;
    m_logicTimer                = new CTimer(optionManager->getSimulationLogicFrequency());
    m_physicsTimer              = new CTimer(optionManager->getSimulationPhysicsFrequency());

    m_simWorld = new CSimulationWorld();

    m_field = new CField();
    m_simWorld->addObject(m_field);

    m_referee = new CReferee(this);
    m_simWorld->addObject(m_referee);

    m_ball = new CBall();
    m_simWorld->addObject(m_ball);

    IPfMatchesDAO *matchesDAO = m_game.getIDAOFactory()->getIPfMatchesDAO();
    m_match = matchesDAO->findByXMatch(xMatch);

    // Home team
    CPfTeams *homeTeam = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_match->getXFkTeamHome());
    std::vector<CPfTeamPlayers*> *homePlayersVector = m_game.getIDAOFactory()->getIPfTeamPlayersDAO()->findLineUpByXFkTeam(homeTeam->getXTeam());
    m_homeTeam = new CTeam(this, homeTeam, homePlayersVector, true);
    m_game.getIDAOFactory()->getIPfTeamPlayersDAO()->freeVector(homePlayersVector);
    delete homeTeam;

    // Away team
    CPfTeams *awayTeam = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_match->getXFkTeamAway());
    std::vector<CPfTeamPlayers*> *awayPlayersVector = m_game.getIDAOFactory()->getIPfTeamPlayersDAO()->findLineUpByXFkTeam(awayTeam->getXTeam());
    m_awayTeam = new CTeam(this, awayTeam, awayPlayersVector, false);
    m_game.getIDAOFactory()->getIPfTeamPlayersDAO()->freeVector(awayPlayersVector);
    delete awayTeam;

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
    srand(time(NULL));
}

CSimulationManager::~CSimulationManager()
{
    LOG_DEBUG("~CSimulationManager()");

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

    delete m_match;
}

void CSimulationManager::update()
{
    if(m_logicTimer->nextTick()) {
        calculateNearestPlayersToBall();
        m_referee->update();
        m_homeTeam->update();
        m_awayTeam->update();
    }

    if(m_physicsTimer->nextTick()) {
        m_simWorld->update();
    }
    CMessageDispatcher::getInstance()->dispatchDelayedMessages();
}

void CSimulationManager::addToLog(const std::string &text)
{
	m_simulatorWindowHandler.addToLog(text);
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
    CDate goalDate(m_match->getDMatch());
    goalDate.setMin(goalDate.getMin()+minute);

    m_goalEvents.push_back(new CGoalMatchEvent(goalDate, m_match->getXMatch(), teamScorer->getXTeam(), playerScorer->getXTeamPlayer(), minute, ownGoal));
    m_simulatorWindowHandler.updateScore();
}

void CSimulationManager::endMatchEvent()
{
	CEventManager	*eventMngr	= CGameEngine::getInstance()->getEventManager();

    // Start match event
	eventMngr->addEvent(new CStartMatchEvent(m_match->getDMatch(), m_match->getXMatch()));

    // Goals events
    std::vector<CGoalMatchEvent*>::iterator it;
    for(it = m_goalEvents.begin(); it!=m_goalEvents.end(); it++) {
    	eventMngr->addEvent((*it));
    }

    // End match event
    CDate endDate(m_match->getDMatch());
    endDate.setMin(endDate.getMin()+90);
    eventMngr->addEvent(new CEndMatchEvent(endDate, m_match->getXMatch()));

    // Send notitify to simulator screen
    m_simulatorWindowHandler.endMatchEvent();
}

void CSimulationManager::changeFormationEvent(int pos)
{
    CPfTeams *team = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
    int xTeam = team->getXTeam();
    if(xTeam == m_homeTeam->getXTeam()) {
        m_homeTeam->changeFormation(pos);
    } else if(xTeam == m_awayTeam->getXTeam()) {
        m_awayTeam->changeFormation(pos);
    } else {
        LOG_ERROR("Can't switch formation, team %d is not playing the match.", xTeam);
    }
    delete team;
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
    if(player->canDoActions()) {
        btVector3 impulse;
        double maxPlayerDash = player->getMaxVelocity();
        btRigidBody *body = player->getBody();
        btVector3 currentVelocity = body->getLinearVelocity();
        btVector3 newVelocity = currentVelocity;
        newVelocity += power;
        if(maxPlayerDash > m_maxPlayerVelocity) {
            truncateVector(&newVelocity, m_maxPlayerVelocity);
        } else {
            truncateVector(&newVelocity, maxPlayerDash);
        }
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
    if(player->canKickBall(m_referee->getCycle()) && player->canDoActions()) {
        btVector3 impulse;
        double maxPlayerKickPower = player->getMaxKickPower();
        btRigidBody *ballBody = m_ball->getBody();
        btVector3 velocity;

        if (maxPlayerKickPower > m_maxKickPower) {
            truncateVector(&power, m_maxKickPower);
        } else {
            truncateVector(&power, maxPlayerKickPower);
        }
        ballBody->applyCentralImpulse(power);
        velocity = ballBody->getLinearVelocity();
        truncateVector(&velocity, m_maxBallVelocity);
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

void CSimulationManager::calculateNearestPlayersToBall()
{
    std::vector<CFootballPlayer*> *homePlayers = getHomeTeam()->getPlayers();
    std::vector<CFootballPlayer*> *awayPlayers = getAwayTeam()->getPlayers();

    int cycle = 0;
    double time = 0.0;
    bool found = false;
    btScalar minHomeDist = 1000;
    btScalar minAwayDist = 1000;
    btScalar auxDist;
    std::vector<CFootballPlayer*>::iterator it;

    CFootballPlayer* nearestPlayer = NULL;
    CFootballPlayer* nearestHomePlayer = NULL;
    CFootballPlayer* nearestAwayPlayer = NULL;

    while(cycle < m_nearestPlayerToBallCycles && !found) {
        btVector3 ballPos = m_ball->futurePosition(time);

        for(it = homePlayers->begin(); it!=homePlayers->end(); it++) {
            btVector3 playerPos = (*it)->getFuturePlayerPosition(time, ballPos);
            auxDist = playerPos.distance(ballPos);
            if(auxDist < minHomeDist) {
                minHomeDist = auxDist;
                nearestHomePlayer = (*it);
            }
        }

        for(it = awayPlayers->begin(); it!=awayPlayers->end(); it++) {
            btVector3 playerPos = (*it)->getFuturePlayerPosition(time, ballPos);
            auxDist = playerPos.distance(ballPos);
            if(auxDist < minAwayDist) {
                minAwayDist = auxDist;
                nearestAwayPlayer = (*it);
            }
        }

        if(minHomeDist < minAwayDist) {
            nearestPlayer = nearestHomePlayer;
            if(minHomeDist < m_maxKickDistance) {
                found = true;
            }
        } else {
            nearestPlayer = nearestAwayPlayer;
            if(minAwayDist < m_maxKickDistance) {
                found = true;
            }
        }

        cycle++;
        time += m_nearestPlayerToBallTime;
    }
    getHomeTeam()->setNearestPlayerToBall(nearestHomePlayer);
    getAwayTeam()->setNearestPlayerToBall(nearestAwayPlayer);
}
