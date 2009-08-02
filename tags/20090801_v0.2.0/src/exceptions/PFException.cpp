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

#include "PFException.h"

#include <stdarg.h>

#define BUFFER_SIZE	512

PFException::PFException(const char *format, ...)
: std::exception(), m_cause()
{
	char buffer[BUFFER_SIZE];
    va_list listArguments;
    va_start( listArguments, format );
    vsnprintf(buffer, BUFFER_SIZE, format, listArguments );
    va_end( listArguments );

    m_cause = buffer;
}

PFException::~PFException() throw ()
{
}

const char * PFException::what() const throw ()
{
	return m_cause.c_str();
}
