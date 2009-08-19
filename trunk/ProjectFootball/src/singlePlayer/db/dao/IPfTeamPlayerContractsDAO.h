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

#ifndef IPFTEAMPLAYERCONTRACTSDAO_H_
#define IPFTEAMPLAYERCONTRACTSDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfTeamPlayerContracts.h"

class IPfTeamPlayerContractsDAO
{
public:
    IPfTeamPlayerContractsDAO(){}
    virtual ~IPfTeamPlayerContractsDAO(){}

    virtual bool deleteReg(CPfTeamPlayerContracts *reg) =0;
    virtual bool insertReg(CPfTeamPlayerContracts *reg) =0;
    virtual bool updateReg(CPfTeamPlayerContracts *reg) =0;

    virtual void freeVector(std::vector<CPfTeamPlayerContracts*>* vector) =0;

    virtual std::vector<CPfTeamPlayerContracts*>* findByXFkTeamPlayer(int XFkTeamPlayer) =0;
    virtual std::vector<CPfTeamPlayerContracts*>* findByXFkTeamPlayer(const std::string &XFkTeamPlayer) =0;
    virtual CPfTeamPlayerContracts* findByXTeamPlayerContract(int XTeamPlayerContract) =0;
    virtual CPfTeamPlayerContracts* findByXTeamPlayerContract(const std::string &XTeamPlayerContract) =0;
    virtual std::vector<CPfTeamPlayerContracts*>* findByXFkTeam(int XFkTeam) =0;
    virtual std::vector<CPfTeamPlayerContracts*>* findByXFkTeam(const std::string &XFkTeam) =0;
    virtual CPfTeamPlayerContracts* findActiveByXFkTeamAndXFkTeamPlayer(int XFkTeam, int XFkTeamPlayer) =0;
    virtual CPfTeamPlayerContracts* findActiveByXFkTeamAndXFkTeamPlayer(const std::string &XFkTeam, const std::string &XFkTeamPlayer) =0;
    virtual CPfTeamPlayerContracts* findActiveByXFkTeamPlayer(int XFkTeamPlayer) =0;
    virtual CPfTeamPlayerContracts* findActiveByXFkTeamPlayer(const std::string &XFkTeamPlayer) =0;

};
#endif /*IPFTEAMPLAYERCONTRACTSDAO_H_*/
