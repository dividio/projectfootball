/******************************************************************************
* Copyright (C) 2007 - Ikaro Games   www.ikarogames.com                       *
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


#ifndef CSCREENMAINMENU_H_
#define CSCREENMAINMENU_H_

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "../CScreen.h"


class CScreenMainMenu : public CScreen
{

public:
    CScreenMainMenu();
    virtual ~CScreenMainMenu();

    virtual void enter();

private:
	bool virtualChampionshipButtonClicked(const CEGUI::EventArgs& e);
	bool newManagerGameButtonClicked(const CEGUI::EventArgs& e);
	bool configButtonClicked(const CEGUI::EventArgs& e);
	bool creditsButtonClicked(const CEGUI::EventArgs& e);
	bool loadGameButtonClicked(const CEGUI::EventArgs& e);
	bool quickLoadButtonClicked(const CEGUI::EventArgs& e);
	bool quitButtonClicked(const CEGUI::EventArgs& e);

	CEGUI::PushButton	*m_virtualChampionshipButton;
	CEGUI::PushButton	*m_newManagerGameButton;
	CEGUI::PushButton	*m_configButton;
	CEGUI::PushButton	*m_creditsButton;
	CEGUI::PushButton	*m_quickLoadButton;
	CEGUI::PushButton	*m_loadGameButton;
	CEGUI::PushButton	*m_quitButton;
	CEGUI::Window       *m_currentDate;
	CEGUI::Window       *m_versionDate;
	CEGUI::Window       *m_version;
};
#endif // CSCREENMAINMENU_H_
