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

#include <iostream>
#include <sstream>

#include "CPfStrategicPositionsDAOSQLite.h"

CPfStrategicPositionsDAOSQLite::CPfStrategicPositionsDAOSQLite(sqlite3 *database)
  : CPfStrategicPositionsDAOSQLiteEntity(database)
{
}

CPfStrategicPositionsDAOSQLite::~CPfStrategicPositionsDAOSQLite()
{
}

std::vector<CPfStrategicPositions*>* CPfStrategicPositionsDAOSQLite::findByXFkFormation(int XFkFormation)
{
    std::ostringstream stream;
    stream << XFkFormation;
    return findByXFkFormation(stream.str());
}

std::vector<CPfStrategicPositions*>* CPfStrategicPositionsDAOSQLite::findByXFkFormation(const std::string &XFkFormation)
{
    std::string sql("SELECT * FROM PF_STRATEGIC_POSITIONS WHERE ");
    sql = sql+"X_FK_FORMATION='"+XFkFormation+"' ";
    sql = sql+"ORDER BY N_LINEUP_ORDER ASC";
    return loadVector(sql);
}

CPfStrategicPositions* CPfStrategicPositionsDAOSQLite::findByXFkRole(int XFkRole)
{
    std::ostringstream stream;
    stream << XFkRole;
    return findByXFkRole(stream.str());
}

CPfStrategicPositions* CPfStrategicPositionsDAOSQLite::findByXFkRole(const std::string &XFkRole)
{
    std::string sql("SELECT * FROM PF_STRATEGIC_POSITIONS WHERE ");
    sql = sql+"X_FK_ROLE='"+XFkRole+"'";
    return loadRegister(sql);
}

CPfStrategicPositions* CPfStrategicPositionsDAOSQLite::findByXStrategicPosition(int XStrategicPosition)
{
    std::ostringstream stream;
    stream << XStrategicPosition;
    return findByXStrategicPosition(stream.str());
}

CPfStrategicPositions* CPfStrategicPositionsDAOSQLite::findByXStrategicPosition(const std::string &XStrategicPosition)
{
    std::string sql("SELECT * FROM PF_STRATEGIC_POSITIONS WHERE ");
    sql = sql+"X_STRATEGIC_POSITION='"+XStrategicPosition+"'";
    return loadRegister(sql);
}
