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

// TODO: Remove CGameEngine dependency
#include "CSingleMatchEventStrategy.h"
#include "../../../engine/CGameEngine.h"

CSingleMatchEventStrategy::CSingleMatchEventStrategy()
{
    m_xMatch    = -1;
    m_started   = false;
    m_ended     = false;
}

CSingleMatchEventStrategy::~CSingleMatchEventStrategy()
{
}

void CSingleMatchEventStrategy::process(CStartMatchEvent &event)
{
    if( !m_started )
    {
        m_xMatch = event.getXMatch();

        // Test that match is not a played yet
        IPfMatchesDAO *matchesDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfMatchesDAO();
        CPfMatches *match = matchesDAO->findByXMatch(m_xMatch);
        if( !match->getLPlayed() ){
            m_started = true;
            // Delete posible previous goals
            IPfGoalsDAO *goalsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfGoalsDAO();
            std::vector<CPfGoals*> * goalsList = goalsDAO->findByXFkMatch(m_xMatch);
            std::vector<CPfGoals*>::iterator it;
            for( it=goalsList->begin(); it!=goalsList->end(); it++ ){
                goalsDAO->deleteReg(*it);
            }
            goalsDAO->freeVector(goalsList);
        }
        delete match;
    }
}

void CSingleMatchEventStrategy::process(CEndMatchEvent &event)
{
    if( m_started && !m_ended && m_xMatch==event.getXMatch() )
    {
        m_ended = true;

        // Save match result
        IPfGoalsDAO *goalsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfGoalsDAO();
        std::vector<CPfGoals*>::iterator it;
        for( it=m_goalsList.begin(); it!=m_goalsList.end(); it++ ){
            goalsDAO->insertReg(*it);
        }

        IPfMatchesDAO *matchesDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfMatchesDAO();
        CPfMatches *match = matchesDAO->findByXMatch(m_xMatch);
        match->setLPlayed(true);
        matchesDAO->updateReg(match);
        delete match;

        // Generate match report
        CGameEngine::getInstance()->getCurrentGame()->getCGameReportRegister()->generateMatchReport(m_xMatch);

        // Reset SingleMatchEventStrategy state
        for( it=m_goalsList.begin(); it!=m_goalsList.end(); it++ ){
            delete (*it);
        }
        m_goalsList.clear();

        m_xMatch    = -1;
        m_started   = false;
        m_ended     = false;
    }
}

void CSingleMatchEventStrategy::process(CGoalMatchEvent &event)
{
    if( m_started && !m_ended && m_xMatch==event.getXMatch() )
    {
        CPfGoals *goal = new CPfGoals();
        goal->setLOwnGoal(event.getLOwnGoal());
        goal->setNMinute(event.getNMinute());
        goal->setXFkMatch(event.getXMatch());
        goal->setXFkTeamScorer(event.getXTeamScorer());
        goal->setXFkTeamPlayerScorer(event.getXTeamPlayerScorer());

        m_goalsList.push_back(goal);
    }
}
