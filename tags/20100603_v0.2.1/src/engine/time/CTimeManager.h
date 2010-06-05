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

#ifndef CTIMEMANAGER_H_
#define CTIMEMANAGER_H_

#include <boost/thread.hpp>
#include "../utils/CDate.h"

// forward declaration
class CSlotConnection;
class IGameEvent;

class CTimeManager {
public:
	CTimeManager();
	virtual ~CTimeManager();

	void 			setCurrentTime(const CDate &date);
	const CDate& 	getCurrentTime() const;

	void 			start();
	void			stop();

private:
	void			runThread();
	void			endDayEventHandler(const IGameEvent &event);

private:
	boost::thread			m_thread;
	bool					m_stopRequest;
	bool					m_stopped;
	CDate					m_currentTime;
	const CSlotConnection	&m_slotConnection;
};

#endif /* CTIMEMANAGER_H_ */
