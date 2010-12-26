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

#include "CReferee.h"

#include <libintl.h>

#include "CFootballPlayer.h"
#include "CTeam.h"
#include "../../../bullet/btBulletDynamicsCommon.h"
#include "../CSimulationManager.h"
#include "../message/MessageTypes.h"
#include "../fsm/CStateMachine.h"
#include "../../wh/CSimulatorWindowHandler.h"
#include "../../../utils/CLog.h"
#include "../../../engine/option/CSystemOptionManager.h"


std::string CReferee::m_pCtorName = "CReferee_p_ctor";


CReferee::CReferee(CSimulationManager *simulationManager)
: CMovingEntity()
{
	m_simulationManager = simulationManager;
	Ogre::SceneManager *scnMgr = Ogre::Root::getSingletonPtr()->getSceneManager(SIMULATION_SCENE_MANAGER_NODE_NAME);

	LOG_DEBUG("CReferee()");
    CLuaManager::getInstance()->runScript("data/scripts/referee.lua");
    m_stateMachine = new CStateMachine<CReferee>(this);
    m_stateMachine->setGlobalState("SRf_Global");
    m_stateMachine->changeState("SRf_BeforeStart");
    m_homeScore = 0;
    m_awayScore = 0;
    m_kickPosition = new btVector3(0,0,0);
    m_homeSideLeft = true;
    m_matchDuration = m_simulationManager->getMatchDuration();
    m_centerOfMassOffset.setOrigin(btVector3(0,-1,0));
    m_entity = scnMgr->createEntity("Referee", "Human.mesh");
    m_entity->setMaterialName("referee");
    m_node = scnMgr->getRootSceneNode()->createChildSceneNode("RefereeNode", Ogre::Vector3(0, 0, -38));
    m_node->attachObject(m_entity);
    m_shape = new btCylinderShape(btVector3(btScalar(1.),btScalar(1.),btScalar(1.)));
    btScalar mass(80.0);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0,0,0);
    if (isDynamic)
        m_shape->calculateLocalInertia(mass,localInertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,this,m_shape,localInertia);
    m_body = new btRigidBody(rbInfo);

    m_cycle = 0;
}


CReferee::~CReferee()
{
    LOG_DEBUG("~CReferee()");
    delete m_stateMachine;
    delete m_kickPosition;
}


CSimulationManager* CReferee::getSimulationManager()
{
	return m_simulationManager;
}


bool CReferee::handleMessage(const CMessage &msg)
{
    return m_stateMachine->handleMessage(msg);
}


void CReferee::setMatchDuration(int cycles)
{
    m_matchDuration = cycles;
}


int CReferee::getMatchDuration() const
{
    return m_matchDuration;
}


void CReferee::setHomeTeamInSideLeft(bool left)
{
    m_homeSideLeft = left;
}


bool CReferee::isHomeTeamInSideLeft() const
{
    return m_homeSideLeft;
}


void CReferee::setKickTeam(CTeam *team)
{
    m_kickTeam = team;
}


void CReferee::setKickPosition(btVector3 &pos)
{
    m_kickPosition->setValue(pos.x(), pos.y(), pos.z());
}

void CReferee::setNextTimeKickOffTeam(CTeam *team)
{
    m_nextTimeKickOffTeam = team;
}

CTeam* CReferee::getKickTeam()
{
    return m_kickTeam;
}


btVector3 CReferee::getKickPosition()
{
    return *m_kickPosition;
}


CTeam* CReferee::getNextTimeKickOffTeam()
{
    return m_nextTimeKickOffTeam;
}

void CReferee::setLastPlayerTouch(CFootballPlayer *player)
{
    m_lastPlayerTouch = player;
}


CFootballPlayer* CReferee::getLastPlayerTouch()
{
    return m_lastPlayerTouch;
}


void CReferee::update()
{
    m_stateMachine->update();
}


CStateMachine<CReferee>* CReferee::getFSM()
{
    return m_stateMachine;
}


bool CReferee::isMoveLegal() const
{
    return (m_currentGameMode == END ||
            m_currentGameMode == BEFORE_START ||
            m_currentGameMode == KICK_OFF ||
            m_currentGameMode == HALF_TIME);
}


GameMode CReferee::getGameMode()
{
    return m_currentGameMode;
}


int CReferee::getCycle() const
{
    return m_cycle;
}


int CReferee::getMinute() const
{
    return ((90*m_cycle) / m_matchDuration);
}


void CReferee::incCycle()
{
    m_cycle++;
}

void CReferee::setGameMode(GameMode newGameMode)
{
    m_currentGameMode = newGameMode;
    printf("Ciclo:%d GameMode: %s\n", m_cycle, getGameModeString().c_str());
}


std::string CReferee::getGameModeString()
{
    std::string mode;
    switch(m_currentGameMode) {
        case BEFORE_START:
            mode = gettext("Before Start");
            break;
        case HALF_TIME:
            mode = gettext("Half Time");
            break;
        case PLAY_ON:
            mode = gettext("Play On");
            break;
        case END:
            mode = gettext("End");
            break;
        case KICK_OFF:
            mode = gettext("Kick Off");
            break;
        case KICK_IN:
            mode = gettext("Kick In");
            break;
        case CORNER_KICK:
            mode = gettext("Corner Kick");
            break;
        case GOAL_KICK:
            mode = gettext("Goal Kick");
            break;
        default:
            break;
    }
    return mode;
}


int CReferee::getHomeScore() const
{
    return m_homeScore;
}


int CReferee::getAwayScore() const
{
    return m_awayScore;
}


void CReferee::addHomeGoal(CFootballPlayer *player)
{
    bool ownGoal = false;
    CTeam *team = m_simulationManager->getHomeTeam();
    if(player->getTeam()->getID() != team->getID()) {
        ownGoal = true;
    }
    m_homeScore++;
    m_simulationManager->goalMatchEvent(team, player, getMinute(), ownGoal);
}


void CReferee::addAwayGoal(CFootballPlayer *player)
{
    bool ownGoal = false;
    CTeam *team = m_simulationManager->getAwayTeam();
    if(player->getTeam()->getID() != team->getID()) {
        ownGoal = true;
    }
    m_awayScore++;
    m_simulationManager->goalMatchEvent(team, player, getMinute(), ownGoal);
}
