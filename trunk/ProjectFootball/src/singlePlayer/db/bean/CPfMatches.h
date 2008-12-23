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
*       Version: 1.20                                                         *
******************************************************************************/

#ifndef CPFMATCHES_H_
#define CPFMATCHES_H_

#include <string>

#include "../../../utils/CDate.h"

class CPfMatches
{
public:
    CPfMatches();
    CPfMatches(const CPfMatches &obj);
    virtual ~CPfMatches();

    int getXFkCompetitionPhase() const;
    const std::string& getXFkCompetitionPhase_str() const;
    int getXFkTeamAway() const;
    const std::string& getXFkTeamAway_str() const;
    CDate getDMatch() const;
    const std::string& getDMatch_str() const;
    int getXMatch() const;
    const std::string& getXMatch_str() const;
    bool getLPlayed() const;
    const std::string& getLPlayed_str() const;
    int getXFkTeamHome() const;
    const std::string& getXFkTeamHome_str() const;

    void setXFkCompetitionPhase(int XFkCompetitionPhase);
    void setXFkCompetitionPhase_str(const std::string &XFkCompetitionPhase);
    void setXFkTeamAway(int XFkTeamAway);
    void setXFkTeamAway_str(const std::string &XFkTeamAway);
    void setDMatch(const CDate &DMatch);
    void setDMatch_str(const std::string &DMatch);
    void setXMatch(int XMatch);
    void setXMatch_str(const std::string &XMatch);
    void setLPlayed(bool LPlayed);
    void setLPlayed_str(const std::string &LPlayed);
    void setXFkTeamHome(int XFkTeamHome);
    void setXFkTeamHome_str(const std::string &XFkTeamHome);

private:
    std::string m_XFkCompetitionPhase;
    std::string m_XFkTeamAway;
    std::string m_DMatch;
    std::string m_XMatch;
    std::string m_LPlayed;
    std::string m_XFkTeamHome;

};
#endif /*CPFMATCHES_H_*/
