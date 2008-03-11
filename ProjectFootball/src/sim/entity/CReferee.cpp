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
#include "../CSimulationManager.h"
#include "../message/MessageTypes.h"
#include "../fsm/CStateMachine.h"
#include "../../state/CStateMonitor.h"
#include "../../utils/CLog.h"
#include "../../engine/option/CSystemOptionManager.h"


char* CReferee::m_pCtorName = "CReferee_p_ctor";

CReferee::CReferee()
: CBaseAgent()
{
    CLog::getInstance()->debug("CReferee()");
    Ogre::SceneManager *scnMgr = CStateMonitor::getInstance()->getSimulationSceneManager();
    CLuaManager::getInstance()->runScript("data/scripts/referee.lua");
    m_stateMachine = new CStateMachine<CReferee>(this);
    m_stateMachine->changeState("SRf_BeforeStart");
    m_homeScore = 0;
    m_awayScore = 0;
    m_homeSideLeft = true;
    m_matchDuration = CSystemOptionManager::getInstance()->getIntOption("Simulation","MatchDuration");
    m_centerOfMassOffset.setOrigin(btVector3(0,-1,0));
    m_entity = scnMgr->createEntity("Referee", "Cylinder.mesh");
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
    CLog::getInstance()->debug("~CReferee()");
    if(m_stateMachine != 0) {
        delete m_stateMachine;
    }
}


bool CReferee::handleMessage(const CMessage &msg)
{
    return m_stateMachine->handleMessage(msg);
}


void CReferee::setMatchDuration(int cycles)
{
    m_matchDuration = cycles;
}


int CReferee::getMatchDuration()
{
    return m_matchDuration;
}


void CReferee::setHomeTeamInSideLeft(bool left)
{
    m_homeSideLeft = left;
}


bool CReferee::isHomeTeamInSideLeft()
{
    return m_homeSideLeft;
}


void CReferee::setKickTeam(CTeam *team)
{
    m_kickTeam = team;
}


CTeam* CReferee::getKickTeam()
{
    return m_kickTeam;
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


bool CReferee::isMoveLegal()
{
    return (m_currentGameMode == KICK_OFF ||
            m_currentGameMode == BEFORE_START ||
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
            mode = "Before Start";
            break;
        case HALF_TIME:
            mode = "Half Time";
            break;
        case PLAY_ON:
            mode = "Play On";
            break;
        case END:
            mode = "End";
            break;
        case KICK_OFF:
            mode = "Kick Off";
            break;
        case KICK_IN:
            mode = "Kick In";
            break;
        case CORNER_KICK:
            mode = "Corner Kick";
            break;
        case GOAL_KICK:
            mode = "Goal Kick";
            break;
        default:
            break;
    }
    return mode;
}


int CReferee::getHomeScore()
{
    return m_homeScore;
}


int CReferee::getAwayScore()
{
    return m_awayScore;
}


void CReferee::addHomeGoal(CFootballPlayer *player)
{
    m_homeScore++;
}


void CReferee::addAwayGoal(CFootballPlayer *player)
{
    m_awayScore++;
}
