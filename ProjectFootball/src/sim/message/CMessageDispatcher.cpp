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


#include "CMessageDispatcher.h"
#include "../entity/CEntityManager.h"
#include "../../utils/CLog.h"



CMessageDispatcher* CMessageDispatcher::getInstance()
{
    static CMessageDispatcher instance;
    return &instance;
}


CMessageDispatcher::CMessageDispatcher()
{
    CLog::getInstance()->debug("CMessageDispatcher()");
    m_timer = new CTimer();
}


CMessageDispatcher::~CMessageDispatcher()
{
    CLog::getInstance()->debug("~CMessageDispatcher()");
    if(m_timer != 0) {
        delete m_timer;
    }
}


void CMessageDispatcher::dispatchMsg(double delay, int sender, int receiver, int msg, void *info)
{
    CBaseGameEntity *entity = CEntityManager::getInstance()->getEntityFromID(receiver);

    if(entity == 0) {
        CLog::getInstance()->debug("Entity %d doesn't exist", receiver);
        return;
    }

    CMessage message(0, sender, receiver, msg, info);
    if(delay <= 0.0) {
        discharge(entity, message);
    } else {
        message.DispatchTime = m_timer->getTime() + delay;
        m_priorityQueue.insert(message);
    }
}

void CMessageDispatcher::dispatchDelayedMessages()
{
    m_timer->nextTick();
    double time = m_timer->getTime();
    while(!m_priorityQueue.empty() &&
            (m_priorityQueue.begin()->DispatchTime < time) &&
            (m_priorityQueue.begin()->DispatchTime > 0)) {

        const CMessage &message = *m_priorityQueue.begin();
        CBaseGameEntity *receiver = CEntityManager::getInstance()->getEntityFromID(message.Receiver);

        discharge(receiver, message);

        m_priorityQueue.erase(m_priorityQueue.begin());
    }
}


void CMessageDispatcher::reset()
{
    m_timer->reset();
    m_priorityQueue.clear();
}


void CMessageDispatcher::discharge(CBaseGameEntity *receiver, const CMessage &msg)
{
    if(!receiver->handleMessage(msg)) {
        CLog::getInstance()->debug("Entity %d can't handle messagge from entity %d",
                receiver->getID(), msg.Sender);
    }
}
