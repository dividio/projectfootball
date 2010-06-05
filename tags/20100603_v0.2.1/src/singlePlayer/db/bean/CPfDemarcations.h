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

#ifndef CPFDEMARCATIONS_H_
#define CPFDEMARCATIONS_H_

#include <string>

class CPfDemarcations
{
public:
    CPfDemarcations();
    CPfDemarcations(const CPfDemarcations &obj);
    virtual ~CPfDemarcations();

    const std::string& getSShortName() const;
    const std::string& getSShortName_str() const;
    int getXDemarcation() const;
    const std::string& getXDemarcation_str() const;
    const std::string& getSName() const;
    const std::string& getSName_str() const;

    void setSShortName(const std::string &SShortName);
    void setSShortName_str(const std::string &SShortName);
    void setXDemarcation(int XDemarcation);
    void setXDemarcation_str(const std::string &XDemarcation);
    void setSName(const std::string &SName);
    void setSName_str(const std::string &SName);

private:
    std::string m_SShortName;
    std::string m_XDemarcation;
    std::string m_SName;

};
#endif /*CPFDEMARCATIONS_H_*/
