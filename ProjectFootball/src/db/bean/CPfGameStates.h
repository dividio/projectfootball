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
*       Version: 1.13                                                         *
******************************************************************************/

#ifndef CPFGAMESTATES_H_
#define CPFGAMESTATES_H_

#include <string>

class CPfGameStates
{
public:
    CPfGameStates();
    virtual ~CPfGameStates();

    const std::string& getSState();
    const std::string& getSState_str();
    int getXState();
    const std::string& getXState_str();
    const std::string& getSValue();
    const std::string& getSValue_str();

    void setSState(const std::string &SState);
    void setSState_str(const std::string &SState);
    void setXState(int XState);
    void setXState_str(const std::string &XState);
    void setSValue(const std::string &SValue);
    void setSValue_str(const std::string &SValue);

private:
    std::string m_SState;
    std::string m_XState;
    std::string m_SValue;

};
#endif /*CPFGAMESTATES_H_*/
