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

#ifndef CLINEUPWINDOWHANDLER_H_
#define CLINEUPWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>
#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CSinglePlayerGame;
class CPfTeamPlayers;



class CLineUpWindowHandler : public CWindowHandler
{
public:
    CLineUpWindowHandler(CSinglePlayerGame &game);
    virtual ~CLineUpWindowHandler();

    virtual void enter();
    virtual void init();
    virtual void leave();

private:
    bool lineUpTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e);
    bool alternateTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e);
    bool notLineUpTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e);

    void loadTeamPlayersList();
    void addPlayerToLineUpList(CPfTeamPlayers *player, CEGUI::MultiColumnList *list, int xFormation);
    void addPlayerToList(CPfTeamPlayers *player, CEGUI::MultiColumnList *list);
    void saveTeamPlayersList();
    void changePlayers(CEGUI::MultiColumnList *list1, int row1, CEGUI::MultiColumnList *list2, int row2);
    void selectChanged(CEGUI::MultiColumnList *list);
    void changeRows(CEGUI::MultiColumnList *list1, int row1, CEGUI::MultiColumnList *list2, int row2);
    void refreshRow(CEGUI::MultiColumnList *list, int row);
    void changeRowSelection(CEGUI::MultiColumnList *list, int row, bool newSelectionState);

    CEGUI::MultiColumnList 	*m_lineUpTeamPlayersList;
    CEGUI::MultiColumnList 	*m_alternateTeamPlayersList;
    CEGUI::MultiColumnList 	*m_notLineUpTeamPlayersList;

    CPfTeamPlayers         	*m_selectedPlayer;
    int                      m_selectedPlayerRow;
    CEGUI::MultiColumnList 	*m_selectedPlayerList;

    CEGUI::Window           *m_teamName;
    CEGUI::Window           *m_teamAverage;
    CEGUI::Window           *m_teamBadge;

    CSinglePlayerGame		&m_game;
    bool					m_initiated;
};

#endif /*CLINEUPWINDOWHANDLER_H_*/
