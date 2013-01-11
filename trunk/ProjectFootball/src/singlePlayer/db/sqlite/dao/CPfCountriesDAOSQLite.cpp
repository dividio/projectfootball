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

#include "CPfCountriesDAOSQLite.h"

CPfCountriesDAOSQLite::CPfCountriesDAOSQLite(sqlite3 *database)
  : CPfCountriesDAOSQLiteEntity(database)
{
}

CPfCountriesDAOSQLite::~CPfCountriesDAOSQLite()
{
}

CPfCountries* CPfCountriesDAOSQLite::findByXCountry(int XCountry)
{
    std::ostringstream stream;
    stream << XCountry;
    return findByXCountry(stream.str());
}

CPfCountries* CPfCountriesDAOSQLite::findByXCountry(const std::string &XCountry)
{
    std::string sql(
    		"SELECT * "
    		"FROM PF_COUNTRIES ");
    sql +=  "WHERE X_COUNTRY='"+XCountry+"'";
    return loadRegister(sql);
}

std::vector<CPfCountries*>* CPfCountriesDAOSQLite::findByXFkConfederation(int XFkConfederation)
{
    std::ostringstream stream;
    stream << XFkConfederation;
    return findByXFkConfederation(stream.str());
}

std::vector<CPfCountries*>* CPfCountriesDAOSQLite::findByXFkConfederation(const std::string &XFkConfederation)
{
    std::string sql(
    		"SELECT * "
    		"FROM PF_COUNTRIES ");
    sql +=  "WHERE X_FK_CONFEDERATION='"+XFkConfederation+"'";
    return loadVector(sql);
}

std::vector<CPfCountries*>* CPfCountriesDAOSQLite::findByXFkConfederationAndXFKSeasonWithLeague(int XFkConfederation, int XFKSeason)
{
    std::ostringstream strXFKConfederation;
    strXFKConfederation << XFkConfederation;

    std::ostringstream strXFKSeason;
    strXFKSeason << XFKSeason;

    return findByXFkConfederationAndXFKSeasonWithLeague(strXFKConfederation.str(), strXFKSeason.str());
}

std::vector<CPfCountries*>* CPfCountriesDAOSQLite::findByXFkConfederationAndXFKSeasonWithLeague(const std::string &XFkConfederation, const std::string &XFKSeason)
{
	std::string sql(
			"SELECT DISTINCT CT.* "
			"FROM PF_COUNTRIES CT "
			"  JOIN PF_COMPETITIONS CO ON CO.X_FK_COUNTRY=CT.X_COUNTRY "
			"  JOIN PF_COMPETITION_PHASES CP ON CP.X_FK_COMPETITION=CO.X_COMPETITION "
			"  JOIN PF_COMPETITION_PHASES_BY_SEASON CPS ON CPS.X_FK_COMPETITION_PHASE=CP.X_COMPETITION_PHASE ");
	sql +=  "WHERE CT.X_FK_CONFEDERATION='"+XFkConfederation+"' AND CPS.X_FK_SEASON='"+XFKSeason+"'";
	return loadVector(sql);
}

std::vector< CPfCountries * > *CPfCountriesDAOSQLite::getAllCounties()
{
	std::string sql("SELECT * FROM PF_COUNTRIES");
	return loadVector(sql);
}

std::vector< CPfCountries * > *CPfCountriesDAOSQLite::findByName(const std::string &name)
{
	std::string sql("SELECT * FROM PF_COUNTRIES WHERE ");
    sql = sql + "S_COUNTRY like '%" + name + "%'";
	return loadVector(sql);
}