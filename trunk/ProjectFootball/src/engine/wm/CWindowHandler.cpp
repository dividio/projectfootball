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

#include "CWindowHandler.h"

#include "../CGameEngine.h"
#include "../../utils/CLog.h"

CWindowHandler::CWindowHandler(const std::string &path)
: m_path(path), m_eventConnections()
{
	registerWindowHandler();
}

CWindowHandler::~CWindowHandler()
{
	disconnectEventConnections();
	unregisterWindowHandler();
}

void CWindowHandler::enter()
{
	// Nothing to do
}

void CWindowHandler::init()
{
	// Nothing to do
}

void CWindowHandler::leave()
{
    // Nothing to do
}

void CWindowHandler::update()
{
    // Nothing to do
}

void CWindowHandler::registerEventConnection(CEGUI::Event::Connection connection)
{
	m_eventConnections.push_back(connection);
}

void CWindowHandler::disconnectEventConnections()
{
	std::vector<CEGUI::Event::Connection>::iterator itEventConnections;
	for( itEventConnections=m_eventConnections.begin(); itEventConnections!=m_eventConnections.end(); itEventConnections++ ){
		(*itEventConnections)->disconnect();
	}
	LOG_DEBUG("#%d CEGUI::Event::Connection disconnected from '%s'", m_eventConnections.size(), m_path.c_str());
	m_eventConnections.clear();
}

void CWindowHandler::registerWindowHandler()
{
	CGameEngine::getInstance()->getWindowManager()->registerWindowHandler(m_path, *this);
}

void CWindowHandler::unregisterWindowHandler()
{
	CGameEngine::getInstance()->getWindowManager()->unregisterWindowHandler(m_path, *this);
}
