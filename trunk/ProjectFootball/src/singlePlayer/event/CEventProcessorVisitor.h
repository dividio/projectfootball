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

#ifndef CEVENTPROCESSORVISITOR_H_
#define CEVENTPROCESSORVISITOR_H_

#include "IEventVisitor.h"
#include <map>
#include <vector>

// Forward declarations
class CSinglePlayerGame;
class CPfGoals;
class CPfMatches;
class CPfTeamAverages;

class CEventProcessorVisitor: public IEventVisitor {
public:
	CEventProcessorVisitor(CSinglePlayerGame *game);
	virtual ~CEventProcessorVisitor();

	virtual void matchEventVisitor(const CMatchEvent &event);
	virtual void startMatchEventVisitor(const CStartMatchEvent &event);
	virtual void goalMatchEventVisitor(const CGoalMatchEvent &event);
	virtual void endMatchEventVisitor(const CEndMatchEvent &event);

private:
	int		getRandomNGoals(CPfTeamAverages *attackTeam, CPfTeamAverages *defenseTeam);
	void 	simulateMatch(CPfMatches *match);

private:
	CSinglePlayerGame						*m_game;
    std::map<int, std::vector<CPfGoals *>*>  m_matchesMap;
};

#endif /* CEVENTPROCESSORVISITOR_H_ */
