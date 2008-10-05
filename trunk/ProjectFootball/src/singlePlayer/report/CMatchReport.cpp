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

#include "CMatchReport.h"

CMatchReport::CMatchReport(int xMatch)
{
	// TODO
//    IPfMatchesDAO *matchesDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfMatchesDAO();
//    m_match = matchesDAO->findByXMatch(xMatch);
//
//    IPfTeamsDAO *teamsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO();
//    m_teamAway = teamsDAO->findByXTeam(m_match->getXFkTeamAway());
//    m_teamHome = teamsDAO->findByXTeam(m_match->getXFkTeamHome());
//
//    IPfGoalsDAO *goalsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfGoalsDAO();
//    m_goalsAwayList = goalsDAO->findByXFkMatchAndXFkTeamScorer(m_match->getXMatch(), m_teamAway->getXTeam());
//    m_goalsHomeList = goalsDAO->findByXFkMatchAndXFkTeamScorer(m_match->getXMatch(), m_teamHome->getXTeam());
}

CMatchReport::~CMatchReport()
{
	// TODO
//    IPfGoalsDAO *goalsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfGoalsDAO();
//    goalsDAO->freeVector(m_goalsAwayList);
//    goalsDAO->freeVector(m_goalsHomeList);
//
//    delete m_teamAway;
//    delete m_teamHome;
//
//    delete m_match;
}

int CMatchReport::getType()
{
    return MATCH_REPORT;
}

CPfMatches* CMatchReport::getMatch()
{
    return m_match;
}

CPfTeams * CMatchReport::getTeamAway()
{
    return m_teamAway;
}

CPfTeams * CMatchReport::getTeamHome()
{
    return m_teamHome;
}

int CMatchReport::getNGoalsAway()
{
    return m_goalsAwayList->size();
}

int CMatchReport::getNGoalsHome()
{
    return m_goalsHomeList->size();
}

std::vector<CPfGoals*>* CMatchReport::getGoalsAway()
{
    return m_goalsAwayList;
}

std::vector<CPfGoals*>* CMatchReport::getGoalsHome()
{
    return m_goalsHomeList;
}
