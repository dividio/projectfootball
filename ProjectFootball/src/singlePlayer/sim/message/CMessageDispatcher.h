/******************************************************************************
* Copyright (C) 2008 - Ikaro Games   www.ikarogames.com                       *
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


#ifndef __CMessageDispatcher_H__
#define __CMessageDispatcher_H__

#include <set>

#include "CMessage.h"
#include "../entity/CBaseGameEntity.h"
#include "../../../utils/CTimer.h"

class CMessageDispatcher
{
public:

    static CMessageDispatcher* getInstance();
    ~CMessageDispatcher();

    void dispatchMsg(double      delay,
                     int         sender,
                     int         receiver,
                     int         msg,
                     void*       info);

    void dispatchDelayedMessages();
    void reset();

private:
    std::set<CMessage> m_priorityQueue;
    CTimer *m_timer;

    CMessageDispatcher();

    void discharge(CBaseGameEntity *receiver, const CMessage &msg);

};

#endif // __CMessageDispatcher_H__
