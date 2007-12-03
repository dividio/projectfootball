/******************************************************************************
* Copyright (C) 2007 - Ikaro Games   www.ikarogames.com                       *
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


#ifndef __CLOG_H__
#define __CLOG_H__

#include <stdarg.h>
#include <stdio.h>

class CLog
{
public:
	/**
	 * Destructor
	 */
	~CLog();


	/**
	 * Return the unique instance of the log
	 * @return The unique instance of the log
	 */
	static CLog* getInstance();


    /**
     * Print a debug message into the log
     *
     * @param format Format of debug message to write into the log
     * @param ... all others parameters
     */
    void debug( const char *format, ... );


    /**
     * Print a info message into the log
     *
     * @param format Format of info message to write into the log
     * @param ... all others parameters
     */
    void info( const char *format, ... );


    /**
     * Print a warning message into the log
     *
     * @param format Format of warning message to write into the log
     * @param ... all others parameters
     */
    void warning( const char *format, ... );


    /**
     * Print a error message into the log
     *
     * @param format Format of error message to write into the log
     * @param ... all others parameters
     */
    void error( const char *format, ... );


    /**
     * Print a error message into the log and trow a exception
     *
     * @param format Format of error message to write into the log
     * @param ... all others parameters
     */
    void exception( const char *format, ... );


private:

	/**
	 * Default constructor
	 */
	CLog();


    /**
     * Print into the log the message indicated if the condition is true
     *
     * @param label Label of the log message
     * @param format Format of the message to write into the log
     * @param parameters all others parameters
     */
    void printLog( const char *label, const char *format, va_list parameters );


private:

    FILE    *m_log;
};

#endif // __CLOG_H__
