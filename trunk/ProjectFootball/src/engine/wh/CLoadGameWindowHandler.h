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

#ifndef CLOADGAMEWINDOWHANDLER_H_
#define CLOADGAMEWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>

#include "../wm/CWindowHandler.h"

class CLoadGameWindowHandler : public CWindowHandler
{
public:
    CLoadGameWindowHandler();
	virtual ~CLoadGameWindowHandler();

    virtual void enter();
    virtual void init();

private:
    void loadGameList();
    bool gamesListDoubleClick       (const CEGUI::EventArgs& e);
    bool gamesListSelectChanged     (const CEGUI::EventArgs& e);
	bool backButtonClicked          (const CEGUI::EventArgs& e);
	bool loadGameButtonClicked      (const CEGUI::EventArgs& e);
	bool deleteGameButtonClicked    (const CEGUI::EventArgs& e);
    bool deleteGameConfirmed		(const CEGUI::EventArgs& e);

	CEGUI::PushButton		*m_backButton;
    CEGUI::MultiColumnList  *m_gamesList;
    CEGUI::PushButton       *m_loadGameButton;
    CEGUI::PushButton       *m_deleteGameButton;
    CEGUI::Window           *m_mainWindow;
};

#endif /*CLOADGAMEWINDOWHANDLER_H_*/
