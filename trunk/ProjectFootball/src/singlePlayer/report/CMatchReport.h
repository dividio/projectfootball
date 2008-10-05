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
******************************************************************************/

#ifndef CMATCHREPORT_H_
#define CMATCHREPORT_H_

#include <vector>

#include "IGameReport.h"
#include "../db/bean/CPfGoals.h"
#include "../db/bean/CPfMatches.h"
#include "../db/bean/CPfTeams.h"

class CMatchReport : public IGameReport
{
public:
	CMatchReport(int xMatch);
	virtual ~CMatchReport();

	virtual int getType();

	CPfMatches*    getMatch();
	CPfTeams *     getTeamHome();
	CPfTeams *     getTeamAway();
	int            getNGoalsHome();
	int            getNGoalsAway();
	std::vector<CPfGoals*>* getGoalsHome();
	std::vector<CPfGoals*>* getGoalsAway();

private:
    std::vector<CPfGoals*>  *m_goalsHomeList;
    std::vector<CPfGoals*>  *m_goalsAwayList;
    CPfMatches              *m_match;
    CPfTeams                *m_teamHome;
    CPfTeams                *m_teamAway;
};

#endif /*CMATCHREPORT_H_*/
