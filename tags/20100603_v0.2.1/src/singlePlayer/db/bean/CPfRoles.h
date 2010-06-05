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

#ifndef CPFROLES_H_
#define CPFROLES_H_

#include <string>

class CPfRoles
{
public:
    CPfRoles();
    CPfRoles(const CPfRoles &obj);
    virtual ~CPfRoles();

    const std::string& getSShortName() const;
    const std::string& getSShortName_str() const;
    int getXRole() const;
    const std::string& getXRole_str() const;
    int getXFkDemarcation() const;
    const std::string& getXFkDemarcation_str() const;
    const std::string& getSName() const;
    const std::string& getSName_str() const;

    void setSShortName(const std::string &SShortName);
    void setSShortName_str(const std::string &SShortName);
    void setXRole(int XRole);
    void setXRole_str(const std::string &XRole);
    void setXFkDemarcation(int XFkDemarcation);
    void setXFkDemarcation_str(const std::string &XFkDemarcation);
    void setSName(const std::string &SName);
    void setSName_str(const std::string &SName);

private:
    std::string m_SShortName;
    std::string m_XRole;
    std::string m_XFkDemarcation;
    std::string m_SName;

};
#endif /*CPFROLES_H_*/
