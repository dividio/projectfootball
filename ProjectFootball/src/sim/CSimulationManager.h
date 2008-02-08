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


#ifndef __CSimulationManager_H__
#define __CSimulationManager_H__


#include <string>
#include <vector>

#include "entity/CFootballPlayer.h"
#include "entity/CReferee.h"
#include "entity/CBall.h"
#include "CSimulationWorld.h"


class CSimulationManager
{
public:
    CSimulationManager();
    ~CSimulationManager();

    void update();

    void startMatch();
    CSimulationWorld* getSimulationWorld();
    CReferee* getReferee();
    CBall* getBall();
    void changePlayersSide();

    //Information Methods
    std::string* getHomeTeamName();
    std::string* getAwayTeamName();
    btVector3 getBallPosition() const;
    bool isNearestPlayerToBall(CFootballPlayer* player) const;
    bool isNearestTeamMatePlayerToBall(CFootballPlayer* player) const;

    // Soccer Commands
    void dash(CFootballPlayer *player, int power);
    void move(CFootballPlayer *player, int x, int z);
    void kick(CFootballPlayer *player, int power, btVector3 direction);
    void turn(CFootballPlayer *player, int moment);

private:
    int m_timer;
    std::string m_homeTeamName;
    std::string m_awayTeamName;
    std::vector<CFootballPlayer*> m_homePlayers;
    std::vector<CFootballPlayer*> m_awayPlayers;
    CReferee *m_referee;
    CBall *m_ball;
    CSimulationWorld *m_simWorld;

    CFootballPlayer *m_homeNearestPlayer;
    CFootballPlayer *m_awayNearestPlayer;
    CFootballPlayer *m_nearestPlayer;

    void setNearestPlayersToBall();
};

#endif // __CSimulationManager_H__
