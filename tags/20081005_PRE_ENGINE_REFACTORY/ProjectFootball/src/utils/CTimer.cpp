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


#include "CTimer.h"
#include "../state/CStateManager.h"

CTimer::CTimer(int frequency)
{
    m_frequency = 1.0/frequency;
    m_currentTime = 0;
    m_previousTime = 0;
}


CTimer::~CTimer()
{
}


void CTimer::update()
{
    m_currentTime += CStateManager::getInstance()->getTimeSinceLastFrame();
}


void CTimer::reset()
{
    m_currentTime = 0;
    m_previousTime = 0;
}


double CTimer::getTime() const
{
    return m_currentTime;
}


bool CTimer::nextTick()
{
    double auxTime;
    bool tick = false;
    auxTime = m_currentTime;
    update();
    if(m_frequency != -1) {
        m_previousTime += (m_currentTime - auxTime);
        if(m_previousTime >= m_frequency) {
            m_previousTime -= m_frequency;
            tick = true;
        }
    } else {
        tick = true;
    }

    return tick;
}
