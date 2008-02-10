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

#ifndef CPFGOALSDAOSQLITE_H_
#define CPFGOALSDAOSQLITE_H_

#include <string>
#include <sqlite3.h>

#include "entity/CPfGoalsDAOSQLiteEntity.h"
#include "../../bean/CPfGoals.h"

class CPfGoalsDAOSQLite : public CPfGoalsDAOSQLiteEntity
{
public:
    CPfGoalsDAOSQLite(sqlite3 *database);
    virtual ~CPfGoalsDAOSQLite();

    virtual CPfGoals* findByXFkTeamScorer(int XFkTeamScorer);
    virtual CPfGoals* findByXFkTeamScorer(const std::string &XFkTeamScorer);
    virtual CPfGoals* findByXGoal(int XGoal);
    virtual CPfGoals* findByXGoal(const std::string &XGoal);
    virtual CPfGoals* findByXFkMatch(int XFkMatch);
    virtual CPfGoals* findByXFkMatch(const std::string &XFkMatch);

};
#endif /*CPFGOALSDAOSQLITE_H_*/
