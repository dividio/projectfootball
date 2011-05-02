/******************************************************************************
* Copyright (C) 2010 - Ikaro Games   www.ikarogames.com                       *
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

#ifndef IPFPHASETYPESDAO_H_
#define IPFPHASETYPESDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfPhaseTypes.h"

class IPfPhaseTypesDAO
{
public:
    IPfPhaseTypesDAO(){}
    virtual ~IPfPhaseTypesDAO(){}

    virtual bool deleteReg(CPfPhaseTypes *reg) =0;
    virtual bool insertReg(CPfPhaseTypes *reg) =0;
    virtual bool updateReg(CPfPhaseTypes *reg) =0;

    virtual void freeVector(std::vector<CPfPhaseTypes*>* vector) =0;

    virtual CPfPhaseTypes* findByXPhaseType(int XPhaseType) =0;
    virtual CPfPhaseTypes* findByXPhaseType(const std::string &XPhaseType) =0;

};
#endif /*IPFPHASETYPESDAO_H_*/