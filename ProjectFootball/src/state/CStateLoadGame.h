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

#ifndef CSTATELOADGAME_H_
#define CSTATELOADGAME_H_

#include "CState.h"

class CStateLoadGame : public CState
{
public:
    static CStateLoadGame* getInstance();
	virtual ~CStateLoadGame();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

    void createNewGame();
    void loadGame();

private:
    CStateLoadGame();

    void loadGameList();
    bool handleSelectChanged(const CEGUI::EventArgs& e);
    bool handleTextChanged(const CEGUI::EventArgs& e);

    CEGUI::MultiColumnList  *m_gamesList;
    CEGUI::Editbox          *m_newGameEditbox;
    CEGUI::PushButton       *m_newGameButton;
    CEGUI::PushButton       *m_loadGameButton;
};

#endif /*CSTATELOADGAME_H_*/
