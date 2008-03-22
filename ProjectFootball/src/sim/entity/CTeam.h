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


#ifndef __CTeam_H__
#define __CTeam_H__

#include <string>
#include <vector>

#include "CBaseGameEntity.h"
#include "../fsm/CStateMachine.h"
#include "../tactic/CFormation.h"
#include "../tactic/CStrategicPosition.h"



class CFootballPlayer;

class CTeam: public CBaseGameEntity
{
public:
    static char* m_pCtorName;
    static CTeam* getTeam(CBaseGameEntity *team);

    CTeam(std::string name, bool sideLeft);
    ~CTeam();

    void setOpponentTeam(CTeam *team);
    CTeam* getOpponentTeam();
    std::string* getName();
    std::vector<CFootballPlayer*>* getPlayers();
    CFootballPlayer* getNearestPlayerToBall() const;
    int getKickPlayerID() const;
    CFormation* getCurrentFormation() const;
    std::vector<CFormation*>* getFormations();
    CStrategicPosition* getPlayerStrategicPosition(int formationPos) const;
    bool isKickForUs() const;
    bool isNearestPlayerToBall(CFootballPlayer* player) const;
    bool isNearestTeamMatePlayerToBall(CFootballPlayer* player) const;

    bool handleMessage(const CMessage &msg);
    void update();
    CStateMachine<CTeam>* getFSM();
    void changeSide();

private:
    std::string m_name;
    std::vector<CFootballPlayer*> m_players;
    CFootballPlayer *m_nearestPlayerToBall;
    CTeam *m_opponentTeam;
    CStateMachine<CTeam> *m_stateMachine;
    CFormation *m_currentFormation;
    std::vector<CFormation*> m_formations;

    void setNearestPlayersToBall();
    void setFormations();
};

#endif // __CTeam_H__
