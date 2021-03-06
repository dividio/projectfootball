/******************************************************************************
* Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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
*       Version: 1.21                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfSeasonsDAOSQLite.h"

CPfSeasonsDAOSQLite::CPfSeasonsDAOSQLite(sqlite3 *database)
  : CPfSeasonsDAOSQLiteEntity(database)
{
}

CPfSeasonsDAOSQLite::~CPfSeasonsDAOSQLite()
{
}

CPfSeasons* CPfSeasonsDAOSQLite::findByXSeason(int XSeason)
{
    std::ostringstream stream;
    stream << XSeason;
    return findByXSeason(stream.str());
}

CPfSeasons* CPfSeasonsDAOSQLite::findByXSeason(const std::string &XSeason)
{
    std::string sql(
    		"SELECT * "
    		"FROM PF_SEASONS ");
    sql +=  "WHERE X_SEASON='"+XSeason+"'";
    return loadRegister(sql);
}

CPfSeasons* CPfSeasonsDAOSQLite::findLastSeason()
{
	return loadRegister("SELECT * FROM PF_SEASONS ORDER BY N_YEAR DESC");
}

std::vector<CPfSeasons*>* CPfSeasonsDAOSQLite::findAll()
{
    std::string sql("SELECT * FROM PF_SEASONS ORDER BY N_YEAR ASC");
    return loadVector(sql);
}
