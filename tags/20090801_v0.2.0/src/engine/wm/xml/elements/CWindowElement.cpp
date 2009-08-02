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

#include "CWindowElement.h"

CWindowElement::CWindowElement()
: m_hook(), m_path(), m_windows()
{}

CWindowElement::CWindowElement(const std::string &hook, const std::string &path)
: m_hook(hook), m_path(path), m_windows()
{}

CWindowElement::CWindowElement(const CWindowElement &window)
: m_hook(window.m_hook), m_path(window.m_path), m_windows(window.m_windows)
{}

CWindowElement::~CWindowElement()
{}

const std::string& CWindowElement::getHook() const
{
	return m_hook;
}

const std::string& CWindowElement::getPath() const
{
	return m_path;
}

void CWindowElement::setHook(const std::string &hook)
{
	m_hook = hook;
}

void CWindowElement::setPath(const std::string &path)
{
	m_path = path;
}

void CWindowElement::addWindow(const CWindowElement& window)
{
	m_windows.push_back(window);
}

const std::vector<CWindowElement>& CWindowElement::getWindows() const
{
	return m_windows;
}

CWindowElement& CWindowElement::operator =(const CWindowElement &window)
{
	m_hook		= window.m_hook;
	m_path		= window.m_path;
	m_windows	= window.m_windows;

	return *this;
}
