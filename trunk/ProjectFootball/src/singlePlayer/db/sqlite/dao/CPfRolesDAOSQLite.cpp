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

#include "CPfRolesDAOSQLite.h"

CPfRolesDAOSQLite::CPfRolesDAOSQLite(sqlite3 *database)
  : CPfRolesDAOSQLiteEntity(database)
{
}

CPfRolesDAOSQLite::~CPfRolesDAOSQLite()
{
}

CPfRoles* CPfRolesDAOSQLite::findByXRole(int XRole)
{
    std::ostringstream stream;
    stream << XRole;
    return findByXRole(stream.str());
}

CPfRoles* CPfRolesDAOSQLite::findByXRole(const std::string &XRole)
{
    std::string sql("SELECT * FROM PF_ROLES WHERE ");
    sql = sql+"X_ROLE='"+XRole+"'";
    return loadRegister(sql);
}

CPfRoles* CPfRolesDAOSQLite::findByXFkDemarcation(int XFkDemarcation)
{
    std::ostringstream stream;
    stream << XFkDemarcation;
    return findByXFkDemarcation(stream.str());
}

CPfRoles* CPfRolesDAOSQLite::findByXFkDemarcation(const std::string &XFkDemarcation)
{
    std::string sql("SELECT * FROM PF_ROLES WHERE ");
    sql = sql+"X_FK_DEMARCATION='"+XFkDemarcation+"'";
    return loadRegister(sql);
}

CPfRoles* CPfRolesDAOSQLite::findByXTeamPlayer(int XTeamPlayer)
{
    std::ostringstream stream;
    stream << XTeamPlayer;
    return findByXTeamPlayer(stream.str());
}

CPfRoles* CPfRolesDAOSQLite::findByXTeamPlayer(const std::string &XTeamPlayer)
{
    std::string sql("SELECT R.* FROM PF_ROLES R ");
    sql = sql+"JOIN PF_ROLES_BY_TEAM_PLAYERS RTP ON RTP.X_FK_ROLE = R.X_ROLE ";
    sql = sql+"WHERE X_FK_TEAM_PLAYER='"+XTeamPlayer+"' ";
    sql = sql+"ORDER BY RTP.N_SKILL DESC";
    return loadRegister(sql);
}

CPfRoles* CPfRolesDAOSQLite::findInStrategicPositionByXFormationAndLineUpOrder(int XFormation, int LineUpOrder)
{
	std::ostringstream stream1;
	std::ostringstream stream2;
	stream1 << XFormation;
	stream2 << LineUpOrder;
	return findInStrategicPositionByXFormationAndLineUpOrder(stream1.str(), stream2.str());
}

CPfRoles* CPfRolesDAOSQLite::findInStrategicPositionByXFormationAndLineUpOrder(const std::string &XFormation, const std::string &LineUpOrder)
{
	std::string sql("SELECT R.* FROM PF_ROLES R ");
	sql = sql+"JOIN PF_STRATEGIC_POSITIONS SP ON SP.X_FK_ROLE = R.X_ROLE ";
	sql = sql+"WHERE SP.X_FK_FORMATION='"+XFormation+"' ";
	sql = sql+"AND SP.N_LINEUP_ORDER='"+LineUpOrder+"' ";
	return loadRegister(sql);
}
