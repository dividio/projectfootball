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
#include "CTeam.h"
#include "../fsm/CStateMachine.h"

enum GameMode {BEFORE_START, PLAY_ON, HALF_TIME, END
    ,KICK_OFF, KICK_IN, CORNER_KICK, GOAL_KICK};


/**
 * This class implements football rules and control the game mode.
 */
class CReferee: public CMovingEntity
{
public:
    static char* m_pCtorName;

    CReferee();
    ~CReferee();

    bool handleMessage(const CMessage &msg);
    void update();

    CStateMachine<CReferee>* getFSM();
    CTeam*                   getKickTeam();
    btVector3                getKickPosition();
    CTeam*                   getNextTimeKickOffTeam();
    CFootballPlayer*         getLastPlayerTouch();
    GameMode                 getGameMode();
    std::string              getGameModeString();
    int                      getCycle() const;
    int                      getMinute() const;
    int                      getMatchDuration() const;
    int                      getHomeScore() const;
    int                      getAwayScore() const;


    void setMatchDuration(int cycles);
    void setHomeTeamInSideLeft(bool left);
    void setKickTeam(CTeam *team);
    void setKickPosition(btVector3 &pos);
    void setNextTimeKickOffTeam(CTeam *team);
    void setLastPlayerTouch(CFootballPlayer *player);
    void setGameMode(GameMode newGameMode);
    void addHomeGoal(CFootballPlayer *player);
    void addAwayGoal(CFootballPlayer *player);
    void incCycle();

    bool isHomeTeamInSideLeft() const;
    bool isMoveLegal() const;

private:
    int                          m_cycle;
    int                          m_matchDuration;
    int                          m_homeScore;
    int                          m_awayScore;
    bool                         m_homeSideLeft;
    GameMode                     m_currentGameMode;
    CFootballPlayer             *m_lastPlayerTouch;
    btVector3                   *m_kickPosition;
    CTeam                       *m_kickTeam;
    CTeam                       *m_nextTimeKickOffTeam;
    CStateMachine<CReferee>     *m_stateMachine;

};

#endif // __CReferee_H__
