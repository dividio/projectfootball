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
*       Version: 1.6                                                          *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfGameOptionsDAOSQLite.h"

CPfGameOptionsDAOSQLite::CPfGameOptionsDAOSQLite(sqlite3 *database)
  : CPfGameOptionsDAOSQLiteEntity(database)
{
}

CPfGameOptionsDAOSQLite::~CPfGameOptionsDAOSQLite()
{
}

std::vector<CPfGameOptions*>* CPfGameOptionsDAOSQLite::findByXFkGame(int XFkGame)
{
    std::ostringstream stream;
    stream << XFkGame;
    return findByXFkGame(stream.str());
}

std::vector<CPfGameOptions*>* CPfGameOptionsDAOSQLite::findByXFkGame(const std::string &XFkGame)
{
    std::string sql("SELECT * FROM PF_EQUIPOS WHERE ");
    sql = sql+"X_FK_GAME='"+XFkGame+"'";
    return loadVector(sql);
}

CPfGameOptions* CPfGameOptionsDAOSQLite::findByXOption(int XOption)
{
    std::ostringstream stream;
    stream << XOption;
    return findByXOption(stream.str());
}

CPfGameOptions* CPfGameOptionsDAOSQLite::findByXOption(const std::string &XOption)
{
    std::string sql("SELECT * FROM PF_EQUIPOS WHERE ");
    sql = sql+"X_OPTION='"+XOption+"'";
    return loadRegister(sql);
}

CPfGameOptions* CPfGameOptionsDAOSQLite::findByXFkGameAndSCategoryAndSAttribute(int XFkGame, const std::string &SCategory, const std::string &SAttribute)
{
    std::ostringstream stream;
    stream << XFkGame;
    return findByXFkGameAndSCategoryAndSAttribute(stream.str(), SCategory, SAttribute);
}

CPfGameOptions* CPfGameOptionsDAOSQLite::findByXFkGameAndSCategoryAndSAttribute(const std::string &XFkGame, const std::string &SCategory, const std::string &SAttribute)
{
    std::string sql("SELECT * FROM PF_EQUIPOS WHERE ");
    sql = sql+"X_FK_GAME='"+XFkGame+"' AND S_CATEGORY='"+SCategory+"' AND S_ATTRIBUTE='"+SAttribute+"'";
    return loadRegister(sql);
}