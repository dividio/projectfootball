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
    m_topLeft = btVector3();
    m_bottomRight = btVector3();
}


CRectangle::CRectangle(const btVector3 &topLeft, const btVector3 &bottomRight)
{
    m_topLeft.setValue(topLeft.x(), topLeft.y(), topLeft.z());
    m_bottomRight.setValue(bottomRight.x(), bottomRight.y(), bottomRight.z());
}


CRectangle::~CRectangle()
{

}


void CRectangle::setTopLeft(const btVector3 &pos)
{
    m_topLeft.setValue(pos.x(), pos.y(), pos.z());
}


void CRectangle::setBottomRight(const btVector3 &pos)
{
    m_bottomRight.setValue(pos.x(), pos.y(), pos.z());
}


btVector3 CRectangle::getTopLeft() const
{
    return m_topLeft;
}


btVector3 CRectangle::getBottomRight() const
{
    return m_bottomRight;
}


bool CRectangle::isInside(const btVector3 &point) const
{
    bool isInside = false;
    btScalar x = point.x();
    btScalar z = point.z();
    if((x < m_topLeft.x() && x > m_bottomRight.x()) &&
       (z > m_topLeft.z() && z < m_bottomRight.z())) {
        isInside = true;
    }
    return isInside;
}
