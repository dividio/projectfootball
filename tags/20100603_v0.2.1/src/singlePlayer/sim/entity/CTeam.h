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


#ifndef CTEAM_H_
#define CTEAM_H_

#include <string>
#include <vector>

#include "CBaseGameEntity.h"
#include "../fsm/CStateMachine.h"


//Forward declarations
class CSimulationManager;
class CFootballPlayer;
class CFormation;
class CStrategicPosition;
class CPfTeams;
class CPfTeamPlayers;

class CTeam: public CBaseGameEntity
{
public:
    static std::string m_pCtorName;
    static CTeam* getTeam(CBaseGameEntity *team);

    CTeam(CSimulationManager *simulationManager, const CPfTeams *team, bool sideLeft);
    ~CTeam();

    void assignSide(bool side);
    void setOpponentTeam(CTeam *team);
    void setControllingPlayer(CFootballPlayer *player);
    void setNearestPlayerToBall(CFootballPlayer *player);
    void setPlayers(std::vector<CFootballPlayer*>* playersVector);
    void setFormation(CFormation *formation);

    CSimulationManager* getSimulationManager();

    CTeam*                          getOpponentTeam();
    const std::string&              getName();
    std::vector<CFootballPlayer*>*  getPlayers();
    CFootballPlayer*                getNearestPlayerToBall() const;
    CFootballPlayer*                getControllingPlayer() const;
    int                             getKickPlayerID() const;
    CFormation*                     getCurrentFormation() const;
    CStrategicPosition*             getPlayerStrategicPosition(int formationPos) const;
    CStateMachine<CTeam>*           getFSM();
    int                             getXTeam();

    bool isKickForUs() const;
    bool inControl() const;
    bool isNearestPlayerToBall(CFootballPlayer* player) const;
    bool isNearestTeamMatePlayerToBall(CFootballPlayer* player) const;
    bool isBallInOwnPenaltyArea() const;
    bool isBallInOpponentPenaltyArea() const;
    bool isSideLeft() const;

    bool handleMessage(const CMessage &msg);
    void update();
    void changeSide();

private:
	CSimulationManager				*m_simulationManager;
    CPfTeams                        *m_team;
    std::vector<CFootballPlayer*>   *m_players;
    CFootballPlayer                 *m_nearestPlayerToBall;
    CFootballPlayer                 *m_controllingPlayer;
    CTeam                           *m_opponentTeam;
    CStateMachine<CTeam>            *m_stateMachine;
    CFormation                      *m_currentFormation;
    bool                             m_sideLeft;

};

#endif // CTEAM_H_
