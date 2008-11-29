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


#include "CMovingEntity.h"

#include "../../../bullet/btBulletDynamicsCommon.h"

CMovingEntity::CMovingEntity()
: CBaseGameEntity()
{
    m_maxVelocity = 10;
    m_heading = btVector3(btScalar(1.0), btScalar(0.0), btScalar(0.0));
    m_side = btVector3(btScalar(0.0), btScalar(0.0), btScalar(1.0));
    m_prevAngle = 0.0;
}


CMovingEntity::~CMovingEntity()
{
}


void CMovingEntity::updateOrientation()
{
    btTransform xform;
    btVector3 baseV(btScalar(1.0), btScalar(0.0), btScalar(0.0));
    btScalar dot = baseV.dot(m_heading);
    if(dot > 1) {
        dot = 1;
    } else if(dot < -1) {
        dot = -1;
    }
    btScalar angle = btAcos(dot);
    btScalar dotSide = baseV.dot(m_side);

    if(dotSide < 0) {
        angle = -angle;
    }

    btScalar rotation = angle - m_prevAngle;
    if(btFabs(rotation) > 0.01) {
        getBody()->getMotionState()->getWorldTransform(xform);
        rotation += m_prevAngle;
        xform.setRotation(btQuaternion(btVector3(0.0, 1.0, 0.0), rotation));
        getBody()->getMotionState()->setWorldTransform(xform);
        getBody()->setCenterOfMassTransform(xform);
    }
}


void CMovingEntity::setPosition(float x, float y, float z)
{
    CBaseGameEntity::setPosition(x,y,z);
    m_body->clearForces();
    m_body->setAngularVelocity(btVector3(0,0,0));
    m_body->setLinearVelocity(btVector3(0,0,0));
}


btVector3 CMovingEntity::futurePosition(double time) const
{
    btVector3 vt = m_body->getLinearVelocity() * time;

    btVector3 coef = m_body->getLinearVelocity().normalized() * 0.5 * time * time;

    return getPosition() + vt + coef;
}


btVector3 CMovingEntity::getHeading() const
{
    return m_heading;
}


void CMovingEntity::setHeading(btVector3 direction)
{
    btVector3 baseV(btScalar(1.0), btScalar(0.0), btScalar(0.0));
    btScalar dotSide = baseV.dot(m_side);
    btScalar dot = baseV.dot(m_heading);
    if(dot > 1) {
        dot = 1;
    } else if(dot < -1) {
        dot = -1;
    }
    m_prevAngle = btAcos(dot);
    if(dotSide < 0) {
        m_prevAngle = -m_prevAngle;
    }
    m_heading = direction.normalized();
    m_side = btVector3(-(m_heading.z()), m_heading.y(), m_heading.getX());
}


btVector3 CMovingEntity::getSide() const
{
    return m_side;
}


double CMovingEntity::getMaxVelocity() const
{
    return m_maxVelocity;
}
