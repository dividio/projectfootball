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

#include "CGNSWindowHandler.h"

#include <libintl.h>
#include "../CSinglePlayerGame.h"
#include "../option/CSinglePlayerOptionManager.h"
#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"

CGNSWindowHandler::CGNSWindowHandler(CSinglePlayerGame &game)
: CWindowHandler("gns.layout"),
  m_action1Button(NULL), m_action2Button(NULL), m_action3Button(NULL), m_action4Button(NULL), m_action5Button(NULL), m_action6Button(NULL), m_action7Button(NULL), m_action8Button(NULL),
  m_statisticsRadio(NULL), m_changingRoomRadio(NULL), m_game(game)
{}

CGNSWindowHandler::~CGNSWindowHandler()
{}

void CGNSWindowHandler::enter()
{
	m_resultModeCheck->setSelected(m_game.getOptionManager()->getMatchResultMode());
}

void CGNSWindowHandler::init()
{
	CEGUI::WindowManager	*windowMngr			= CEGUI::WindowManager::getSingletonPtr();
	CEGUI::PushButton		*exitButton			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/ExitButton"));
	CEGUI::PushButton		*homeButton			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/HomeButton"));
	CEGUI::PushButton		*mainMenuButton		= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/MainMenuButton"));
	CEGUI::PushButton		*playButton			= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/PlayButton"));
	CEGUI::PushButton		*quickSaveButton	= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/QuickSaveButton"));
	m_resultModeCheck		= static_cast<CEGUI::Checkbox*>(windowMngr->getWindow((CEGUI::utf8*)"GNS/ResultModeCheckbox"));
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
	homeButton				->setTooltipText((CEGUI::utf8*)gettext("Game Menu"));
	mainMenuButton			->setTooltipText((CEGUI::utf8*)gettext("Return to Main Menu"));
	playButton				->setTooltipText((CEGUI::utf8*)gettext("Play Match"));
	quickSaveButton			->setTooltipText((CEGUI::utf8*)gettext("Quick Save"));
	m_resultModeCheck		->setTooltipText((CEGUI::utf8*)gettext("Result Mode"));
    m_changingRoomRadio		->setTooltipText((CEGUI::utf8*)gettext("Changing Room"));
    m_statisticsRadio		->setTooltipText((CEGUI::utf8*)gettext("Statistics"));

	// Event handle
	registerEventConnection(exitButton			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::exitButtonClicked, this)));
	registerEventConnection(homeButton			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::homeButtonClicked, this)));
	registerEventConnection(mainMenuButton		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::mainMenuButtonClicked, this)));
	registerEventConnection(playButton			->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::playButtonClicked, this)));
	registerEventConnection(quickSaveButton		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::quickSaveButtonClicked, this)));
	registerEventConnection(m_resultModeCheck	->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&CGNSWindowHandler::resultModeCheckStateChanged, this)));
	registerEventConnection(m_action1Button		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action2Button		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action3Button		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action4Button		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action5Button		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action6Button		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action7Button		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_action8Button		->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CGNSWindowHandler::actionButtonClicked, this)));
	registerEventConnection(m_changingRoomRadio	->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged, CEGUI::Event::Subscriber(&CGNSWindowHandler::gnsSelectionChanged, this)));
	registerEventConnection(m_statisticsRadio	->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged, CEGUI::Event::Subscriber(&CGNSWindowHandler::gnsSelectionChanged, this)));

	m_changingRoomRadio->setSelected(true);
}

bool CGNSWindowHandler::actionButtonClicked(const CEGUI::EventArgs &e)
{
	const CEGUI::WindowEventArgs	&we	= static_cast<const CEGUI::WindowEventArgs&>(e);
	CGameEngine::getInstance()->getWindowManager()->nextScreen(we.window->getUserString("screen").c_str());

	return true;
}

bool CGNSWindowHandler::gnsSelectionChanged(const CEGUI::EventArgs &e)
{
	CEGUI::RadioButton *button = m_changingRoomRadio->getSelectedButtonInGroup();
	if( button==m_changingRoomRadio ){
		m_action1Button->setText((CEGUI::utf8*)gettext("Line Up"));
		m_action1Button->setUserString("screen", "LineUp");
		m_action1Button->setEnabled(true);
		m_action2Button->setText((CEGUI::utf8*)gettext("Team Players"));
		m_action2Button->setUserString("screen", "TeamPlayers");
		m_action2Button->setEnabled(true);
		m_action3Button->setText("");
		m_action3Button->setUserString("screen", "");
		m_action3Button->setEnabled(false);
		m_action4Button->setText("");
		m_action4Button->setUserString("screen", "");
		m_action4Button->setEnabled(false);
		m_action5Button->setText("");
		m_action5Button->setUserString("screen", "");
		m_action5Button->setEnabled(false);
		m_action6Button->setText("");
		m_action6Button->setUserString("screen", "");
		m_action6Button->setEnabled(false);
		m_action7Button->setText("");
		m_action7Button->setUserString("screen", "");
		m_action7Button->setEnabled(false);
		m_action8Button->setText("");
		m_action8Button->setUserString("screen", "");
		m_action8Button->setEnabled(false);
	}
	else if( button==m_statisticsRadio ){
		m_action1Button->setText((CEGUI::utf8*)gettext("Results"));
		m_action1Button->setUserString("screen", "Results");
		m_action1Button->setEnabled(true);
		m_action2Button->setText((CEGUI::utf8*)gettext("Ranking"));
		m_action2Button->setUserString("screen", "Ranking");
		m_action2Button->setEnabled(true);
		m_action3Button->setText((CEGUI::utf8*)gettext("Scorers"));
		m_action3Button->setUserString("screen", "Ranking");
		m_action3Button->setEnabled(true);
		m_action4Button->setText("");
		m_action4Button->setUserString("screen", "");
		m_action4Button->setEnabled(false);
		m_action5Button->setText("");
		m_action5Button->setUserString("screen", "");
		m_action5Button->setEnabled(false);
		m_action6Button->setText("");
		m_action6Button->setUserString("screen", "");
		m_action6Button->setEnabled(false);
		m_action7Button->setText("");
		m_action7Button->setUserString("screen", "");
		m_action7Button->setEnabled(false);
		m_action8Button->setText("");
		m_action8Button->setUserString("screen", "");
		m_action8Button->setEnabled(false);
	}
	else{
		m_action1Button->setText("");
		m_action1Button->setUserString("screen", "");
		m_action1Button->setEnabled(false);
		m_action2Button->setText("");
		m_action2Button->setUserString("screen", "");
		m_action2Button->setEnabled(false);
		m_action3Button->setText("");
		m_action3Button->setUserString("screen", "");
		m_action3Button->setEnabled(false);
		m_action4Button->setText("");
		m_action4Button->setUserString("screen", "");
		m_action4Button->setEnabled(false);
		m_action5Button->setText("");
		m_action5Button->setUserString("screen", "");
		m_action5Button->setEnabled(false);
		m_action6Button->setText("");
		m_action6Button->setUserString("screen", "");
		m_action6Button->setEnabled(false);
		m_action7Button->setText("");
		m_action7Button->setUserString("screen", "");
		m_action7Button->setEnabled(false);
		m_action8Button->setText("");
		m_action8Button->setUserString("screen", "");
		m_action8Button->setEnabled(false);
	}

	return true;
}

bool CGNSWindowHandler::exitButtonClicked(const CEGUI::EventArgs &e)
{
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game and return to MS Windows?"), CEGUI::Event::Subscriber(&CGNSWindowHandler::exitConfirmed, this));
	#elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
		CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game and return to GNU/Linux?"), CEGUI::Event::Subscriber(&CGNSWindowHandler::exitConfirmed, this));
	#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game and return to Mac OS?"), CEGUI::Event::Subscriber(&CGNSWindowHandler::exitConfirmed, this));
	#else
		CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game and return to the Operating System?"), CEGUI::Event::Subscriber(&CGNSWindowHandler::exitConfirmed, this));
	#endif
	return true;
}

bool CGNSWindowHandler::exitConfirmed(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->exit();
	return true;
}

bool CGNSWindowHandler::homeButtonClicked(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->getWindowManager()->nextScreen("Game");
	return true;
}

bool CGNSWindowHandler::mainMenuButtonClicked(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->getWindowManager()->confirm(gettext("Are you sure you want to exit this game?"), CEGUI::Event::Subscriber(&CGNSWindowHandler::mainMenuConfirmed, this));
	return true;
}

bool CGNSWindowHandler::mainMenuConfirmed(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->unloadCurrentGame();
	return true;
}

bool CGNSWindowHandler::playButtonClicked(const CEGUI::EventArgs &e)
{
	if( m_game.getCurrentMatch()==NULL ){
		m_game.setGameState(CSinglePlayerGame::SimulatingUntilTheNextEvent);
		CGameEngine::getInstance()->getTimeManager()->start();
	}
	else{
		if( m_game.getOptionManager()->getMatchResultMode() ){
			m_game.simulateMatch(*m_game.getCurrentMatch());
			m_game.setGameState(CSinglePlayerGame::PlayingMatch);
			CGameEngine::getInstance()->getTimeManager()->start();
		}else{
			CGameEngine::getInstance()->getWindowManager()->nextScreen("Simulator");
		}
	}
	return true;
}

bool CGNSWindowHandler::resultModeCheckStateChanged(const CEGUI::EventArgs& e)
{
	m_game.getOptionManager()->setMatchResultMode(m_resultModeCheck->isSelected());
	return true;
}

bool CGNSWindowHandler::quickSaveButtonClicked(const CEGUI::EventArgs &e)
{
    try {
        CGameEngine::getInstance()->save();
        CGameEngine::getInstance()->getWindowManager()->alert(gettext("The game has been saved"));
    } catch(...) {
        CGameEngine::getInstance()->getWindowManager()->alert(gettext("ATTENTION: Game can not be saved"));
    }
	return true;
}
