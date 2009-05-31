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

#ifndef CSCREENSCONFIG_XMLHANDLER_H_
#define CSCREENSCONFIG_XMLHANDLER_H_

#include <vector>

#include <CEGUI/CEGUIString.h>
#include <CEGUI/CEGUIXMLAttributes.h>
#include <CEGUI/CEGUIXMLHandler.h>

#include "elements/CScreensConfigElement.h"
#include "elements/CScreenElement.h"
#include "elements/CWindowElement.h"

class CScreensConfig_xmlHandler : public CEGUI::XMLHandler
{
public:
	CScreensConfig_xmlHandler();
	virtual ~CScreensConfig_xmlHandler();

	virtual void elementStart(const CEGUI::String& element, const CEGUI::XMLAttributes& attributes);
	virtual void elementEnd(const CEGUI::String& element);

	const CScreensConfigElement& getScreensConfig() const;
private:
	CScreensConfigElement		m_screensConfig;
	CScreenElement				m_currentScreen;
	std::vector<CWindowElement>	m_windowStack;
};

#endif /* CSCREENSCONFIG_XMLHANDLER_H_ */
