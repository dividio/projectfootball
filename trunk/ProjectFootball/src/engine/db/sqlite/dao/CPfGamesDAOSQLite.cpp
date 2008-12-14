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
*       Version: 1.20                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfGamesDAOSQLite.h"

CPfGamesDAOSQLite::CPfGamesDAOSQLite(sqlite3 *database)
  : CPfGamesDAOSQLiteEntity(database)
{
}

CPfGamesDAOSQLite::~CPfGamesDAOSQLite()
{
}

std::vector<CPfGames*>* CPfGamesDAOSQLite::findByXFkUser(int XFkUser)
{
    std::ostringstream stream;
    stream << XFkUser;
    return findByXFkUser(stream.str());
}

std::vector<CPfGames*>* CPfGamesDAOSQLite::findByXFkUser(const std::string &XFkUser)
{
    std::string sql("SELECT * FROM PF_GAMES WHERE ");
    sql = sql+"X_FK_USER='"+XFkUser+"' ORDER BY D_LAST_SAVED DESC";
    return loadVector(sql);
}

std::vector<CPfGames*>* CPfGamesDAOSQLite::findByXFkUserAndSGameType(int XFkUser, const std::string &SGameType)
{
    std::ostringstream stream;
    stream << XFkUser;
    return findByXFkUserAndSGameType(stream.str(), SGameType);
}

std::vector<CPfGames*>* CPfGamesDAOSQLite::findByXFkUserAndSGameType(const std::string &XFkUser, const std::string &SGameType)
{
    std::string sql("SELECT * FROM PF_GAMES WHERE ");
    sql = sql+"X_FK_USER='"+XFkUser+"' AND S_GAME_TYPE='"+SGameType+"' ORDER BY D_LAST_SAVED DESC";
    return loadVector(sql);
}

CPfGames* CPfGamesDAOSQLite::findByXGame(int XGame)
{
    std::ostringstream stream;
    stream << XGame;
    return findByXGame(stream.str());
}

CPfGames* CPfGamesDAOSQLite::findByXGame(const std::string &XGame)
{
    std::string sql("SELECT * FROM PF_GAMES WHERE ");
    sql = sql+"X_GAME='"+XGame+"'";
    return loadRegister(sql);
}

std::vector<CPfGames*>* CPfGamesDAOSQLite::findBySGameName(const std::string &SGameName)
{
    std::string sql("SELECT * FROM PF_GAMES WHERE ");
    sql = sql+"S_GAME_NAME='"+SGameName+"'";
    return loadVector(sql);
}

std::vector<CPfGames*>* CPfGamesDAOSQLite::findBySGameType(const std::string &SGameType)
{
    std::string sql("SELECT * FROM PF_GAMES WHERE ");
    sql = sql+"S_GAME_TYPE='"+SGameType+"'";
    return loadVector(sql);
}
