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

#ifndef CSCREENLOADGAME_H_
#define CSCREENLOADGAME_H_

#include "../CScreen.h"

class CScreenLoadGame : public CScreen
{
public:
    static CScreenLoadGame* getInstance();
	virtual ~CScreenLoadGame();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

    void newGame();
    void loadGame();
    void deleteGame();

private:
    CScreenLoadGame();

    void loadGameList();
    bool handleDoubleClick(const CEGUI::EventArgs& e);
    bool handleSelectChanged(const CEGUI::EventArgs& e);
    bool handleTextChanged(const CEGUI::EventArgs& e);

    CEGUI::MultiColumnList  *m_gamesList;
    CEGUI::Editbox          *m_newGameEditbox;
    CEGUI::PushButton       *m_newGameButton;
    CEGUI::PushButton       *m_loadGameButton;
    CEGUI::PushButton       *m_deleteGameButton;
};

#endif /*CSCREENLOADGAME_H_*/
