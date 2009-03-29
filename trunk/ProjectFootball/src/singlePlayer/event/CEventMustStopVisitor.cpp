/*******************************************************************************
 * Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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

#include "CEventMustStopVisitor.h"

#include "season/CStartSeasonEvent.h"
#include "season/CEndSeasonEvent.h"

#include "competition/CStartCompetitionEvent.h"
#include "competition/CEndCompetitionEvent.h"

#include "match/CMatchEvent.h"
#include "match/CStartMatchEvent.h"
#include "match/CGoalMatchEvent.h"
#include "match/CEndMatchEvent.h"

#include "../CSinglePlayerGame.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

CEventMustStopVisitor::CEventMustStopVisitor(CSinglePlayerGame *game)
{
	m_eventMustStop = false;
	m_game			= game;
}

CEventMustStopVisitor::~CEventMustStopVisitor()
{
}

void CEventMustStopVisitor::startSeasonEventVisitor(const CStartSeasonEvent &event)
{
	m_eventMustStop = false;
}

void CEventMustStopVisitor::endSeasonEventVisitor(const CEndSeasonEvent &event)
{
	m_eventMustStop = false;
}

void CEventMustStopVisitor::startCompetitionEventVisitor(const CStartCompetitionEvent &event)
{
	m_eventMustStop = false;
}

void CEventMustStopVisitor::endCompetitionEventVisitor(const CEndCompetitionEvent &event)
{
	m_eventMustStop = false;
}

void CEventMustStopVisitor::matchEventVisitor(const CMatchEvent &event)
{
	IPfMatchesDAO 	*matchesDAO 	= m_game->getIDAOFactory()->getIPfMatchesDAO();
	CPfMatches 		*match			= matchesDAO->findByXMatch(event.getXMatch());
	int				 xPlayerTeam	= m_game->getOptionManager()->getGamePlayerTeam();

	m_eventMustStop = (match->getXFkTeamAway()==xPlayerTeam || match->getXFkTeamHome()==xPlayerTeam);
	if( m_eventMustStop ){
		m_game->setCurrentMatch(match);
	}
	delete match;
}

void CEventMustStopVisitor::startMatchEventVisitor(const CStartMatchEvent &event)
{
	m_eventMustStop = false;
}

void CEventMustStopVisitor::goalMatchEventVisitor(const CGoalMatchEvent &event)
{
	m_eventMustStop = false;
}

void CEventMustStopVisitor::endMatchEventVisitor(const CEndMatchEvent &event)
{
	m_eventMustStop = false;
}

bool CEventMustStopVisitor::eventMustStop()
{
	return m_eventMustStop;
}
