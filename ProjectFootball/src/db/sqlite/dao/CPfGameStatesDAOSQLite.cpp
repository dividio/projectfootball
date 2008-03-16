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
*       generated by dia/DAOcodegen.py                                        *
*       Version: 1.10                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfGameStatesDAOSQLite.h"

CPfGameStatesDAOSQLite::CPfGameStatesDAOSQLite(sqlite3 *database)
  : CPfGameStatesDAOSQLiteEntity(database)
{
}

CPfGameStatesDAOSQLite::~CPfGameStatesDAOSQLite()
{
}

CPfGameStates* CPfGameStatesDAOSQLite::findByXState(int XState)
{
    std::ostringstream stream;
    stream << XState;
    return findByXState(stream.str());
}

CPfGameStates* CPfGameStatesDAOSQLite::findByXState(const std::string &XState)
{
    std::string sql("SELECT * FROM PF_GAME_STATES WHERE ");
    sql = sql+"X_STATE='"+XState+"'";
    return loadRegister(sql);
}

CPfGameStates* CPfGameStatesDAOSQLite::findBySState(const std::string &SState)
{
    std::string sql("SELECT * FROM PF_GAME_STATES WHERE ");
    sql = sql+"S_STATE='"+SState+"'";
    return loadRegister(sql);
}

