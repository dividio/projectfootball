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

#ifndef CSIMULATIONMANAGER_H_
#define CSIMULATIONMANAGER_H_

#include <string>
#include <vector>

//Forward declarations
class CSinglePlayerGame;
class CSimulationWorld;
class CFootballPlayer;
class CFormation;
class CTeam;
class CReferee;
class CBall;
class CField;
class CTimer;
class CPfMatches;
class CPfFormations;
class CGoalMatchEvent;
class btVector3;
class CSimulatorWindowHandler;


class CSimulationManager
{
public:
    CSimulationManager(int xMatch, CSinglePlayerGame &game, CSimulatorWindowHandler &simulatorWH);
    ~CSimulationManager();

    void update();

    void addToLog(const std::string &text);

    void startMatch();
    void goalMatchEvent(CTeam *teamScorer, CFootballPlayer *playerScorer, int minute, bool ownGoal);
    void endMatchEvent();
    void changeFormationEvent(int pos);
    void changePlayersSide();

    CSimulationWorld* getSimulationWorld();
    CReferee*         getReferee();
    CBall*            getBall();
    CField*           getField();
    CTeam*            getHomeTeam();
    CTeam*            getAwayTeam();


    //Information Methods
    const std::string& getHomeTeamName();
    const std::string& getAwayTeamName();
    btVector3 getBallPosition() const;
    int getMatchDuration() const;


    // Soccer Commands
    void dash(CFootballPlayer *player, btVector3 power);
    void move(CFootballPlayer *player, int x, int z);
    void kick(CFootballPlayer *player, btVector3 power);

private:
    CPfMatches						*m_match;
    std::vector<CGoalMatchEvent*> 	 m_goalEvents;
    CTimer 							*m_logicTimer;
    CTimer 							*m_physicsTimer;
    CTeam 							*m_homeTeam;
    CTeam 							*m_awayTeam;
    CReferee 						*m_referee;
    CBall 							*m_ball;
    CField 							*m_field;
    CSimulationWorld 				*m_simWorld;
    std::vector<CFootballPlayer*>   *m_homeTeamPlayers;
    std::vector<CFootballPlayer*>   *m_awayTeamPlayers;
    CFormation                      *m_homeFormation;
    CFormation                      *m_awayFormation;

    CSinglePlayerGame				&m_game;
    CSimulatorWindowHandler			&m_simulatorWindowHandler;

    // Simulation Options
    int                              m_maxBallVelocity;
    int                              m_maxPlayerVelocity;
    int                              m_maxKickPower;
    int                              m_maxKickDistance;
    int                              m_nearestPlayerToBallCycles;
    double                           m_nearestPlayerToBallTime;

    void truncateVector(btVector3 *v, double max);
    void calculateNearestPlayersToBall();

    std::vector<CFootballPlayer*>* loadTeamPlayers(CTeam *team);
    CFormation*                    loadFormation(CPfFormations *formation);

};

#endif // CSIMULATIONMANAGER_H_
