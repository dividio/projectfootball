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
*       Version: 1.15                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfRanking.h"

CPfRanking::CPfRanking()
{
    m_NWins = "0";
    m_NPlayed = "0";
    m_STeam = "";
    m_NGoalsAgainst = "0";
    m_NPoints = "0";
    m_NGoalsFor = "0";
    m_NLosses = "0";
    m_NDraws = "0";
}

CPfRanking::CPfRanking(const CPfRanking &obj)
{
    m_NWins = obj.m_NWins;
    m_NPlayed = obj.m_NPlayed;
    m_STeam = obj.m_STeam;
    m_NGoalsAgainst = obj.m_NGoalsAgainst;
    m_NPoints = obj.m_NPoints;
    m_NGoalsFor = obj.m_NGoalsFor;
    m_NLosses = obj.m_NLosses;
    m_NDraws = obj.m_NDraws;
}

CPfRanking::~CPfRanking()
{
}

int CPfRanking::getNWins()
{
    if( m_NWins=="" ){
        return 0;
    }else{
        return atoi(m_NWins.c_str());
    }
}

const std::string& CPfRanking::getNWins_str()
{
    return m_NWins;
}

int CPfRanking::getNPlayed()
{
    if( m_NPlayed=="" ){
        return 0;
    }else{
        return atoi(m_NPlayed.c_str());
    }
}

const std::string& CPfRanking::getNPlayed_str()
{
    return m_NPlayed;
}

const std::string& CPfRanking::getSTeam()
{
    return m_STeam;
}

const std::string& CPfRanking::getSTeam_str()
{
    return m_STeam;
}

int CPfRanking::getNGoalsAgainst()
{
    if( m_NGoalsAgainst=="" ){
        return 0;
    }else{
        return atoi(m_NGoalsAgainst.c_str());
    }
}

const std::string& CPfRanking::getNGoalsAgainst_str()
{
    return m_NGoalsAgainst;
}

int CPfRanking::getNPoints()
{
    if( m_NPoints=="" ){
        return 0;
    }else{
        return atoi(m_NPoints.c_str());
    }
}

const std::string& CPfRanking::getNPoints_str()
{
    return m_NPoints;
}

int CPfRanking::getNGoalsFor()
{
    if( m_NGoalsFor=="" ){
        return 0;
    }else{
        return atoi(m_NGoalsFor.c_str());
    }
}

const std::string& CPfRanking::getNGoalsFor_str()
{
    return m_NGoalsFor;
}

int CPfRanking::getNLosses()
{
    if( m_NLosses=="" ){
        return 0;
    }else{
        return atoi(m_NLosses.c_str());
    }
}

const std::string& CPfRanking::getNLosses_str()
{
    return m_NLosses;
}

int CPfRanking::getNDraws()
{
    if( m_NDraws=="" ){
        return 0;
    }else{
        return atoi(m_NDraws.c_str());
    }
}

const std::string& CPfRanking::getNDraws_str()
{
    return m_NDraws;
}

void CPfRanking::setNWins(int NWins)
{
    std::ostringstream stream;
    stream << NWins;
    m_NWins = stream.str();
}

void CPfRanking::setNWins_str(const std::string &NWins)
{
    m_NWins = NWins;
}

void CPfRanking::setNPlayed(int NPlayed)
{
    std::ostringstream stream;
    stream << NPlayed;
    m_NPlayed = stream.str();
}

void CPfRanking::setNPlayed_str(const std::string &NPlayed)
{
    m_NPlayed = NPlayed;
}

void CPfRanking::setSTeam(const std::string &STeam)
{
    m_STeam = STeam;
}

void CPfRanking::setSTeam_str(const std::string &STeam)
{
    m_STeam = STeam;
}

void CPfRanking::setNGoalsAgainst(int NGoalsAgainst)
{
    std::ostringstream stream;
    stream << NGoalsAgainst;
    m_NGoalsAgainst = stream.str();
}

void CPfRanking::setNGoalsAgainst_str(const std::string &NGoalsAgainst)
{
    m_NGoalsAgainst = NGoalsAgainst;
}

void CPfRanking::setNPoints(int NPoints)
{
    std::ostringstream stream;
    stream << NPoints;
    m_NPoints = stream.str();
}

void CPfRanking::setNPoints_str(const std::string &NPoints)
{
    m_NPoints = NPoints;
}

void CPfRanking::setNGoalsFor(int NGoalsFor)
{
    std::ostringstream stream;
    stream << NGoalsFor;
    m_NGoalsFor = stream.str();
}

void CPfRanking::setNGoalsFor_str(const std::string &NGoalsFor)
{
    m_NGoalsFor = NGoalsFor;
}

void CPfRanking::setNLosses(int NLosses)
{
    std::ostringstream stream;
    stream << NLosses;
    m_NLosses = stream.str();
}

void CPfRanking::setNLosses_str(const std::string &NLosses)
{
    m_NLosses = NLosses;
}

void CPfRanking::setNDraws(int NDraws)
{
    std::ostringstream stream;
    stream << NDraws;
    m_NDraws = stream.str();
}

void CPfRanking::setNDraws_str(const std::string &NDraws)
{
    m_NDraws = NDraws;
}

