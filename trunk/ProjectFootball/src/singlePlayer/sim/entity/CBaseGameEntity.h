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


#ifndef __CBaseGameEntity_H__
#define __CBaseGameEntity_H__

#include <Ogre.h>

#include "../message/CMessage.h"
#include "../../../bullet/btBulletDynamicsCommon.h"


class CBaseGameEntity: public btMotionState
{
public:

    virtual ~CBaseGameEntity(){};

    void        update(){};
    int         getID() const;
    static void resetNextID();

    virtual bool handleMessage(const CMessage &msg){return false;};

    //synchronizes world transform from user to physics
    void    getWorldTransform(btTransform& centerOfMassWorldTrans ) const;

    //synchronizes world transform from physics to user
    //Bullet only calls the update of worldtransform for active objects
    void    setWorldTransform(const btTransform& centerOfMassWorldTrans);

    btCollisionShape* getShape();
    btRigidBody*      getBody();
    btVector3         getPosition() const;
    void              setPosition(float x, float y, float z);

protected:
    Ogre::Entity     *m_entity;
    Ogre::SceneNode  *m_node;
    btCollisionShape *m_shape;
    btRigidBody      *m_body;
    btTransform       m_centerOfMassOffset;

    btTransform getGraphicTrans() const;
    void        setGraphicTrans(btTransform trans);
    CBaseGameEntity();

private:
    int        m_ID;
    static int m_nextValidID;
};

#endif // __CBaseGameEntity_H__
