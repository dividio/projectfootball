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

class CGameState
{
public:
	CGameState(std::string idGameState, IDAOFactory *daoFactory, CGameReportRegister *reportRegister, IGameEventStrategy *eventStrategy);
	virtual ~CGameState();

    IDAOFactory*           getIDAOFactory();
    IGameEventStrategy*    getIGameEventStrategy();
	CGameReportRegister*   getCGameReportRegister();
	CGameOptionManager*    getCGameOptionManager();

private:
    std::string          m_idGameState;
    IDAOFactory         *m_daoFactory;
    IGameEventStrategy  *m_eventStrategy;
    CGameReportRegister *m_reportRegister;
    CGameOptionManager  *m_optionManager;
};

#endif /*CGAMESTATE_H_*/
