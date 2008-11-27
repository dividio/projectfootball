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


#ifndef CSTEERINGBEHAVIORS_H_
#define CSTEERINGBEHAVIORS_H_

#include "../bullet/LinearMath/btVector3.h"

//Forward declarations
class CMovingEntity;

class CSteeringBehaviors
{
public:
    CSteeringBehaviors(CMovingEntity *agent);
    ~CSteeringBehaviors();

    void setTargetPoint(const btVector3 &target);
    void setTargetEntity(CMovingEntity *entity);
    btVector3 getTarget() const;

    btVector3 force() const;
    btVector3 calculate();
    btVector3 sumForces();
    double forwardComponent() const;
    double sideComponent() const;

    void seekOn();
    void stopOn();
    void arriveOn();
    void pursuitOn();
    void interposeOn();

    void seekOff();
    void stopOff();
    void arriveOff();
    void pursuitOff();
    void interposeOff();

private:
    CMovingEntity *m_agent;
    CMovingEntity *m_targetEntity;

    bool m_seek;
    bool m_stop;
    bool m_arrive;
    bool m_pursuit;
    bool m_interpose;

    btVector3 m_steeringForce;
    btVector3 m_target;

    enum Deceleration{slow = 3, normal = 2, fast = 1};

    btVector3 seek(const btVector3 &target);
    btVector3 stop();
    btVector3 arrive(const btVector3 &target, Deceleration decel);
    btVector3 pursuit(CMovingEntity *entity);
    btVector3 interpose(CMovingEntity *objectA, CMovingEntity *objectB);

};

#endif // CSTEERINGBEHAVIORS_H_
