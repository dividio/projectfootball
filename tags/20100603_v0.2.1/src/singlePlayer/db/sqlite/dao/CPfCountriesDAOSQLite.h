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

#ifndef CPFCOUNTRIESDAOSQLITE_H_
#define CPFCOUNTRIESDAOSQLITE_H_

#include <string>
#include <sqlite3.h>

#include "entity/CPfCountriesDAOSQLiteEntity.h"
#include "../../bean/CPfCountries.h"

class CPfCountriesDAOSQLite : public CPfCountriesDAOSQLiteEntity
{
public:
    CPfCountriesDAOSQLite(sqlite3 *database);
    virtual ~CPfCountriesDAOSQLite();

    virtual CPfCountries* findByXCountry(int XCountry);
    virtual CPfCountries* findByXCountry(const std::string &XCountry);
    virtual std::vector<CPfCountries*>* findByXFkConfederation(int XFkConfederation);
    virtual std::vector<CPfCountries*>* findByXFkConfederation(const std::string &XFkConfederation);
    virtual std::vector<CPfCountries*>* findByXFkConfederationAndXFKSeasonWithLeague(int XFkConfederation, int XFKSeason);
    virtual std::vector<CPfCountries*>* findByXFkConfederationAndXFKSeasonWithLeague(const std::string &XFkConfederation, const std::string &XFKSeason);

};
#endif /*CPFCOUNTRIESDAOSQLITE_H_*/