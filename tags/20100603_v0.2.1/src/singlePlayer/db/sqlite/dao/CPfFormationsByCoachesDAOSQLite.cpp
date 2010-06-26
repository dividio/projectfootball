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
*       Version: 1.23                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfFormationsByCoachesDAOSQLite.h"

CPfFormationsByCoachesDAOSQLite::CPfFormationsByCoachesDAOSQLite(sqlite3 *database)
  : CPfFormationsByCoachesDAOSQLiteEntity(database)
{
}

CPfFormationsByCoachesDAOSQLite::~CPfFormationsByCoachesDAOSQLite()
{
}

CPfFormationsByCoaches* CPfFormationsByCoachesDAOSQLite::findByXFkFormation(int XFkFormation)
{
    std::ostringstream stream;
    stream << XFkFormation;
    return findByXFkFormation(stream.str());
}

CPfFormationsByCoaches* CPfFormationsByCoachesDAOSQLite::findByXFkFormation(const std::string &XFkFormation)
{
    std::string sql("SELECT * FROM PF_FORMATIONS_BY_COACHES WHERE ");
    sql = sql+"X_FK_FORMATION='"+XFkFormation+"'";
    return loadRegister(sql);
}

CPfFormationsByCoaches* CPfFormationsByCoachesDAOSQLite::findByXFkCoach(int XFkCoach)
{
    std::ostringstream stream;
    stream << XFkCoach;
    return findByXFkCoach(stream.str());
}

CPfFormationsByCoaches* CPfFormationsByCoachesDAOSQLite::findByXFkCoach(const std::string &XFkCoach)
{
    std::string sql("SELECT * FROM PF_FORMATIONS_BY_COACHES WHERE ");
    sql = sql+"X_FK_COACH='"+XFkCoach+"'";
    return loadRegister(sql);
}

CPfFormationsByCoaches* CPfFormationsByCoachesDAOSQLite::findByXFormationByCoach(int XFormationByCoach)
{
    std::ostringstream stream;
    stream << XFormationByCoach;
    return findByXFormationByCoach(stream.str());
}

CPfFormationsByCoaches* CPfFormationsByCoachesDAOSQLite::findByXFormationByCoach(const std::string &XFormationByCoach)
{
    std::string sql("SELECT * FROM PF_FORMATIONS_BY_COACHES WHERE ");
    sql = sql+"X_FORMATION_BY_COACH='"+XFormationByCoach+"'";
    return loadRegister(sql);
}
