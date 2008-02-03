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

#include "CPfGameOptions.h"

CPfGameOptions::CPfGameOptions()
{
    m_SCategory = "";
    m_XFkGame = "0";
    m_XOption = "0";
    m_SValue = "";
    m_SAttribute = "";
}

CPfGameOptions::~CPfGameOptions()
{
}

const std::string& CPfGameOptions::getSCategory()
{
    return m_SCategory;
}

int CPfGameOptions::getXFkGame_int()
{
    return atoi(m_XFkGame.c_str());
}

const std::string& CPfGameOptions::getXFkGame()
{
    return m_XFkGame;
}

int CPfGameOptions::getXOption_int()
{
    return atoi(m_XOption.c_str());
}

const std::string& CPfGameOptions::getXOption()
{
    return m_XOption;
}

const std::string& CPfGameOptions::getSValue()
{
    return m_SValue;
}

const std::string& CPfGameOptions::getSAttribute()
{
    return m_SAttribute;
}

void CPfGameOptions::setSCategory(const std::string &SCategory)
{
    m_SCategory = SCategory;
}

void CPfGameOptions::setXFkGame(int XFkGame)
{
    std::ostringstream stream;
    stream << XFkGame;
    m_XFkGame = stream.str();
}

void CPfGameOptions::setXFkGame(const std::string &XFkGame)
{
    m_XFkGame = XFkGame;
}

void CPfGameOptions::setXOption(int XOption)
{
    std::ostringstream stream;
    stream << XOption;
    m_XOption = stream.str();
}

void CPfGameOptions::setXOption(const std::string &XOption)
{
    m_XOption = XOption;
}

void CPfGameOptions::setSValue(const std::string &SValue)
{
    m_SValue = SValue;
}

void CPfGameOptions::setSAttribute(const std::string &SAttribute)
{
    m_SAttribute = SAttribute;
}
