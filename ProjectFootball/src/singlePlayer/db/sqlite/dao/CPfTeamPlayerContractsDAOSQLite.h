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
*       Version: 1.16                                                         *
******************************************************************************/

#ifndef CPFTEAMPLAYERCONTRACTSDAOSQLITE_H_
#define CPFTEAMPLAYERCONTRACTSDAOSQLITE_H_

#include <string>
#include <sqlite3.h>

#include "entity/CPfTeamPlayerContractsDAOSQLiteEntity.h"
#include "../../bean/CPfTeamPlayerContracts.h"

class CPfTeamPlayerContractsDAOSQLite : public CPfTeamPlayerContractsDAOSQLiteEntity
{
public:
    CPfTeamPlayerContractsDAOSQLite(sqlite3 *database);
    virtual ~CPfTeamPlayerContractsDAOSQLite();

    virtual std::vector<CPfTeamPlayerContracts*>* findByXFkTeamPlayer(int XFkTeamPlayer);
    virtual std::vector<CPfTeamPlayerContracts*>* findByXFkTeamPlayer(const std::string &XFkTeamPlayer);
    virtual CPfTeamPlayerContracts* findByXTeamPlayerContract(int XTeamPlayerContract);
    virtual CPfTeamPlayerContracts* findByXTeamPlayerContract(const std::string &XTeamPlayerContract);
    virtual std::vector<CPfTeamPlayerContracts*>* findByXFkTeam(int XFkTeam);
    virtual std::vector<CPfTeamPlayerContracts*>* findByXFkTeam(const std::string &XFkTeam);
    virtual CPfTeamPlayerContracts* findActiveByXFkTeamAndXFkTeamPlayer(int XFkTeam, int XFkTeamPlayer);
    virtual CPfTeamPlayerContracts* findActiveByXFkTeamAndXFkTeamPlayer(const std::string &XFkTeam, const std::string &XFkTeamPlayer);

};
#endif /*CPFTEAMPLAYERCONTRACTSDAOSQLITE_H_*/