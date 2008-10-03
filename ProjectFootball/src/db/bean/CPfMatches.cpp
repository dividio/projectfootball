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

#include "CPfMatches.h"

CPfMatches::CPfMatches()
{
    m_XFkCompetitionPhase = "0";
    m_XFkTeamAway = "0";
    m_DMatch = "";
    m_XMatch = "0";
    m_LPlayed = "N";
    m_XFkTeamHome = "0";
}

CPfMatches::CPfMatches(const CPfMatches &obj)
{
    m_XFkCompetitionPhase = obj.m_XFkCompetitionPhase;
    m_XFkTeamAway = obj.m_XFkTeamAway;
    m_DMatch = obj.m_DMatch;
    m_XMatch = obj.m_XMatch;
    m_LPlayed = obj.m_LPlayed;
    m_XFkTeamHome = obj.m_XFkTeamHome;
}

CPfMatches::~CPfMatches()
{
}

int CPfMatches::getXFkCompetitionPhase() const
{
    if( m_XFkCompetitionPhase=="" ){
        return 0;
    }else{
        return atoi(m_XFkCompetitionPhase.c_str());
    }
}

const std::string& CPfMatches::getXFkCompetitionPhase_str() const
{
    return m_XFkCompetitionPhase;
}

int CPfMatches::getXFkTeamAway() const
{
    if( m_XFkTeamAway=="" ){
        return 0;
    }else{
        return atoi(m_XFkTeamAway.c_str());
    }
}

const std::string& CPfMatches::getXFkTeamAway_str() const
{
    return m_XFkTeamAway;
}

CDate CPfMatches::getDMatch() const
{
    return m_DMatch;
}

const std::string& CPfMatches::getDMatch_str() const
{
    return m_DMatch;
}

int CPfMatches::getXMatch() const
{
    if( m_XMatch=="" ){
        return 0;
    }else{
        return atoi(m_XMatch.c_str());
    }
}

const std::string& CPfMatches::getXMatch_str() const
{
    return m_XMatch;
}

bool CPfMatches::getLPlayed() const
{
    return m_LPlayed!="" && m_LPlayed!="N";
}

const std::string& CPfMatches::getLPlayed_str() const
{
    return m_LPlayed;
}

int CPfMatches::getXFkTeamHome() const
{
    if( m_XFkTeamHome=="" ){
        return 0;
    }else{
        return atoi(m_XFkTeamHome.c_str());
    }
}

const std::string& CPfMatches::getXFkTeamHome_str() const
{
    return m_XFkTeamHome;
}

void CPfMatches::setXFkCompetitionPhase(int XFkCompetitionPhase)
{
    std::ostringstream stream;
    stream << XFkCompetitionPhase;
    m_XFkCompetitionPhase = stream.str();
}

void CPfMatches::setXFkCompetitionPhase_str(const std::string &XFkCompetitionPhase)
{
    m_XFkCompetitionPhase = XFkCompetitionPhase;
}

void CPfMatches::setXFkTeamAway(int XFkTeamAway)
{
    std::ostringstream stream;
    stream << XFkTeamAway;
    m_XFkTeamAway = stream.str();
}

void CPfMatches::setXFkTeamAway_str(const std::string &XFkTeamAway)
{
    m_XFkTeamAway = XFkTeamAway;
}

void CPfMatches::setDMatch(CDate &DMatch)
{
    m_DMatch = DMatch.getTimestamp();
}

void CPfMatches::setDMatch_str(const std::string &DMatch)
{
    m_DMatch = DMatch;
}

void CPfMatches::setXMatch(int XMatch)
{
    std::ostringstream stream;
    stream << XMatch;
    m_XMatch = stream.str();
}

void CPfMatches::setXMatch_str(const std::string &XMatch)
{
    m_XMatch = XMatch;
}

void CPfMatches::setLPlayed(bool LPlayed)
{
    if( LPlayed ){
        m_LPlayed = "Y";
    }else{
        m_LPlayed = "N";
    }
}

void CPfMatches::setLPlayed_str(const std::string &LPlayed)
{
    m_LPlayed = LPlayed;
}

void CPfMatches::setXFkTeamHome(int XFkTeamHome)
{
    std::ostringstream stream;
    stream << XFkTeamHome;
    m_XFkTeamHome = stream.str();
}

void CPfMatches::setXFkTeamHome_str(const std::string &XFkTeamHome)
{
    m_XFkTeamHome = XFkTeamHome;
}

