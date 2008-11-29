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

#ifndef CSINGLEMPLAYEREVENTSTRATEGY_H_
#define CSINGLEMPLAYEREVENTSTRATEGY_H_

#include <vector>

#include "../match/CStartMatchEvent.h"
#include "../match/CEndMatchEvent.h"
#include "../match/CGoalMatchEvent.h"

#include "../../report/CSinglePlayerReportRegister.h"

#include "../../db/bean/CPfGoals.h"
#include "../../db/dao/factory/IDAOFactory.h"

class CSinglePlayerEventStrategy
{
public:
	CSinglePlayerEventStrategy(IDAOFactory *daoFactory, CSinglePlayerReportRegister *reportRegister);
	virtual ~CSinglePlayerEventStrategy();

    virtual void process(CStartMatchEvent &event);
    virtual void process(CEndMatchEvent   &event);
    virtual void process(CGoalMatchEvent  &event);

private:
    int     					m_xMatch;
    bool    					m_started;
    bool    					m_ended;
    std::vector<CPfGoals *> 	m_goalsList;

    IDAOFactory					*m_daoFactory;
    CSinglePlayerReportRegister *m_reportRegister;
};

#endif /*CSINGLEMPLAYEREVENTSTRATEGY_H_*/
