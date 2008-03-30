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
*       Version: 1.15                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfCompetitionPhasesDAOSQLite.h"

CPfCompetitionPhasesDAOSQLite::CPfCompetitionPhasesDAOSQLite(sqlite3 *database)
  : CPfCompetitionPhasesDAOSQLiteEntity(database)
{
}

CPfCompetitionPhasesDAOSQLite::~CPfCompetitionPhasesDAOSQLite()
{
}

CPfCompetitionPhases* CPfCompetitionPhasesDAOSQLite::findByXCompetitionPhase(int XCompetitionPhase)
{
    std::ostringstream stream;
    stream << XCompetitionPhase;
    return findByXCompetitionPhase(stream.str());
}

CPfCompetitionPhases* CPfCompetitionPhasesDAOSQLite::findByXCompetitionPhase(const std::string &XCompetitionPhase)
{
    std::string sql("SELECT * FROM PF_COMPETITION_PHASES WHERE ");
    sql = sql+"X_COMPETITION_PHASE='"+XCompetitionPhase+"'";
    return loadRegister(sql);
}

CPfCompetitionPhases* CPfCompetitionPhasesDAOSQLite::findByXFkCompetition(int XFkCompetition)
{
    std::ostringstream stream;
    stream << XFkCompetition;
    return findByXFkCompetition(stream.str());
}

CPfCompetitionPhases* CPfCompetitionPhasesDAOSQLite::findByXFkCompetition(const std::string &XFkCompetition)
{
    std::string sql("SELECT * FROM PF_COMPETITION_PHASES WHERE ");
    sql = sql+"X_FK_COMPETITION='"+XFkCompetition+"'";
    return loadRegister(sql);
}

