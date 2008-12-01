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
*       Version: 1.12                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfMatchesDAOSQLite.h"

CPfMatchesDAOSQLite::CPfMatchesDAOSQLite(sqlite3 *database)
  : CPfMatchesDAOSQLiteEntity(database)
{
}

CPfMatchesDAOSQLite::~CPfMatchesDAOSQLite()
{
}

std::vector<CPfMatches*>* CPfMatchesDAOSQLite::findByXFkCompetitionPhase(int XFkCompetitionPhase)
{
    std::ostringstream stream;
    stream << XFkCompetitionPhase;
    return findByXFkCompetitionPhase(stream.str());
}

std::vector<CPfMatches*>* CPfMatchesDAOSQLite::findByXFkCompetitionPhase(const std::string &XFkCompetitionPhase)
{
    std::string sql("SELECT * FROM PF_MATCHES WHERE ");
    sql = sql+"X_FK_COMPETITION_PHASE='"+XFkCompetitionPhase+"'";
    return loadVector(sql);
}

CPfMatches* CPfMatchesDAOSQLite::findByXFkTeamHome(int XFkTeamHome)
{
    std::ostringstream stream;
    stream << XFkTeamHome;
    return findByXFkTeamHome(stream.str());
}

CPfMatches* CPfMatchesDAOSQLite::findByXFkTeamHome(const std::string &XFkTeamHome)
{
    std::string sql("SELECT * FROM PF_MATCHES WHERE ");
    sql = sql+"X_FK_TEAM_HOME='"+XFkTeamHome+"'";
    return loadRegister(sql);
}

CPfMatches* CPfMatchesDAOSQLite::findByXMatch(int XMatch)
{
    std::ostringstream stream;
    stream << XMatch;
    return findByXMatch(stream.str());
}

CPfMatches* CPfMatchesDAOSQLite::findByXMatch(const std::string &XMatch)
{
    std::string sql("SELECT * FROM PF_MATCHES WHERE ");
    sql = sql+"X_MATCH='"+XMatch+"'";
    return loadRegister(sql);
}

CPfMatches* CPfMatchesDAOSQLite::findByXFkTeamAway(int XFkTeamAway)
{
    std::ostringstream stream;
    stream << XFkTeamAway;
    return findByXFkTeamAway(stream.str());
}

CPfMatches* CPfMatchesDAOSQLite::findByXFkTeamAway(const std::string &XFkTeamAway)
{
    std::string sql("SELECT * FROM PF_MATCHES WHERE ");
    sql = sql+"X_FK_TEAM_AWAY='"+XFkTeamAway+"'";
    return loadRegister(sql);
}

std::vector<CPfMatches*>* CPfMatchesDAOSQLite::findMatches()
{
    std::string sql("SELECT * FROM PF_MATCHES ORDER BY D_MATCH");
    return loadVector(sql);
}

CPfMatches* CPfMatchesDAOSQLite::findNextPlayerTeamMatch()
{
    std::string sql("SELECT * FROM PF_MATCHES WHERE L_PLAYED='N' AND (X_FK_TEAM_HOME=(SELECT S_VALUE FROM PF_GAME_STATES WHERE S_STATE='PLAYER_TEAM') OR X_FK_TEAM_AWAY=(SELECT S_VALUE FROM PF_GAME_STATES WHERE S_STATE='PLAYER_TEAM')) ORDER BY D_MATCH");
    std::vector<CPfMatches*>* matchesList = loadVector(sql);
    if( matchesList->empty() ){
        freeVector(matchesList);
        return NULL;
    }else{
        CPfMatches *match = new CPfMatches(*(matchesList->operator[](0)));
        freeVector(matchesList);
        return match;
    }
}

CPfMatches* CPfMatchesDAOSQLite::findLastPlayerTeamMatch()
{
    std::string sql("SELECT * FROM PF_MATCHES WHERE L_PLAYED='Y' AND (X_FK_TEAM_HOME=(SELECT S_VALUE FROM PF_GAME_STATES WHERE S_STATE='PLAYER_TEAM') OR X_FK_TEAM_AWAY=(SELECT S_VALUE FROM PF_GAME_STATES WHERE S_STATE='PLAYER_TEAM')) ORDER BY D_MATCH");
    std::vector<CPfMatches*>* matchesList = loadVector(sql);
    if( matchesList->empty() ){
        freeVector(matchesList);
        return NULL;
    }else{
        CPfMatches *match = new CPfMatches(*(matchesList->back()));
        freeVector(matchesList);
        return match;
    }
}