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

#ifndef CWINDOWMANAGER_H_
#define CWINDOWMANAGER_H_

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <CEGUI/CEGUI.h>

#include "IWindowHandler.h"

#include "xml/elements/CScreensConfigElement.h"
#include "xml/elements/CWindowElement.h"

class CWindowManager {
	friend class CGameEngine;
public:
	CWindowManager();
	virtual ~CWindowManager();

	void		clearHistory();
	const char*	getCurrentScreen();
	void		nextScreen();
	void		nextScreen(const std::string &screenId);
	void		previousScreen();

	void registerWindowHandler(const std::string &path, IWindowHandler &windowHandler);
	void unregisterWindowHandler(const std::string &path, IWindowHandler &windowHandler);

	void alert(const std::string &text);
	void confirm(const std::string &text, CEGUI::Event::Subscriber acceptSubscriber);
	void confirm(const std::string &text, CEGUI::Event::Subscriber acceptSubscriber, CEGUI::Event::Subscriber cancelSubscriber);
	void loading(const std::string &text);
	void loadingUpdate(const std::string &text, bool stop);

protected:
	void update();

	void _clearHistory();
	void _nextScreen();
	void _nextScreen(const std::string &screenId);
	void _previousScreen();

	void enterEvent(const CScreenElement &screen);
	void leaveEvent(const CScreenElement &screen);
	void updateEvent(const CScreenElement &screen);

	void enterEvent(const CWindowElement &window);
	void leaveEvent(const CWindowElement &window);
	void updateEvent(const CWindowElement &window);

	void hookWindow(const CWindowElement &window);
	void unHookWindow(const CWindowElement &window);

	const CScreenElement*	getScreen(const std::string &screenId);
	CEGUI::Window*			getCEGUIWindow(const std::string &path);

	// Confirm & acept events handlers
	bool alertAcceptClicked(const CEGUI::EventArgs& e);
	bool confirmAcceptClicked(const CEGUI::EventArgs& e);
	bool confirmCancelClicked(const CEGUI::EventArgs& e);

private:
	CScreensConfigElement									m_screensConfig;
	std::map<std::string, CEGUI::Window*>					m_windows;
	std::map<std::string, std::map<IWindowHandler*, bool> >	m_windowsHandlers;

	std::list<std::string>									m_commandsList;
	const CScreenElement									*m_currentScreen;
	std::vector<std::string>								m_nextScreensStack;
	std::vector<std::string>								m_previousScreensStack;

	// confirm & alert
	CEGUI::Window											*m_alertWindow;
	CEGUI::Window											*m_confirmWindow;
	CEGUI::Window											*m_loadingWindow;
	CEGUI::Event::Subscriber								m_confirmAcceptSubscriber;
	CEGUI::Event::Subscriber								m_confirmCancelSubscriber;
};

#endif /* CWINDOWMANAGER_H_ */
