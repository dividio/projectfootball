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

#ifndef CPFGAMEOPTIONS_H_
#define CPFGAMEOPTIONS_H_

#include <string>

class CPfGameOptions
{
public:
    CPfGameOptions();
    CPfGameOptions(const CPfGameOptions &obj);
    virtual ~CPfGameOptions();

    const std::string& getSCategory();
    const std::string& getSCategory_str();
    int getXOption();
    const std::string& getXOption_str();
    const std::string& getSValue();
    const std::string& getSValue_str();
    const std::string& getSAttribute();
    const std::string& getSAttribute_str();

    void setSCategory(const std::string &SCategory);
    void setSCategory_str(const std::string &SCategory);
    void setXOption(int XOption);
    void setXOption_str(const std::string &XOption);
    void setSValue(const std::string &SValue);
    void setSValue_str(const std::string &SValue);
    void setSAttribute(const std::string &SAttribute);
    void setSAttribute_str(const std::string &SAttribute);

private:
    std::string m_SCategory;
    std::string m_XOption;
    std::string m_SValue;
    std::string m_SAttribute;

};
#endif /*CPFGAMEOPTIONS_H_*/
