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


#ifndef CLOG_H_
#define CLOG_H_

#include <stdio.h>

#ifdef NDEBUG

#define LOG_DEBUG(format, ...)
#define LOG_INFO(format, ...)		CLog::getInstance()->log("[INFO]\t"    format, ## __VA_ARGS__);
#define LOG_WARNING(format, ...)	CLog::getInstance()->log("[WARNING]\t" format, ## __VA_ARGS__);
#define LOG_ERROR(format, ...)		CLog::getInstance()->log("[ERROR]\t"   format, ## __VA_ARGS__);
#define LOG_FATAL(format, ...)		CLog::getInstance()->log("[FATAL]\t"   format, ## __VA_ARGS__);

#else /* Not NDEBUG */

#define _LOG_QUOTE_AUX_(x) #x
#define _LOG_QUOTE_(x) _LOG_QUOTE_AUX_(x)
#define __LOG_INFO_FORMAT__ "%-80s"
#define __LOG_INFO__ "[" __FILE__ ":" _LOG_QUOTE_(__LINE__) "]: "

#define LOG_DEBUG(format, ...)		CLog::getInstance()->log("[DEBUG]\t"   __LOG_INFO_FORMAT__ format, __LOG_INFO__, ## __VA_ARGS__);
#define LOG_INFO(format, ...)		CLog::getInstance()->log("[INFO]\t"    __LOG_INFO_FORMAT__ format, __LOG_INFO__, ## __VA_ARGS__);
#define LOG_WARNING(format, ...)	CLog::getInstance()->log("[WARNING]\t" __LOG_INFO_FORMAT__ format, __LOG_INFO__, ## __VA_ARGS__);
#define LOG_ERROR(format, ...)		CLog::getInstance()->log("[ERROR]\t"   __LOG_INFO_FORMAT__ format, __LOG_INFO__, ## __VA_ARGS__);
#define LOG_FATAL(format, ...)		CLog::getInstance()->log("[FATAL]\t"   __LOG_INFO_FORMAT__ format, __LOG_INFO__, ## __VA_ARGS__);

#endif // NDEBUG


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
     * Print a log message into the log
     *
     * @param format Format of debug message to write into the log
     * @param ... all others parameters
     */
    void log( const char *format, ... );


private:

	/**
	 * Default constructor
	 */
	CLog();


private:

    FILE    *m_log;

};

#endif // CLOG_H_
