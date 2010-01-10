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

#include "CPfRoles.h"

CPfRoles::CPfRoles()
{
    m_SShortName = "";
    m_XRole = "0";
    m_XFkDemarcation = "0";
    m_SName = "";
}

CPfRoles::CPfRoles(const CPfRoles &obj)
{
    m_SShortName = obj.m_SShortName;
    m_XRole = obj.m_XRole;
    m_XFkDemarcation = obj.m_XFkDemarcation;
    m_SName = obj.m_SName;
}

CPfRoles::~CPfRoles()
{
}

const std::string& CPfRoles::getSShortName() const
{
    return m_SShortName;
}

const std::string& CPfRoles::getSShortName_str() const
{
    return m_SShortName;
}

int CPfRoles::getXRole() const
{
    if( m_XRole=="" ){
        return 0;
    }else{
        return atoi(m_XRole.c_str());
    }
}

const std::string& CPfRoles::getXRole_str() const
{
    return m_XRole;
}

int CPfRoles::getXFkDemarcation() const
{
    if( m_XFkDemarcation=="" ){
        return 0;
    }else{
        return atoi(m_XFkDemarcation.c_str());
    }
}

const std::string& CPfRoles::getXFkDemarcation_str() const
{
    return m_XFkDemarcation;
}

const std::string& CPfRoles::getSName() const
{
    return m_SName;
}

const std::string& CPfRoles::getSName_str() const
{
    return m_SName;
}

void CPfRoles::setSShortName(const std::string &SShortName)
{
    m_SShortName = SShortName;
}

void CPfRoles::setSShortName_str(const std::string &SShortName)
{
    m_SShortName = SShortName;
}

void CPfRoles::setXRole(int XRole)
{
    std::ostringstream stream;
    stream << XRole;
    m_XRole = stream.str();
}

void CPfRoles::setXRole_str(const std::string &XRole)
{
    m_XRole = XRole;
}

void CPfRoles::setXFkDemarcation(int XFkDemarcation)
{
    std::ostringstream stream;
    stream << XFkDemarcation;
    m_XFkDemarcation = stream.str();
}

void CPfRoles::setXFkDemarcation_str(const std::string &XFkDemarcation)
{
    m_XFkDemarcation = XFkDemarcation;
}

void CPfRoles::setSName(const std::string &SName)
{
    m_SName = SName;
}

void CPfRoles::setSName_str(const std::string &SName)
{
    m_SName = SName;
}

