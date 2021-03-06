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

#include "CPfFormations.h"

CPfFormations::CPfFormations()
{
    m_XFkCoachOwner = "0";
    m_SName = "";
    m_XFormation = "0";
}

CPfFormations::CPfFormations(const CPfFormations &obj)
{
    m_XFkCoachOwner = obj.m_XFkCoachOwner;
    m_SName = obj.m_SName;
    m_XFormation = obj.m_XFormation;
}

CPfFormations::~CPfFormations()
{
}

int CPfFormations::getXFkCoachOwner() const
{
    if( m_XFkCoachOwner=="" ){
        return 0;
    }else{
        return atoi(m_XFkCoachOwner.c_str());
    }
}

const std::string& CPfFormations::getXFkCoachOwner_str() const
{
    return m_XFkCoachOwner;
}

const std::string& CPfFormations::getSName() const
{
    return m_SName;
}

const std::string& CPfFormations::getSName_str() const
{
    return m_SName;
}

int CPfFormations::getXFormation() const
{
    if( m_XFormation=="" ){
        return 0;
    }else{
        return atoi(m_XFormation.c_str());
    }
}

const std::string& CPfFormations::getXFormation_str() const
{
    return m_XFormation;
}

void CPfFormations::setXFkCoachOwner(int XFkCoachOwner)
{
    std::ostringstream stream;
    stream << XFkCoachOwner;
    m_XFkCoachOwner = stream.str();
}

void CPfFormations::setXFkCoachOwner_str(const std::string &XFkCoachOwner)
{
    m_XFkCoachOwner = XFkCoachOwner;
}

void CPfFormations::setSName(const std::string &SName)
{
    m_SName = SName;
}

void CPfFormations::setSName_str(const std::string &SName)
{
    m_SName = SName;
}

void CPfFormations::setXFormation(int XFormation)
{
    std::ostringstream stream;
    stream << XFormation;
    m_XFormation = stream.str();
}

void CPfFormations::setXFormation_str(const std::string &XFormation)
{
    m_XFormation = XFormation;
}

