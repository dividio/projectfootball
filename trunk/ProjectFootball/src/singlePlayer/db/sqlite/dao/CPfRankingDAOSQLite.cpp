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

#include "CPfRankingDAOSQLite.h"

CPfRankingDAOSQLite::CPfRankingDAOSQLite(sqlite3 *database)
  : CPfRankingDAOSQLiteEntity(database)
{
}

CPfRankingDAOSQLite::~CPfRankingDAOSQLite()
{
}

std::vector<CPfRanking*>* CPfRankingDAOSQLite::findRankingByXSeasonAndXCompetition(int XSeason, int XCompetition)
{
    std::ostringstream season;
    std::ostringstream competition;
    season << XSeason;
    competition << XCompetition;

    std::string sql("");
    sql += "SELECT "
                 "S_TEAM, "
                 "SUM(POINTS) AS N_POINTS, "
                 "SUM(WINS+DRAWS+LOSSES) AS N_PLAYED, "
                 "SUM(WINS) AS N_WINS, "
                 "SUM(DRAWS) AS N_DRAWS, "
                 "SUM(LOSSES) AS N_LOSSES, "
                 "SUM((CASE WHEN GOALS_FOR IS NULL THEN 0 ELSE GOALS_FOR END)) AS N_GOALS_FOR, "
                 "SUM((CASE WHEN GOALS_AGAINST IS NULL THEN 0 ELSE GOALS_AGAINST END)) AS N_GOALS_AGAINST "
           "FROM "
           "( "
             "SELECT "
                   " S_TEAM, "
                   "(CASE WHEN (X_FK_TEAM_HOME=X_TEAM AND RESULT='HOME_WIN') OR (X_FK_TEAM_AWAY=X_TEAM AND RESULT='AWAY_WIN') THEN 3 WHEN RESULT='DRAW' THEN 1 ELSE 0 END) AS POINTS, "
                   "(CASE WHEN (X_FK_TEAM_HOME=X_TEAM AND RESULT='HOME_WIN') OR (X_FK_TEAM_AWAY=X_TEAM AND RESULT='AWAY_WIN') THEN 1 ELSE 0 END) AS WINS, "
                   "(CASE WHEN RESULT='DRAW' THEN 1 ELSE 0 END) AS DRAWS, "
                   "(CASE WHEN (X_FK_TEAM_HOME=X_TEAM AND RESULT='AWAY_WIN') OR (X_FK_TEAM_AWAY=X_TEAM AND RESULT='HOME_WIN') THEN 1 ELSE 0 END) AS LOSSES, "
                   "(CASE WHEN X_FK_TEAM_HOME=X_TEAM THEN HOME_GOALS ELSE AWAY_GOALS END) AS GOALS_FOR, "
                   "(CASE WHEN X_FK_TEAM_HOME=X_TEAM THEN AWAY_GOALS ELSE HOME_GOALS END) AS GOALS_AGAINST "
             "FROM PF_TEAMS "
             "JOIN "
             "( "
               "SELECT "
                     "X_MATCH, "
                     "X_FK_TEAM_HOME, "
                     "X_FK_TEAM_AWAY, "
                     "HOME_GOALS, "
                     "AWAY_GOALS, "
                     "(CASE WHEN HOME_GOALS>AWAY_GOALS THEN 'HOME_WIN' WHEN HOME_GOALS=AWAY_GOALS THEN 'DRAW' ELSE 'AWAY_WIN' END) AS RESULT "
               "FROM "
               "( "
                 "SELECT "
                       "X_MATCH, "
                       "X_FK_TEAM_HOME, "
                       "X_FK_TEAM_AWAY, "
                       "(SELECT COUNT(X_GOAL) FROM PF_GOALS WHERE X_FK_TEAM_SCORER=X_FK_TEAM_HOME AND X_FK_MATCH=X_MATCH) AS HOME_GOALS, "
                       "(SELECT COUNT(X_GOAL) FROM PF_GOALS WHERE X_FK_TEAM_SCORER=X_FK_TEAM_AWAY AND X_FK_MATCH=X_MATCH) AS AWAY_GOALS "
                 "FROM PF_MATCHES "
                 "JOIN PF_COMPETITION_PHASES ON X_COMPETITION_PHASE = X_FK_COMPETITION_PHASE AND X_FK_COMPETITION = " + competition.str() + " "
                 "WHERE L_PLAYED='Y' AND X_FK_SEASON = " + season.str() + " "
               ") "
             ") ON X_FK_TEAM_HOME=X_TEAM OR X_FK_TEAM_AWAY=X_TEAM "
           ") "
           "GROUP BY S_TEAM "
           "ORDER BY N_POINTS DESC, N_PLAYED DESC";
    return loadVector(sql);
}
