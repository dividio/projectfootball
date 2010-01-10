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

#ifndef CPFTEAMPLAYERSDAOSQLITE_H_
#define CPFTEAMPLAYERSDAOSQLITE_H_

#include <string>
#include <sqlite3.h>

#include "entity/CPfTeamPlayersDAOSQLiteEntity.h"
#include "../../bean/CPfTeamPlayers.h"

class CPfTeamPlayersDAOSQLite : public CPfTeamPlayersDAOSQLiteEntity
{
public:
    CPfTeamPlayersDAOSQLite(sqlite3 *database);
    virtual ~CPfTeamPlayersDAOSQLite();

    virtual CPfTeamPlayers* findByXFkRoleSelected(int XFkRoleSelected);
    virtual CPfTeamPlayers* findByXFkRoleSelected(const std::string &XFkRoleSelected);
    virtual CPfTeamPlayers* findByXTeamPlayer(int XTeamPlayer);
    virtual CPfTeamPlayers* findByXTeamPlayer(const std::string &XTeamPlayer);
    virtual std::vector<CPfTeamPlayers*>* findActiveByXFkTeam(int XFkTeam, const std::string &timestamp);
    virtual std::vector<CPfTeamPlayers*>* findActiveByXFkTeam(const std::string &XFkTeam, const std::string &timestamp);
    virtual std::vector<CPfTeamPlayers*>* findLineUpByXFkTeam(int XFkTeam, const std::string &timestamp);
    virtual std::vector<CPfTeamPlayers*>* findLineUpByXFkTeam(const std::string &XFkTeam, const std::string &timestamp);
    virtual std::vector<CPfTeamPlayers*>* findAlternateByXFkTeam(int XFkTeam, const std::string &timestamp);
    virtual std::vector<CPfTeamPlayers*>* findAlternateByXFkTeam(const std::string &XFkTeam, const std::string &timestamp);
    virtual std::vector<CPfTeamPlayers*>* findNotLineUpByXFkTeam(int XFkTeam, const std::string &timestamp);
    virtual std::vector<CPfTeamPlayers*>* findNotLineUpByXFkTeam(const std::string &XFkTeam, const std::string &timestamp);
    virtual CPfTeamPlayers* findByXFkCountry(int XFkCountry);
    virtual CPfTeamPlayers* findByXFkCountry(const std::string &XFkCountry);

};
#endif /*CPFTEAMPLAYERSDAOSQLITE_H_*/
