/******************************************************************************
* Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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

#ifndef CSCREENNEWMANAGERGAME_H_
#define CSCREENNEWMANAGERGAME_H_

#include <CEGUI/CEGUI.h>

#include "../wm/CWindowHandler.h"

class CScreenNewManagerGame : public CWindowHandler
{
public:
    CScreenNewManagerGame();
	virtual ~CScreenNewManagerGame();

    virtual void enter();
    virtual void init();

private:
    bool newGameEditboxTextChanged  (const CEGUI::EventArgs& e);
	bool backButtonClicked          (const CEGUI::EventArgs& e);
	bool newGameButtonClicked       (const CEGUI::EventArgs& e);

	CEGUI::PushButton		*m_backButton;
    CEGUI::Editbox          *m_newGameEditbox;
    CEGUI::PushButton       *m_newGameButton;
};

#endif /* CSCREENNEWMANAGERGAME_H_ */
