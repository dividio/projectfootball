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

#include "CPfTeamPlayerContracts.h"

CPfTeamPlayerContracts::CPfTeamPlayerContracts()
{
    m_DBegin = "";
    m_XTeamPlayerContract = "0";
    m_DEnd = "";
    m_XFkTeamPlayer = "0";
    m_NLineupOrder = "0";
    m_XFkTeam = "0";
}

CPfTeamPlayerContracts::CPfTeamPlayerContracts(const CPfTeamPlayerContracts &obj)
{
    m_DBegin = obj.m_DBegin;
    m_XTeamPlayerContract = obj.m_XTeamPlayerContract;
    m_DEnd = obj.m_DEnd;
    m_XFkTeamPlayer = obj.m_XFkTeamPlayer;
    m_NLineupOrder = obj.m_NLineupOrder;
    m_XFkTeam = obj.m_XFkTeam;
}

CPfTeamPlayerContracts::~CPfTeamPlayerContracts()
{
}

CDate CPfTeamPlayerContracts::getDBegin() const
{
    return m_DBegin;
}

const std::string& CPfTeamPlayerContracts::getDBegin_str() const
{
    return m_DBegin;
}

int CPfTeamPlayerContracts::getXTeamPlayerContract() const
{
    if( m_XTeamPlayerContract=="" ){
        return 0;
    }else{
        return atoi(m_XTeamPlayerContract.c_str());
    }
}

const std::string& CPfTeamPlayerContracts::getXTeamPlayerContract_str() const
{
    return m_XTeamPlayerContract;
}

CDate CPfTeamPlayerContracts::getDEnd() const
{
    return m_DEnd;
}

const std::string& CPfTeamPlayerContracts::getDEnd_str() const
{
    return m_DEnd;
}

int CPfTeamPlayerContracts::getXFkTeamPlayer() const
{
    if( m_XFkTeamPlayer=="" ){
        return 0;
    }else{
        return atoi(m_XFkTeamPlayer.c_str());
    }
}

const std::string& CPfTeamPlayerContracts::getXFkTeamPlayer_str() const
{
    return m_XFkTeamPlayer;
}

int CPfTeamPlayerContracts::getNLineupOrder() const
{
    if( m_NLineupOrder=="" ){
        return 0;
    }else{
        return atoi(m_NLineupOrder.c_str());
    }
}

const std::string& CPfTeamPlayerContracts::getNLineupOrder_str() const
{
    return m_NLineupOrder;
}

int CPfTeamPlayerContracts::getXFkTeam() const
{
    if( m_XFkTeam=="" ){
        return 0;
    }else{
        return atoi(m_XFkTeam.c_str());
    }
}

const std::string& CPfTeamPlayerContracts::getXFkTeam_str() const
{
    return m_XFkTeam;
}

void CPfTeamPlayerContracts::setDBegin(CDate &DBegin)
{
    m_DBegin = DBegin.getTimestamp();
}

void CPfTeamPlayerContracts::setDBegin_str(const std::string &DBegin)
{
    m_DBegin = DBegin;
}

void CPfTeamPlayerContracts::setXTeamPlayerContract(int XTeamPlayerContract)
{
    std::ostringstream stream;
    stream << XTeamPlayerContract;
    m_XTeamPlayerContract = stream.str();
}

void CPfTeamPlayerContracts::setXTeamPlayerContract_str(const std::string &XTeamPlayerContract)
{
    m_XTeamPlayerContract = XTeamPlayerContract;
}

void CPfTeamPlayerContracts::setDEnd(CDate &DEnd)
{
    m_DEnd = DEnd.getTimestamp();
}

void CPfTeamPlayerContracts::setDEnd_str(const std::string &DEnd)
{
    m_DEnd = DEnd;
}

void CPfTeamPlayerContracts::setXFkTeamPlayer(int XFkTeamPlayer)
{
    std::ostringstream stream;
    stream << XFkTeamPlayer;
    m_XFkTeamPlayer = stream.str();
}

void CPfTeamPlayerContracts::setXFkTeamPlayer_str(const std::string &XFkTeamPlayer)
{
    m_XFkTeamPlayer = XFkTeamPlayer;
}

void CPfTeamPlayerContracts::setNLineupOrder(int NLineupOrder)
{
    std::ostringstream stream;
    stream << NLineupOrder;
    m_NLineupOrder = stream.str();
}

void CPfTeamPlayerContracts::setNLineupOrder_str(const std::string &NLineupOrder)
{
    m_NLineupOrder = NLineupOrder;
}

void CPfTeamPlayerContracts::setXFkTeam(int XFkTeam)
{
    std::ostringstream stream;
    stream << XFkTeam;
    m_XFkTeam = stream.str();
}

void CPfTeamPlayerContracts::setXFkTeam_str(const std::string &XFkTeam)
{
    m_XFkTeam = XFkTeam;
}

