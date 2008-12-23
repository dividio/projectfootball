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
*       Version: 1.20                                                         *
******************************************************************************/

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "CPfTeamPlayers.h"

CPfTeamPlayers::CPfTeamPlayers()
{
    m_NKickPower = "0";
    m_NVelocity = "0";
    m_XTeamPlayer = "0";
    m_SShortName = "";
    m_SName = "";
    m_XFkCountry = "0";
}

CPfTeamPlayers::CPfTeamPlayers(const CPfTeamPlayers &obj)
{
    m_NKickPower = obj.m_NKickPower;
    m_NVelocity = obj.m_NVelocity;
    m_XTeamPlayer = obj.m_XTeamPlayer;
    m_SShortName = obj.m_SShortName;
    m_SName = obj.m_SName;
    m_XFkCountry = obj.m_XFkCountry;
}

CPfTeamPlayers::~CPfTeamPlayers()
{
}

int CPfTeamPlayers::getNKickPower() const
{
    if( m_NKickPower=="" ){
        return 0;
    }else{
        return atoi(m_NKickPower.c_str());
    }
}

const std::string& CPfTeamPlayers::getNKickPower_str() const
{
    return m_NKickPower;
}

int CPfTeamPlayers::getNVelocity() const
{
    if( m_NVelocity=="" ){
        return 0;
    }else{
        return atoi(m_NVelocity.c_str());
    }
}

const std::string& CPfTeamPlayers::getNVelocity_str() const
{
    return m_NVelocity;
}

int CPfTeamPlayers::getXTeamPlayer() const
{
    if( m_XTeamPlayer=="" ){
        return 0;
    }else{
        return atoi(m_XTeamPlayer.c_str());
    }
}

const std::string& CPfTeamPlayers::getXTeamPlayer_str() const
{
    return m_XTeamPlayer;
}

const std::string& CPfTeamPlayers::getSShortName() const
{
    return m_SShortName;
}

const std::string& CPfTeamPlayers::getSShortName_str() const
{
    return m_SShortName;
}

const std::string& CPfTeamPlayers::getSName() const
{
    return m_SName;
}

const std::string& CPfTeamPlayers::getSName_str() const
{
    return m_SName;
}

int CPfTeamPlayers::getXFkCountry() const
{
    if( m_XFkCountry=="" ){
        return 0;
    }else{
        return atoi(m_XFkCountry.c_str());
    }
}

const std::string& CPfTeamPlayers::getXFkCountry_str() const
{
    return m_XFkCountry;
}

void CPfTeamPlayers::setNKickPower(int NKickPower)
{
    std::ostringstream stream;
    stream << NKickPower;
    m_NKickPower = stream.str();
}

void CPfTeamPlayers::setNKickPower_str(const std::string &NKickPower)
{
    m_NKickPower = NKickPower;
}

void CPfTeamPlayers::setNVelocity(int NVelocity)
{
    std::ostringstream stream;
    stream << NVelocity;
    m_NVelocity = stream.str();
}

void CPfTeamPlayers::setNVelocity_str(const std::string &NVelocity)
{
    m_NVelocity = NVelocity;
}

void CPfTeamPlayers::setXTeamPlayer(int XTeamPlayer)
{
    std::ostringstream stream;
    stream << XTeamPlayer;
    m_XTeamPlayer = stream.str();
}

void CPfTeamPlayers::setXTeamPlayer_str(const std::string &XTeamPlayer)
{
    m_XTeamPlayer = XTeamPlayer;
}

void CPfTeamPlayers::setSShortName(const std::string &SShortName)
{
    m_SShortName = SShortName;
}

void CPfTeamPlayers::setSShortName_str(const std::string &SShortName)
{
    m_SShortName = SShortName;
}

void CPfTeamPlayers::setSName(const std::string &SName)
{
    m_SName = SName;
}

void CPfTeamPlayers::setSName_str(const std::string &SName)
{
    m_SName = SName;
}

void CPfTeamPlayers::setXFkCountry(int XFkCountry)
{
    std::ostringstream stream;
    stream << XFkCountry;
    m_XFkCountry = stream.str();
}

void CPfTeamPlayers::setXFkCountry_str(const std::string &XFkCountry)
{
    m_XFkCountry = XFkCountry;
}

