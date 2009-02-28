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

#ifndef CEVENTCONSUMER_H_
#define CEVENTCONSUMER_H_

// Forward declarations
class IGameEvent;
class CEventMustStopVisitor;
class CEventProcessorVisitor;
class CSinglePlayerGame;

class CEventConsumer {
public:
	CEventConsumer(CSinglePlayerGame *game);
	virtual ~CEventConsumer();

	void consumeEvents();
	void consumeLastEvent();
	void consumeCurrentDayEvents();

	const IGameEvent* getLastEvent() const;

private:
	CSinglePlayerGame 		*m_game;
	IGameEvent				*m_lastEvent;
	CEventMustStopVisitor	*m_eventMustStopVisitor;
	CEventProcessorVisitor	*m_eventProcessorVisitor;
};

#endif /* CEVENTCONSUMER_H_ */
