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

#ifndef CCONFIGGAMEWINDOWHANDLER_H_
#define CCONFIGGAMEWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>

#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CSinglePlayerGame;

class CConfigGameWindowHandler : public CWindowHandler
{
public:
    CConfigGameWindowHandler(CSinglePlayerGame &game);
	virtual ~CConfigGameWindowHandler();

    virtual void enter();
    virtual void init();

private:
    bool backButtonClicked(const CEGUI::EventArgs& e);
	bool saveButtonClicked(const CEGUI::EventArgs& e);

	CEGUI::PushButton   *m_acceptButton;
	CEGUI::PushButton	*m_cancelButton;
    CEGUI::Combobox 	*m_simulationTimeCombo;
    CEGUI::Checkbox 	*m_resultModeCheck;

    CSinglePlayerGame   &m_game;
    bool                 m_initiated;
};

#endif /*CCONFIGGAMEWINDOWHANDLER_H_*/
