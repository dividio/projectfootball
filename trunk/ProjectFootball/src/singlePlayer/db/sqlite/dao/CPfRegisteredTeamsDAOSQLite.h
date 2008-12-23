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

#ifndef CPFREGISTEREDTEAMSDAOSQLITE_H_
#define CPFREGISTEREDTEAMSDAOSQLITE_H_

#include <string>
#include <sqlite3.h>

#include "entity/CPfRegisteredTeamsDAOSQLiteEntity.h"
#include "../../bean/CPfRegisteredTeams.h"

class CPfRegisteredTeamsDAOSQLite : public CPfRegisteredTeamsDAOSQLiteEntity
{
public:
    CPfRegisteredTeamsDAOSQLite(sqlite3 *database);
    virtual ~CPfRegisteredTeamsDAOSQLite();

    virtual CPfRegisteredTeams* findByXRegisteredTeam(int XRegisteredTeam);
    virtual CPfRegisteredTeams* findByXRegisteredTeam(const std::string &XRegisteredTeam);
    virtual CPfRegisteredTeams* findByXFkCompetition(int XFkCompetition);
    virtual CPfRegisteredTeams* findByXFkCompetition(const std::string &XFkCompetition);
    virtual CPfRegisteredTeams* findByXFkTeam(int XFkTeam);
    virtual CPfRegisteredTeams* findByXFkTeam(const std::string &XFkTeam);

};
#endif /*CPFREGISTEREDTEAMSDAOSQLITE_H_*/
