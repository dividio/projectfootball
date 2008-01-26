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

#ifndef CSINGLEMATCHEVENTSTATEGY_H_
#define CSINGLEMATCHEVENTSTATEGY_H_

#include <string>

#include "IGameEventStrategy.h"

class CSingleMatchEventStategy : IGameEventStrategy
{
public:
	CSingleMatchEventStategy(std::string idMatch);
	virtual ~CSingleMatchEventStategy();

    virtual void process(CStartMatchEvent *event);
    virtual void process(CEndMatchEvent *event);
    virtual void process(CGoalMatchEvent *event);

private:
    std::string m_idMatch;
    bool        m_started;
    bool        m_ended;
};

#endif /*CSINGLEMATCHEVENTSTATEGY_H_*/
