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

#ifndef CPFTEAMSBYCOMPETITIONS_H_
#define CPFTEAMSBYCOMPETITIONS_H_

#include <string>

class CPfTeamsByCompetitions
{
public:
    CPfTeamsByCompetitions();
    CPfTeamsByCompetitions(const CPfTeamsByCompetitions &obj);
    virtual ~CPfTeamsByCompetitions();

    int getXFkCompetitionBySeason() const;
    const std::string& getXFkCompetitionBySeason_str() const;
    int getXTeamByCompetition() const;
    const std::string& getXTeamByCompetition_str() const;
    int getXFkTeam() const;
    const std::string& getXFkTeam_str() const;

    void setXFkCompetitionBySeason(int XFkCompetitionBySeason);
    void setXFkCompetitionBySeason_str(const std::string &XFkCompetitionBySeason);
    void setXTeamByCompetition(int XTeamByCompetition);
    void setXTeamByCompetition_str(const std::string &XTeamByCompetition);
    void setXFkTeam(int XFkTeam);
    void setXFkTeam_str(const std::string &XFkTeam);

private:
    std::string m_XFkCompetitionBySeason;
    std::string m_XTeamByCompetition;
    std::string m_XFkTeam;

};
#endif /*CPFTEAMSBYCOMPETITIONS_H_*/
