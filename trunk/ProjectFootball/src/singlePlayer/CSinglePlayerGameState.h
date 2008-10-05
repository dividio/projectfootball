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

#ifndef CSINGLEPLAYERGAMESTATE_H_
#define CSINGLEPLAYERGAMESTATE_H_

#include <string>

// TODO: Remove engine dependency
#include "../engine/IGameState.h"
#include "db/dao/factory/IDAOFactory.h"
#include "db/sqlite/dao/factory/CDAOFactorySQLite.h"
#include "../engine/CGameReportRegister.h"
#include "event/strategy/IGameEventStrategy.h"
#include "option/CGameOptionManager.h"
#include "../engine/db/bean/CPfGames.h"

class CSinglePlayerGameState : public IGameState
{
public:
	CSinglePlayerGameState(int xGame);
	virtual ~CSinglePlayerGameState();

	virtual void save();

    virtual IDAOFactory*           getIDAOFactory();
    virtual IGameEventStrategy*    getIGameEventStrategy();
    virtual CGameReportRegister*   getCGameReportRegister();
    virtual CGameOptionManager*    getCGameOptionManager();

private:
    void setGameOptionsDefaultValues();
    void copyFile(const std::string &origin, const std::string &destination);

private:
    CPfGames                    *m_game;
    CDAOFactorySQLite           *m_daoFactory;
    IGameEventStrategy          *m_eventStrategy;
    CGameReportRegister         *m_reportRegister;
    CGameOptionManager          *m_optionManager;
    std::string                 m_database_filepath;
    std::string                 m_database_tmp_filepath;
};

#endif /*CSINGLEPLAYERGAMESTATE_H_*/
