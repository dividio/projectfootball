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

#ifndef CDATE_H_
#define CDATE_H_

#include <time.h>
#include <string>

class CDate
{
public:
    CDate();
    CDate(const CDate &date);
    CDate(int day, int month, int year);
    CDate(int day, int month, int year, int hour, int minutes, int seconds);
	CDate(const std::string &str, const std::string &format);
	virtual ~CDate();

	void parse( const std::string &str, const std::string &format);
	std::string format(const std::string &format);

	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMin();
	int getSec();

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setHour(int hour);
    void setMin(int minutes);
    void setSec(int seconds);

	CDate& operator +(int nDays);
	CDate& operator ++();

	CDate& operator -(int nDays);
	CDate& operator --();

	CDate& operator =(const CDate &date);

	bool operator ==(const CDate &date);
	bool operator !=(const CDate &date);
	bool operator <(const CDate &date);
	bool operator <=(const CDate &date);
    bool operator >(const CDate &date);
    bool operator >=(const CDate &date);

private:
    struct tm m_tm;
};

#endif /*CDATE_H_*/
