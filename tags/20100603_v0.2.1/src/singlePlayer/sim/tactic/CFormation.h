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


#ifndef CFORMATION_H_
#define CFORMATION_H_

#include <string>

#include "CStrategicPosition.h"


class CFormation
{
public:
    CFormation();
    CFormation(const char* name);
    ~CFormation();

    CStrategicPosition* getPlayerStrategicPosition(int player) const;
    const std::string&  getName();
    FormationType       getCurrentFormationType();
    int                 getKickOffPlayerId() const;
    int                 getKickInPlayerId() const;
    int                 getRightCornerKickPlayerId() const;
    int                 getLeftCornerKickPlayerId() const;
    int                 getRightTrowInPlayerId() const;
    int                 getLeftTrowInPlayerId() const;
    int                 getGoalKickPlayerId() const;

    void setCurrentFormationType(FormationType type);
    void setKickOffPlayerId(int player);
    void setKickInPlayerId(int player);
    void setRightCornerKickPlayerId(int player);
    void setLeftCornerKickPlayerId(int player);
    void setRightTrowInPlayerId(int player);
    void setLeftTrowInPlayerId(int player);
    void setGoalKickPlayerId(int player);

private:
    std::string             m_name;
    FormationType           m_currentFormationType;
    CStrategicPosition     *m_positions[11];
    int                     m_kickOffPlayerId;
    int                     m_kickInPlayerId;
    int                     m_rightCornerKickPlayerId;
    int                     m_leftCornerKickPlayerId;
    int                     m_rightTrowInPlayerId;
    int                     m_leftTrowInPlayerId;
    int                     m_goalKickPlayerId;
};

#endif // CFORMATION_H_
