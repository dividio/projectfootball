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

#ifndef CPFROLESBYTEAMPLAYERS_H_
#define CPFROLESBYTEAMPLAYERS_H_

#include <string>

class CPfRolesByTeamPlayers
{
public:
    CPfRolesByTeamPlayers();
    CPfRolesByTeamPlayers(const CPfRolesByTeamPlayers &obj);
    virtual ~CPfRolesByTeamPlayers();

    int getXRoleByTeamPlayer() const;
    const std::string& getXRoleByTeamPlayer_str() const;
    int getXFkTeamPlayer() const;
    const std::string& getXFkTeamPlayer_str() const;
    int getNSkill() const;
    const std::string& getNSkill_str() const;
    int getXFkRole() const;
    const std::string& getXFkRole_str() const;

    void setXRoleByTeamPlayer(int XRoleByTeamPlayer);
    void setXRoleByTeamPlayer_str(const std::string &XRoleByTeamPlayer);
    void setXFkTeamPlayer(int XFkTeamPlayer);
    void setXFkTeamPlayer_str(const std::string &XFkTeamPlayer);
    void setNSkill(int NSkill);
    void setNSkill_str(const std::string &NSkill);
    void setXFkRole(int XFkRole);
    void setXFkRole_str(const std::string &XFkRole);

private:
    std::string m_XRoleByTeamPlayer;
    std::string m_XFkTeamPlayer;
    std::string m_NSkill;
    std::string m_XFkRole;

};
#endif /*CPFROLESBYTEAMPLAYERS_H_*/