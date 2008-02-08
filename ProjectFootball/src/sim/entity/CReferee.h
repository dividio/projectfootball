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


#ifndef __CReferee_H__
#define __CReferee_H__

#include <string>

#include "CMovingEntity.h"
#include "CFootballPlayer.h"

enum GameMode {BEFORE_START, PLAY_ON, HALF_TIME, END
    ,KICK_OFF_LEFT,KICK_OFF_RIGHT
    ,KICK_IN_LEFT,KICK_IN_RIGHT
    ,CORNER_KICK_LEFT,CORNER_KICK_RIGHT
    ,GOAL_KICK_LEFT,GOAL_KICK_RIGHT};

class CReferee: public CMovingEntity
{
public:
    CReferee();
    ~CReferee();

    bool handleMessage(const CMessage &msg);
    void update();
    void playerKickEvent(CFootballPlayer *player);
    bool isMoveLegal();
    GameMode getGameMode();
    std::string getGameModeString();

private:
    int m_cycle;
    GameMode m_currentGameMode;
    int m_homeScore;
    int m_awayScore;
    bool m_homeSideLeft;
    CFootballPlayer *m_lastPlayerKick;

    bool verifyBallPosition();
    void setGameMode(GameMode newGameMode);
};

#endif // __CReferee_H__
