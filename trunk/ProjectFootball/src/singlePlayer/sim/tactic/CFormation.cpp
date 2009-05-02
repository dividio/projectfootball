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


#include "CFormation.h"

#include "../../../exceptions/PFException.h"
#include "../../../utils/CLog.h"

CFormation::CFormation()
{
    int i = 0;
    for(i = 0; i < 11; i++) {
        m_positions[i] = new CStrategicPosition();
    }
    m_name = "";
}


CFormation::CFormation(const char* name)
{
    int i = 0;
    for(i = 0; i < 11; i++) {
        m_positions[i] = new CStrategicPosition();
    }
    m_name = name;
}


CFormation::~CFormation()
{
    int i = 0;
    for(i = 0; i < 11; i++) {
        delete m_positions[i];
    }
}


CStrategicPosition* CFormation::getPlayerStrategicPosition(int player) const
{
    CStrategicPosition* pos = 0;
    if(player >= 11 || player < 0) {
        throw PFEXCEPTION("Can't access to CStrategicPosition number %d", player);
    } else {
        pos = m_positions[player];
    }
    return pos;
}


const std::string& CFormation::getName()
{
    return m_name;
}


FormationType CFormation::getCurrentFormationType()
{
    return m_currentFormationType;
}


int CFormation::getKickOffPlayerId() const
{
    return m_kickOffPlayerId;
}


int CFormation::getKickInPlayerId() const
{
    return m_kickInPlayerId;
}


int CFormation::getRightCornerKickPlayerId() const
{
    return m_rightCornerKickPlayerId;
}


int CFormation::getLeftCornerKickPlayerId() const
{
    return m_leftCornerKickPlayerId;
}


int CFormation::getRightTrowInPlayerId() const
{
    return m_rightTrowInPlayerId;
}


int CFormation::getLeftTrowInPlayerId() const
{
    return m_leftTrowInPlayerId;
}


int CFormation::getGoalKickPlayerId() const
{
    return m_goalKickPlayerId;
}


void CFormation::setCurrentFormationType(FormationType type)
{
    m_currentFormationType = type;
    int i = 0;
    btVector3 *newPos;
    for(i = 0; i < 11; i++) {
        newPos = m_positions[i]->getPosition(type);
        m_positions[i]->setCurrentPosition(newPos);
    }
}


void CFormation::setKickOffPlayerId(int player)
{
    m_kickOffPlayerId = player;
}


void CFormation::setKickInPlayerId(int player)
{
    m_kickInPlayerId = player;
}


void CFormation::setRightCornerKickPlayerId(int player)
{
    m_rightCornerKickPlayerId = player;
}


void CFormation::setLeftCornerKickPlayerId(int player)
{
    m_leftCornerKickPlayerId = player;
}


void CFormation::setRightTrowInPlayerId(int player)
{
    m_rightTrowInPlayerId = player;
}


void CFormation::setLeftTrowInPlayerId(int player)
{
    m_leftTrowInPlayerId = player;
}


void CFormation::setGoalKickPlayerId(int player)
{
    m_goalKickPlayerId = player;
}
