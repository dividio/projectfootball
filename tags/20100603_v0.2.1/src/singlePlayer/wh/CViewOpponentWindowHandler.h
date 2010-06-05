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

#ifndef CVIEWOPPONENTWINDOWHANDLER_H_
#define CVIEWOPPONENTWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>
#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CSinglePlayerGame;
class CPfTeamPlayers;
class CPfTeams;



class CViewOpponentWindowHandler : public CWindowHandler
{
public:
    CViewOpponentWindowHandler(CSinglePlayerGame &game);
    virtual ~CViewOpponentWindowHandler();

    virtual void enter();
    virtual void init();
    virtual void leave();

private:
    void loadTeamInfo        (CPfTeams *team);
    void loadOpponentTeamInfo(CPfTeams *team);
    void loadTeamPlayersList (CPfTeams *team, CEGUI::MultiColumnList *list);
    void addPlayerToList     (CPfTeamPlayers *player, CEGUI::MultiColumnList *list);

    CEGUI::MultiColumnList 	*m_teamPlayersList;
    CEGUI::MultiColumnList  *m_opponentTeamPlayersList;

    CEGUI::Window           *m_teamName;
    CEGUI::Window           *m_teamAverage;
    CEGUI::Window           *m_teamBadge;
    CEGUI::Window           *m_opponentTeamName;
    CEGUI::Window           *m_opponentTeamAverage;
    CEGUI::Window           *m_opponentTeamBadge;

    CSinglePlayerGame		&m_game;
    bool					m_initiated;
};

#endif /*CVIEWOPPONENTWINDOWHANDLER_H_*/
