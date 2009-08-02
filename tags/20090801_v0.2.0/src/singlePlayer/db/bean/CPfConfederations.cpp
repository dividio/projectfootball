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

#include "CPfConfederations.h"

CPfConfederations::CPfConfederations()
{
    m_XConfederation = "0";
    m_SConfederation = "";
    m_SLogo = "";
}

CPfConfederations::CPfConfederations(const CPfConfederations &obj)
{
    m_XConfederation = obj.m_XConfederation;
    m_SConfederation = obj.m_SConfederation;
    m_SLogo = obj.m_SLogo;
}

CPfConfederations::~CPfConfederations()
{
}

int CPfConfederations::getXConfederation() const
{
    if( m_XConfederation=="" ){
        return 0;
    }else{
        return atoi(m_XConfederation.c_str());
    }
}

const std::string& CPfConfederations::getXConfederation_str() const
{
    return m_XConfederation;
}

const std::string& CPfConfederations::getSConfederation() const
{
    return m_SConfederation;
}

const std::string& CPfConfederations::getSConfederation_str() const
{
    return m_SConfederation;
}

const std::string& CPfConfederations::getSLogo() const
{
    return m_SLogo;
}

const std::string& CPfConfederations::getSLogo_str() const
{
    return m_SLogo;
}

void CPfConfederations::setXConfederation(int XConfederation)
{
    std::ostringstream stream;
    stream << XConfederation;
    m_XConfederation = stream.str();
}

void CPfConfederations::setXConfederation_str(const std::string &XConfederation)
{
    m_XConfederation = XConfederation;
}

void CPfConfederations::setSConfederation(const std::string &SConfederation)
{
    m_SConfederation = SConfederation;
}

void CPfConfederations::setSConfederation_str(const std::string &SConfederation)
{
    m_SConfederation = SConfederation;
}

void CPfConfederations::setSLogo(const std::string &SLogo)
{
    m_SLogo = SLogo;
}

void CPfConfederations::setSLogo_str(const std::string &SLogo)
{
    m_SLogo = SLogo;
}

