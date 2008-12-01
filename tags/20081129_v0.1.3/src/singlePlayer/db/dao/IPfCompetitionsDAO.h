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

#ifndef IPFCOMPETITIONSDAO_H_
#define IPFCOMPETITIONSDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfCompetitions.h"

class IPfCompetitionsDAO
{
public:
    IPfCompetitionsDAO(){}
    virtual ~IPfCompetitionsDAO(){}

    virtual bool deleteReg(CPfCompetitions *reg) =0;
    virtual bool insertReg(CPfCompetitions *reg) =0;
    virtual bool updateReg(CPfCompetitions *reg) =0;

    virtual void freeVector(std::vector<CPfCompetitions*>* vector) =0;

    virtual std::vector<CPfCompetitions*>*  findCompetitions() =0;
    virtual CPfCompetitions* findByXCompetition(int XCompetition) =0;
    virtual CPfCompetitions* findByXCompetition(const std::string &XCompetition) =0;
    virtual std::vector<CPfCompetitions*>* findByXFkCountry(int XFkCountry) =0;
    virtual std::vector<CPfCompetitions*>* findByXFkCountry(const std::string &XFkCountry) =0;

};
#endif /*IPFCOMPETITIONSDAO_H_*/