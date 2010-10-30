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
#include "tactic/CFormation.h"

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

    int sideLeft = true;
    std::string currentTimestamp = m_game.getCurrentTime().getTimestamp();

    // Home team
    CPfTeams *homeTeam = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_match->getXFkTeamHome());
    m_homeTeam = new CTeam(this, homeTeam, sideLeft);
    CPfFormations *formation = m_game.getIDAOFactory()->getIPfFormationsDAO()->findActiveByXTeam(m_homeTeam->getXTeam(), currentTimestamp);
    m_homeFormation = loadFormation(formation);
    m_homeTeam->setFormation(m_homeFormation);
    m_homeTeamPlayers = loadTeamPlayers(m_homeTeam);
    m_homeTeam->setPlayers(m_homeTeamPlayers);
    m_homeTeam->assignSide(sideLeft);
    delete homeTeam;
    delete formation;

    // Away team
    CPfTeams *awayTeam = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_match->getXFkTeamAway());
    m_awayTeam = new CTeam(this, awayTeam, !sideLeft);
    formation = m_game.getIDAOFactory()->getIPfFormationsDAO()->findActiveByXTeam(m_awayTeam->getXTeam(), currentTimestamp);
    m_awayFormation = loadFormation(formation);
    m_awayTeam->setFormation(m_awayFormation);
    m_awayTeamPlayers = loadTeamPlayers(m_awayTeam);
    m_awayTeam->setPlayers(m_awayTeamPlayers);
    m_awayTeam->assignSide(!sideLeft);
    delete awayTeam;
    delete formation;

    m_homeTeam->setOpponentTeam(m_awayTeam);
    m_awayTeam->setOpponentTeam(m_homeTeam);

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
        delete m_homeFormation;

    }
    if(m_awayTeam != NULL) {
        delete m_awayTeam;
        delete m_awayFormation;
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
    	CPfFormations *formation = m_game.getIDAOFactory()->getIPfFormationsDAO()->findByXFormation(pos);
    	CFormation *aux = m_homeFormation;
    	m_homeFormation = loadFormation(formation);
        m_homeTeam->setFormation(m_homeFormation);
        delete formation;
        delete aux;
    } else if(xTeam == m_awayTeam->getXTeam()) {
    	CPfFormations *formation = m_game.getIDAOFactory()->getIPfFormationsDAO()->findByXFormation(pos);
    	CFormation *aux = m_awayFormation;
    	m_awayFormation = loadFormation(formation);
        m_awayTeam->setFormation(m_awayFormation);
        delete formation;
        delete aux;
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

int CSimulationManager::getMatchDuration() const
{
    return m_game.getOptionManager()->getMatchDuration();
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
        CAudioSystem::getInstance()->lowKick()->play();
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

std::vector<CFootballPlayer*>* CSimulationManager::loadTeamPlayers(CTeam *team)
{
	int xTeam = team->getXTeam();
	std::string currentTimestamp = m_game.getCurrentTime().getTimestamp();
	std::vector<CPfTeamPlayers*> *playersVector = m_game.getIDAOFactory()->getIPfTeamPlayersDAO()->findLineUpByXFkTeam(xTeam, currentTimestamp);

	std::vector<CFootballPlayer*>* teamPlayers = new std::vector<CFootballPlayer*>();

    // TODO: Initialize football players on a loop
    CFootballPlayer *player = new CFootballPlayer(this, playersVector->at(0), 1, team);
    CLuaManager::getInstance()->runScript("data/scripts/goalie.lua");
    player->getFSM()->setGlobalState("SGoalie_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(1), 2, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(2), 3, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(3), 4, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(4), 5, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(5), 6, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(6), 7, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(7), 8, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(8), 9, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(9), 10, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(this, playersVector->at(10), 11, team);
    CLuaManager::getInstance()->runScript("data/scripts/player.lua");
    player->getFSM()->setGlobalState("SPl_Global");
    teamPlayers->push_back(player);
    m_simWorld->addObject(player);


	m_game.getIDAOFactory()->getIPfTeamPlayersDAO()->freeVector(playersVector);

	return teamPlayers;
}


CFormation* CSimulationManager::loadFormation(CPfFormations *formation)
{

	CFormation *teamFormation = new CFormation(formation->getSName().c_str());

	btVector3 point;
	btVector3 topLeft, bottomRight;
	CStrategicPosition *pos;
	std::vector<CPfStrategicPositions*> *positions = m_game.getIDAOFactory()->getIPfStrategicPositionsDAO()->findByXFkFormation(formation->getXFormation());

	std::vector<CPfStrategicPositions*>::iterator it;
	for(it = positions->begin(); it != positions->end(); it++) {
		pos = teamFormation->getPlayerStrategicPosition((*it)->getNLineupOrder() - 1);

		point.setValue((*it)->getNInitialPosX(),0,(*it)->getNInitialPosZ());
		pos->setInitialPosition(&point);
		point.setValue((*it)->getNDefensivePosX(),0,(*it)->getNDefensivePosZ());
		pos->setDefensivePosition(&point);
		point.setValue((*it)->getNOffensivePosX(),0,(*it)->getNOffensivePosZ());
		pos->setOffensivePosition(&point);

		topLeft.setValue((*it)->getNTopLeftAreaX(),0,(*it)->getNTopLeftAreaZ());
		bottomRight.setValue((*it)->getNBottomRightAreaX(),0,(*it)->getNBottomRightAreaZ());
		pos->setPlayingArea(&topLeft, &bottomRight);

		pos->setAttractionX((*it)->getNAttractionX());
		pos->setAttractionZ((*it)->getNAttractionZ());

	}
	//TODO make this in tactics?
	if(formation->getXFormation() == 1) {
		teamFormation->setKickOffPlayerId(10);
		teamFormation->setKickInPlayerId(5);
		teamFormation->setRightCornerKickPlayerId(6);
		teamFormation->setLeftCornerKickPlayerId(7);
		teamFormation->setRightTrowInPlayerId(6);
		teamFormation->setLeftTrowInPlayerId(7);
		teamFormation->setGoalKickPlayerId(0);
	} else {
		teamFormation->setKickOffPlayerId(8);
		teamFormation->setKickInPlayerId(5);
		teamFormation->setRightCornerKickPlayerId(6);
		teamFormation->setLeftCornerKickPlayerId(7);
		teamFormation->setRightTrowInPlayerId(6);
		teamFormation->setLeftTrowInPlayerId(7);
		teamFormation->setGoalKickPlayerId(0);
	}

	m_game.getIDAOFactory()->getIPfStrategicPositionsDAO()->freeVector(positions);

	return teamFormation;
}
