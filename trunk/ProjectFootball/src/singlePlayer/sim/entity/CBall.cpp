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

#include <Ogre.h>

#include "CBall.h"
#include "../../screen/CScreenSimulator.h"
#include "../../../utils/CLog.h"

CBall::CBall()
: CMovingEntity()
{
	Ogre::SceneManager *scnMgr = Ogre::Root::getSingletonPtr()->getSceneManager(SIMULATION_SCENE_MANAGER_NODE_NAME);

    CLog::getInstance()->debug("CBall()");
    m_centerOfMassOffset.setOrigin(btVector3(0,-0.5,0));
    m_entity = scnMgr->createEntity("Ball", "Ball.mesh");
    m_node = scnMgr->getRootSceneNode()->createChildSceneNode("BallNode", Ogre::Vector3(0, 0, 0));
    m_node->attachObject(m_entity);
    m_shape = new btSphereShape(btScalar(0.5));
    btScalar mass(0.5);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0,0,0);
    if (isDynamic){
        m_shape->calculateLocalInertia(mass,localInertia);
    }
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,this,m_shape,localInertia);
    rbInfo.m_restitution = btScalar(0.8);
    rbInfo.m_friction = 0.5;
    rbInfo.m_angularDamping = 0.9;
    rbInfo.m_linearDamping = 0.2;
    m_body = new btRigidBody(rbInfo);
    m_body->setActivationState(DISABLE_DEACTIVATION);
}


CBall::~CBall()
{
    CLog::getInstance()->debug("~CBall()");
}


bool CBall::isInLeftGoal() const
{
    bool result = false;
    btVector3 pos = getPosition();
    if((pos.x() < -55) && (pos.y() <= 2.44) &&
       (pos.z() > -3.66) && (pos.z() < 3.66)) {
        result = true;
    }
    return result;
}


bool CBall::isInRightGoal() const
{
    bool result = false;
    btVector3 pos = getPosition();
    if((pos.x() > 55) && (pos.y() <= 2.44) &&
       (pos.z() > -3.66) && (pos.z() < 3.66)) {
        result = true;
    }
    return result;
}


bool CBall::crossLeftLine() const
{
    bool result = false;
    btVector3 pos = getPosition();
    if(pos.x() < -55) {
        result = true;
    }
    return result;
}


bool CBall::crossRightLine() const
{
    bool result = false;
    btVector3 pos = getPosition();
    if(pos.x() > 55) {
        result = true;
    }
    return result;
}


bool CBall::crossTopLine() const
{
    bool result = false;
    btVector3 pos = getPosition();
    if(pos.z() < -35) {
        result = true;
    }
    return result;
}


bool CBall::crossBottomLine() const
{
    bool result = false;
    btVector3 pos = getPosition();
    if(pos.z() > 35) {
        result = true;
    }
    return result;
}
