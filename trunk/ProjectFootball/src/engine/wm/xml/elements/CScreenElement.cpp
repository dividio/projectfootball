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

#include "CScreenElement.h"

CScreenElement::CScreenElement()
: m_window(), m_id()
{}

CScreenElement::CScreenElement(const std::string &id, const CWindowElement &window)
: m_window(window), m_id(id)
{}

CScreenElement::CScreenElement(const CScreenElement &screen)
: m_window(screen.m_window), m_id(screen.m_id)
{}

CScreenElement::~CScreenElement()
{}

const std::string& CScreenElement::getId() const
{
	return m_id;
}

const CWindowElement& CScreenElement::getWindow() const
{
	return m_window;
}

void CScreenElement::setId(const std::string &id)
{
	m_id = id;
}

void CScreenElement::setWindow(const CWindowElement &window)
{
	m_window = window;
}

CScreenElement& CScreenElement::operator =(const CScreenElement &screen)
{
	m_id		= screen.m_id;
	m_window	= screen.m_window;

	return *this;
}
