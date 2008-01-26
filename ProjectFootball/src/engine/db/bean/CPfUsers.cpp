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
*       Version: 1.6                                                          *
******************************************************************************/

#include <iostream>
#include <sstream>

#include "CPfUsers.h"

CPfUsers::CPfUsers()
{
    m_XUser = "0";
    m_SUser = "";
}

CPfUsers::~CPfUsers()
{
}

int CPfUsers::getXUser_int()
{
    return atoi(m_XUser.c_str());
}

const std::string& CPfUsers::getXUser()
{
    return m_XUser;
}

const std::string& CPfUsers::getSUser()
{
    return m_SUser;
}

void CPfUsers::setXUser(int XUser)
{
    std::ostringstream stream;
    stream << XUser;
    m_XUser = stream.str();
}

void CPfUsers::setXUser(const std::string &XUser)
{
    m_XUser = XUser;
}

void CPfUsers::setSUser(const std::string &SUser)
{
    m_SUser = SUser;
}

