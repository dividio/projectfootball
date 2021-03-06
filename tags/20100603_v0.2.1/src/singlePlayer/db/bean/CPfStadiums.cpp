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
*       Version: 1.23                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "CPfStadiums.h"

CPfStadiums::CPfStadiums()
{
    m_DBuild = "";
    m_NCapacity = "0";
    m_SName = "";
    m_SPhoto = "";
    m_XStadium = "0";
    m_XFkCountry = "0";
}

CPfStadiums::CPfStadiums(const CPfStadiums &obj)
{
    m_DBuild = obj.m_DBuild;
    m_NCapacity = obj.m_NCapacity;
    m_SName = obj.m_SName;
    m_SPhoto = obj.m_SPhoto;
    m_XStadium = obj.m_XStadium;
    m_XFkCountry = obj.m_XFkCountry;
}

CPfStadiums::~CPfStadiums()
{
}

CDate CPfStadiums::getDBuild() const
{
    return m_DBuild;
}

const std::string& CPfStadiums::getDBuild_str() const
{
    return m_DBuild;
}

int CPfStadiums::getNCapacity() const
{
    if( m_NCapacity=="" ){
        return 0;
    }else{
        return atoi(m_NCapacity.c_str());
    }
}

const std::string& CPfStadiums::getNCapacity_str() const
{
    return m_NCapacity;
}

const std::string& CPfStadiums::getSName() const
{
    return m_SName;
}

const std::string& CPfStadiums::getSName_str() const
{
    return m_SName;
}

const std::string& CPfStadiums::getSPhoto() const
{
    return m_SPhoto;
}

const std::string& CPfStadiums::getSPhoto_str() const
{
    return m_SPhoto;
}

int CPfStadiums::getXStadium() const
{
    if( m_XStadium=="" ){
        return 0;
    }else{
        return atoi(m_XStadium.c_str());
    }
}

const std::string& CPfStadiums::getXStadium_str() const
{
    return m_XStadium;
}

int CPfStadiums::getXFkCountry() const
{
    if( m_XFkCountry=="" ){
        return 0;
    }else{
        return atoi(m_XFkCountry.c_str());
    }
}

const std::string& CPfStadiums::getXFkCountry_str() const
{
    return m_XFkCountry;
}

void CPfStadiums::setDBuild(const CDate &DBuild)
{
    m_DBuild = DBuild.getTimestamp();
}

void CPfStadiums::setDBuild_str(const std::string &DBuild)
{
    m_DBuild = DBuild;
}

void CPfStadiums::setNCapacity(int NCapacity)
{
    std::ostringstream stream;
    stream << NCapacity;
    m_NCapacity = stream.str();
}

void CPfStadiums::setNCapacity_str(const std::string &NCapacity)
{
    m_NCapacity = NCapacity;
}

void CPfStadiums::setSName(const std::string &SName)
{
    m_SName = SName;
}

void CPfStadiums::setSName_str(const std::string &SName)
{
    m_SName = SName;
}

void CPfStadiums::setSPhoto(const std::string &SPhoto)
{
    m_SPhoto = SPhoto;
}

void CPfStadiums::setSPhoto_str(const std::string &SPhoto)
{
    m_SPhoto = SPhoto;
}

void CPfStadiums::setXStadium(int XStadium)
{
    std::ostringstream stream;
    stream << XStadium;
    m_XStadium = stream.str();
}

void CPfStadiums::setXStadium_str(const std::string &XStadium)
{
    m_XStadium = XStadium;
}

void CPfStadiums::setXFkCountry(int XFkCountry)
{
    std::ostringstream stream;
    stream << XFkCountry;
    m_XFkCountry = stream.str();
}

void CPfStadiums::setXFkCountry_str(const std::string &XFkCountry)
{
    m_XFkCountry = XFkCountry;
}

