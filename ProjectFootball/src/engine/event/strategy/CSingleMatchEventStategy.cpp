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

#include "CSingleMatchEventStategy.h"

CSingleMatchEventStategy::CSingleMatchEventStategy(std::string idMatch)
{
    m_idMatch   = idMatch;
    m_started   = false;
    m_ended     = false;
}

CSingleMatchEventStategy::~CSingleMatchEventStategy()
{
}

void CSingleMatchEventStategy::process(CStartMatchEvent *event)
{
    if( event && event->getIdMatch()==m_idMatch && !m_started ){
        m_started = true;
    }
}

void CSingleMatchEventStategy::process(CEndMatchEvent *event)
{
    if( event && event->getIdMatch()==m_idMatch && m_started && !m_ended){
        m_ended = true;
    }
}

void CSingleMatchEventStategy::process(CGoalMatchEvent *event)
{
    if( event && event->getIdMatch()==m_idMatch && m_started && !m_ended){

    }
}
