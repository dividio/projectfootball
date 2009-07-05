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

#ifndef CEVENTSQUEUE_H_
#define CEVENTSQUEUE_H_

#include <queue>

#include "IGameEvent.h"
#include "../../utils/CDate.h"

class CEventsQueue
{
public:
    CEventsQueue();
    virtual ~CEventsQueue();

    /**
     * Push the event into the queue
     */
    void push(IGameEvent *event);

    /**
     * Return the event from the queue whose date is the lowest.
     */
    IGameEvent* pop();

    /**
     * Return the event from the queue whose date is the lowest.
     * If a date is specified then, the date of the event is lower
     * than that indicated. If there isn't any event or don't
     * complies with the indicated restrictions, then NULL is
     * returned.
     */
    IGameEvent* pop(const CDate &date);


    /**
     * Return if the queue is empty or not
     */
    bool empty();
//
//    /**
//     * Subscribe an observer of the events queue. When a event
//     * is pushed o popped all the observers will be notified.
//     */
//    void addObserver(const IEventsQueueObserver &observer);
//
//    /**
//     * Remove an observer of the events queue.
//     */
//    void removeObserver(const IEventsQueueObserver &observer);

private:
    std::priority_queue<IGameEvent*, std::vector<IGameEvent*>, bool (*)(const IGameEvent*, const IGameEvent*)> m_queue;
//
//    std::list<const IEventsQueueObserver*> m_observers;
};

#endif /*CEVENTSQUEUE_H_*/
