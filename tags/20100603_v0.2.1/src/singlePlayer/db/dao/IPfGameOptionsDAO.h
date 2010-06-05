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

#ifndef IPFGAMEOPTIONSDAO_H_
#define IPFGAMEOPTIONSDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfGameOptions.h"

class IPfGameOptionsDAO
{
public:
    IPfGameOptionsDAO(){}
    virtual ~IPfGameOptionsDAO(){}

    virtual bool deleteReg(CPfGameOptions *reg) =0;
    virtual bool insertReg(CPfGameOptions *reg) =0;
    virtual bool updateReg(CPfGameOptions *reg) =0;

    virtual void freeVector(std::vector<CPfGameOptions*>* vector) =0;

    virtual std::vector<CPfGameOptions*>* findAll() =0;
    virtual CPfGameOptions* findBySCategoryAndSAttribute(const std::string &SCategory, const std::string &SAttribute) =0;
    virtual CPfGameOptions* findByXOption(int XOption) =0;
    virtual CPfGameOptions* findByXOption(const std::string &XOption) =0;

};
#endif /*IPFGAMEOPTIONSDAO_H_*/
