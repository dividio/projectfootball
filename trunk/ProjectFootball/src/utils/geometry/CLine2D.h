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


#ifndef __CLine2D_H__
#define __CLine2D_H__

#include "../../bullet/btBulletDynamicsCommon.h"

/** This class represents lines in 2D by the formula ay + bx + c = 0.
 *  b= -m = -(y2-y1)/(x2-x1) and c = -b' = -(y1 - b*x1) in classic y = mx + b' formula
 */
class CLine2D
{
public:
    CLine2D();
    CLine2D(btScalar a, btScalar b, btScalar c);

    /** This method calculates the line between two points (x1,z1) (x2,z2) where
     *  b=-(z2-z1)/(x2-x1) and c = -(z1 - b*x1)
     */
    CLine2D(const btVector3 &pointA, const btVector3 &pointB);
    ~CLine2D();

    btVector3 getIntersectionPoint(const CLine2D &line) const;
    btScalar  getACoefficient() const;
    btScalar  getBCoefficient() const;
    btScalar  getCCoefficient() const;

private:
    btScalar m_a;
    btScalar m_b;
    btScalar m_c;
};

#endif // __CLine2D_H__
