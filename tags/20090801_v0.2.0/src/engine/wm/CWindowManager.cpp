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

#include "CWindowManager.h"

#include <algorithm>
#include <vector>

#include <libintl.h>

//#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/CEGUIXMLParser.h>

#include "xml/CScreensConfig_xmlHandler.h"
#include "xml/elements/CScreenElement.h"
#include "xml/elements/CWindowElement.h"

#include "../../utils/gui/CImageListboxItem.h"
#include "gui/renderer/CPFStatic.h"
#include "gui/renderer/CPFStaticText.h"
#include "gui/renderer/CPFRotatingText.h"

#include "../../exceptions/PFException.h"
#include "../../utils/CLog.h"

CWindowManager::CWindowManager()
: m_windows(), m_windowsHandlers(), m_currentScreen(NULL), m_nextScreensStack(), m_previousScreensStack(),
  m_alertWindow(getCEGUIWindow("alert.layout")), m_confirmWindow(getCEGUIWindow("confirm.layout")), m_confirmAceptSubscriber(), m_confirmCancelSubscriber()
{
	CScreensConfig_xmlHandler xmlHandler;

	try{
		CEGUI::System::getSingleton().getXMLParser()->parseXMLFile(xmlHandler, "screens-config.xml", "screens-config.xsd", CEGUI::WindowManager::getSingleton().getDefaultResourceGroup());
		m_screensConfig = xmlHandler.getScreensConfig();
		LOG_INFO("Successfully Completed loading of 'screens-config.xml'");
	}
	catch( ... ){
		throw PFEXCEPTION("Error while parsing file 'screens-config.xml'");
	}

	// Bind events of confirm & alert windows
	CEGUI::WindowManager &windowMngr	= CEGUI::WindowManager::getSingleton();

	CEGUI::PushButton	*alertAceptButton		= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"AlertWindow/AceptButton"));
	CEGUI::PushButton	*confirmAceptButton		= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"ConfirmWindow/AceptButton"));
	CEGUI::PushButton	*confirmCancelButton	= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"ConfirmWindow/CancelButton"));

	alertAceptButton	->setText((CEGUI::utf8*)gettext("Acept"));
	confirmAceptButton	->setText((CEGUI::utf8*)gettext("Acept"));
	confirmCancelButton	->setText((CEGUI::utf8*)gettext("Cancel"));

	alertAceptButton	->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CWindowManager::alertAceptClicked, this));
	confirmAceptButton	->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CWindowManager::confirmAceptClicked, this));
	confirmCancelButton	->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CWindowManager::confirmCancelClicked, this));

	// Add new WindowFactory to CEGUI::WindowFactoryManager
	CEGUI::WindowFactoryManager::getSingleton().addFactory(&(CEGUI::getCImageListboxItemFactory()));

	// Add new WindowRendererFactory to CEGUI::WindowRendererManager
	CEGUI::WindowRendererManager::getSingleton().addFactory(&CEGUI::s_CPFStaticWRFactory);
	CEGUI::WindowRendererManager::getSingleton().addFactory(&CEGUI::s_CPFStaticTextWRFactory);
	CEGUI::WindowRendererManager::getSingleton().addFactory(&CEGUI::s_CPFRotatingTextWRFactory);
}

CWindowManager::~CWindowManager()
{
	if( m_currentScreen!=NULL ){
		leaveEvent(*m_currentScreen);
		m_currentScreen = NULL;
	}

	// Destroy windows
	std::map<std::string, CEGUI::Window*>::iterator itWindows;
	for( itWindows=m_windows.begin(); itWindows!=m_windows.end(); itWindows++ ){
		CEGUI::WindowManager::getSingleton().destroyWindow(itWindows->second);
	}
}

void CWindowManager::clearHistory()
{
	m_commandsList.push_back("cs");
}

void CWindowManager::nextScreen()
{
	m_commandsList.push_back("ns");
}

void CWindowManager::nextScreen(const std::string &screenId)
{
	m_commandsList.push_back("ns"+screenId);
}

void CWindowManager::previousScreen()
{
	m_commandsList.push_back("ps");
}

void CWindowManager::registerWindowHandler(const std::string &path, IWindowHandler &windowHandler)
{
	m_windowsHandlers[path][&windowHandler] = false;
	LOG_INFO("Registered an IWindowHandler for '%s'", path.c_str());
}

void CWindowManager::unregisterWindowHandler(const std::string &path, IWindowHandler &windowHandler)
{
	std::map<std::string, std::map<IWindowHandler*, bool> >::iterator itWindowsHandlersMap = m_windowsHandlers.find(path);
	if( itWindowsHandlersMap!=m_windowsHandlers.end() ){
		std::map<IWindowHandler*, bool> &windowsHandlersMap = itWindowsHandlersMap->second;
		windowsHandlersMap.erase(&windowHandler);
		LOG_INFO("Unregistered an IWindowHandler from '%s'", path.c_str());
	}
}

void CWindowManager::alert(const std::string &text)
{
	CEGUI::Window			*alertText	= static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"AlertWindow/Text"));
	alertText->setText((CEGUI::utf8*)text.c_str());

	CEGUI::Window	*currentWindow = getCEGUIWindow(m_currentScreen->getWindow().getPath().c_str());
	currentWindow->addChildWindow(m_alertWindow);
	m_alertWindow->setModalState(true);
}

void CWindowManager::confirm(const std::string &text, CEGUI::Event::Subscriber aceptSubscriber)
{
	confirm(text, aceptSubscriber, CEGUI::Event::Subscriber());
}

void CWindowManager::confirm(const std::string &text, CEGUI::Event::Subscriber aceptSubscriber, CEGUI::Event::Subscriber cancelSubscriber)
{
	m_confirmAceptSubscriber	= aceptSubscriber;
	m_confirmCancelSubscriber	= cancelSubscriber;

	CEGUI::Window			*confirmText	= static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"ConfirmWindow/Text"));
	confirmText->setText((CEGUI::utf8*)text.c_str());

	CEGUI::Window	*currentWindow = getCEGUIWindow(m_currentScreen->getWindow().getPath().c_str());
	currentWindow->addChildWindow(m_confirmWindow);
	m_confirmWindow->setModalState(true);

}

void CWindowManager::update()
{
	while( !m_commandsList.empty() ){
		std::string command = m_commandsList.front();
		m_commandsList.pop_front();
		if( command=="ps" ){
			_previousScreen();
		}
		else if( command=="ns" ){
			_nextScreen();
		}
		else if( command.substr(0,2)=="ns" ){
			_nextScreen(command.substr(2, std::string::npos));
		}
		else if( command=="cs" ){
			_clearHistory();
		}
		else{
			LOG_WARNING("Unrecognized command: '%s'", command.c_str());
		}
	}

	if( m_currentScreen!=NULL ){
		updateEvent(*m_currentScreen);
	}
}

void CWindowManager::_clearHistory()
{
	m_previousScreensStack.clear();
	m_nextScreensStack.clear();
}

void CWindowManager::_nextScreen()
{
	if( !m_nextScreensStack.empty() ){
		const CScreenElement *nextScreen = getScreen(m_nextScreensStack.back());
		if( nextScreen==NULL ){
			LOG_ERROR("Not screen found with the id '%s'", m_nextScreensStack.back().c_str());
			return;
		}

		if( m_currentScreen!=NULL ){
			leaveEvent(*m_currentScreen);
			m_previousScreensStack.push_back(m_currentScreen->getId());
		}
		enterEvent(*nextScreen);
		m_currentScreen = nextScreen;
		m_nextScreensStack.pop_back();
	}
}

void CWindowManager::_nextScreen(const std::string &screenId)
{
	const CScreenElement *nextScreen = getScreen(screenId);
	if( nextScreen==NULL ){
		LOG_ERROR("Not screen found with the id '%s'", screenId.c_str());
		return;
	}

	if( m_currentScreen!=NULL ){
		leaveEvent(*m_currentScreen);
		m_previousScreensStack.push_back(m_currentScreen->getId());
	}
	enterEvent(*nextScreen);
	m_currentScreen = nextScreen;
	m_nextScreensStack.clear();
}

void CWindowManager::_previousScreen()
{
	if( !m_previousScreensStack.empty() ){
		const CScreenElement *previousScreen = getScreen(m_previousScreensStack.back());
		if( previousScreen==NULL ){
			LOG_ERROR("Not screen found with the id '%s'", m_nextScreensStack.back().c_str());
			return;
		}

		if( m_currentScreen!=NULL ){
			leaveEvent(*m_currentScreen);
			m_nextScreensStack.push_back(m_currentScreen->getId());
		}
		enterEvent(*previousScreen);
		m_currentScreen = previousScreen;
		m_previousScreensStack.pop_back();
	}
}

void CWindowManager::enterEvent(const CScreenElement &screen)
{
	hookWindow(screen.getWindow());
	CEGUI::System::getSingleton().setGUISheet(getCEGUIWindow(screen.getWindow().getPath().c_str()));
//	Ogre::Root::getSingleton().getSceneManager("Default SceneManager")->clearScene();
	enterEvent(screen.getWindow());
}

void CWindowManager::leaveEvent(const CScreenElement &screen)
{
	unHookWindow(screen.getWindow());
	leaveEvent(screen.getWindow());
}

void CWindowManager::updateEvent(const CScreenElement &screen)
{
	updateEvent(screen.getWindow());
}

void CWindowManager::enterEvent(const CWindowElement &window)
{
	std::map<std::string, std::map<IWindowHandler*, bool> >::iterator itWindowsHandlersMap = m_windowsHandlers.find(window.getPath());
	if( itWindowsHandlersMap!=m_windowsHandlers.end() ){
		std::map<IWindowHandler*, bool> &windowsHandlersMap = itWindowsHandlersMap->second;
		std::map<IWindowHandler*, bool>::iterator itWindowsHandlers;
		for( itWindowsHandlers=windowsHandlersMap.begin(); itWindowsHandlers!=windowsHandlersMap.end(); itWindowsHandlers++ ){
			itWindowsHandlers->first->enter();
		}
	}

	if( !window.getWindows().empty() ){
		std::vector<CWindowElement>::const_iterator itWindows;
		for( itWindows=window.getWindows().begin(); itWindows!=window.getWindows().end(); itWindows++ ){
			enterEvent(*itWindows);
		}
	}
}

void CWindowManager::leaveEvent(const CWindowElement &window)
{
	std::map<std::string, std::map<IWindowHandler*, bool> >::iterator itWindowsHandlersMap = m_windowsHandlers.find(window.getPath());
	if( itWindowsHandlersMap!=m_windowsHandlers.end() ){
		std::map<IWindowHandler*, bool> &windowsHandlersMap = itWindowsHandlersMap->second;
		std::map<IWindowHandler*, bool>::iterator itWindowsHandlers;
		for( itWindowsHandlers=windowsHandlersMap.begin(); itWindowsHandlers!=windowsHandlersMap.end(); itWindowsHandlers++ ){
			itWindowsHandlers->first->leave();
		}
	}

	if( !window.getWindows().empty() ){
		std::vector<CWindowElement>::const_iterator itWindows;
		for( itWindows=window.getWindows().begin(); itWindows!=window.getWindows().end(); itWindows++ ){
			leaveEvent(*itWindows);
		}
	}
}

void CWindowManager::updateEvent(const CWindowElement &window)
{
	std::map<std::string, std::map<IWindowHandler*, bool> >::iterator itWindowsHandlersMap = m_windowsHandlers.find(window.getPath());
	if( itWindowsHandlersMap!=m_windowsHandlers.end() ){
		std::map<IWindowHandler*, bool> &windowsHandlersMap = itWindowsHandlersMap->second;
		std::map<IWindowHandler*, bool>::iterator itWindowsHandlers;
		for( itWindowsHandlers=windowsHandlersMap.begin(); itWindowsHandlers!=windowsHandlersMap.end(); itWindowsHandlers++ ){
			itWindowsHandlers->first->update();
		}
	}

	if( !window.getWindows().empty() ){
		std::vector<CWindowElement>::const_iterator itWindows;
		for( itWindows=window.getWindows().begin(); itWindows!=window.getWindows().end(); itWindows++ ){
			updateEvent(*itWindows);
		}
	}
}

void CWindowManager::hookWindow(const CWindowElement &window)
{
	if( window.getWindows().empty() ){
		return;
	}
	else{
		CEGUI::Window *ceguiWindow = getCEGUIWindow(window.getPath().c_str());

		std::vector<CWindowElement>::const_iterator itWindows;
		for( itWindows=window.getWindows().begin(); itWindows!= window.getWindows().end(); itWindows++ ){
			const CWindowElement &childWindow = *itWindows;

			CEGUI::Window *hookNode = ceguiWindow->getChildRecursive((CEGUI::utf8*)childWindow.getHook().c_str());
			if( hookNode==NULL ){
				LOG_ERROR("Not found hook '%s' in the window '%s'", childWindow.getHook().c_str(), window.getPath().c_str());
			}
			else{
				hookNode->addChildWindow(getCEGUIWindow(childWindow.getPath()));
			}

			hookWindow(childWindow);
		}
	}
}

void CWindowManager::unHookWindow(const CWindowElement &window)
{
	if( window.getWindows().empty() ){
		return;
	}
	else{
		CEGUI::Window *ceguiWindow = getCEGUIWindow(window.getPath().c_str());

		std::vector<CWindowElement>::const_iterator itWindows;
		for( itWindows=window.getWindows().begin(); itWindows!= window.getWindows().end(); itWindows++ ){
			const CWindowElement &childWindow = *itWindows;
			unHookWindow(childWindow);

			CEGUI::Window *hookNode = ceguiWindow->getChildRecursive((CEGUI::utf8*)childWindow.getHook().c_str());
			if( hookNode==NULL ){
				LOG_ERROR("Not found hook '%s' in the window '%s'", childWindow.getHook().c_str(), window.getPath().c_str());
			}
			else{
				while( hookNode->getChildCount()>0 ){
					hookNode->removeChildWindow(hookNode->getChildAtIdx(0));
				}
			}
		}
	}
}

const CScreenElement* CWindowManager::getScreen(const std::string &screenId)
{
	std::vector<CScreenElement>::const_iterator itScreens;
	for( itScreens=m_screensConfig.getScreens().begin(); itScreens!=m_screensConfig.getScreens().end(); itScreens++ ){
		const CScreenElement &screen = *itScreens;
		if( screen.getId()==screenId ){
			return &screen;
		}
	}

	return NULL;
}

CEGUI::Window* CWindowManager::getCEGUIWindow(const std::string &path)
{
	CEGUI::Window *window = NULL;
	std::map<std::string, CEGUI::Window*>::iterator itWindows = m_windows.find(path);
	if( itWindows==m_windows.end() ){
		LOG_INFO("Loading ... '%s'", path.c_str());

		window = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)path.c_str());
		m_windows[path] = window;
	}
	else{
		window = itWindows->second;
	}

	// Init the window handler
	std::map<std::string, std::map<IWindowHandler*, bool> >::iterator itWindowsHandlersMap = m_windowsHandlers.find(path);
	if( itWindowsHandlersMap!=m_windowsHandlers.end() ){
		std::map<IWindowHandler*, bool> &windowsHandlersMap = itWindowsHandlersMap->second;
		std::map<IWindowHandler*, bool>::iterator itWindowsHandlers;
		for( itWindowsHandlers=windowsHandlersMap.begin(); itWindowsHandlers!=windowsHandlersMap.end(); itWindowsHandlers++ ){
			if( !itWindowsHandlers->second ){
				itWindowsHandlers->first->init();
				itWindowsHandlers->second = true;
			}
		}
	}

	return window;
}

bool CWindowManager::alertAceptClicked(const CEGUI::EventArgs& e)
{
	CEGUI::Window	*currentWindow = getCEGUIWindow(m_currentScreen->getWindow().getPath().c_str());
	currentWindow->removeChildWindow(m_alertWindow);
	m_alertWindow->setModalState(false);

	return true;
}

bool CWindowManager::confirmAceptClicked(const CEGUI::EventArgs& e)
{
	CEGUI::Window	*currentWindow = getCEGUIWindow(m_currentScreen->getWindow().getPath().c_str());
	currentWindow->removeChildWindow(m_confirmWindow);
	m_confirmWindow->setModalState(false);

	if( m_confirmAceptSubscriber.connected() ){
		m_confirmAceptSubscriber(e);
	}

	return true;
}

bool CWindowManager::confirmCancelClicked(const CEGUI::EventArgs& e)
{
	CEGUI::Window	*currentWindow = getCEGUIWindow(m_currentScreen->getWindow().getPath().c_str());
	currentWindow->removeChildWindow(m_confirmWindow);
	m_confirmWindow->setModalState(false);

	if( m_confirmCancelSubscriber.connected() ){
		m_confirmCancelSubscriber(e);
	}

	return true;
}
