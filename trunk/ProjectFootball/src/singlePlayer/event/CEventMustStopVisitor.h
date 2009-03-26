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

#ifndef CEVENTMUSTSTOPVISITOR_H_
#define CEVENTMUSTSTOPVISITOR_H_

#include "IEventVisitor.h"

// Forward declarations
class CSinglePlayerGame;

class CEventMustStopVisitor: public IEventVisitor {
public:
	CEventMustStopVisitor(CSinglePlayerGame *game);
	virtual ~CEventMustStopVisitor();

	virtual void startSeasonEventVisitor(const CStartSeasonEvent &event);
	virtual void endSeasonEventVisitor(const CEndSeasonEvent &event);

	virtual void startCompetitionEventVisitor(const CStartCompetitionEvent &event);
	virtual void endCompetitionEventVisitor(const CEndCompetitionEvent &event);

	virtual void matchEventVisitor(const CMatchEvent &event);
	virtual void startMatchEventVisitor(const CStartMatchEvent &event);
	virtual void goalMatchEventVisitor(const CGoalMatchEvent &event);
	virtual void endMatchEventVisitor(const CEndMatchEvent &event);

	bool eventMustStop();

private:
	bool				 m_eventMustStop;
	CSinglePlayerGame	*m_game;
};

#endif /* CEVENTMUSTSTOPVISITOR_H_ */
