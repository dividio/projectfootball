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


#ifndef CMOVINGENTITY_H_
#define CMOVINGENTITY_H_

#include "CBaseGameEntity.h"

class CMovingEntity : public CBaseGameEntity
{
public:
    virtual ~CMovingEntity();

    void      setPosition(float x, float y, float z);
    void      updateOrientation();
    btVector3 futurePosition(double time) const;
    btVector3 getHeading() const;
    btVector3 getSide() const;
    double    getMaxVelocity() const;
    void      setHeading(btVector3 direction);

protected:
    btVector3 m_heading;
    btVector3 m_side;
    btScalar  m_prevAngle;
    double    m_maxVelocity;
    CMovingEntity();

};

#endif // CMOVINGENTITY_H_
