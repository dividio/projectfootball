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

#ifndef CTEAMPLAYERSWINDOWHANDLER_H_
#define CTEAMPLAYERSWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>
#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CSinglePlayerGame;
class CPfTeamPlayers;



class CTeamPlayersWindowHandler : public CWindowHandler
{
public:
    CTeamPlayersWindowHandler(CSinglePlayerGame &game);
    virtual ~CTeamPlayersWindowHandler();

    virtual void enter();
    virtual void init();
    virtual void leave();

private:
    bool lineUpTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e);
    bool alternateTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e);
    bool notLineUpTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e);
    bool changePlayersButtonClicked(const CEGUI::EventArgs& e);

    void loadTeamPlayersList();
    void addPlayerToList(CPfTeamPlayers *player, CEGUI::MultiColumnList *list);
    void saveTeamPlayersList();
    void changePlayers();
    void selectChanged(CEGUI::MultiColumnList *list);
    void changeRows(CEGUI::MultiColumnList *list1, int row1, CEGUI::MultiColumnList *list2, int row2);
    void changeRowSelection(CEGUI::MultiColumnList *list, int row, bool newSelectionState);

    CEGUI::MultiColumnList 	*m_lineUpTeamPlayersList;
    CEGUI::MultiColumnList 	*m_alternateTeamPlayersList;
    CEGUI::MultiColumnList 	*m_notLineUpTeamPlayersList;

    CPfTeamPlayers         	*m_selectedPlayer1;
    CPfTeamPlayers         	*m_selectedPlayer2;
    int                      m_selectedPlayer1Row;
    int                      m_selectedPlayer2Row;

    CEGUI::MultiColumnList 	*m_selectedPlayer1List;
    CEGUI::MultiColumnList 	*m_selectedPlayer2List;
    CEGUI::PushButton		*m_changePlayersButton;
    CEGUI::Window           *m_teamName;
    CEGUI::Window           *m_teamAverage;
    CEGUI::Window           *m_teamCrest;

    enum SelectedPlayers {NONE, PLAYER1, PLAYER2, BOTH};
    SelectedPlayers          m_selectedPlayers;

    CSinglePlayerGame		&m_game;
    bool					m_initiated;
};

#endif /*CTEAMPLAYERSWINDOWHANDLER_H_*/
