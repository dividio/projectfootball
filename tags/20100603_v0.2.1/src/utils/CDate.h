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
    CDate(const std::string &timestamp);
    virtual ~CDate();

    std::string format(const std::string &format) const;
    std::string getTimestamp() const;

    bool isValid() const;
    bool isLeap() const;
    static bool isLeap(int year);

    int getYear()  const;
    int getMonth() const;
    int getDay()   const;
    int getHour()  const;
    int getMin()   const;
    int getSec()   const;

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setHour(int hour);
    void setMin(int minutes);
    void setSec(int seconds);

    CDate& operator =(const CDate &date);

    bool operator ==(const CDate &date) const;
    bool operator !=(const CDate &date) const;
    bool operator <(const CDate &date)  const;
    bool operator <=(const CDate &date) const;
    bool operator >(const CDate &date)  const;
    bool operator >=(const CDate &date) const;

public:
	static const CDate MIN_DATE;
	static const CDate MAX_DATE;

private:
    struct tm m_tm;
};

#endif /*CDATE_H_*/
