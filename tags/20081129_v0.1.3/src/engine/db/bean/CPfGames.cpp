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

#include "CPfGames.h"

CPfGames::CPfGames()
{
    m_XFkUser = "0";
    m_XGame = "0";
    m_SGameName = "";
    m_SConnectionString = "";
    m_SDriverName = "";
    m_SGameType = "";
    m_DLastSaved = "";
}

CPfGames::CPfGames(const CPfGames &obj)
{
    m_XFkUser = obj.m_XFkUser;
    m_XGame = obj.m_XGame;
    m_SGameName = obj.m_SGameName;
    m_SConnectionString = obj.m_SConnectionString;
    m_SDriverName = obj.m_SDriverName;
    m_SGameType = obj.m_SGameType;
    m_DLastSaved = obj.m_DLastSaved;
}

CPfGames::~CPfGames()
{
}

int CPfGames::getXFkUser() const
{
    if( m_XFkUser=="" ){
        return 0;
    }else{
        return atoi(m_XFkUser.c_str());
    }
}

const std::string& CPfGames::getXFkUser_str() const
{
    return m_XFkUser;
}

int CPfGames::getXGame() const
{
    if( m_XGame=="" ){
        return 0;
    }else{
        return atoi(m_XGame.c_str());
    }
}

const std::string& CPfGames::getXGame_str() const
{
    return m_XGame;
}

const std::string& CPfGames::getSGameName() const
{
    return m_SGameName;
}

const std::string& CPfGames::getSGameName_str() const
{
    return m_SGameName;
}

const std::string& CPfGames::getSConnectionString() const
{
    return m_SConnectionString;
}

const std::string& CPfGames::getSConnectionString_str() const
{
    return m_SConnectionString;
}

const std::string& CPfGames::getSDriverName() const
{
    return m_SDriverName;
}

const std::string& CPfGames::getSDriverName_str() const
{
    return m_SDriverName;
}

const std::string& CPfGames::getSGameType() const
{
    return m_SGameType;
}

const std::string& CPfGames::getSGameType_str() const
{
    return m_SGameType;
}

CDate CPfGames::getDLastSaved() const
{
    return m_DLastSaved;
}

const std::string& CPfGames::getDLastSaved_str() const
{
    return m_DLastSaved;
}

void CPfGames::setXFkUser(int XFkUser)
{
    std::ostringstream stream;
    stream << XFkUser;
    m_XFkUser = stream.str();
}

void CPfGames::setXFkUser_str(const std::string &XFkUser)
{
    m_XFkUser = XFkUser;
}

void CPfGames::setXGame(int XGame)
{
    std::ostringstream stream;
    stream << XGame;
    m_XGame = stream.str();
}

void CPfGames::setXGame_str(const std::string &XGame)
{
    m_XGame = XGame;
}

void CPfGames::setSGameName(const std::string &SGameName)
{
    m_SGameName = SGameName;
}

void CPfGames::setSGameName_str(const std::string &SGameName)
{
    m_SGameName = SGameName;
}

void CPfGames::setSConnectionString(const std::string &SConnectionString)
{
    m_SConnectionString = SConnectionString;
}

void CPfGames::setSConnectionString_str(const std::string &SConnectionString)
{
    m_SConnectionString = SConnectionString;
}

void CPfGames::setSDriverName(const std::string &SDriverName)
{
    m_SDriverName = SDriverName;
}

void CPfGames::setSDriverName_str(const std::string &SDriverName)
{
    m_SDriverName = SDriverName;
}

void CPfGames::setSGameType(const std::string &SGameType)
{
    m_SGameType = SGameType;
}

void CPfGames::setSGameType_str(const std::string &SGameType)
{
    m_SGameType = SGameType;
}

void CPfGames::setDLastSaved(CDate &DLastSaved)
{
    m_DLastSaved = DLastSaved.getTimestamp();
}

void CPfGames::setDLastSaved_str(const std::string &DLastSaved)
{
    m_DLastSaved = DLastSaved;
}
