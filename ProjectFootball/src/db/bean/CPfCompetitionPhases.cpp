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
#include <stdlib.h>

#include "CPfCompetitionPhases.h"

CPfCompetitionPhases::CPfCompetitionPhases()
{
    m_NOrder = "0";
    m_XCompetitionPhase = "0";
    m_SCompetitionPhase = "";
    m_XFkCompetition = "0";
}

CPfCompetitionPhases::CPfCompetitionPhases(const CPfCompetitionPhases &obj)
{
    m_NOrder = obj.m_NOrder;
    m_XCompetitionPhase = obj.m_XCompetitionPhase;
    m_SCompetitionPhase = obj.m_SCompetitionPhase;
    m_XFkCompetition = obj.m_XFkCompetition;
}

CPfCompetitionPhases::~CPfCompetitionPhases()
{
}

int CPfCompetitionPhases::getNOrder() const
{
    if( m_NOrder=="" ){
        return 0;
    }else{
        return atoi(m_NOrder.c_str());
    }
}

const std::string& CPfCompetitionPhases::getNOrder_str() const
{
    return m_NOrder;
}

int CPfCompetitionPhases::getXCompetitionPhase() const
{
    if( m_XCompetitionPhase=="" ){
        return 0;
    }else{
        return atoi(m_XCompetitionPhase.c_str());
    }
}

const std::string& CPfCompetitionPhases::getXCompetitionPhase_str() const
{
    return m_XCompetitionPhase;
}

const std::string& CPfCompetitionPhases::getSCompetitionPhase() const
{
    return m_SCompetitionPhase;
}

const std::string& CPfCompetitionPhases::getSCompetitionPhase_str() const
{
    return m_SCompetitionPhase;
}

int CPfCompetitionPhases::getXFkCompetition() const
{
    if( m_XFkCompetition=="" ){
        return 0;
    }else{
        return atoi(m_XFkCompetition.c_str());
    }
}

const std::string& CPfCompetitionPhases::getXFkCompetition_str() const
{
    return m_XFkCompetition;
}

void CPfCompetitionPhases::setNOrder(int NOrder)
{
    std::ostringstream stream;
    stream << NOrder;
    m_NOrder = stream.str();
}

void CPfCompetitionPhases::setNOrder_str(const std::string &NOrder)
{
    m_NOrder = NOrder;
}

void CPfCompetitionPhases::setXCompetitionPhase(int XCompetitionPhase)
{
    std::ostringstream stream;
    stream << XCompetitionPhase;
    m_XCompetitionPhase = stream.str();
}

void CPfCompetitionPhases::setXCompetitionPhase_str(const std::string &XCompetitionPhase)
{
    m_XCompetitionPhase = XCompetitionPhase;
}

void CPfCompetitionPhases::setSCompetitionPhase(const std::string &SCompetitionPhase)
{
    m_SCompetitionPhase = SCompetitionPhase;
}

void CPfCompetitionPhases::setSCompetitionPhase_str(const std::string &SCompetitionPhase)
{
    m_SCompetitionPhase = SCompetitionPhase;
}

void CPfCompetitionPhases::setXFkCompetition(int XFkCompetition)
{
    std::ostringstream stream;
    stream << XFkCompetition;
    m_XFkCompetition = stream.str();
}

void CPfCompetitionPhases::setXFkCompetition_str(const std::string &XFkCompetition)
{
    m_XFkCompetition = XFkCompetition;
}

