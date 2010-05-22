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

#include "CPfFormationsDAOSQLite.h"

CPfFormationsDAOSQLite::CPfFormationsDAOSQLite(sqlite3 *database)
  : CPfFormationsDAOSQLiteEntity(database)
{
}

CPfFormationsDAOSQLite::~CPfFormationsDAOSQLite()
{
}

CPfFormations* CPfFormationsDAOSQLite::findByXFkCoachOwner(int XFkCoachOwner)
{
    std::ostringstream stream;
    stream << XFkCoachOwner;
    return findByXFkCoachOwner(stream.str());
}

CPfFormations* CPfFormationsDAOSQLite::findByXFkCoachOwner(const std::string &XFkCoachOwner)
{
    std::string sql("SELECT * FROM PF_FORMATIONS WHERE ");
    sql = sql+"X_FK_COACH_OWNER='"+XFkCoachOwner+"'";
    return loadRegister(sql);
}

CPfFormations* CPfFormationsDAOSQLite::findByXFormation(int XFormation)
{
    std::ostringstream stream;
    stream << XFormation;
    return findByXFormation(stream.str());
}

CPfFormations* CPfFormationsDAOSQLite::findByXFormation(const std::string &XFormation)
{
    std::string sql("SELECT * FROM PF_FORMATIONS WHERE ");
    sql = sql+"X_FORMATION='"+XFormation+"'";
    return loadRegister(sql);
}

CPfFormations* CPfFormationsDAOSQLite::findActiveByXTeam(int XTeam, const std::string &timestamp)
{
	std::ostringstream stream;
	stream << XTeam;
	return findActiveByXTeam(stream.str(), timestamp);
}

CPfFormations* CPfFormationsDAOSQLite::findActiveByXTeam(const std::string &XTeam, const std::string &timestamp)
{
	std::string sql("SELECT F.* FROM PF_FORMATIONS F ");
	sql = sql+"JOIN PF_COACHES C ON C.X_FK_FORMATION_SELECTED = F.X_FORMATION ";
	sql = sql+"JOIN PF_COACH_CONTRACTS CC ON CC.X_FK_COACH = C.X_COACH ";
	sql = sql+"WHERE CC.X_FK_TEAM='"+XTeam+"' ";
	sql = sql+"AND CC.D_BEGIN<='" + timestamp + "' AND (CC.D_END IS NULL OR CC.D_END>'" + timestamp + "')";
	return loadRegister(sql);
}

std::vector<CPfFormations*>* CPfFormationsDAOSQLite::findByXTeam(int XTeam, const std::string &timestamp)
{
	std::ostringstream stream;
	stream << XTeam;
	return findByXTeam(stream.str(), timestamp);
}

std::vector<CPfFormations*>* CPfFormationsDAOSQLite::findByXTeam(const std::string &XTeam, const std::string &timestamp)
{
	std::string sql("SELECT F.* FROM PF_FORMATIONS F ");
	sql = sql+"LEFT OUTER JOIN PF_COACH_CONTRACTS CC ON (CC.X_FK_COACH = F.X_FK_COACH_OWNER ";
	sql = sql+"AND CC.X_FK_TEAM='"+XTeam+"' ";
	sql = sql+"AND CC.D_BEGIN<='" + timestamp + "' AND (CC.D_END IS NULL OR CC.D_END>'" + timestamp + "')) ";
	sql = sql+"ORDER BY F.S_NAME DESC ";
	return loadVector(sql);
}
