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

#include "CPfCountries.h"

CPfCountries::CPfCountries()
{
    m_XFkConfederation = "0";
    m_SFlag = "";
    m_SCapital = "";
    m_SCountry = "";
    m_XCountry = "0";
    m_SShortName = "";
}

CPfCountries::CPfCountries(const CPfCountries &obj)
{
    m_XFkConfederation = obj.m_XFkConfederation;
    m_SFlag = obj.m_SFlag;
    m_SCapital = obj.m_SCapital;
    m_SCountry = obj.m_SCountry;
    m_XCountry = obj.m_XCountry;
    m_SShortName = obj.m_SShortName;
}

CPfCountries::~CPfCountries()
{
}

int CPfCountries::getXFkConfederation() const
{
    if( m_XFkConfederation=="" ){
        return 0;
    }else{
        return atoi(m_XFkConfederation.c_str());
    }
}

const std::string& CPfCountries::getXFkConfederation_str() const
{
    return m_XFkConfederation;
}

const std::string& CPfCountries::getSFlag() const
{
    return m_SFlag;
}

const std::string& CPfCountries::getSFlag_str() const
{
    return m_SFlag;
}

const std::string& CPfCountries::getSCapital() const
{
    return m_SCapital;
}

const std::string& CPfCountries::getSCapital_str() const
{
    return m_SCapital;
}

const std::string& CPfCountries::getSCountry() const
{
    return m_SCountry;
}

const std::string& CPfCountries::getSCountry_str() const
{
    return m_SCountry;
}

int CPfCountries::getXCountry() const
{
    if( m_XCountry=="" ){
        return 0;
    }else{
        return atoi(m_XCountry.c_str());
    }
}

const std::string& CPfCountries::getXCountry_str() const
{
    return m_XCountry;
}

const std::string& CPfCountries::getSShortName() const
{
    return m_SShortName;
}

const std::string& CPfCountries::getSShortName_str() const
{
    return m_SShortName;
}

void CPfCountries::setXFkConfederation(int XFkConfederation)
{
    std::ostringstream stream;
    stream << XFkConfederation;
    m_XFkConfederation = stream.str();
}

void CPfCountries::setXFkConfederation_str(const std::string &XFkConfederation)
{
    m_XFkConfederation = XFkConfederation;
}

void CPfCountries::setSFlag(const std::string &SFlag)
{
    m_SFlag = SFlag;
}

void CPfCountries::setSFlag_str(const std::string &SFlag)
{
    m_SFlag = SFlag;
}

void CPfCountries::setSCapital(const std::string &SCapital)
{
    m_SCapital = SCapital;
}

void CPfCountries::setSCapital_str(const std::string &SCapital)
{
    m_SCapital = SCapital;
}

void CPfCountries::setSCountry(const std::string &SCountry)
{
    m_SCountry = SCountry;
}

void CPfCountries::setSCountry_str(const std::string &SCountry)
{
    m_SCountry = SCountry;
}

void CPfCountries::setXCountry(int XCountry)
{
    std::ostringstream stream;
    stream << XCountry;
    m_XCountry = stream.str();
}

void CPfCountries::setXCountry_str(const std::string &XCountry)
{
    m_XCountry = XCountry;
}

void CPfCountries::setSShortName(const std::string &SShortName)
{
    m_SShortName = SShortName;
}

void CPfCountries::setSShortName_str(const std::string &SShortName)
{
    m_SShortName = SShortName;
}

