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

#include "CPfTeamPlayerContractsDAOSQLite.h"

CPfTeamPlayerContractsDAOSQLite::CPfTeamPlayerContractsDAOSQLite(sqlite3 *database)
  : CPfTeamPlayerContractsDAOSQLiteEntity(database)
{
}

CPfTeamPlayerContractsDAOSQLite::~CPfTeamPlayerContractsDAOSQLite()
{
}

std::vector<CPfTeamPlayerContracts*>* CPfTeamPlayerContractsDAOSQLite::findByXFkTeamPlayer(int XFkTeamPlayer)
{
    std::ostringstream stream;
    stream << XFkTeamPlayer;
    return findByXFkTeamPlayer(stream.str());
}

std::vector<CPfTeamPlayerContracts*>* CPfTeamPlayerContractsDAOSQLite::findByXFkTeamPlayer(const std::string &XFkTeamPlayer)
{
    std::string sql("SELECT * FROM PF_TEAM_PLAYER_CONTRACTS WHERE ");
    sql = sql+"X_FK_TEAM_PLAYER='"+XFkTeamPlayer+"'";
    return loadVector(sql);
}

CPfTeamPlayerContracts* CPfTeamPlayerContractsDAOSQLite::findByXTeamPlayerContract(int XTeamPlayerContract)
{
    std::ostringstream stream;
    stream << XTeamPlayerContract;
    return findByXTeamPlayerContract(stream.str());
}

CPfTeamPlayerContracts* CPfTeamPlayerContractsDAOSQLite::findByXTeamPlayerContract(const std::string &XTeamPlayerContract)
{
    std::string sql("SELECT * FROM PF_TEAM_PLAYER_CONTRACTS WHERE ");
    sql = sql+"X_TEAM_PLAYER_CONTRACT='"+XTeamPlayerContract+"'";
    return loadRegister(sql);
}

std::vector<CPfTeamPlayerContracts*>* CPfTeamPlayerContractsDAOSQLite::findByXFkTeam(int XFkTeam)
{
    std::ostringstream stream;
    stream << XFkTeam;
    return findByXFkTeam(stream.str());
}

std::vector<CPfTeamPlayerContracts*>* CPfTeamPlayerContractsDAOSQLite::findByXFkTeam(const std::string &XFkTeam)
{
    std::string sql("SELECT * FROM PF_TEAM_PLAYER_CONTRACTS WHERE ");
    sql = sql+"X_FK_TEAM='"+XFkTeam+"'";
    return loadVector(sql);
}

CPfTeamPlayerContracts* CPfTeamPlayerContractsDAOSQLite::findActiveByXFkTeamAndXFkTeamPlayer(int XFkTeam, int XFkTeamPlayer)
{
    std::ostringstream sXFkTeam;
    sXFkTeam << XFkTeam;
    std::ostringstream sXFkTeamPlayer;
    sXFkTeamPlayer << XFkTeamPlayer;
    return findActiveByXFkTeamAndXFkTeamPlayer(sXFkTeam.str(), sXFkTeamPlayer.str());
}

CPfTeamPlayerContracts* CPfTeamPlayerContractsDAOSQLite::findActiveByXFkTeamAndXFkTeamPlayer(const std::string &XFkTeam, const std::string &XFkTeamPlayer)
{
    std::string sql("SELECT * FROM PF_TEAM_PLAYER_CONTRACTS WHERE ");
    sql = sql+"X_FK_TEAM='"+XFkTeam+"' ";
    sql = sql+"  AND X_FK_TEAM_PLAYER='"+XFkTeamPlayer+"' ";
    sql = sql+"  AND D_BEGIN<=CURRENT_TIMESTAMP AND (D_END IS NULL OR D_END>CURRENT_TIMESTAMP)";
    return loadRegister(sql);
}
