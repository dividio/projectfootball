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

#include "CTimeManager.h"

#include "../CGameEngine.h"
#include "../event/IGameEvent.h"
#include "../event/CEventManager.h"
#include "../event/slot/CSlotConnection.h"
#include "../event/system/CNoMoreEventsToday.h"
#include "../event/system/CTimeStartEvent.h"
#include "../event/system/CTimeStopEvent.h"
#include "../../utils/CLog.h"

#include <boost/date_time/posix_time/posix_time.hpp>

CTimeManager::CTimeManager() :
	m_thread(),
	m_stopRequest(true),
	m_stopped(true),
	m_currentTime(),
	m_slotConnection(CGameEngine::getInstance()->getEventManager()->subscribeEvent(CNoMoreEventsToday::type, &CTimeManager::noMoreEventsTodayHandler, this))
{}

CTimeManager::~CTimeManager()
{
	m_stopRequest = true;
	m_thread.join();
	CGameEngine::getInstance()->getEventManager()->disconnectSlot(m_slotConnection);
}

void CTimeManager::setCurrentTime(const CDate &date)
{
	m_currentTime = date;
}

const CDate& CTimeManager::getCurrentTime() const
{
	return m_currentTime;
}

void CTimeManager::start()
{
	// if the thread is running already, then we will not create a new one
	if( m_stopped ){
		m_stopRequest	= false;
		m_stopped		= false;
		m_thread		= boost::thread(boost::bind(&CTimeManager::runThread, this));
	}
}

void CTimeManager::stop()
{
	m_stopRequest = true;
}

void CTimeManager::runThread()
{
	LOG_DEBUG("Time started [date:%s]", m_currentTime.getTimestamp().c_str());

	unsigned int 						nEvents = 0;
	boost::posix_time::time_duration	td;
	CEventManager 						*eventMngr = CGameEngine::getInstance()->getEventManager();

	eventMngr->fireEvent(CTimeStartEvent(m_currentTime));
	for(;;){
		if( m_stopRequest ){
			break;
		}

		boost::system_time time = boost::get_system_time();
		eventMngr->consumeEvent();
		td += (boost::get_system_time()-time);

		nEvents++;
	}
	m_stopped = true;
	eventMngr->fireEvent(CTimeStopEvent(m_currentTime));

	LOG_DEBUG("Time stopped [date:%s, nEvents: %u, avgTime: %s]", m_currentTime.getTimestamp().c_str(), nEvents, boost::posix_time::to_simple_string(td/nEvents).c_str());
}

void CTimeManager::noMoreEventsTodayHandler(const IGameEvent &event)
{
	// Only one "NoMoreEventsToday" event is on the events queue at time,
	// so we need to add a new event of this type for tomorrow

	CDate date = event.getDate();
	date.setDay(date.getDay()+1);
	date.setHour(23);
	date.setMin(59);
	date.setSec(59);
	CGameEngine::getInstance()->getEventManager()->addEvent(new CNoMoreEventsToday(date));
}
