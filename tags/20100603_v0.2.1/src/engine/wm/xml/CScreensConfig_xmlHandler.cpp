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

#include "CScreensConfig_xmlHandler.h"

#include "../../../utils/CLog.h"

CScreensConfig_xmlHandler::CScreensConfig_xmlHandler()
: m_screensConfig(), m_currentScreen(), m_windowStack()
{}

CScreensConfig_xmlHandler::~CScreensConfig_xmlHandler()
{}

void CScreensConfig_xmlHandler::elementStart(const CEGUI::String& element, const CEGUI::XMLAttributes& attributes)
{
	if( element=="screens-config" ){
		m_screensConfig = CScreensConfigElement();
	}
	else if( element=="screen" ){
		m_currentScreen = CScreenElement();
		m_currentScreen.setId(attributes.getValue("id").c_str());
	}
	else if( element=="window"){
		CWindowElement window = CWindowElement();
		window.setHook(attributes.getValue("hook").c_str());
		window.setPath(attributes.getValue("path").c_str());
		m_windowStack.push_back(window);
	}
	else{
		LOG_WARNING("Unknown element: %s", element.c_str());
	}
}

void CScreensConfig_xmlHandler::elementEnd(const CEGUI::String& element)
{
	if( element=="screens-config" ){
		// nothing to do
	}
	else if( element=="screen" ){
		m_screensConfig.addScreen(m_currentScreen);
	}
	else if( element=="window" ){
		CWindowElement window = m_windowStack.back();
		m_windowStack.pop_back();
		if( m_windowStack.empty() ){
			m_currentScreen.setWindow(window);
		}
		else{
			m_windowStack.back().addWindow(window);
		}
	}
	else{
		LOG_WARNING("Unknown element: %s", element.c_str());
	}
}

const CScreensConfigElement& CScreensConfig_xmlHandler::getScreensConfig() const
{
	return m_screensConfig;
}
