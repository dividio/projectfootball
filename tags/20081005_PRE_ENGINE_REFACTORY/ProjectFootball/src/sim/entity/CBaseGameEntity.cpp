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


#include "CBaseGameEntity.h"
#include "CEntityManager.h"


int CBaseGameEntity::m_nextValidID = 0;

CBaseGameEntity::CBaseGameEntity()
{
    m_ID = m_nextValidID;
    m_nextValidID++;
    m_centerOfMassOffset.setIdentity();
    CEntityManager::getInstance()->addEntity(this);
}


int CBaseGameEntity::getID() const
{
    return m_ID;
}


void CBaseGameEntity::resetNextID()
{
    m_nextValidID = 0;
}


//synchronizes world transform from user to physics
void CBaseGameEntity::getWorldTransform(btTransform& centerOfMassWorldTrans) const
{
    centerOfMassWorldTrans = m_centerOfMassOffset.inverse() * getGraphicTrans();
}


//synchronizes world transform from physics to user
//Bullet only calls the update of worldtransform for active objects
void CBaseGameEntity::setWorldTransform(const btTransform& centerOfMassWorldTrans)
{
    setGraphicTrans(centerOfMassWorldTrans * m_centerOfMassOffset);
}


btTransform CBaseGameEntity::getGraphicTrans() const
{
    Ogre::Vector3 v(m_node->getWorldPosition());
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(v.x,v.y,v.z));
    return trans;
}


void CBaseGameEntity::setGraphicTrans(btTransform trans)
{
    btVector3 v = trans.getOrigin();
    m_node->setPosition(v.getX(), v.getY(), v.getZ());

    btQuaternion q = trans.getRotation();
    m_node->setOrientation(q.w(), q.x(), q.y(), q.z());
}


btCollisionShape* CBaseGameEntity::getShape()
{
    return m_shape;
}


btRigidBody* CBaseGameEntity::getBody()
{
    return m_body;
}


btVector3 CBaseGameEntity::getPosition() const
{
    Ogre::Vector3 v(m_node->getWorldPosition());
    return btVector3(v.x,v.y,v.z);
}


void CBaseGameEntity::setPosition(float x, float y, float z)
{
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(x,y,z));
    m_body->proceedToTransform(m_centerOfMassOffset.inverse()*trans);
}
