/*******************************************************************************
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

#ifndef CGNSWINDOWHANDLER_H_
#define CGNSWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>

#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CSinglePlayerGame;

class CGNSWindowHandler: public CWindowHandler {
public:
	CGNSWindowHandler(CSinglePlayerGame &game);
	virtual ~CGNSWindowHandler();

	virtual void enter();
	virtual void init();

protected:
	bool actionButtonClicked			(const CEGUI::EventArgs &e);
	bool gnsSelectionChanged			(const CEGUI::EventArgs &e);

	bool exitButtonClicked				(const CEGUI::EventArgs &e);
	bool exitConfirmed					(const CEGUI::EventArgs &e);
	bool mainMenuButtonClicked			(const CEGUI::EventArgs &e);
	bool mainMenuConfirmed				(const CEGUI::EventArgs &e);
	bool playButtonClicked				(const CEGUI::EventArgs &e);
	bool resultModeCheckStateChanged	(const CEGUI::EventArgs &e);
	bool quickSaveButtonClicked			(const CEGUI::EventArgs &e);

	bool homeButtonClicked				(const CEGUI::EventArgs &e);
	bool nextScreenButtonClicked		(const CEGUI::EventArgs &e);
	bool previousScreenButtonClicked	(const CEGUI::EventArgs &e);

private:
	CEGUI::Window		*m_noButtonsBackground;
	CEGUI::Window		*m_buttonsBackground;
	CEGUI::PushButton	*m_homeButton;
	CEGUI::PushButton	*m_nextScreenButton;
	CEGUI::PushButton	*m_previousScreenButton;

	CEGUI::PushButton	*m_action1Button;
	CEGUI::PushButton	*m_action2Button;
	CEGUI::PushButton	*m_action3Button;
	CEGUI::PushButton	*m_action4Button;
	CEGUI::PushButton	*m_action5Button;
	CEGUI::PushButton	*m_action6Button;
	CEGUI::PushButton	*m_action7Button;
	CEGUI::PushButton	*m_action8Button;

	CEGUI::RadioButton	*m_statisticsRadio;
	CEGUI::RadioButton	*m_changingRoomRadio;

	CEGUI::Checkbox		*m_resultModeCheck;

    CSinglePlayerGame	&m_game;

};

#endif /* CGNSWINDOWHANDLER_H_ */
