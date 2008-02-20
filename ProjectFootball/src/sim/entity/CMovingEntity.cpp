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

CMovingEntity::CMovingEntity()
: CBaseGameEntity()
{
    m_maxVelocity = 10;
    m_heading = btVector3(1,0,0);
    m_side = btVector3(0,0,1);
}

CMovingEntity::~CMovingEntity()
{
}

void CMovingEntity::setPosition(float x, float y, float z)
{
    CBaseGameEntity::setPosition(x,y,z);
    m_body->clearForces();
    m_body->setAngularVelocity(btVector3(0,0,0));
    m_body->setLinearVelocity(btVector3(0,0,0));
    m_body->setInvInertiaDiagLocal(btVector3(0,0,0));
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


btVector3 CMovingEntity::getSide() const
{
    return m_side;
}


double CMovingEntity::getMaxVelocity() const
{
    return m_maxVelocity;
}
