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

#ifndef CSCREENXMLELEMENT_H_
#define CSCREENXMLELEMENT_H_

#include <string>
#include "CWindowElement.h"

class CScreenElement {
public:
	CScreenElement();
	CScreenElement(const std::string &id, const CWindowElement &window);
	CScreenElement(const CScreenElement &screen);
	virtual ~CScreenElement();

	const std::string& getId() const;
	const CWindowElement& getWindow() const;
	void setId(const std::string &id);
	void setWindow(const CWindowElement &window);

	CScreenElement& operator=(const CScreenElement &screen);

private:
	CWindowElement		m_window;
	std::string			m_id;
};

#endif /* CSCREENXMLELEMENT_H_ */
