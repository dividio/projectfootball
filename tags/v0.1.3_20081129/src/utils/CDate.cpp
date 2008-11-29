/******************************************************************************
* Copyright (C) 2008 - Ikaro Games   www.ikarogames.com                       *
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

#include "CDate.h"

#include <string.h>

CDate::CDate()
{
    memset(&m_tm, 0, sizeof(m_tm));
    time_t now = time(NULL);
    memcpy(&m_tm, localtime(&now), sizeof(m_tm));
}

CDate::CDate(const CDate &date)
{
    m_tm = date.m_tm;
}

CDate::CDate(int day, int month, int year)
{
    memset(&m_tm, 0, sizeof(m_tm));
    m_tm.tm_mday    = day;
    m_tm.tm_mon     = month-1; // January=0, February=1, ...
    m_tm.tm_year    = year-1900; // Years since 1900
    mktime(&m_tm);
}

CDate::CDate(int day, int month, int year, int hour, int minutes, int seconds)
{
    memset(&m_tm, 0, sizeof(m_tm));
    m_tm.tm_mday    = day;
    m_tm.tm_mon     = month-1; // January=0, February=1, ...
    m_tm.tm_year    = year-1900; // Years since 1900
    m_tm.tm_hour    = hour;
    m_tm.tm_min     = minutes;
    m_tm.tm_sec     = seconds;
    mktime(&m_tm);
}

CDate::CDate(const std::string &timestamp)
{
    // Timestamp i.e.: 2008-12-31 23:59:59
    memset(&m_tm, 0, sizeof(m_tm));
    if( timestamp!="" ){
        const char *date = timestamp.c_str();

        int     i       = 0;
        char    c;

        int     year    = 0;
        int     month   = 0;
        int     day     = 0;
        int     hour    = 0;
        int     minutes = 0;
        int     seconds = 0;

        // Match year
        for( i=0; i<4; i++ ){
            c = *date;
            if( c<'0' || c>'9' ){ return; }

            year *= 10;
            year += c-'0';
            date++;
        }
        // Match literal '-'
        if( *date!='-' ){ return; }
        date++;
        // Match month
        for( i=0; i<2; i++ ){
            c = *date;
            if( c<'0' || c>'9' ){ return; }

            month *= 10;
            month += c-'0';
            date++;
        }
        // Match literal '-'
        if( *date!='-' ){ return; }
        date++;
        // Match day of the month
        for( i=0; i<2; i++ ){
            c = *date;
            if( c<'0' || c>'9' ){ return; }

            day *= 10;
            day += c-'0';
            date++;
        }
        // Match literal ' ' (space)
        if( *date!=' ' ){ return; }
        date++;
        // Match hour (24H format)
        for( i=0; i<2; i++ ){
            c = *date;
            if( c<'0' || c>'9' ){ return; }

            hour *= 10;
            hour += c-'0';
            date++;
        }
        // Match literal ':'
        if( *date!=':' ){ return; }
        date++;
        // Match minutes
        for( i=0; i<2; i++ ){
            c = *date;
            if( c<'0' || c>'9' ){ return; }

            minutes *= 10;
            minutes += c-'0';
            date++;
        }
        // Match literal ':'
        if( *date!=':' ){ return; }
        date++;
        // Match seconds
        for( i=0; i<2; i++ ){
            c = *date;
            if( c<'0' || c>'9' ){ return; }

            seconds *= 10;
            seconds += c-'0';
            date++;
        }

        m_tm.tm_mday    = day;
        m_tm.tm_mon     = month-1; // January=0, February=1, ...
        m_tm.tm_year    = year-1900; // Years since 1900
        m_tm.tm_hour    = hour;
        m_tm.tm_min     = minutes;
        m_tm.tm_sec     = seconds;
        mktime(&m_tm);
    }
}

CDate::~CDate()
{
}

std::string CDate::format(const std::string &format) const
{
    if( !isValid() || format=="" ){
        return "";
    }

    char buffer[255];
    strftime(buffer, sizeof(buffer), format.c_str(), &m_tm);
    return buffer;
}

std::string CDate::getTimestamp() const
{
    return format("%Y-%m-%d %H:%M:%S");
}

bool CDate::isValid() const
{
    return  m_tm.tm_mday>=1 && m_tm.tm_mday<=31
            && m_tm.tm_mon>=0 && m_tm.tm_mon<=11
            && m_tm.tm_year>=0
            && m_tm.tm_hour>=0 && m_tm.tm_hour<=23
            && m_tm.tm_min>=0 && m_tm.tm_min<=59
            && m_tm.tm_sec>=0 && m_tm.tm_sec<=59;
}

int CDate::getYear() const
{
    return m_tm.tm_year+1900;
}

int CDate::getMonth() const
{
    return m_tm.tm_mon+1;
}

int CDate::getDay() const
{
    return m_tm.tm_mday;
}

int CDate::getHour() const
{
    return m_tm.tm_hour;
}

int CDate::getMin() const
{
    return m_tm.tm_min;
}

int CDate::getSec() const
{
    return m_tm.tm_sec;
}

void CDate::setYear(int year)
{
    m_tm.tm_year = year-1900; // Years since 1900
    mktime(&m_tm);
}

void CDate::setMonth(int month)
{
    m_tm.tm_mon = month-1; // January=0, February=1, ...
    mktime(&m_tm);
}

void CDate::setDay(int day)
{
    m_tm.tm_mday = day;
    mktime(&m_tm);
}

void CDate::setHour(int hour)
{
    m_tm.tm_hour = hour;
    mktime(&m_tm);
}

void CDate::setMin(int minutes)
{
    m_tm.tm_min = minutes;
    mktime(&m_tm);
}

void CDate::setSec(int seconds)
{
    m_tm.tm_sec = seconds;
    mktime(&m_tm);
}

CDate& CDate::operator +=(int nDays)
{
    m_tm.tm_mday += nDays;
    mktime(&m_tm);

    return *this;
}

CDate& CDate::operator ++()
{
    m_tm.tm_mday++;
    mktime(&m_tm);

    return *this;
}

CDate& CDate::operator -=(int nDays)
{
    m_tm.tm_mday -= nDays;
    mktime(&m_tm);

    return *this;
}

CDate& CDate::operator --()
{
    m_tm.tm_mday--;
    mktime(&m_tm);

    return *this;
}

CDate& CDate::operator =(const CDate &date)
{
    m_tm = date.m_tm;
}

bool CDate::operator ==(const CDate &date) const
{
    return  this->m_tm.tm_mday==date.m_tm.tm_mday
            && this->m_tm.tm_mon==date.m_tm.tm_mon
            && this->m_tm.tm_year==date.m_tm.tm_year
            && this->m_tm.tm_hour==date.m_tm.tm_hour
            && this->m_tm.tm_min==date.m_tm.tm_min
            && this->m_tm.tm_sec==date.m_tm.tm_sec;
}

bool CDate::operator !=(const CDate &date) const
{
    return !this->operator ==(date);
}

bool CDate::operator <(const CDate &date) const
{
    return  this->m_tm.tm_year<date.m_tm.tm_year
            || (this->m_tm.tm_year==date.m_tm.tm_year && this->m_tm.tm_mon<date.m_tm.tm_mon)
            || (this->m_tm.tm_year==date.m_tm.tm_year && this->m_tm.tm_mon==date.m_tm.tm_mon && this->m_tm.tm_mday<date.m_tm.tm_mday)
            || (this->m_tm.tm_year==date.m_tm.tm_year && this->m_tm.tm_mon==date.m_tm.tm_mon && this->m_tm.tm_mday==date.m_tm.tm_mday && this->m_tm.tm_hour<date.m_tm.tm_hour)
            || (this->m_tm.tm_year==date.m_tm.tm_year && this->m_tm.tm_mon==date.m_tm.tm_mon && this->m_tm.tm_mday==date.m_tm.tm_mday && this->m_tm.tm_hour==date.m_tm.tm_hour && this->m_tm.tm_min<date.m_tm.tm_min)
            || (this->m_tm.tm_year==date.m_tm.tm_year && this->m_tm.tm_mon==date.m_tm.tm_mon && this->m_tm.tm_mday==date.m_tm.tm_mday && this->m_tm.tm_hour==date.m_tm.tm_hour && this->m_tm.tm_min==date.m_tm.tm_min && this->m_tm.tm_sec<date.m_tm.tm_sec);
}

bool CDate::operator <=(const CDate &date) const
{
    return this->operator <(date) || this->operator ==(date);
}

bool CDate::operator >(const CDate &date) const
{
    return !this->operator <(date) && !this->operator ==(date);
}

bool CDate::operator >=(const CDate &date) const
{
    return !this->operator <(date);
}
