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
#include "CSimulationManager.h"
#include "../state/CStateMonitor.h"
#include "../utils/CLog.h"

CReferee::CReferee(Ogre::SceneManager *scnMgr)
{
    m_homeScore = 0;
    m_awayScore = 0;
    m_homeSideLeft = true;
    m_centerOfMassOffset.setOrigin(btVector3(0,-1,0));
    m_entity = scnMgr->createEntity("Referee", "Cylinder.mesh");
    m_entity->setMaterialName("referee");
    m_node = scnMgr->getRootSceneNode()->createChildSceneNode("RefereeNode", Ogre::Vector3(0, 0, -38));
    m_node->attachObject(m_entity);
    m_shape = new btCylinderShape(btVector3(btScalar(1.),btScalar(1.),btScalar(1.)));
    btScalar mass(1.);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0,0,0);
    if (isDynamic)
        m_shape->calculateLocalInertia(mass,localInertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,this,m_shape,localInertia);
    m_body = new btRigidBody(rbInfo);

    m_cycle = 0;
    setGameMode(BEFORE_START);
}


CReferee::~CReferee()
{
}


void CReferee::update()
{
    CSimulationManager *sim = CStateMonitor::getInstance()->getSimulationManager();
    CBall *ball = sim->getBall();
    int halfTime = 1000;
    if(m_currentGameMode != BEFORE_START
                  && m_currentGameMode != HALF_TIME
                  && m_currentGameMode != END) {
        ++m_cycle;
        if(m_currentGameMode == PLAY_ON) {
            verifyBallPosition();
        }
        if(m_cycle == halfTime*2) {
            setGameMode(END);
            CLog::getInstance()->info("End of the match");
            CLog::getInstance()->info("%s %d - %d %s", sim->getHomeTeamName()->c_str(), m_homeScore, m_awayScore, sim->getAwayTeamName()->c_str());

        } else if(m_cycle == halfTime) {
            setGameMode(HALF_TIME);
            sim->changePlayersSide();
            m_homeSideLeft = false;
            ball->setPosition(0,1,0);
            CLog::getInstance()->info("Half Time");
            CLog::getInstance()->info("%s %d - %d %s", sim->getHomeTeamName()->c_str(), m_homeScore, m_awayScore, sim->getAwayTeamName()->c_str());
        }
    }
}


void CReferee::startMatchEvent()
{
    if(m_currentGameMode == BEFORE_START) {
        setGameMode(KICK_OFF_LEFT);
    } else if(m_currentGameMode == HALF_TIME) {
        setGameMode(KICK_OFF_LEFT);
    }
}


void CReferee::playerKickEvent(CFootballPlayer *player)
{
    m_lastPlayerKick = player;
    if(m_currentGameMode == KICK_OFF_LEFT ||
            m_currentGameMode == GOAL_KICK_LEFT ||
            m_currentGameMode == KICK_IN_LEFT ||
            m_currentGameMode == CORNER_KICK_LEFT) {
        if(m_lastPlayerKick->isTeamLeft()) {
            setGameMode(PLAY_ON);
        } else {
            setGameMode(KICK_IN_LEFT);
        }
    } else if(m_currentGameMode == KICK_OFF_RIGHT ||
            m_currentGameMode == GOAL_KICK_RIGHT ||
            m_currentGameMode == KICK_IN_RIGHT ||
            m_currentGameMode == CORNER_KICK_RIGHT) {
        if(!m_lastPlayerKick->isTeamLeft()) {
            setGameMode(PLAY_ON);
        } else {
            setGameMode(KICK_IN_RIGHT);
        }
    }
}


bool CReferee::isMoveLegal()
{
    return (m_currentGameMode == KICK_OFF_LEFT ||
            m_currentGameMode == KICK_OFF_RIGHT ||
            m_currentGameMode == BEFORE_START ||
            m_currentGameMode == HALF_TIME);
}


GameMode CReferee::getGameMode()
{
    return m_currentGameMode;
}


void CReferee::setGameMode(GameMode newGameMode)
{
    m_currentGameMode = newGameMode;
    printf("Ciclo:%d   Game Mode: %s\n", m_cycle, getGameModeString().c_str());
}


std::string CReferee::getGameModeString()
{
    std::string mode;
    switch(m_currentGameMode) {
        case BEFORE_START:
            mode = "Before_Start";
            break;
        case HALF_TIME:
            mode = "Half_Time";
            break;
        case PLAY_ON:
            mode = "Play_On";
            break;
        case END:
            mode = "End";
            break;
        case KICK_OFF_LEFT:
            mode = "Kick_Off_Left";
            break;
        case KICK_OFF_RIGHT:
            mode = "Kick_Off_Right";
            break;
        case KICK_IN_LEFT:
            mode = "Kick_In_Left";
            break;
        case KICK_IN_RIGHT:
            mode = "Kick_In_Right";
            break;
        case CORNER_KICK_LEFT:
            mode = "Corner_Kick_Left";
            break;
        case CORNER_KICK_RIGHT:
            mode = "Corner_Kick_Right";
            break;
        case GOAL_KICK_LEFT:
            mode = "Goal_Kick_Left";
            break;
        case GOAL_KICK_RIGHT:
            mode = "Goal_Kick_Right";
            break;
        default:
            break;
    }
    return mode;
}


bool CReferee::verifyBallPosition()
{
    CSimulationManager *sim = CStateMonitor::getInstance()->getSimulationManager();
    CBall *ball = sim->getBall();
    btVector3 pos = ball->getPosition();
    float x = pos.x();
    float y = pos.y();
    float z = pos.z();
    if(x >= -55 && x <= 55) {
        if(z < -35) {
            if(m_lastPlayerKick->isTeamLeft()) {
                setGameMode(KICK_IN_RIGHT);
            } else {
                setGameMode(KICK_IN_LEFT);
            }
            ball->setPosition(x,1,-35);
        } else if(z > 35) {
            if(m_lastPlayerKick->isTeamLeft()) {
                setGameMode(KICK_IN_RIGHT);
            } else {
                setGameMode(KICK_IN_LEFT);
            }
            ball->setPosition(x,1,35);
        }
    } else if(x < -55){
        if(y > 2.44) {
            if (z <= 0) {
                if(m_lastPlayerKick->isTeamLeft()) {
                    setGameMode(CORNER_KICK_RIGHT);
                    ball->setPosition(-54.5,1,-34.5);
                } else {
                    setGameMode(GOAL_KICK_LEFT);
                    ball->setPosition(-49.5,1,-9);
                }
            } else {
                if(m_lastPlayerKick->isTeamLeft()) {
                    setGameMode(CORNER_KICK_RIGHT);
                    ball->setPosition(-54.5,1,34.5);
                } else {
                    setGameMode(GOAL_KICK_LEFT);
                    ball->setPosition(-49.5,1,9);
                }
            }
        } else {
            if (z <= -3.66) {
                if(m_lastPlayerKick->isTeamLeft()) {
                    setGameMode(CORNER_KICK_RIGHT);
                    ball->setPosition(-54.5,1,-34.5);
                } else {
                    setGameMode(GOAL_KICK_LEFT);
                    ball->setPosition(-49.5,1,-9);
                }
            } else if(z >= 3.66){
                if(m_lastPlayerKick->isTeamLeft()) {
                    setGameMode(CORNER_KICK_RIGHT);
                    ball->setPosition(-54.5,1,34.5);
                } else {
                    setGameMode(GOAL_KICK_LEFT);
                    ball->setPosition(-49.5,1,9);
                }
            } else {
                setGameMode(KICK_OFF_LEFT);
                ball->setPosition(0,1,0);
                if(m_homeSideLeft) {
                    m_awayScore++;
                    CLog::getInstance()->info("Player %s scores!!", m_lastPlayerKick->getIdent().c_str());
                } else {
                    m_homeScore++;
                    CLog::getInstance()->info("Player %s scores!!", m_lastPlayerKick->getIdent().c_str());
                }
            }
        }
    } else if(x > 55) {
        if(y > 2.44) {
            if (z <= 0) {
                if(m_lastPlayerKick->isTeamLeft()) {
                    setGameMode(GOAL_KICK_RIGHT);
                    ball->setPosition(49.5,1,-9);
                } else {
                    setGameMode(CORNER_KICK_LEFT);
                    ball->setPosition(54.5,1,-34.5);
                }
            } else {
                if(m_lastPlayerKick->isTeamLeft()) {
                    setGameMode(GOAL_KICK_RIGHT);
                    ball->setPosition(49.5,1,9);
                } else {
                    setGameMode(CORNER_KICK_LEFT);
                    ball->setPosition(54.5,1,34.5);
                }
            }
        } else {
            if (z <= -3.66) {
                if(m_lastPlayerKick->isTeamLeft()) {
                    setGameMode(GOAL_KICK_RIGHT);
                    ball->setPosition(49.5,1,-9);
                } else {
                    setGameMode(CORNER_KICK_LEFT);
                    ball->setPosition(54.5,1,-34.5);
                }
            } else if(z >= 3.66){
                if(m_lastPlayerKick->isTeamLeft()) {
                    setGameMode(GOAL_KICK_RIGHT);
                    ball->setPosition(49.5,1,9);
                } else {
                    setGameMode(CORNER_KICK_LEFT);
                    ball->setPosition(54.5,1,34.5);
                }
            } else {
                setGameMode(KICK_OFF_RIGHT);
                ball->setPosition(0,1,0);
                if(m_homeSideLeft) {
                    m_homeScore++;
                    CLog::getInstance()->info("Player %s scores!!", m_lastPlayerKick->getIdent().c_str());
                } else {
                    m_awayScore++;
                    CLog::getInstance()->info("Player %s scores!!", m_lastPlayerKick->getIdent().c_str());
                }
            }
        }
    }
}
