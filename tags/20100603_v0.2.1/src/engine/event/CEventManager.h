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

#ifndef CEVENTMANAGER_H_
#define CEVENTMANAGER_H_

#include <map>
#include <list>

#include "IGameEvent.h"
#include "CEventsQueue.h"

#include "slot/ISlotFunctorBase.h"
#include "slot/CMemberFunctionSlot.h"
#include "slot/CSlotConnection.h"

#include "../time/CTimeManager.h"

class CEventManager {
	friend class CTimeManager;
public:
	CEventManager();
	virtual ~CEventManager();

	void addEvent(IGameEvent *event);
	void clearEvents();
	void consumeEvent();

	template<typename T>
	CSlotConnection subscribeEvent( const char *eventType, void (T::*function)(const IGameEvent&), T *object )
	{
		ISlotFunctorBase *slot = new CMemberFunctionSlot<T>(function, object);
		m_eventsSubscribers[eventType].push_back(slot);
		return CSlotConnection(eventType, slot);
	}

	void disconnectSlot( const CSlotConnection &connection );

private:
	void fireEvent(const IGameEvent &event);

private:
	typedef std::list<ISlotFunctorBase*>		TSlotList;
	typedef std::map<const char*, TSlotList>	TSubscribersMap;

	TSubscribersMap		m_eventsSubscribers;
	CEventsQueue		m_eventsQueue;

};

#endif /* CEVENTMANAGER_H_ */
