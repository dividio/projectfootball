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
*       Version: 1.4                                                          *
******************************************************************************/

#ifndef CPFPAISES_H_
#define CPFPAISES_H_

#include <string>

class CPfPaises
{
public:
    CPfPaises();
    virtual ~CPfPaises();

    const std::string* getSPais();
    int getXPais_int();
    const std::string* getXPais();
    const std::string* getSRutaBandera();

    void setSPais(const std::string SPais);
    void setXPais(int XPais);
    void setXPais(const std::string XPais);
    void setSRutaBandera(const std::string SRutaBandera);

private:
    std::string m_SPais;
    std::string m_XPais;
    std::string m_SRutaBandera;

};
#endif /*CPFPAISES_H_*/
