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


#include "CObject.h"
#include "../utils/CLog.h"


CObject::CObject()
{
    CLog::getInstance()->debug("CObject()");
    m_centerOfMassOffset.setIdentity();
}


CObject::~CObject()
{
    CLog::getInstance()->debug("~CObject()");
    if(m_shape != NULL) {
        //delete m_shape;
    }
}


///synchronizes world transform from user to physics
void CObject::getWorldTransform(btTransform& centerOfMassWorldTrans) const
{
    centerOfMassWorldTrans = m_centerOfMassOffset.inverse() * getGraphicTrans();
}

///synchronizes world transform from physics to user
///Bullet only calls the update of worldtransform for active objects
void CObject::setWorldTransform(const btTransform& centerOfMassWorldTrans)
{
    setGraphicTrans(centerOfMassWorldTrans * m_centerOfMassOffset);
}


btTransform CObject::getGraphicTrans() const
{
    Ogre::Vector3 v(m_node->getWorldPosition());
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(v.x,v.y,v.z));
    return trans;
}


void CObject::setGraphicTrans(btTransform trans)
{
    btVector3 v = trans.getOrigin();
    m_node->setPosition(v.getX(), v.getY(), v.getZ());

    btQuaternion q = trans.getRotation();
    m_node->setOrientation(q.w(), q.x(), q.y(), q.z());
}


btCollisionShape* CObject::getShape()
{
    return m_shape;
}


btRigidBody* CObject::getBody()
{
    return m_body;
}


btVector3 CObject::getPosition()
{
    Ogre::Vector3 v(m_node->getWorldPosition());
    return btVector3(v.x,v.y,v.z);
}


void CObject::setPosition(float x, float y, float z)
{
    btVector3 pos = getPosition();
    btVector3 desp(-pos.getX() + x, -pos.getY() + y, -pos.getZ() + z);
    m_body->translate(desp);
    m_body->clearForces();
    m_body->setAngularVelocity(btVector3(0,0,0));
    m_body->setLinearVelocity(btVector3(0,0,0));
    m_body->setInvInertiaDiagLocal(btVector3(0,0,0));
}
