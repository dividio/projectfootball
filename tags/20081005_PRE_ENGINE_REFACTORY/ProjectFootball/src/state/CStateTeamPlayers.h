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

#ifndef CSTATETEAMPLAYERS_H_
#define CSTATETEAMPLAYERS_H_

#include "CState.h"
#include "../engine/CGameEngine.h"

enum SelectedPlayers {NONE, PLAYER1, PLAYER2, BOTH};

class CStateTeamPlayers : public CState
{
public:
    static CStateTeamPlayers* getInstance();
    virtual ~CStateTeamPlayers();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

    bool handleChangePlayers();

private:
    CStateTeamPlayers();

    void loadTeamPlayersList();
    void saveTeamPlayersList();
    void changePlayers();
    void selectChanged(CEGUI::MultiColumnList *list);
    bool handleLineUpSelectChanged(const CEGUI::EventArgs& e);
    bool handleAlternateSelectChanged(const CEGUI::EventArgs& e);
    bool handleNotLineUpSelectChanged(const CEGUI::EventArgs& e);

    CEGUI::MultiColumnList *m_lineUpTeamPlayersList;
    CEGUI::MultiColumnList *m_alternateTeamPlayersList;
    CEGUI::MultiColumnList *m_notLineUpTeamPlayersList;

    CPfTeamPlayers         *m_selectedPlayer1;
    CPfTeamPlayers         *m_selectedPlayer2;
    CEGUI::ListboxItem     *m_item1;
    CEGUI::ListboxItem     *m_item2;
    CEGUI::MultiColumnList *m_selectedPlayer1List;
    CEGUI::MultiColumnList *m_selectedPlayer2List;
    SelectedPlayers         m_selectedPlayers;
    bool                    m_forcedSelection;
};

#endif /*CSTATETEAMPLAYERS_H_*/
