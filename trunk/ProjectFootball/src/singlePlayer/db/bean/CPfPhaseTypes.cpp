/******************************************************************************
* Copyright (C) 2010 - Ikaro Games   www.ikarogames.com                       *
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

#include "CPfPhaseTypes.h"

CPfPhaseTypes::CPfPhaseTypes()
{
    m_SPhaseType = "";
    m_XPhaseType = "0";
}

CPfPhaseTypes::CPfPhaseTypes(const CPfPhaseTypes &obj)
{
    m_SPhaseType = obj.m_SPhaseType;
    m_XPhaseType = obj.m_XPhaseType;
}

CPfPhaseTypes::~CPfPhaseTypes()
{
}

const std::string& CPfPhaseTypes::getSPhaseType() const
{
    return m_SPhaseType;
}

const std::string& CPfPhaseTypes::getSPhaseType_str() const
{
    return m_SPhaseType;
}

int CPfPhaseTypes::getXPhaseType() const
{
    if( m_XPhaseType=="" ){
        return 0;
    }else{
        return atoi(m_XPhaseType.c_str());
    }
}

const std::string& CPfPhaseTypes::getXPhaseType_str() const
{
    return m_XPhaseType;
}

void CPfPhaseTypes::setSPhaseType(const std::string &SPhaseType)
{
    m_SPhaseType = SPhaseType;
}

void CPfPhaseTypes::setSPhaseType_str(const std::string &SPhaseType)
{
    m_SPhaseType = SPhaseType;
}

void CPfPhaseTypes::setXPhaseType(int XPhaseType)
{
    std::ostringstream stream;
    stream << XPhaseType;
    m_XPhaseType = stream.str();
}

void CPfPhaseTypes::setXPhaseType_str(const std::string &XPhaseType)
{
    m_XPhaseType = XPhaseType;
}
