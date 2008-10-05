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


#ifndef CSTATEMATCHRESULT_H_
#define CSTATEMATCHRESULT_H_

#include "CState.h"
#include "../engine/CGameEngine.h"


class CStateMatchResult : public CState
{
public:
    static CStateMatchResult* getInstance();
    virtual ~CStateMatchResult();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

private:
    CPfMatches              *m_match;
    CEGUI::Window           *m_competitionName;
    CEGUI::Window           *m_competitionPhaseName;
    CEGUI::Window           *m_homeName;
    CEGUI::Window           *m_awayName;
    CEGUI::Window           *m_homeScore;
    CEGUI::Window           *m_awayScore;
    CEGUI::Window           *m_homeLogo;
    CEGUI::Window           *m_awayLogo;
    CEGUI::MultiColumnList  *m_homeEventsList;
    CEGUI::MultiColumnList  *m_awayEventsList;

    CStateMatchResult();

    /** Simulate others matches of same competition phase than m_match
     * TODO Simulate all matches with Date less or equal than current user match
     */
    void simulateMatches();
    int  getRandomNGoals();
    void loadMatchInfo(CPfMatches *match);
};

#endif /*CSTATEMATCHRESULT_H_*/
