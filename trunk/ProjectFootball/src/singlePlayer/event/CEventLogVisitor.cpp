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

#include "CEventLogVisitor.h"

#include "season/CStartSeasonEvent.h"
#include "season/CEndSeasonEvent.h"

#include "competition/CStartCompetitionEvent.h"
#include "competition/CEndCompetitionEvent.h"

#include "match/CMatchEvent.h"
#include "match/CStartMatchEvent.h"
#include "match/CGoalMatchEvent.h"
#include "match/CEndMatchEvent.h"

#include "../../utils/CLog.h"

CEventLogVisitor::CEventLogVisitor()
: IEventVisitor()
{
}

CEventLogVisitor::~CEventLogVisitor()
{
}

void CEventLogVisitor::endCompetitionEventVisitor(const CEndCompetitionEvent &event)
{
	LOG_DEBUG("--> CEndCompetitionEvent");
}

void CEventLogVisitor::endMatchEventVisitor(const CEndMatchEvent &event)
{
	LOG_DEBUG("--> CEndMatchEvent");
}

void CEventLogVisitor::endSeasonEventVisitor(const CEndSeasonEvent &event)
{
	LOG_DEBUG("--> CEndSeasonEvent");
}

void CEventLogVisitor::goalMatchEventVisitor(const CGoalMatchEvent &event)
{
	LOG_DEBUG("--> CGoalMatchEvent");
}

void CEventLogVisitor::matchEventVisitor(const CMatchEvent &event)
{
	LOG_DEBUG("--> CMatchEvent");
}

void CEventLogVisitor::startCompetitionEventVisitor(const CStartCompetitionEvent &event)
{
	LOG_DEBUG("--> CStartCompetitionEvent");
}

void CEventLogVisitor::startMatchEventVisitor(const CStartMatchEvent &event)
{
	LOG_DEBUG("--> CStartMatchEvent");
}

void CEventLogVisitor::startSeasonEventVisitor(const CStartSeasonEvent &event)
{
	LOG_DEBUG("--> CStartSeasonEvent");
}
