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


#ifndef __CStrategicPosition_H__
#define __CStrategicPosition_H__

#include "../../../bullet/btBulletDynamicsCommon.h"
#include "../../../utils/geometry/CRectangle.h"


enum FormationType
{
    FT_Initial,
    FT_Offensive,
    FT_Defensive
};

class CStrategicPosition
{
public:
    CStrategicPosition();
    ~CStrategicPosition();

    void setAttractionX(float attrX);
    void setAttractionZ(float attrZ);
    void setBehindBall(bool behind);
    void setInitialPosition(btVector3 *pos);
    void setDefensivePosition(btVector3 *pos);
    void setOffensivePosition(btVector3 *pos);
    void setCurrentPosition(btVector3 *pos);
    void setPlayingArea(btVector3 *topLeft, btVector3 *bottomRight);

    float       getAttractionX();
    float       getAttractionZ();
    bool        getBehindBall();
    btVector3*  getPosition(FormationType type) const;
    btVector3*  getInitialPosition() const;
    btVector3*  getDefensivePosition() const;
    btVector3*  getOffensivePosition() const;
    btVector3*  getCurrentPosition() const;
    CRectangle* getPlayingArea() const;

private:
    float       m_attractionX;
    float       m_attractionZ;
    bool        m_behindBall;
    btVector3  *m_initialPosition;
    btVector3  *m_defensivePosition;
    btVector3  *m_offensivePosition;
    btVector3  *m_currentPosition;
    CRectangle *m_playingArea;
};

#endif // __CStrategicPosition_H__
