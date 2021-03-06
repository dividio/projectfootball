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

#include "CPfTeamPlayers.h"

CPfTeamPlayers::CPfTeamPlayers()
{
    m_NWeight = "0";
    m_NLineupOrder = "0";
    m_NSquadNumber = "0";
    m_NHeight = "0";
    m_NSpeed = "0";
    m_NKickPower = "0";
    m_XTeamPlayer = "0";
    m_SShortName = "";
    m_NFortitude = "0";
    m_SName = "";
    m_SPhoto = "";
    m_DBirthday = "";
    m_XFkCountry = "0";
    m_NMoral = "0";
}

CPfTeamPlayers::CPfTeamPlayers(const CPfTeamPlayers &obj)
{
    m_NWeight = obj.m_NWeight;
    m_NLineupOrder = obj.m_NLineupOrder;
    m_NSquadNumber = obj.m_NSquadNumber;
    m_NHeight = obj.m_NHeight;
    m_NSpeed = obj.m_NSpeed;
    m_NKickPower = obj.m_NKickPower;
    m_XTeamPlayer = obj.m_XTeamPlayer;
    m_SShortName = obj.m_SShortName;
    m_NFortitude = obj.m_NFortitude;
    m_SName = obj.m_SName;
    m_SPhoto = obj.m_SPhoto;
    m_DBirthday = obj.m_DBirthday;
    m_XFkCountry = obj.m_XFkCountry;
    m_NMoral = obj.m_NMoral;
}

CPfTeamPlayers::~CPfTeamPlayers()
{
}

int CPfTeamPlayers::getNWeight() const
{
    if( m_NWeight=="" ){
        return 0;
    }else{
        return atoi(m_NWeight.c_str());
    }
}

const std::string& CPfTeamPlayers::getNWeight_str() const
{
    return m_NWeight;
}

int CPfTeamPlayers::getNLineupOrder() const
{
    if( m_NLineupOrder=="" ){
        return 0;
    }else{
        return atoi(m_NLineupOrder.c_str());
    }
}

const std::string& CPfTeamPlayers::getNLineupOrder_str() const
{
    return m_NLineupOrder;
}

int CPfTeamPlayers::getNSquadNumber() const
{
    if( m_NSquadNumber=="" ){
        return 0;
    }else{
        return atoi(m_NSquadNumber.c_str());
    }
}

const std::string& CPfTeamPlayers::getNSquadNumber_str() const
{
    return m_NSquadNumber;
}

int CPfTeamPlayers::getNHeight() const
{
    if( m_NHeight=="" ){
        return 0;
    }else{
        return atoi(m_NHeight.c_str());
    }
}

const std::string& CPfTeamPlayers::getNHeight_str() const
{
    return m_NHeight;
}

int CPfTeamPlayers::getNSpeed() const
{
    if( m_NSpeed=="" ){
        return 0;
    }else{
        return atoi(m_NSpeed.c_str());
    }
}

const std::string& CPfTeamPlayers::getNSpeed_str() const
{
    return m_NSpeed;
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

int CPfTeamPlayers::getNFortitude() const
{
    if( m_NFortitude=="" ){
        return 0;
    }else{
        return atoi(m_NFortitude.c_str());
    }
}

const std::string& CPfTeamPlayers::getNFortitude_str() const
{
    return m_NFortitude;
}

const std::string& CPfTeamPlayers::getSName() const
{
    return m_SName;
}

const std::string& CPfTeamPlayers::getSName_str() const
{
    return m_SName;
}

const std::string& CPfTeamPlayers::getSPhoto() const
{
    return m_SPhoto;
}

const std::string& CPfTeamPlayers::getSPhoto_str() const
{
    return m_SPhoto;
}

CDate CPfTeamPlayers::getDBirthday() const
{
    return m_DBirthday;
}

const std::string& CPfTeamPlayers::getDBirthday_str() const
{
    return m_DBirthday;
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

int CPfTeamPlayers::getNMoral() const
{
    if( m_NMoral=="" ){
        return 0;
    }else{
        return atoi(m_NMoral.c_str());
    }
}

const std::string& CPfTeamPlayers::getNMoral_str() const
{
    return m_NMoral;
}

void CPfTeamPlayers::setNWeight(int NWeight)
{
    std::ostringstream stream;
    stream << NWeight;
    m_NWeight = stream.str();
}

void CPfTeamPlayers::setNWeight_str(const std::string &NWeight)
{
    m_NWeight = NWeight;
}

void CPfTeamPlayers::setNLineupOrder(int NLineupOrder)
{
    std::ostringstream stream;
    stream << NLineupOrder;
    m_NLineupOrder = stream.str();
}

void CPfTeamPlayers::setNLineupOrder_str(const std::string &NLineupOrder)
{
    m_NLineupOrder = NLineupOrder;
}

void CPfTeamPlayers::setNSquadNumber(int NSquadNumber)
{
    std::ostringstream stream;
    stream << NSquadNumber;
    m_NSquadNumber = stream.str();
}

void CPfTeamPlayers::setNSquadNumber_str(const std::string &NSquadNumber)
{
    m_NSquadNumber = NSquadNumber;
}

void CPfTeamPlayers::setNHeight(int NHeight)
{
    std::ostringstream stream;
    stream << NHeight;
    m_NHeight = stream.str();
}

void CPfTeamPlayers::setNHeight_str(const std::string &NHeight)
{
    m_NHeight = NHeight;
}

void CPfTeamPlayers::setNSpeed(int NSpeed)
{
    std::ostringstream stream;
    stream << NSpeed;
    m_NSpeed = stream.str();
}

void CPfTeamPlayers::setNSpeed_str(const std::string &NSpeed)
{
    m_NSpeed = NSpeed;
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

void CPfTeamPlayers::setNFortitude(int NFortitude)
{
    std::ostringstream stream;
    stream << NFortitude;
    m_NFortitude = stream.str();
}

void CPfTeamPlayers::setNFortitude_str(const std::string &NFortitude)
{
    m_NFortitude = NFortitude;
}

void CPfTeamPlayers::setSName(const std::string &SName)
{
    m_SName = SName;
}

void CPfTeamPlayers::setSName_str(const std::string &SName)
{
    m_SName = SName;
}

void CPfTeamPlayers::setSPhoto(const std::string &SPhoto)
{
    m_SPhoto = SPhoto;
}

void CPfTeamPlayers::setSPhoto_str(const std::string &SPhoto)
{
    m_SPhoto = SPhoto;
}

void CPfTeamPlayers::setDBirthday(const CDate &DBirthday)
{
    m_DBirthday = DBirthday.getTimestamp();
}

void CPfTeamPlayers::setDBirthday_str(const std::string &DBirthday)
{
    m_DBirthday = DBirthday;
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

void CPfTeamPlayers::setNMoral(int NMoral)
{
    std::ostringstream stream;
    stream << NMoral;
    m_NMoral = stream.str();
}

void CPfTeamPlayers::setNMoral_str(const std::string &NMoral)
{
    m_NMoral = NMoral;
}

