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

#ifndef CPFGOALS_H_
#define CPFGOALS_H_

#include <string>

class CPfGoals
{
public:
    CPfGoals();
    CPfGoals(const CPfGoals &obj);
    virtual ~CPfGoals();

    int getXFkTeamPlayerScorer() const;
    const std::string& getXFkTeamPlayerScorer_str() const;
    int getXGoal() const;
    const std::string& getXGoal_str() const;
    bool getLOwnGoal() const;
    const std::string& getLOwnGoal_str() const;
    int getXFkTeamScorer() const;
    const std::string& getXFkTeamScorer_str() const;
    int getXFkMatch() const;
    const std::string& getXFkMatch_str() const;
    int getNMinute() const;
    const std::string& getNMinute_str() const;

    void setXFkTeamPlayerScorer(int XFkTeamPlayerScorer);
    void setXFkTeamPlayerScorer_str(const std::string &XFkTeamPlayerScorer);
    void setXGoal(int XGoal);
    void setXGoal_str(const std::string &XGoal);
    void setLOwnGoal(bool LOwnGoal);
    void setLOwnGoal_str(const std::string &LOwnGoal);
    void setXFkTeamScorer(int XFkTeamScorer);
    void setXFkTeamScorer_str(const std::string &XFkTeamScorer);
    void setXFkMatch(int XFkMatch);
    void setXFkMatch_str(const std::string &XFkMatch);
    void setNMinute(int NMinute);
    void setNMinute_str(const std::string &NMinute);

private:
    std::string m_XFkTeamPlayerScorer;
    std::string m_XGoal;
    std::string m_LOwnGoal;
    std::string m_XFkTeamScorer;
    std::string m_XFkMatch;
    std::string m_NMinute;

};
#endif /*CPFGOALS_H_*/
