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


#include "CFootballPlayer.h"
#include "../CSimulationManager.h"
#include "CReferee.h"
#include "../../state/CStateMonitor.h"


CFootballPlayer::CFootballPlayer(int number, std::string teamName, int x, int y, int z, bool sideLeft)
:CBaseAgent()
{
    Ogre::SceneManager *scnMgr = CStateMonitor::getInstance()->getSimulationSceneManager();
    Ogre::String id;
    char charId[20];
    m_centerOfMassOffset.setOrigin(btVector3(0,-1,0));
    m_sideLeft = sideLeft;
    m_teamName = teamName;
    m_number = number;
    m_direction = btVector3(btScalar(1.0),btScalar(0.0),btScalar(0.0));

    if(m_sideLeft) {
        m_strategicX = x;
        m_strategicZ = z;
    } else {
        m_strategicX = -x;
        m_strategicZ = -z;
    }
    //m_direction.normalize();
    sprintf(charId,"%s%d", m_teamName.c_str(), number);
    m_ident = charId;
    id = charId;
    m_entity = scnMgr->createEntity("Cylinder"+id, "Cylinder.mesh");
    if(sideLeft) {
        if(number == 1) {
            m_entity->setMaterialName("goalie_red");
        } else {
            m_entity->setMaterialName("player_red");
        }
    } else {
        if(number == 1) {
            m_entity->setMaterialName("goalie_yellow");
        } else {
            m_entity->setMaterialName("player_yellow");
        }
    }
    m_node = scnMgr->getRootSceneNode()->createChildSceneNode("PlayerNode"+id, Ogre::Vector3(m_strategicX, y, m_strategicZ));
    m_node->attachObject(m_entity);
    m_shape = new btCylinderShape(btVector3(btScalar(1.),btScalar(1.),btScalar(1.)));
    btScalar mass(70.0);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0,0,0);
    if (isDynamic)
        m_shape->calculateLocalInertia(mass,localInertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,this,m_shape,localInertia);
    m_body = new btRigidBody(rbInfo);
    m_body->setAngularFactor(btScalar(0));
    m_body->setActivationState(DISABLE_DEACTIVATION);

    m_steeringBehavior = new CSteeringBehaviors(this);
}


CFootballPlayer::~CFootballPlayer()
{

}


void CFootballPlayer::update()
{
    m_canDoActions = true;
    CSimulationManager *simulator = CStateMonitor::getInstance()->getSimulationManager();
    CReferee *referee = simulator->getReferee();
    GameMode mode = referee->getGameMode();
    if(mode != PLAY_ON) {
        if(mode != BEFORE_START && mode != HALF_TIME && mode != END) {
            if(simulator->isNearestPlayerToBall(this)) {
                if(getPosition().distance(simulator->getBallPosition()) < 2) {
                    if(m_sideLeft) {
                        btVector3 direction = (btVector3(55,0,0) - getPosition());
                        simulator->kick(this, direction);
                    } else {
                        btVector3 direction = (btVector3(-55,0,0) - getPosition());
                        simulator->kick(this, direction);
                    }
                } else {
                    m_steeringBehavior->setTarget(simulator->getBallPosition());
                    simulator->dash(this, m_steeringBehavior->calculate());
                }
            } else {
                if((getPosition().x() > m_strategicX + 1 || getPosition().x() < m_strategicX - 1) &&
                        (getPosition().z() > m_strategicZ + 1 || getPosition().z() < m_strategicZ - 1)) {
                    m_steeringBehavior->setTarget(btVector3(m_strategicX, 0, m_strategicZ));
                    simulator->dash(this, m_steeringBehavior->calculate());
                }
            }
        } else {
            simulator->move(this, m_strategicX, m_strategicZ);
        }
    } else {
        if(getPosition().distance(simulator->getBallPosition()) > 2.2) {
            if(simulator->isNearestTeamMatePlayerToBall(this)) {
                m_steeringBehavior->setTarget(simulator->getBallPosition());
                simulator->dash(this, m_steeringBehavior->calculate());
            } else if((getPosition().x() > m_strategicX + 1 || getPosition().x() < m_strategicX - 1) &&
                    (getPosition().z() > m_strategicZ + 1 || getPosition().z() < m_strategicZ - 1)) {
                m_steeringBehavior->setTarget(btVector3(m_strategicX, 0, m_strategicZ));
                simulator->dash(this, m_steeringBehavior->calculate());
            }
        } else {
            if(m_sideLeft) {
                btVector3 direction = (btVector3(55,0,0) - getPosition());
                simulator->kick(this, direction);
            } else {
                btVector3 direction = (btVector3(-55,0,0) - getPosition());
                simulator->kick(this, direction);
            }
        }
    }
}


bool CFootballPlayer::canDoActions()
{
    bool aux = m_canDoActions;
    m_canDoActions = false;
    return aux;
}


bool CFootballPlayer::canKickBall(int cycle)
{
    if((cycle - m_lastKickBallCycle) > 3) {
        m_lastKickBallCycle = cycle;
        return true;
    }
    return false;
}


btVector3 CFootballPlayer::getDirection() const
{
    return m_direction;
}


std::string CFootballPlayer::getIdent() const
{
    return m_ident;
}


std::string CFootballPlayer::getTeamName() const
{
    return m_teamName;
}


bool CFootballPlayer::isTeamLeft() const
{
    return m_sideLeft;
}


void CFootballPlayer::changeSide()
{
    CSimulationManager *simulator = CStateMonitor::getInstance()->getSimulationManager();
    m_sideLeft = !m_sideLeft;
    m_strategicX = -m_strategicX;
    m_strategicZ = -m_strategicZ;
    simulator->move(this, m_strategicX, m_strategicZ);
}


void CFootballPlayer::moveToPos(btVector3 pos, int angle)
{

}


//void CFootballPlayer::turnBodyToObject(CObject o)
//{
//
//}


void CFootballPlayer::turnBodyToPoint(btVector3 pos, int cycles)
{

}

