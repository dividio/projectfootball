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

#ifndef CPFGAMES_H_
#define CPFGAMES_H_

#include <string>

#include "../../../utils/CDate.h"

class CPfGames
{
public:
    CPfGames();
    CPfGames(const CPfGames &obj);
    virtual ~CPfGames();

    int getXFkUser() const;
    const std::string& getXFkUser_str() const;
    int getXGame() const;
    const std::string& getXGame_str() const;
    const std::string& getSGameName() const;
    const std::string& getSGameName_str() const;
    const std::string& getSConnectionString() const;
    const std::string& getSConnectionString_str() const;
    const std::string& getSDriverName() const;
    const std::string& getSDriverName_str() const;
    const std::string& getSGameType() const;
    const std::string& getSGameType_str() const;
    CDate getDLastSaved() const;
    const std::string& getDLastSaved_str() const;

    void setXFkUser(int XFkUser);
    void setXFkUser_str(const std::string &XFkUser);
    void setXGame(int XGame);
    void setXGame_str(const std::string &XGame);
    void setSGameName(const std::string &SGameName);
    void setSGameName_str(const std::string &SGameName);
    void setSConnectionString(const std::string &SConnectionString);
    void setSConnectionString_str(const std::string &SConnectionString);
    void setSDriverName(const std::string &SDriverName);
    void setSDriverName_str(const std::string &SDriverName);
    void setSGameType(const std::string &SGameType);
    void setSGameType_str(const std::string &SGameType);
    void setDLastSaved(CDate &DLastSaved);
    void setDLastSaved_str(const std::string &DLastSaved);

private:
    std::string m_XFkUser;
    std::string m_XGame;
    std::string m_SGameName;
    std::string m_SConnectionString;
    std::string m_SDriverName;
    std::string m_SGameType;
    std::string m_DLastSaved;

};
#endif /*CPFGAMES_H_*/