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

#ifndef CPFFORMATIONSBYCOACHES_H_
#define CPFFORMATIONSBYCOACHES_H_

#include <string>

class CPfFormationsByCoaches
{
public:
    CPfFormationsByCoaches();
    CPfFormationsByCoaches(const CPfFormationsByCoaches &obj);
    virtual ~CPfFormationsByCoaches();

    int getXFkFormation() const;
    const std::string& getXFkFormation_str() const;
    int getNSkill() const;
    const std::string& getNSkill_str() const;
    int getXFkCoach() const;
    const std::string& getXFkCoach_str() const;
    int getXFormationByCoach() const;
    const std::string& getXFormationByCoach_str() const;

    void setXFkFormation(int XFkFormation);
    void setXFkFormation_str(const std::string &XFkFormation);
    void setNSkill(int NSkill);
    void setNSkill_str(const std::string &NSkill);
    void setXFkCoach(int XFkCoach);
    void setXFkCoach_str(const std::string &XFkCoach);
    void setXFormationByCoach(int XFormationByCoach);
    void setXFormationByCoach_str(const std::string &XFormationByCoach);

private:
    std::string m_XFkFormation;
    std::string m_NSkill;
    std::string m_XFkCoach;
    std::string m_XFormationByCoach;

};
#endif /*CPFFORMATIONSBYCOACHES_H_*/
