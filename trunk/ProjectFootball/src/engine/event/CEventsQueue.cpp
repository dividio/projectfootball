/******************************************************************************
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

#include "CEventsQueue.h"

bool eventsCompare(const IGameEvent* x, const IGameEvent* y)
{
    return (x->getDate()) > (y->getDate());
}

CEventsQueue::CEventsQueue() :
	m_queue(eventsCompare)
{}

CEventsQueue::~CEventsQueue()
{
    while( !m_queue.empty() ){
        IGameEvent *event = m_queue.top();
        m_queue.pop();
        delete event;
    }
}

void CEventsQueue::push(IGameEvent *event)
{
    m_queue.push(event);
}

IGameEvent* CEventsQueue::pop()
{
    if( m_queue.empty() ){
        return NULL;
    }

    IGameEvent *event = m_queue.top();
    m_queue.pop();

	return event;
}

IGameEvent* CEventsQueue::pop(const CDate &date)
{
	if( m_queue.empty() ){
		return NULL;
	}

	IGameEvent *event = m_queue.top();
	if( event->getDate()<date ){
		m_queue.pop();
		return event;
	}
	else{
		return NULL;
	}
}

bool CEventsQueue::empty()
{
	return m_queue.empty();
}
