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

#ifndef CNEWMANAGERGAMEWINDOWHANDLER_H_
#define CNEWMANAGERGAMEWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>

#include "../wm/CWindowHandler.h"

class CNewManagerGameWindowHandler : public CWindowHandler
{
public:
    CNewManagerGameWindowHandler();
	virtual ~CNewManagerGameWindowHandler();

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

#endif /* CNEWMANAGERGAMEWINDOWHANDLER_H_ */
