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


#ifndef CFOOTBALLPLAYER_H_
#define CFOOTBALLPLAYER_H_


#include <string>

#include "CMovingEntity.h"
#include "../fsm/CStateMachine.h"

//Forward declarations
class CSimulationManager;
class CTeam;
class CSteeringBehaviors;
class CPfTeamPlayers;

/**
 * This class represents a football player in the simulation manager.
 */
class CFootballPlayer: public CMovingEntity
{
public:
    static std::string m_pCtorName;
    static CFootballPlayer* getPlayer(CBaseGameEntity *player);

    CFootballPlayer(CSimulationManager *simulationManager, const CPfTeamPlayers *teamPlayer, int number, CTeam *team, bool sideLeft);
    ~CFootballPlayer();

    double                          getMaxKickPower() const;
    double                          getMaxVelocity() const;
    CStateMachine<CFootballPlayer>* getFSM();
    CSteeringBehaviors*             getSteering() const;
    btVector3                       getStrategicPosition() const;
    btVector3                       getKickPosition() const;
    btVector3                       getHomeGoalFacing() const;
    CTeam*                          getTeam() const;
    int                             getXTeamPlayer();
    bool                            handleMessage(const CMessage &msg);
    bool                            isTeamLeft() const;
    bool                            isBallKickable() const;
    bool                            canDoActions();
    bool                            atHome();
    bool                            atKickPosition();
    bool                            canKickBall(int cycle);
    void                            update();
    void                            changeSide();

    CSimulationManager* getSimulationManager();

    void setWorldTransform(const btTransform& centerOfMassWorldTrans);

    /**
     * Makes a kick command for stopping the ball.
     */
    void freezeBall();

    /**
     * Makes a kick command for making the ball velocity equal to the given velocity.
     * @param velocity New velocity for the ball
     */
    void accelerateBallToVelocity(btVector3 velocity);

    /**
     * Makes a kick command for kicking the ball with an initial speed to take target point.
     * @param target Target point for the ball
     * @param speed Initial speed for the ball
     */
    void kickTo(btVector3 target, btScalar speed);

protected:
    void setGraphicTrans(btTransform trans);

private:
	CSimulationManager				*m_simulationManager;
    CStateMachine<CFootballPlayer>  *m_stateMachine;
    CSteeringBehaviors              *m_steeringBehavior;
    Ogre::SceneNode                 *m_ringNode;
    CPfTeamPlayers                  *m_teamPlayer;
    CTeam                           *m_team;
    bool                             m_canDoActions;
    bool                             m_sideLeft;
    int                              m_lastKickBallCycle;
    int                              m_number;
    double                           m_maxKickPower;
    double                           m_maxVelocity;
};

#endif // CFOOTBALLPLAYER_H_
