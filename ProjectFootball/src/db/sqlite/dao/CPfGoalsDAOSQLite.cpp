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
*       Version: 1.10                                                          *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfGoalsDAOSQLite.h"

CPfGoalsDAOSQLite::CPfGoalsDAOSQLite(sqlite3 *database)
  : CPfGoalsDAOSQLiteEntity(database)
{
}

CPfGoalsDAOSQLite::~CPfGoalsDAOSQLite()
{
}

CPfGoals* CPfGoalsDAOSQLite::findByXFkTeamScorer(int XFkTeamScorer)
{
    std::ostringstream stream;
    stream << XFkTeamScorer;
    return findByXFkTeamScorer(stream.str());
}

CPfGoals* CPfGoalsDAOSQLite::findByXFkTeamScorer(const std::string &XFkTeamScorer)
{
    std::string sql("SELECT * FROM PF_GOALS WHERE ");
    sql = sql+"X_FK_TEAM_SCORER='"+XFkTeamScorer+"'";
    return loadRegister(sql);
}

CPfGoals* CPfGoalsDAOSQLite::findByXGoal(int XGoal)
{
    std::ostringstream stream;
    stream << XGoal;
    return findByXGoal(stream.str());
}

CPfGoals* CPfGoalsDAOSQLite::findByXGoal(const std::string &XGoal)
{
    std::string sql("SELECT * FROM PF_GOALS WHERE ");
    sql = sql+"X_GOAL='"+XGoal+"'";
    return loadRegister(sql);
}

CPfGoals* CPfGoalsDAOSQLite::findByXFkMatch(int XFkMatch)
{
    std::ostringstream stream;
    stream << XFkMatch;
    return findByXFkMatch(stream.str());
}

CPfGoals* CPfGoalsDAOSQLite::findByXFkMatch(const std::string &XFkMatch)
{
    std::string sql("SELECT * FROM PF_GOALS WHERE ");
    sql = sql+"X_FK_MATCH='"+XFkMatch+"'";
    return loadRegister(sql);
}
