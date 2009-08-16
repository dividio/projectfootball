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

#ifndef CPFSEASONS_H_
#define CPFSEASONS_H_

#include <string>

class CPfSeasons
{
public:
    CPfSeasons();
    CPfSeasons(const CPfSeasons &obj);
    virtual ~CPfSeasons();

    int getXSeason() const;
    const std::string& getXSeason_str() const;
    int getNYear() const;
    const std::string& getNYear_str() const;
    const std::string& getSSeason() const;
    const std::string& getSSeason_str() const;

    void setXSeason(int XSeason);
    void setXSeason_str(const std::string &XSeason);
    void setNYear(int NYear);
    void setNYear_str(const std::string &NYear);
    void setSSeason(const std::string &SSeason);
    void setSSeason_str(const std::string &SSeason);

private:
    std::string m_XSeason;
    std::string m_NYear;
    std::string m_SSeason;

};
#endif /*CPFSEASONS_H_*/
