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


#ifndef __CFootballPlayer_H__
#define __CFootballPlayer_H__


#include <string>

#include "CBaseAgent.h"
#include "../CSteeringBehaviors.h"
#include "../fsm/CStateMachine.h"
#include "../db/bean/CPfTeamPlayers.h"


class CTeam;

class CFootballPlayer: public CBaseAgent
{
public:
    static char* m_pCtorName;
    static CFootballPlayer* getPlayer(CBaseGameEntity *player);

    CFootballPlayer(int XTeamPlayer, int number, CTeam *team, bool sideLeft);
    ~CFootballPlayer();

    CStateMachine<CFootballPlayer>* getFSM();
    CSteeringBehaviors*             getSteering() const;
    btVector3                       getStrategicPosition() const;
    CTeam*                          getTeam() const;
    int                             getXTeamPlayer();
    bool                            isTeamLeft() const;
    bool                            isBallKickable() const;
    bool                            canDoActions();
    bool                            canKickBall(int cycle);
    bool                            atHome();
    bool                            atKickPosition();
    bool                            handleMessage(const CMessage &msg);
    void                            update();
    void                            changeSide();

    void setWorldTransform(const btTransform& centerOfMassWorldTrans);

protected:
    void setGraphicTrans(btTransform trans);

private:
    CStateMachine<CFootballPlayer>  *m_stateMachine;
    CSteeringBehaviors              *m_steeringBehavior;
    Ogre::SceneNode                 *m_ringNode;
    CPfTeamPlayers                  *m_teamPlayer;
    CTeam                           *m_team;
    bool                             m_canDoActions;
    bool                             m_sideLeft;
    int                              m_lastKickBallCycle;
    int                              m_number;
};

#endif // __CFootballPlayer_H__
