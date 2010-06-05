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

#ifndef CPFSCORERS_H_
#define CPFSCORERS_H_

#include <string>

class CPfScorers
{
public:
    CPfScorers();
    CPfScorers(const CPfScorers &obj);
    virtual ~CPfScorers();

    const std::string& getSShortTeamPlayerName() const;
    const std::string& getSShortTeamPlayerName_str() const;
    const std::string& getSShortTeamName() const;
    const std::string& getSShortTeamName_str() const;
    int getNGoals() const;
    const std::string& getNGoals_str() const;
    const std::string& getSTeamPlayer() const;
    const std::string& getSTeamPlayer_str() const;
    const std::string& getSTeam() const;
    const std::string& getSTeam_str() const;

    void setSShortTeamPlayerName(const std::string &SShortTeamPlayerName);
    void setSShortTeamPlayerName_str(const std::string &SShortTeamPlayerName);
    void setSShortTeamName(const std::string &SShortTeamName);
    void setSShortTeamName_str(const std::string &SShortTeamName);
    void setNGoals(int NGoals);
    void setNGoals_str(const std::string &NGoals);
    void setSTeamPlayer(const std::string &STeamPlayer);
    void setSTeamPlayer_str(const std::string &STeamPlayer);
    void setSTeam(const std::string &STeam);
    void setSTeam_str(const std::string &STeam);

private:
    std::string m_SShortTeamPlayerName;
    std::string m_SShortTeamName;
    std::string m_NGoals;
    std::string m_STeamPlayer;
    std::string m_STeam;

};
#endif /*CPFSCORERS_H_*/
