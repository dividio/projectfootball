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


#include "CFootballPlayer.h"


CFootballPlayer::CFootballPlayer(Ogre::String id, Ogre::SceneManager *scnMgr, float x, float y, float z)
:CObject()
{
    m_centerOfMassOffset.setOrigin(btVector3(0,-1,0));
    m_entity = scnMgr->createEntity("Cylinder"+id, "Cylinder.mesh");
    m_node = scnMgr->getRootSceneNode()->createChildSceneNode("PlayerNode"+id, Ogre::Vector3(x, y, z));
    m_node->attachObject(m_entity);
    m_shape = new btCylinderShape(btVector3(btScalar(1.),btScalar(1.),btScalar(1.)));
    btScalar mass(1.);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0,0,0);
    if (isDynamic)
        m_shape->calculateLocalInertia(mass,localInertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,this,m_shape,localInertia);
    m_body = new btRigidBody(rbInfo);
}


CFootballPlayer::~CFootballPlayer()
{

}


void CFootballPlayer::update()
{
//    if(m_sim->isPlayOn()) {
//        m_sim->dash(this, 100);
//    }
}
