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


#ifndef CSIMULATIONWORLD_H_
#define CSIMULATIONWORLD_H_

#include <vector>

#include "../bullet/LinearMath/btAlignedObjectArray.h"

class CBaseGameEntity;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btCollisionShape;
class btSequentialImpulseConstraintSolver;
class btBroadphaseInterface;
class btDiscreteDynamicsWorld;

class CSimulationWorld
{
public:
    CSimulationWorld();
    ~CSimulationWorld();

    void update();
    void addObject(CBaseGameEntity *object);

private:
    //Bullet Objects
    btCollisionConfiguration                *m_collisionConfiguration;
    btCollisionDispatcher                   *m_dispatcher;
    btSequentialImpulseConstraintSolver     *m_solver;
    btBroadphaseInterface                   *m_broadphase;
    btDiscreteDynamicsWorld                 *m_world;
    btAlignedObjectArray<btCollisionShape*>  m_collisionShapes;
};

#endif // CSIMULATIONWORLD_H_
