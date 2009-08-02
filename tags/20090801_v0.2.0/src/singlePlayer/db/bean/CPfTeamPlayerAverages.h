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
*       Version: 1.21                                                         *
******************************************************************************/

#ifndef CPFTEAMPLAYERAVERAGES_H_
#define CPFTEAMPLAYERAVERAGES_H_

#include <string>

class CPfTeamPlayerAverages
{
public:
    CPfTeamPlayerAverages();
    CPfTeamPlayerAverages(const CPfTeamPlayerAverages &obj);
    virtual ~CPfTeamPlayerAverages();

    int getXTeamPlayer() const;
    const std::string& getXTeamPlayer_str() const;
    int getNTotal() const;
    const std::string& getNTotal_str() const;
    int getNAttack() const;
    const std::string& getNAttack_str() const;
    int getNDefense() const;
    const std::string& getNDefense_str() const;

    void setXTeamPlayer(int XTeamPlayer);
    void setXTeamPlayer_str(const std::string &XTeamPlayer);
    void setNTotal(int NTotal);
    void setNTotal_str(const std::string &NTotal);
    void setNAttack(int NAttack);
    void setNAttack_str(const std::string &NAttack);
    void setNDefense(int NDefense);
    void setNDefense_str(const std::string &NDefense);

private:
    std::string m_XTeamPlayer;
    std::string m_NTotal;
    std::string m_NAttack;
    std::string m_NDefense;

};
#endif /*CPFTEAMPLAYERAVERAGES_H_*/
