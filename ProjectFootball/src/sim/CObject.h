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


#ifndef __CObject_H__
#define __CObject_H__

#include <Ogre.h>

#include "bullet/btBulletDynamicsCommon.h"

class CObject: public btMotionState
{
public:

    CObject();
    ~CObject();

    ///synchronizes world transform from user to physics
    virtual void    getWorldTransform(btTransform& centerOfMassWorldTrans ) const;

    ///synchronizes world transform from physics to user
    ///Bullet only calls the update of worldtransform for active objects
    virtual void    setWorldTransform(const btTransform& centerOfMassWorldTrans);

    btTransform getGraphicTrans() const;
    void setGraphicTrans(btTransform trans);
    btCollisionShape* getShape();
    btRigidBody* getBody();
    void setPosition(float x, float y, float z);

protected:
    Ogre::Entity *m_entity;
    Ogre::SceneNode *m_node;
    btCollisionShape *m_shape;
    btRigidBody* m_body;
    btTransform m_centerOfMassOffset;
};

#endif // __CObject_H__
