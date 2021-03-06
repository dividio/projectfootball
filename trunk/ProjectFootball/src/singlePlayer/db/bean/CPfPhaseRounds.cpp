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

#include "CPfPhaseRounds.h"

CPfPhaseRounds::CPfPhaseRounds()
{
    m_XFkCompetitionPhase = "0";
    m_NOrder = "0";
    m_SPhaseRound = "";
    m_XPhaseRound = "0";
}

CPfPhaseRounds::CPfPhaseRounds(const CPfPhaseRounds &obj)
{
    m_XFkCompetitionPhase = obj.m_XFkCompetitionPhase;
    m_NOrder = obj.m_NOrder;
    m_SPhaseRound = obj.m_SPhaseRound;
    m_XPhaseRound = obj.m_XPhaseRound;
}

CPfPhaseRounds::~CPfPhaseRounds()
{
}

int CPfPhaseRounds::getXFkCompetitionPhase() const
{
    if( m_XFkCompetitionPhase=="" ){
        return 0;
    }else{
        return atoi(m_XFkCompetitionPhase.c_str());
    }
}

const std::string& CPfPhaseRounds::getXFkCompetitionPhase_str() const
{
    return m_XFkCompetitionPhase;
}

int CPfPhaseRounds::getNOrder() const
{
    if( m_NOrder=="" ){
        return 0;
    }else{
        return atoi(m_NOrder.c_str());
    }
}

const std::string& CPfPhaseRounds::getNOrder_str() const
{
    return m_NOrder;
}

const std::string& CPfPhaseRounds::getSPhaseRound() const
{
    return m_SPhaseRound;
}

const std::string& CPfPhaseRounds::getSPhaseRound_str() const
{
    return m_SPhaseRound;
}

int CPfPhaseRounds::getXPhaseRound() const
{
    if( m_XPhaseRound=="" ){
        return 0;
    }else{
        return atoi(m_XPhaseRound.c_str());
    }
}

const std::string& CPfPhaseRounds::getXPhaseRound_str() const
{
    return m_XPhaseRound;
}

void CPfPhaseRounds::setXFkCompetitionPhase(int XFkCompetitionPhase)
{
    std::ostringstream stream;
    stream << XFkCompetitionPhase;
    m_XFkCompetitionPhase = stream.str();
}

void CPfPhaseRounds::setXFkCompetitionPhase_str(const std::string &XFkCompetitionPhase)
{
    m_XFkCompetitionPhase = XFkCompetitionPhase;
}

void CPfPhaseRounds::setNOrder(int NOrder)
{
    std::ostringstream stream;
    stream << NOrder;
    m_NOrder = stream.str();
}

void CPfPhaseRounds::setNOrder_str(const std::string &NOrder)
{
    m_NOrder = NOrder;
}

void CPfPhaseRounds::setSPhaseRound(const std::string &SPhaseRound)
{
    m_SPhaseRound = SPhaseRound;
}

void CPfPhaseRounds::setSPhaseRound_str(const std::string &SPhaseRound)
{
    m_SPhaseRound = SPhaseRound;
}

void CPfPhaseRounds::setXPhaseRound(int XPhaseRound)
{
    std::ostringstream stream;
    stream << XPhaseRound;
    m_XPhaseRound = stream.str();
}

void CPfPhaseRounds::setXPhaseRound_str(const std::string &XPhaseRound)
{
    m_XPhaseRound = XPhaseRound;
}

