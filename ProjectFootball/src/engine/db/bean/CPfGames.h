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

#ifndef CPFGAMES_H_
#define CPFGAMES_H_

#include <string>

class CPfGames
{
public:
    CPfGames();
    virtual ~CPfGames();

    int getXFkUser_int();
    const std::string& getXFkUser();
    const std::string& getSConnectionString();
    int getXGame_int();
    const std::string& getXGame();
    const std::string& getSDriverName();
    const std::string& getSGameName();

    void setXFkUser(int XFkUser);
    void setXFkUser(const std::string &XFkUser);
    void setSConnectionString(const std::string &SConnectionString);
    void setXGame(int XGame);
    void setXGame(const std::string &XGame);
    void setSDriverName(const std::string &SDriverName);
    void setSGameName(const std::string &SGameName);

private:
    std::string m_XFkUser;
    std::string m_SConnectionString;
    std::string m_XGame;
    std::string m_SDriverName;
    std::string m_SGameName;

};
#endif /*CPFGAMES_H_*/