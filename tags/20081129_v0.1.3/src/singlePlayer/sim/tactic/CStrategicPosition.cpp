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


#include "CStrategicPosition.h"

#include "../../../bullet/LinearMath/btVector3.h"
#include "../../../utils/geometry/CRectangle.h"


CStrategicPosition::CStrategicPosition()
{
    m_attractionX       = 0.0;
    m_attractionZ       = 0.0;
    m_behindBall        = false;
    m_initialPosition   = new btVector3();
    m_defensivePosition = new btVector3();
    m_offensivePosition = new btVector3();
    m_currentPosition   = m_initialPosition;
    m_playingArea       = new CRectangle();
}


CStrategicPosition::~CStrategicPosition()
{
    delete m_initialPosition;
    delete m_defensivePosition;
    delete m_offensivePosition;
    delete m_playingArea;
}


void CStrategicPosition::setAttractionX(float attrX)
{
    m_attractionX = attrX;
}


void CStrategicPosition::setAttractionZ(float attrZ)
{
    m_attractionZ = attrZ;
}


void CStrategicPosition::setBehindBall(bool behind)
{
    m_behindBall = behind;
}


void CStrategicPosition::setInitialPosition(btVector3 *pos)
{
    m_initialPosition->setValue(pos->x(), pos->y(), pos->z());
}


void CStrategicPosition::setDefensivePosition(btVector3 *pos)
{
    m_defensivePosition->setValue(pos->x(), pos->y(), pos->z());
}


void CStrategicPosition::setOffensivePosition(btVector3 *pos)
{
    m_offensivePosition->setValue(pos->x(), pos->y(), pos->z());
}


void CStrategicPosition::setCurrentPosition(btVector3 *pos)
{
    m_currentPosition = pos;
}


void CStrategicPosition::setPlayingArea(btVector3 *topLeft, btVector3 *bottomRight)
{
    m_playingArea->setTopLeft(btVector3(topLeft->x(), topLeft->y(), topLeft->z()));
    m_playingArea->setBottomRight(btVector3(bottomRight->x(), bottomRight->y(), bottomRight->z()));
}


float CStrategicPosition::getAttractionX()
{
    return m_attractionX;
}


float CStrategicPosition::getAttractionZ()
{
    return m_attractionZ;
}


bool CStrategicPosition::getBehindBall()
{
    return m_behindBall;
}


btVector3* CStrategicPosition::getPosition(FormationType type) const
{
    btVector3 *pos = m_initialPosition;
    switch (type) {
        case FT_Initial:
            pos = m_initialPosition;
            break;
        case FT_Offensive:
            pos = m_offensivePosition;
            break;
        case FT_Defensive:
            pos = m_defensivePosition;
            break;
        default:
            pos = m_initialPosition;
            break;
    }
    return pos;
}


btVector3* CStrategicPosition::getInitialPosition() const
{
    return m_initialPosition;
}


btVector3* CStrategicPosition::getDefensivePosition() const
{
    return m_defensivePosition;
}


btVector3* CStrategicPosition::getOffensivePosition() const
{
    return m_offensivePosition;
}


btVector3* CStrategicPosition::getCurrentPosition() const
{
    return m_currentPosition;
}


CRectangle* CStrategicPosition::getPlayingArea() const
{
    return m_playingArea;
}
