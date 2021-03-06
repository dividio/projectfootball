/******************************************************************************
* Copyright (C) 2010 - Ikaro Games   www.ikarogames.com                       *
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

#ifndef CPFCOMPETITIONSDAOSQLITE_H_
#define CPFCOMPETITIONSDAOSQLITE_H_

#include <string>
#include <sqlite3.h>

#include "entity/CPfCompetitionsDAOSQLiteEntity.h"
#include "../../bean/CPfCompetitions.h"

class CPfCompetitionsDAOSQLite : public CPfCompetitionsDAOSQLiteEntity
{
public:
    CPfCompetitionsDAOSQLite(sqlite3 *database);
    virtual ~CPfCompetitionsDAOSQLite();

    virtual std::vector<CPfCompetitions*>*  findCompetitions();
    virtual CPfCompetitions* findByXCompetition(int XCompetition);
    virtual CPfCompetitions* findByXCompetition(const std::string &XCompetition);
    virtual std::vector<CPfCompetitions*>* findByXFkCountryAndXFKSeason(int XFkCountry, int XFKseason);
    virtual std::vector<CPfCompetitions*>* findByXFkCountryAndXFKSeason(const std::string &XFkCountry, const std::string &XFKSeason);
    virtual std::vector<CPfCompetitions*>* findByXFkSeason(int XFKSeason);
    virtual std::vector<CPfCompetitions*>* findByXFkSeason(const std::string &XFKSeason);
	virtual std::vector< CPfCompetitions * > *findbyName(const std::string &name);

};
#endif /*CPFCOMPETITIONSDAOSQLITE_H_*/
