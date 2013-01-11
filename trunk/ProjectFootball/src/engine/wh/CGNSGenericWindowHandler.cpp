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

#include "CGNSGenericWindowHandler.h"

#include <libintl.h>
#include "../CGameEngine.h"
#include "../../utils/CLog.h"

CGNSGenericWindowHandler::CGNSGenericWindowHandler(const std::string &homeScreen, const std::string &configScreen) :
	CWindowHandler("gns.layout"),
	m_noButtonsBackground(NULL), m_buttonsBackground(NULL), m_homeButton(NULL), m_nextScreenButton(NULL), m_previousScreenButton(NULL),
	m_action1Button(NULL), m_action2Button(NULL), m_action3Button(NULL), m_action4Button(NULL), m_action5Button(NULL), m_action6Button(NULL), m_action7Button(NULL), m_action8Button(NULL),
	m_statisticsRadio(NULL), m_changingRoomRadio(NULL), m_historyRadio(NULL), m_homeScreen(homeScreen), m_configScreen(configScreen)
{}

CGNSGenericWindowHandler::~CGNSGenericWindowHandler()
{}

void CGNSGenericWindowHandler::enter()
{

}

void CGNSGenericWindowHandler::init()
{
	CEGUI::WindowManager	*windowMngr			= CEGUI::WindowManager::getSingletonPtr();
	CEGUI::PushButton		*exitButton			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/ExitButton"));
	CEGUI::PushButton		*mainMenuButton		= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/MainMenuButton"));
	CEGUI::PushButton		*playButton			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/PlayButton"));
	CEGUI::PushButton		*quickSaveButton	= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/QuickSaveButton"));
	CEGUI::PushButton       *configGameButton   = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/ConfigButton"));
	m_action1Button			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/Action1Button"));
	m_action2Button			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/Action2Button"));
	m_action3Button			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/Action3Button"));
	m_action4Button			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/Action4Button"));
	m_action5Button			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/Action5Button"));
	m_action6Button			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/Action6Button"));
	m_action7Button			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/Action7Button"));
	m_action8Button			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/Action8Button"));
	m_changingRoomRadio		= static_cast<CEGUI::RadioButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/ChangingRoomButton"));
	m_statisticsRadio		= static_cast<CEGUI::RadioButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/StatisticsButton"));
	m_historyRadio          = static_cast<CEGUI::RadioButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/HistoryButton"));

	m_noButtonsBackground	= static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/GNSListEndE"));
	m_buttonsBackground		= static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/GNSListEndF"));
	m_homeButton			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/HomeButton"));
	m_nextScreenButton		= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/NextScreenButton"));
	m_previousScreenButton	= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/PreviousScreenButton"));

	// i18n support
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	exitButton->setTooltipText((CEGUI::utf8*)gettext("Exit to MS Windows"));
	#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
		exitButton->setTooltipText((CEGUI::utf8*)gettext("Exit to GNU/Linux"));
	#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		exitButton->setTooltipText((CEGUI::utf8*)gettext("Exit to Mac OS"));
	#else
		exitButton->setTooltipText((CEGUI::utf8*)gettext("Exit to OS"));
	#endif
	mainMenuButton			->setTooltipText((CEGUI::utf8*)gettext("Return to Main Menu"));
	configGameButton        ->setTooltipText((CEGUI::utf8*)gettext("Configuration"));
	quickSaveButton			->setTooltipText((CEGUI::utf8*)gettext("Quick Save"));
	m_homeButton			->setTooltipText((CEGUI::utf8*)gettext("Home"));
	m_nextScreenButton		->setTooltipText((CEGUI::utf8*)gettext("Next Screen"));
	m_previousScreenButton	->setTooltipText((CEGUI::utf8*)gettext("Previous Screen"));
	m_homeButton			->setTooltipText((CEGUI::utf8*)gettext("Home"));
    m_changingRoomRadio		->setTooltipText((CEGUI::utf8*)gettext("Changing Room"));
    m_statisticsRadio		->setTooltipText((CEGUI::utf8*)gettext("Statistics"));
    m_historyRadio          ->setTooltipText((CEGUI::utf8*)gettext("Info Manager"));

	m_noButtonsBackground->setRiseOnClickEnabled(false);
	m_buttonsBackground->setRiseOnClickEnabled(false);


	// Event handle
	registerEventConnection(exitButton				->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::exitButtonClicked, this)));
	registerEventConnection(mainMenuButton			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::mainMenuButtonClicked, this)));
	registerEventConnection(playButton				->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::playButtonClicked, this)));
	registerEventConnection(configGameButton        ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::configGameButtonClicked, this)));
	registerEventConnection(quickSaveButton			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::quickSaveButtonClicked, this)));
	registerEventConnection(m_action1Button			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action2Button			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action3Button			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action4Button			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action5Button			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action6Button			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action7Button			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action8Button			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_changingRoomRadio		->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::gnsSelectionChanged, this)));
	registerEventConnection(m_statisticsRadio		->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::gnsSelectionChanged, this)));
	registerEventConnection(m_historyRadio          ->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::gnsSelectionChanged, this)));
	registerEventConnection(m_homeButton			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::homeButtonClicked, this)));
	registerEventConnection(m_nextScreenButton		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::nextScreenButtonClicked, this)));
	registerEventConnection(m_previousScreenButton	->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::previousScreenButtonClicked, this)));

	m_changingRoomRadio->setSelected(true);
}

bool CGNSGenericWindowHandler::actionButtonClicked(const CEGUI::EventArgs &e)
{
	const CEGUI::WindowEventArgs	&we	= static_cast<const CEGUI::WindowEventArgs&>(e);
	CGameEngine::getInstance()->getWindowManager()->nextScreen(we.window->getUserString("screen").c_str());

	return true;
}

bool CGNSGenericWindowHandler::gnsSelectionChanged(const CEGUI::EventArgs &e)
{
	return true;
}

bool CGNSGenericWindowHandler::exitButtonClicked(const CEGUI::EventArgs &e)
{
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game and return to MS Windows?"), CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::exitConfirmed, this));
	#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
		CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game and return to GNU/Linux?"), CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::exitConfirmed, this));
	#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game and return to Mac OS?"), CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::exitConfirmed, this));
	#else
		CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game and return to the Operating System?"), CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::exitConfirmed, this));
	#endif
	return true;
}

bool CGNSGenericWindowHandler::exitConfirmed(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->exit();
	return true;
}

bool CGNSGenericWindowHandler::mainMenuButtonClicked(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game?"), CEGUI::Event::Subscriber(&CGNSGenericWindowHandler::mainMenuConfirmed, this));
	return true;
}

bool CGNSGenericWindowHandler::mainMenuConfirmed(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->unloadCurrentGame();
	return true;
}

bool CGNSGenericWindowHandler::playButtonClicked(const CEGUI::EventArgs &e)
{
	return true;
}

bool CGNSGenericWindowHandler::configGameButtonClicked(const CEGUI::EventArgs &e)
{
    CGameEngine::getInstance()->getWindowManager()->nextScreen(m_configScreen);
    return true;
}

bool CGNSGenericWindowHandler::quickSaveButtonClicked(const CEGUI::EventArgs &e)
{
	return true;
}

bool CGNSGenericWindowHandler::homeButtonClicked(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->getWindowManager()->nextScreen(m_homeScreen);
	return true;
}

bool CGNSGenericWindowHandler::nextScreenButtonClicked(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->getWindowManager()->nextScreen();
	return true;
}

bool CGNSGenericWindowHandler::previousScreenButtonClicked(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->getWindowManager()->previousScreen();
	return true;
}
