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

#ifndef IPFSTRATEGICPOSITIONSDAO_H_
#define IPFSTRATEGICPOSITIONSDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfStrategicPositions.h"

class IPfStrategicPositionsDAO
{
public:
    IPfStrategicPositionsDAO(){}
    virtual ~IPfStrategicPositionsDAO(){}

    virtual bool deleteReg(CPfStrategicPositions *reg) =0;
    virtual bool insertReg(CPfStrategicPositions *reg) =0;
    virtual bool updateReg(CPfStrategicPositions *reg) =0;

    virtual void freeVector(std::vector<CPfStrategicPositions*>* vector) =0;

    virtual std::vector<CPfStrategicPositions*>* findByXFkFormation(int XFkFormation) =0;
    virtual std::vector<CPfStrategicPositions*>* findByXFkFormation(const std::string &XFkFormation) =0;
    virtual CPfStrategicPositions* findByXFkRole(int XFkRole) =0;
    virtual CPfStrategicPositions* findByXFkRole(const std::string &XFkRole) =0;
    virtual CPfStrategicPositions* findByXStrategicPosition(int XStrategicPosition) =0;
    virtual CPfStrategicPositions* findByXStrategicPosition(const std::string &XStrategicPosition) =0;

};
#endif /*IPFSTRATEGICPOSITIONSDAO_H_*/
