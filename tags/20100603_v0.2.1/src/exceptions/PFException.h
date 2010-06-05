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

#ifndef PFEXCEPTION_H_
#define PFEXCEPTION_H_

#include <exception>
#include <string>

#define _EXCEPTION_QUOTE_AUX_(x) #x
#define _EXCEPTION_QUOTE_(x) _EXCEPTION_QUOTE_AUX_(x)

#define PFEXCEPTION(format, ...) PFException("[" __FILE__ ":" _EXCEPTION_QUOTE_(__LINE__) "]\t" format, ## __VA_ARGS__)

class PFException : public std::exception {
public:
	PFException(const char *format, ...);
	virtual ~PFException() throw ();

	virtual const char * what() const throw();

private:
	std::string m_cause;
};

#endif /* PFEXCEPTION_H_ */
