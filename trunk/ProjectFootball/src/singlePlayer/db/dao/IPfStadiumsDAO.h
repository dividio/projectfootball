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

#ifndef IPFSTADIUMSDAO_H_
#define IPFSTADIUMSDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfStadiums.h"

class IPfStadiumsDAO
{
public:
    IPfStadiumsDAO(){}
    virtual ~IPfStadiumsDAO(){}

    virtual bool deleteReg(CPfStadiums *reg) =0;
    virtual bool insertReg(CPfStadiums *reg) =0;
    virtual bool updateReg(CPfStadiums *reg) =0;

    virtual void freeVector(std::vector<CPfStadiums*>* vector) =0;

    virtual CPfStadiums* findByXStadium(int XStadium) =0;
    virtual CPfStadiums* findByXStadium(const std::string &XStadium) =0;
    virtual CPfStadiums* findByXFkCountry(int XFkCountry) =0;
    virtual CPfStadiums* findByXFkCountry(const std::string &XFkCountry) =0;
	virtual std::vector<CPfStadiums*>* findByName(const std::string &name) = 0;

};
#endif /*IPFSTADIUMSDAO_H_*/
