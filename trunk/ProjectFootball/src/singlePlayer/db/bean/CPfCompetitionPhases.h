/******************************************************************************
* Copyright (C) 2010 - Ikaro Games   www.ikarogames.com                       *
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

#ifndef CPFCOMPETITIONPHASES_H_
#define CPFCOMPETITIONPHASES_H_

#include <string>

class CPfCompetitionPhases
{
public:
    CPfCompetitionPhases();
    CPfCompetitionPhases(const CPfCompetitionPhases &obj);
    virtual ~CPfCompetitionPhases();

    int getNNumberTeams() const;
    const std::string& getNNumberTeams_str() const;
    const std::string& getSCompetitionPhase() const;
    const std::string& getSCompetitionPhase_str() const;
    int getXFkCompetition() const;
    const std::string& getXFkCompetition_str() const;
    int getXCompetitionPhase() const;
    const std::string& getXCompetitionPhase_str() const;
    int getNOrder() const;
    const std::string& getNOrder_str() const;
    int getXFkPhaseType() const;
    const std::string& getXFkPhaseType_str() const;

    void setNNumberTeams(int NNumberTeams);
    void setNNumberTeams_str(const std::string &NNumberTeams);
    void setSCompetitionPhase(const std::string &SCompetitionPhase);
    void setSCompetitionPhase_str(const std::string &SCompetitionPhase);
    void setXFkCompetition(int XFkCompetition);
    void setXFkCompetition_str(const std::string &XFkCompetition);
    void setXCompetitionPhase(int XCompetitionPhase);
    void setXCompetitionPhase_str(const std::string &XCompetitionPhase);
    void setNOrder(int NOrder);
    void setNOrder_str(const std::string &NOrder);
    void setXFkPhaseType(int XFkPhaseType);
    void setXFkPhaseType_str(const std::string &XFkPhaseType);

private:
    std::string m_NNumberTeams;
    std::string m_SCompetitionPhase;
    std::string m_XFkCompetition;
    std::string m_XCompetitionPhase;
    std::string m_NOrder;
    std::string m_XFkPhaseType;

};
#endif /*CPFCOMPETITIONPHASES_H_*/
