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


#include "CRectangle.h"


CRectangle::CRectangle()
{
    m_topLeft = new btVector3();
    m_bottomRight = new btVector3();
}


CRectangle::CRectangle(btVector3 *topLeft, btVector3 *bottomRight)
{
    m_topLeft = new btVector3(topLeft->x(), topLeft->y(), topLeft->z());
    m_bottomRight = new btVector3(bottomRight->x(), bottomRight->y(), bottomRight->z());
}


CRectangle::~CRectangle()
{
    delete m_topLeft;
    delete m_bottomRight;
}


void CRectangle::setTopLeft(btVector3 *pos)
{
    m_topLeft->setX(pos->x());
    m_topLeft->setY(pos->y());
    m_topLeft->setZ(pos->z());
    m_topLeft->setW(btScalar(0.0));
}


void CRectangle::setBottomRight(btVector3 *pos)
{
    m_bottomRight->setX(pos->x());
    m_bottomRight->setY(pos->y());
    m_bottomRight->setZ(pos->z());
    m_bottomRight->setW(btScalar(0.0));
}


btVector3* CRectangle::getTopLeft() const
{
    return m_topLeft;
}


btVector3* CRectangle::getBottomRight() const
{
    return m_bottomRight;
}


bool CRectangle::isInside(btVector3 *point) const
{
    bool isInside = false;
    btScalar x = point->x();
    btScalar z = point->z();
    if((x < m_topLeft->x() && x > m_bottomRight->x()) &&
       (z > m_topLeft->z() && z < m_bottomRight->z())) {
        isInside = true;
    }
    return isInside;
}
