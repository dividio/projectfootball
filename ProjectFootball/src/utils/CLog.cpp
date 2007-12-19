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

#include <exception>
#include "CLog.h"


CLog::CLog()
{

    m_log = fopen( "ProjectFootball.log", "w" );
    if( m_log==NULL ){
    	m_log = stdout;
        error( "Error at open the log file. Redirecting to stdout." );
    }
    info( "Log initialized" );
}


CLog::~CLog()
{
    info( "Log deinitialized" );
    if( m_log!=stdout ){
        fclose( m_log );
    }
}


CLog* CLog::getInstance()
{
	static CLog instance;
	return &instance;
}


void CLog::debug( const char *format, ... )
{
    va_list listArguments;
    va_start( listArguments, format );

    printLog( "[DEBUG]", format, listArguments );

    va_end( listArguments );
}


void CLog::info( const char *format, ... )
{
    va_list listArguments;
    va_start( listArguments, format );

    printLog( "[INFO]", format, listArguments );

    va_end( listArguments );
}


void CLog::warning( const char *format, ... )
{
    va_list listArguments;
    va_start( listArguments, format );

    printLog( "[WARNING]", format, listArguments );

    va_end( listArguments );
}


void CLog::error( const char *format, ... )
{
    va_list listArguments;
    va_start( listArguments, format );

    printLog( "[ERROR]", format, listArguments );

    va_end( listArguments );
}


void CLog::exception( const char *format, ... )
{
    va_list listArguments;
    va_start( listArguments, format );

    printLog( "[EXCEPTION]", format, listArguments );

    va_end( listArguments );

    throw std::exception();
}


void CLog::printLog( const char *label, const char *format, va_list listArguments )
{
    fprintf( m_log, "%s\t", label );
    vfprintf( m_log, format, listArguments );
    fprintf( m_log, "\n" );

    fflush(m_log);
}
