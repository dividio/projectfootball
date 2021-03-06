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

#ifndef CPFROLESBYTEAMPLAYERSDAOSQLITE_H_
#define CPFROLESBYTEAMPLAYERSDAOSQLITE_H_

#include <string>
#include <sqlite3.h>

#include "entity/CPfRolesByTeamPlayersDAOSQLiteEntity.h"
#include "../../bean/CPfRolesByTeamPlayers.h"

class CPfRolesByTeamPlayersDAOSQLite : public CPfRolesByTeamPlayersDAOSQLiteEntity
{
public:
    CPfRolesByTeamPlayersDAOSQLite(sqlite3 *database);
    virtual ~CPfRolesByTeamPlayersDAOSQLite();

    virtual CPfRolesByTeamPlayers* findByXRoleByTeamPlayer(int XRoleByTeamPlayer);
    virtual CPfRolesByTeamPlayers* findByXRoleByTeamPlayer(const std::string &XRoleByTeamPlayer);
    virtual CPfRolesByTeamPlayers* findByXFkTeamPlayer(int XFkTeamPlayer);
    virtual CPfRolesByTeamPlayers* findByXFkTeamPlayer(const std::string &XFkTeamPlayer);
    virtual CPfRolesByTeamPlayers* findByXFkRole(int XFkRole);
    virtual CPfRolesByTeamPlayers* findByXFkRole(const std::string &XFkRole);

};
#endif /*CPFROLESBYTEAMPLAYERSDAOSQLITE_H_*/
