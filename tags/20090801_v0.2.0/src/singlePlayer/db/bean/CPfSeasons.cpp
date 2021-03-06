/******************************************************************************
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
*       generated by dia/DAOcodegen.py                                        *
*       Version: 1.21                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "CPfSeasons.h"

CPfSeasons::CPfSeasons()
{
    m_XSeason = "0";
    m_NYear = "0";
    m_SSeason = "";
}

CPfSeasons::CPfSeasons(const CPfSeasons &obj)
{
    m_XSeason = obj.m_XSeason;
    m_NYear = obj.m_NYear;
    m_SSeason = obj.m_SSeason;
}

CPfSeasons::~CPfSeasons()
{
}

int CPfSeasons::getXSeason() const
{
    if( m_XSeason=="" ){
        return 0;
    }else{
        return atoi(m_XSeason.c_str());
    }
}

const std::string& CPfSeasons::getXSeason_str() const
{
    return m_XSeason;
}

int CPfSeasons::getNYear() const
{
    if( m_NYear=="" ){
        return 0;
    }else{
        return atoi(m_NYear.c_str());
    }
}

const std::string& CPfSeasons::getNYear_str() const
{
    return m_NYear;
}

const std::string& CPfSeasons::getSSeason() const
{
    return m_SSeason;
}

const std::string& CPfSeasons::getSSeason_str() const
{
    return m_SSeason;
}

void CPfSeasons::setXSeason(int XSeason)
{
    std::ostringstream stream;
    stream << XSeason;
    m_XSeason = stream.str();
}

void CPfSeasons::setXSeason_str(const std::string &XSeason)
{
    m_XSeason = XSeason;
}

void CPfSeasons::setNYear(int NYear)
{
    std::ostringstream stream;
    stream << NYear;
    m_NYear = stream.str();
}

void CPfSeasons::setNYear_str(const std::string &NYear)
{
    m_NYear = NYear;
}

void CPfSeasons::setSSeason(const std::string &SSeason)
{
    m_SSeason = SSeason;
}

void CPfSeasons::setSSeason_str(const std::string &SSeason)
{
    m_SSeason = SSeason;
}

