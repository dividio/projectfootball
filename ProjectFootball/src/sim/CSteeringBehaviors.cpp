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


CSteeringBehaviors::CSteeringBehaviors(CMovingEntity *agent)
{
    m_agent = agent;
    m_targetEntity = 0;
    m_target = btVector3(0,0,0);
    m_steeringForce = btVector3(0,0,0);
    m_seek = false;
    m_arrive = false;
    m_pursuit = false;
    m_interpose = false;
}


CSteeringBehaviors::~CSteeringBehaviors()
{
}


btVector3 CSteeringBehaviors::getTarget() const
{
    return m_target;
}


void CSteeringBehaviors::setTargetPoint(const btVector3 target)
{
    m_target.setValue(target.x(), 0, target.z());
}


void CSteeringBehaviors::setTargetEntity(CMovingEntity *entity)
{
    m_targetEntity = entity;
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
    btVector3 sum(0,0,0);
    if(m_seek) {
        sum += seek(m_target);
    }

    if(m_stop) {
        sum += stop();
    }

    if(m_arrive) {
        sum += arrive(m_target, fast);
    }

    if(m_pursuit) {
        sum += pursuit(m_targetEntity);
    }

    if(m_interpose) {
        sum += interpose(this->m_agent, m_targetEntity);
    }

    return sum;
}


void CSteeringBehaviors::seekOn()
{
    m_seek = true;
}


void CSteeringBehaviors::stopOn()
{
    m_stop = true;
}


void CSteeringBehaviors::arriveOn()
{
    m_arrive = true;
}


void CSteeringBehaviors::pursuitOn()
{
    m_pursuit = true;
}


void CSteeringBehaviors::interposeOn()
{
    m_interpose = true;
}


void CSteeringBehaviors::seekOff()
{
    m_seek = false;
}


void CSteeringBehaviors::stopOff()
{
    m_stop = false;
}


void CSteeringBehaviors::arriveOff()
{
    m_arrive = false;
}


void CSteeringBehaviors::pursuitOff()
{
    m_pursuit = false;
}


void CSteeringBehaviors::interposeOff()
{
    m_interpose = false;
}


btVector3 CSteeringBehaviors::seek(btVector3 target)
{
    btVector3 desiredVelocity = btVector3(target - m_agent->getPosition());
    desiredVelocity.normalize();
    desiredVelocity *= m_agent->getMaxVelocity();
    return (desiredVelocity - m_agent->getBody()->getLinearVelocity());
}


btVector3 CSteeringBehaviors::stop()
{
    return -(m_agent->getBody()->getLinearVelocity())/4;
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


double CSteeringBehaviors::forwardComponent() const
{
  return m_agent->getHeading().normalized().dot(m_steeringForce.normalized());
}


double CSteeringBehaviors::sideComponent() const
{
  return m_agent->getSide().normalized().dot(m_steeringForce.normalized());
}


btVector3 CSteeringBehaviors::pursuit(CMovingEntity *entity)
{
    btVector3 result;
    btVector3 entityPos = entity->getPosition();
    btVector3 agentPos = m_agent->getPosition();
    btVector3 toEntity = entityPos - agentPos;
    btVector3 entityVel = entity->getBody()->getLinearVelocity();
    double relativeHeading = m_agent->getHeading().dot(entityVel.normalized());

    if((toEntity.dot(m_agent->getHeading()) > 0) &&
       (relativeHeading < -0.95)) {
        setTargetPoint(entityPos);
        result = seek(m_target);
    } else {
        double lookTime = 0.0;
        double velocity = entityVel.length();
        if(velocity > 0.0001) {
            lookTime = toEntity.length() / (m_agent->getMaxVelocity() + velocity);
        }

        btVector3 futurePos = entity->futurePosition(lookTime);

        if(futurePos.distance(agentPos) < 1) {
            setTargetPoint(entityPos);
        } else {
            setTargetPoint(futurePos);
        }
        //result = arrive(m_target, fast);
        result = seek(m_target);
    }
    return result;
}

//TODO Consider speeds of the objects
btVector3 CSteeringBehaviors::interpose(CMovingEntity *objectA, CMovingEntity *objectB)
{
    btVector3 middle = (objectA->getPosition() + objectB->getPosition()) / 2;

    return arrive(middle, fast);
}
