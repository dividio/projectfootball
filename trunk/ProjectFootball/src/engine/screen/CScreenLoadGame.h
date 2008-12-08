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
    CScreenLoadGame();
	virtual ~CScreenLoadGame();

    virtual void enter();

private:
    void loadGameList();
    bool gamesListDoubleClick       (const CEGUI::EventArgs& e);
    bool gamesListSelectChanged     (const CEGUI::EventArgs& e);
    bool newGameEditboxTextChanged  (const CEGUI::EventArgs& e);
	bool backButtonClicked          (const CEGUI::EventArgs& e);
	bool newGameButtonClicked       (const CEGUI::EventArgs& e);
	bool loadGameButtonClicked      (const CEGUI::EventArgs& e);
	bool deleteGameButtonClicked    (const CEGUI::EventArgs& e);
    bool removeConfirmButtonClicked (const CEGUI::EventArgs& e);
    bool removeCancelButtonClicked  (const CEGUI::EventArgs& e);

	CEGUI::PushButton		*m_backButton;
    CEGUI::MultiColumnList  *m_gamesList;
    CEGUI::Editbox          *m_newGameEditbox;
    CEGUI::PushButton       *m_newGameButton;
    CEGUI::PushButton       *m_loadGameButton;
    CEGUI::PushButton       *m_deleteGameButton;
    CEGUI::PushButton       *m_removeConfirmButton;
    CEGUI::PushButton       *m_removeCancelButton;
    CEGUI::Window           *m_mainWindow;
    CEGUI::FrameWindow      *m_confirmRemoveWindow;
    CEGUI::Window           *m_confirmRemoveNote;
};

#endif /*CSCREENLOADGAME_H_*/
