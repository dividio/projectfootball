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

#ifndef CEVENTSHANDLER_H_
#define CEVENTSHANDLER_H_

#include <list>
#include <map>
#include <vector>

// forward declarations
class IGameEvent;
class CSlotConnection;
class CSinglePlayerGame;
class CPfGoals;
class CPfTeamPlayers;

class CEventsHandler {
public:
	CEventsHandler(CSinglePlayerGame &game);
	virtual ~CEventsHandler();

private:
	// Match events
	void matchEventHandler(const IGameEvent &event);
	void startMatchEventHandler(const IGameEvent &event);
	void goalMatchEventHandler(const IGameEvent &event);
	void endMatchEventHandler(const IGameEvent &event);

	// Season events
	void endSeasonEventHandler(const IGameEvent &event);

	// System events
	void endDayEventHandler(const IGameEvent &event);
	void timeStartEventHandler(const IGameEvent &event);
	void timeStopEventHandler(const IGameEvent &event);

	// Update players stats
	void updateLineUpPlayersStats   (std::vector<CPfTeamPlayers*> *players, int teamGoals, int opponentGoals);
	void updateAlternatePlayersStats(std::vector<CPfTeamPlayers*> *players, int teamGoals, int opponentGoals);
	void updateNotLineUpPlayersStats(std::vector<CPfTeamPlayers*> *players, int teamGoals, int opponentGoals);
private:
	typedef std::list<CSlotConnection>		TSlotConnectionsList;
	typedef std::list<CPfGoals*>			TGoalsList;
	typedef std::map<int, TGoalsList*>		TMatchesMap;

	CSinglePlayerGame		&m_game;
	TMatchesMap				m_matchesMap;

	TSlotConnectionsList	m_slotsList;
};

#endif /* CEVENTSHANDLER_H_ */
