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

#include "CPfTeams.h"

CPfTeams::CPfTeams()
{
    m_SLogo = "";
    m_XTeam = "0";
    m_STeam = "";
    m_NBudget = "0";
    m_SShortName = "";
    m_XFkStadium = "0";
    m_XFkCountry = "0";
}

CPfTeams::CPfTeams(const CPfTeams &obj)
{
    m_SLogo = obj.m_SLogo;
    m_XTeam = obj.m_XTeam;
    m_STeam = obj.m_STeam;
    m_NBudget = obj.m_NBudget;
    m_SShortName = obj.m_SShortName;
    m_XFkStadium = obj.m_XFkStadium;
    m_XFkCountry = obj.m_XFkCountry;
}

CPfTeams::~CPfTeams()
{
}

const std::string& CPfTeams::getSLogo() const
{
    return m_SLogo;
}

const std::string& CPfTeams::getSLogo_str() const
{
    return m_SLogo;
}

int CPfTeams::getXTeam() const
{
    if( m_XTeam=="" ){
        return 0;
    }else{
        return atoi(m_XTeam.c_str());
    }
}

const std::string& CPfTeams::getXTeam_str() const
{
    return m_XTeam;
}

const std::string& CPfTeams::getSTeam() const
{
    return m_STeam;
}

const std::string& CPfTeams::getSTeam_str() const
{
    return m_STeam;
}

int CPfTeams::getNBudget() const
{
    if( m_NBudget=="" ){
        return 0;
    }else{
        return atoi(m_NBudget.c_str());
    }
}

const std::string& CPfTeams::getNBudget_str() const
{
    return m_NBudget;
}

const std::string& CPfTeams::getSShortName() const
{
    return m_SShortName;
}

const std::string& CPfTeams::getSShortName_str() const
{
    return m_SShortName;
}

int CPfTeams::getXFkStadium() const
{
    if( m_XFkStadium=="" ){
        return 0;
    }else{
        return atoi(m_XFkStadium.c_str());
    }
}

const std::string& CPfTeams::getXFkStadium_str() const
{
    return m_XFkStadium;
}

int CPfTeams::getXFkCountry() const
{
    if( m_XFkCountry=="" ){
        return 0;
    }else{
        return atoi(m_XFkCountry.c_str());
    }
}

const std::string& CPfTeams::getXFkCountry_str() const
{
    return m_XFkCountry;
}

void CPfTeams::setSLogo(const std::string &SLogo)
{
    m_SLogo = SLogo;
}

void CPfTeams::setSLogo_str(const std::string &SLogo)
{
    m_SLogo = SLogo;
}

void CPfTeams::setXTeam(int XTeam)
{
    std::ostringstream stream;
    stream << XTeam;
    m_XTeam = stream.str();
}

void CPfTeams::setXTeam_str(const std::string &XTeam)
{
    m_XTeam = XTeam;
}

void CPfTeams::setSTeam(const std::string &STeam)
{
    m_STeam = STeam;
}

void CPfTeams::setSTeam_str(const std::string &STeam)
{
    m_STeam = STeam;
}

void CPfTeams::setNBudget(int NBudget)
{
    std::ostringstream stream;
    stream << NBudget;
    m_NBudget = stream.str();
}

void CPfTeams::setNBudget_str(const std::string &NBudget)
{
    m_NBudget = NBudget;
}

void CPfTeams::setSShortName(const std::string &SShortName)
{
    m_SShortName = SShortName;
}

void CPfTeams::setSShortName_str(const std::string &SShortName)
{
    m_SShortName = SShortName;
}

void CPfTeams::setXFkStadium(int XFkStadium)
{
    std::ostringstream stream;
    stream << XFkStadium;
    m_XFkStadium = stream.str();
}

void CPfTeams::setXFkStadium_str(const std::string &XFkStadium)
{
    m_XFkStadium = XFkStadium;
}

void CPfTeams::setXFkCountry(int XFkCountry)
{
    std::ostringstream stream;
    stream << XFkCountry;
    m_XFkCountry = stream.str();
}

void CPfTeams::setXFkCountry_str(const std::string &XFkCountry)
{
    m_XFkCountry = XFkCountry;
}
