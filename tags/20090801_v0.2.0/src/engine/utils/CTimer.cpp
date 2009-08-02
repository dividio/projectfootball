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

#include "IClock.h"
#include "../CGameEngine.h"


CTimer::CTimer(int frequency) : m_clock(CGameEngine::getInstance()->getClock())
{
	reset();

	if( frequency<=0 ){
		m_period = -1.0;
	}else{
		m_period = 1.0/(double)frequency;
	}
}


CTimer::~CTimer()
{
}


void CTimer::reset()
{
    m_previousTime = m_clock.getCurrentTime();
}


bool CTimer::nextTick()
{
    bool tick = false;
    if( m_period>0 ){
        double currentTime  = m_clock.getCurrentTime();
        if( currentTime<m_previousTime ){
            // clock overflow detected
            m_previousTime = currentTime;
        }

        double timeLapse    = currentTime - m_previousTime;
        if( timeLapse>m_period ){
            m_previousTime += m_period;
            tick = true;
        }else{
            tick = false;
        }
    }
    return tick;
}
