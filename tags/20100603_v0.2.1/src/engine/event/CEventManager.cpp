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

#include "CEventManager.h"

#include "../CGameEngine.h"
#include "../time/CTimeManager.h"
#include "../../utils/CLog.h"

CEventManager::CEventManager() :
	m_eventsSubscribers(),
	m_eventsQueue()
{}

CEventManager::~CEventManager()
{
	TSubscribersMap::iterator it;
	for( it=m_eventsSubscribers.begin(); it!=m_eventsSubscribers.end(); it++ ){

		TSlotList 			&subscribers = it->second;
		TSlotList::iterator	itSlots;
		for( itSlots=subscribers.begin(); itSlots!=subscribers.end(); itSlots++ ){
			delete (*itSlots);
		}
		subscribers.clear();
	}
	m_eventsSubscribers.clear();
}

void CEventManager::addEvent(IGameEvent *event)
{
	if( event!=NULL ){
		m_eventsQueue.push(event);
	}
}

void CEventManager::clearEvents()
{
	while( !m_eventsQueue.empty() ){
		delete m_eventsQueue.pop();
	}

}

void CEventManager::consumeEvent()
{
	if( m_eventsQueue.empty() ){
		CGameEngine::getInstance()->getTimeManager()->stop();
		LOG_WARNING("No events in the queue!");
	}
	else{
		IGameEvent *event = m_eventsQueue.pop();
		fireEvent(*event);
		CGameEngine::getInstance()->getTimeManager()->setCurrentTime(event->getDate());
		delete event;
	}
}

void CEventManager::disconnectSlot( const CSlotConnection &connection )
{
	if( connection.isConnected() ){
		TSlotList 			&list = m_eventsSubscribers[connection.getEventType()];
		TSlotList::iterator it;
		for( it=list.begin(); it!=list.end(); it++ ){
			if( (*it)==connection.getSlot() ){
				list.erase(it);
				delete connection.getSlot();
				connection.setConnected(false);
				break;
			}
		}
	}
}

void CEventManager::fireEvent(const IGameEvent &event)
{
	TSlotList 			&list = m_eventsSubscribers[event.getType()];
	TSlotList::iterator	it;
	for( it=list.begin(); it!=list.end(); it++ ){
		(*(*it))(event); // invoke subscriber
	}
}
