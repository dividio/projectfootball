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

#ifndef CTEAMPLAYERDETAILSWINDOWHANDLER_H_
#define CTEAMPLAYERDETAILSWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>
#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CSinglePlayerGame;
class CPfTeamPlayers;



class CTeamPlayerDetailsWindowHandler : public CWindowHandler
{
public:
    CTeamPlayerDetailsWindowHandler(CSinglePlayerGame &game);
    virtual ~CTeamPlayerDetailsWindowHandler();

    virtual void enter();
    virtual void init();
    virtual void leave();

private:
    const CPfTeamPlayers    *m_selectedTeamPlayer;

    CEGUI::Window           *m_name;
    CEGUI::Window           *m_photo;
    CEGUI::Window           *m_shortName;
    CEGUI::Window           *m_birthday;
    CEGUI::Window           *m_weight;
    CEGUI::Window           *m_height;
    CEGUI::Window           *m_years;
    CEGUI::Window           *m_country;
    CEGUI::Window           *m_teamName;
    CEGUI::Window           *m_dateBegin;
    CEGUI::Window           *m_dateEnd;
    CEGUI::Window           *m_salary;
    CEGUI::Window           *m_releaseClause;

    CSinglePlayerGame       &m_game;
};

#endif /*CTEAMPLAYERDETAILSWINDOWHANDLER_H_*/
