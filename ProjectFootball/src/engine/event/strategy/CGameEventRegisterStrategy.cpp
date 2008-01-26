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

#include "CGameEventRegisterStrategy.h"

CGameEventRegisterStrategy::CGameEventRegisterStrategy(IGameEventStrategy *delegatedEventStrategy)
{
    m_delegatedEventStrategy = delegatedEventStrategy;
}

CGameEventRegisterStrategy::~CGameEventRegisterStrategy()
{
}

void CGameEventRegisterStrategy::process(CEndMatchEvent *event)
{
    if( m_delegatedEventStrategy ){
        m_delegatedEventStrategy->process(event);
    }
}

void CGameEventRegisterStrategy::process(CGoalMatchEvent *event)
{
    if( m_delegatedEventStrategy ){
        m_delegatedEventStrategy->process(event);
    }
}

void CGameEventRegisterStrategy::process(CStartMatchEvent *event)
{
    if( m_delegatedEventStrategy ){
        m_delegatedEventStrategy->process(event);
    }
}
