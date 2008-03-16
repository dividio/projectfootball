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

#ifndef CGAMESTATE_H_
#define CGAMESTATE_H_

#include <string>

#include "../db/dao/factory/IDAOFactory.h"
#include "CGameReportRegister.h"
#include "event/strategy/IGameEventStrategy.h"
#include "option/CGameOptionManager.h"
#include "db/bean/CPfGames.h"

class CGameState
{
public:
	CGameState(int xGame);
	virtual ~CGameState();

	virtual void save();

    IDAOFactory*           getIDAOFactory();
    IGameEventStrategy*    getIGameEventStrategy();
	CGameReportRegister*   getCGameReportRegister();
	CGameOptionManager*    getCGameOptionManager();

	CPfTeams*              getPlayerTeam();
	CPfMatches*            getNextPlayerTeamMatch();

private:
    void setGameOptionsDefaultValues();

private:
    CPfGames                    *m_game;
    IDAOFactory                 *m_daoFactory;
    IGameEventStrategy          *m_eventStrategy;
    CGameReportRegister         *m_reportRegister;
    CGameOptionManager          *m_optionManager;
    CPfTeams                    *m_playerTeam;
    std::vector<CPfMatches*>    *m_matchesList;
};

#endif /*CGAMESTATE_H_*/
