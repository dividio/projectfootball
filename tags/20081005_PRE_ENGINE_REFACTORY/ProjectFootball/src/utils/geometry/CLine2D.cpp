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

#include "CLine2D.h"

CLine2D::CLine2D()
{
    m_a = 0;
    m_b = 0;
    m_c = 0;
}


CLine2D::CLine2D(btScalar a, btScalar b, btScalar c)
{
    m_a = a;
    m_b = b;
    m_c = c;
}


CLine2D::CLine2D(const btVector3 &pointA, const btVector3 &pointB)
{
    // 1*y + bx + c = 0 => y = -bx - c
    // with -b the direction coefficient (or slope)
    // and c = - y - bx
    double temp = pointB.x() - pointA.x(); // determine the slope
    if(fabs(temp) < 0.0001) {
      // ay + bx + c = 0 with vertical slope=> a = 0, b = 1
      m_a = 0.0;
      m_b = 1.0;
    } else {
      // y = (-b)x -c with -b the slope of the line
      m_a = 1.0;
      m_b = -(pointB.z() - pointA.z())/temp;
    }
    // ay + bx + c = 0 ==> c = -a*y - b*x
    m_c =  - m_a*pointB.z()  - m_b * pointB.x();
}


CLine2D::~CLine2D()
{
}


btVector3 CLine2D::getIntersectionPoint(const CLine2D &line) const
{
//    btVector3 point(0,0,0);
//    btScalar x, z;
//    btScalar a = line.getACoefficient();
//    btScalar b = line.getBCoefficient();
//    btScalar c = line.getCCoefficient();
//    if((m_a/m_b) != (a/b)) {
//        x = (-c + m_c)/(-m_b + b);
//        z = (c*m_b - m_c*b) / (-m_b + b);
//        point.setX(x);
//        point.setZ(z);
//    }
//    return point;
    btScalar a = line.getACoefficient();
    btScalar b = line.getBCoefficient();
    btScalar c = line.getCCoefficient();
    double x = 0.0, y = 0.0;
    if((m_a / m_b) != (a / b)) { // If equal then lines are parallel, no intersection
        if( m_a == 0 ) {         // bx + c = 0 and a2*y + b2*x + c2 = 0 ==> x = -c/b
          x = -m_c/m_b;          // calculate x using the current line
          y =  -(b*x+c)/a;       // and calculate the y using the second line
        }
        else if( a == 0 ) {     // ay + bx + c = 0 and b2*x + c2 = 0 ==> x = -c2/b2
         x = -c/b;              // calculate x using
         y = -(m_b*x+m_c)/m_a;  // 2nd line and calculate y using current line
        } else {
        // ay + bx + c = 0 and a2y + b2*x + c2 = 0
        // y = (-b2/a2)x - c2/a2
        // bx = -a*y - c =>  bx = -a*(-b2/a2)x -a*(-c2/a2) - c ==>
        // ==> a2*bx = a*b2*x + a*c2 - a2*c ==> x = (a*c2 - a2*c)/(a2*b - a*b2)
        // calculate x using the above formula and the y using the current line
          x = (m_a*c - a*m_c)/(a*m_b - m_a*b);
          y = -(m_b*x+m_c)/m_a;
        }
    }

    return btVector3( x, 0, y );
}


btScalar CLine2D::getACoefficient() const
{
    return m_a;
}


btScalar CLine2D::getBCoefficient() const
{
    return m_b;
}


btScalar CLine2D::getCCoefficient() const
{
    return m_c;
}
