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


#include "CSteeringBehaviors.h"


CSteeringBehaviors::CSteeringBehaviors(CBaseAgent *agent)
{
    m_agent = agent;
    //m_ball = ball;
    m_steeringForce = btVector3(0,0,0);
}


CSteeringBehaviors::~CSteeringBehaviors()
{
}


btVector3 CSteeringBehaviors::getTarget() const
{
    return m_target;
}


void CSteeringBehaviors::setTarget(const btVector3 target)
{
    m_target = target;
}


btVector3 CSteeringBehaviors::force() const
{
    return m_steeringForce;
}

btVector3 CSteeringBehaviors::calculate()
{
    m_steeringForce = btVector3(0,0,0);
    m_steeringForce = sumForces();
//    truncateVector(m_steeringForce, maxForce);
    return m_steeringForce;
}


btVector3 CSteeringBehaviors::sumForces()
{
    btVector3 sum;
    sum = arrive(m_target, normal);
    return sum;
}


btVector3 CSteeringBehaviors::seek(btVector3 target)
{
    btVector3 desiredVelocity = btVector3(target - m_agent->getPosition());
    desiredVelocity.normalize();
    desiredVelocity *= m_agent->getMaxVelocity();
    return (desiredVelocity - m_agent->getBody()->getLinearVelocity());
}


btVector3 CSteeringBehaviors::arrive(btVector3 target, Deceleration decel)
{
    btVector3 steer(0,0,0);
    btVector3 toTarget = target - m_agent->getPosition();

    double dist = toTarget.length();

    if(dist > 0) {

        double tweaker = 0.3;
        double speed =  dist / ((double)decel * tweaker);
        if(speed > m_agent->getMaxVelocity()) {
            speed = m_agent->getMaxVelocity();
        }

        btVector3 desiredVelocity =  toTarget * speed / dist;
        steer = desiredVelocity - m_agent->getBody()->getLinearVelocity();
    }

    return steer;
}
