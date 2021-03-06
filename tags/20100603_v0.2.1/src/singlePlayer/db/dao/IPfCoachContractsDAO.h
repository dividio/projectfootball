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

#ifndef IPFCOACHCONTRACTSDAO_H_
#define IPFCOACHCONTRACTSDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfCoachContracts.h"

class IPfCoachContractsDAO
{
public:
    IPfCoachContractsDAO(){}
    virtual ~IPfCoachContractsDAO(){}

    virtual bool deleteReg(CPfCoachContracts *reg) =0;
    virtual bool insertReg(CPfCoachContracts *reg) =0;
    virtual bool updateReg(CPfCoachContracts *reg) =0;

    virtual void freeVector(std::vector<CPfCoachContracts*>* vector) =0;

    virtual CPfCoachContracts* findByXCoachContract(int XCoachContract) =0;
    virtual CPfCoachContracts* findByXCoachContract(const std::string &XCoachContract) =0;
    virtual CPfCoachContracts* findByXFkCoach(int XFkCoach) =0;
    virtual CPfCoachContracts* findByXFkCoach(const std::string &XFkCoach) =0;
    virtual CPfCoachContracts* findActiveByXFkTeam(int XFkTeam, const std::string &timestamp) =0;
    virtual CPfCoachContracts* findActiveByXFkTeam(const std::string &XFkTeam, const std::string &timestamp) =0;
    virtual std::vector<CPfCoachContracts*>* findByXFkCoachAndXSeason(int XFkCoach, int XSeason) =0;
    virtual std::vector<CPfCoachContracts*>* findByXFkCoachAndXSeason(const std::string &XFkCoach, const std::string &XSeason) =0;

};
#endif /*IPFCOACHCONTRACTSDAO_H_*/
