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
*       generated by dia/DAOcodegen.py                                        *
*       Version: 1.16                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfCompetitions.h"

CPfCompetitions::CPfCompetitions()
{
    m_SCompetition = "";
    m_XCompetition = "0";
}

CPfCompetitions::CPfCompetitions(const CPfCompetitions &obj)
{
    m_SCompetition = obj.m_SCompetition;
    m_XCompetition = obj.m_XCompetition;
}

CPfCompetitions::~CPfCompetitions()
{
}

const std::string& CPfCompetitions::getSCompetition() const
{
    return m_SCompetition;
}

const std::string& CPfCompetitions::getSCompetition_str() const
{
    return m_SCompetition;
}

int CPfCompetitions::getXCompetition() const
{
    if( m_XCompetition=="" ){
        return 0;
    }else{
        return atoi(m_XCompetition.c_str());
    }
}

const std::string& CPfCompetitions::getXCompetition_str() const
{
    return m_XCompetition;
}

void CPfCompetitions::setSCompetition(const std::string &SCompetition)
{
    m_SCompetition = SCompetition;
}

void CPfCompetitions::setSCompetition_str(const std::string &SCompetition)
{
    m_SCompetition = SCompetition;
}

void CPfCompetitions::setXCompetition(int XCompetition)
{
    std::ostringstream stream;
    stream << XCompetition;
    m_XCompetition = stream.str();
}

void CPfCompetitions::setXCompetition_str(const std::string &XCompetition)
{
    m_XCompetition = XCompetition;
}
