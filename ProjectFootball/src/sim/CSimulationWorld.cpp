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


#include "CSimulationWorld.h"
#include "utils/CLog.h"


CSimulationWorld::CSimulationWorld()
{
    CLog::getInstance()->debug("CSimulationWorld()");

    //Bullet initialization
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_dispatcher = new  btCollisionDispatcher(m_collisionConfiguration);
    btVector3 worldAabbMin(-1000,-1000,-1000);
    btVector3 worldAabbMax(1000,1000,1000);
    int maxProxies = 1024;
    m_broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);
    m_solver = new btSequentialImpulseConstraintSolver();

    m_world = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
    m_world->setGravity(btVector3(0,-10,0));


    ///create a few basic rigid bodies
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(60.),btScalar(1.),btScalar(45.)));

    //keep track of the shapes, we release memory at exit.
    //make sure to re-use collision shapes among rigid bodies whenever possible!

    m_collisionShapes.push_back(groundShape);

    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0,-1,0));

    {
        btScalar mass(0.);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (isDynamic)
            groundShape->calculateLocalInertia(mass,localInertia);

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        //add the body to the dynamics world
        m_world->addRigidBody(body);
    }
}


CSimulationWorld::~CSimulationWorld()
{
    CLog::getInstance()->debug("~CSimulationWorld()");

    //Delete Bullet objects in reverse order

    //remove the rigidbodies from the dynamics world and delete them
    for (int i = m_world->getNumCollisionObjects()-1; i >= 0; i--) {
        btCollisionObject* obj = m_world->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        m_world->removeCollisionObject( obj );
        delete obj;
    }

    //delete collision shapes
    for (int j = 0; j < m_collisionShapes.size(); j++) {
        btCollisionShape* shape = m_collisionShapes[j];
        m_collisionShapes[j] = 0;
        delete shape;
    }
    delete m_world;
    delete m_solver;
    delete m_broadphase;
    delete m_dispatcher;
    delete m_collisionConfiguration;
}


void CSimulationWorld::update()
{
    m_world->stepSimulation(1.f/60.f,10);
}


void CSimulationWorld::addObject(CObject *object)
{
    m_world->addRigidBody(object->getBody());
}
