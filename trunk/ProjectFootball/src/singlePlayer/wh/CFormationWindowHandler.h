/******************************************************************************
* Copyright (C) 2012 - Ikaro Games   www.ikarogames.com                       *
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

#ifndef CFORMATIONWINDOWHANDLER_H_
#define CFORMATIONWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>
#include <boost/array.hpp>
#include "../../engine/wm/CWindowHandler.h"
#include "../db/bean/CPfStrategicPositions.h"

//Forward declarations
class CSinglePlayerGame;
class CPfTeamPlayers;



class CFormationWindowHandler : public CWindowHandler
{
public:
    CFormationWindowHandler(CSinglePlayerGame &game);
    virtual ~CFormationWindowHandler();

    virtual void enter();
    virtual void init();
    virtual void leave();

private:
    bool lineUpTeamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e);

    void loadTeamPlayersList();
    void addPlayerToLineUpList(CPfTeamPlayers *player, CEGUI::MultiColumnList *list, int xFormation);
    void saveTeamPlayersList();
    void changePlayers(CEGUI::MultiColumnList *list1, int row1, CEGUI::MultiColumnList *list2, int row2);
    void selectChanged(CEGUI::MultiColumnList *list);
    void changeRows(CEGUI::MultiColumnList *list1, int row1, CEGUI::MultiColumnList *list2, int row2);
    void changeRowSelection(CEGUI::MultiColumnList *list, int row, bool newSelectionState);
	void setOffDefPosVisability();

    CEGUI::MultiColumnList 	*m_lineUpTeamPlayersList;

    CPfTeamPlayers         	*m_selectedPlayer;
    int                      m_selectedPlayerRow;
    CEGUI::MultiColumnList 	*m_selectedPlayerList;
	
	CEGUI::Window *m_teamFormationName;
	CEGUI::Window *m_teamFormationImg;

	boost::array< std::pair< CEGUI::Window *, CEGUI::Window * >, 13 > m_lineUpGui;

    CSinglePlayerGame		&m_game;
    bool					m_initiated;
	bool					m_highlight_player;
};

#endif /*CFORMATIONWINDOWHANDLER_H_*/
