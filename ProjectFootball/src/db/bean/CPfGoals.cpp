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
*       Version: 1.11                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfGoals.h"

CPfGoals::CPfGoals()
{
    m_XFkTeplScorer = "0";
    m_XGoal = "0";
    m_LOwnGoal = "N";
    m_XFkTeamScorer = "0";
    m_XFkMatch = "0";
    m_NMinute = "0";
}

CPfGoals::~CPfGoals()
{
}

int CPfGoals::getXFkTeplScorer()
{
    if( m_XFkTeplScorer=="" ){
        return 0;
    }else{
        return atoi(m_XFkTeplScorer.c_str());
    }
}

const std::string& CPfGoals::getXFkTeplScorer_str()
{
    return m_XFkTeplScorer;
}

int CPfGoals::getXGoal()
{
    if( m_XGoal=="" ){
        return 0;
    }else{
        return atoi(m_XGoal.c_str());
    }
}

const std::string& CPfGoals::getXGoal_str()
{
    return m_XGoal;
}

bool CPfGoals::getLOwnGoal()
{
    return m_LOwnGoal!="" && m_LOwnGoal!="N";
}

const std::string& CPfGoals::getLOwnGoal_str()
{
    return m_LOwnGoal;
}

int CPfGoals::getXFkTeamScorer()
{
    if( m_XFkTeamScorer=="" ){
        return 0;
    }else{
        return atoi(m_XFkTeamScorer.c_str());
    }
}

const std::string& CPfGoals::getXFkTeamScorer_str()
{
    return m_XFkTeamScorer;
}

int CPfGoals::getXFkMatch()
{
    if( m_XFkMatch=="" ){
        return 0;
    }else{
        return atoi(m_XFkMatch.c_str());
    }
}

const std::string& CPfGoals::getXFkMatch_str()
{
    return m_XFkMatch;
}

int CPfGoals::getNMinute()
{
    if( m_NMinute=="" ){
        return 0;
    }else{
        return atoi(m_NMinute.c_str());
    }
}

const std::string& CPfGoals::getNMinute_str()
{
    return m_NMinute;
}

void CPfGoals::setXFkTeplScorer(int XFkTeplScorer)
{
    std::ostringstream stream;
    stream << XFkTeplScorer;
    m_XFkTeplScorer = stream.str();
}

void CPfGoals::setXFkTeplScorer(const std::string &XFkTeplScorer)
{
    m_XFkTeplScorer = XFkTeplScorer;
}

void CPfGoals::setXGoal(int XGoal)
{
    std::ostringstream stream;
    stream << XGoal;
    m_XGoal = stream.str();
}

void CPfGoals::setXGoal(const std::string &XGoal)
{
    m_XGoal = XGoal;
}

void CPfGoals::setLOwnGoal(bool LOwnGoal)
{
    if( LOwnGoal ){
        m_LOwnGoal = "Y";
    }else{
        m_LOwnGoal = "N";
    }
}

void CPfGoals::setLOwnGoal(const std::string &LOwnGoal)
{
    m_LOwnGoal = LOwnGoal;
}

void CPfGoals::setXFkTeamScorer(int XFkTeamScorer)
{
    std::ostringstream stream;
    stream << XFkTeamScorer;
    m_XFkTeamScorer = stream.str();
}

void CPfGoals::setXFkTeamScorer(const std::string &XFkTeamScorer)
{
    m_XFkTeamScorer = XFkTeamScorer;
}

void CPfGoals::setXFkMatch(int XFkMatch)
{
    std::ostringstream stream;
    stream << XFkMatch;
    m_XFkMatch = stream.str();
}

void CPfGoals::setXFkMatch(const std::string &XFkMatch)
{
    m_XFkMatch = XFkMatch;
}

void CPfGoals::setNMinute(int NMinute)
{
    std::ostringstream stream;
    stream << NMinute;
    m_NMinute = stream.str();
}

void CPfGoals::setNMinute(const std::string &NMinute)
{
    m_NMinute = NMinute;
}

