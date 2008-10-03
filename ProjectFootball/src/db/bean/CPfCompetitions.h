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
*       Version: 1.18                                                         *
******************************************************************************/

#ifndef CPFCOMPETITIONS_H_
#define CPFCOMPETITIONS_H_

#include <string>

class CPfCompetitions
{
public:
    CPfCompetitions();
    CPfCompetitions(const CPfCompetitions &obj);
    virtual ~CPfCompetitions();

    const std::string& getSCompetition() const;
    const std::string& getSCompetition_str() const;
    int getXCompetition() const;
    const std::string& getXCompetition_str() const;
    int getXFkCountry() const;
    const std::string& getXFkCountry_str() const;

    void setSCompetition(const std::string &SCompetition);
    void setSCompetition_str(const std::string &SCompetition);
    void setXCompetition(int XCompetition);
    void setXCompetition_str(const std::string &XCompetition);
    void setXFkCountry(int XFkCountry);
    void setXFkCountry_str(const std::string &XFkCountry);

private:
    std::string m_SCompetition;
    std::string m_XCompetition;
    std::string m_XFkCountry;

};
#endif /*CPFCOMPETITIONS_H_*/
