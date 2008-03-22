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
*       Version: 1.15                                                         *
******************************************************************************/

#ifndef CPFRANKING_H_
#define CPFRANKING_H_

#include <string>

class CPfRanking
{
public:
    CPfRanking();
    CPfRanking(const CPfRanking &obj);
    virtual ~CPfRanking();

    int getNWins();
    const std::string& getNWins_str();
    int getNPlayed();
    const std::string& getNPlayed_str();
    const std::string& getSTeam();
    const std::string& getSTeam_str();
    int getNGoalsAgainst();
    const std::string& getNGoalsAgainst_str();
    int getNPoints();
    const std::string& getNPoints_str();
    int getNGoalsFor();
    const std::string& getNGoalsFor_str();
    int getNLosses();
    const std::string& getNLosses_str();
    int getNDraws();
    const std::string& getNDraws_str();

    void setNWins(int NWins);
    void setNWins_str(const std::string &NWins);
    void setNPlayed(int NPlayed);
    void setNPlayed_str(const std::string &NPlayed);
    void setSTeam(const std::string &STeam);
    void setSTeam_str(const std::string &STeam);
    void setNGoalsAgainst(int NGoalsAgainst);
    void setNGoalsAgainst_str(const std::string &NGoalsAgainst);
    void setNPoints(int NPoints);
    void setNPoints_str(const std::string &NPoints);
    void setNGoalsFor(int NGoalsFor);
    void setNGoalsFor_str(const std::string &NGoalsFor);
    void setNLosses(int NLosses);
    void setNLosses_str(const std::string &NLosses);
    void setNDraws(int NDraws);
    void setNDraws_str(const std::string &NDraws);

private:
    std::string m_NWins;
    std::string m_NPlayed;
    std::string m_STeam;
    std::string m_NGoalsAgainst;
    std::string m_NPoints;
    std::string m_NGoalsFor;
    std::string m_NLosses;
    std::string m_NDraws;

};
#endif /*CPFRANKING_H_*/
