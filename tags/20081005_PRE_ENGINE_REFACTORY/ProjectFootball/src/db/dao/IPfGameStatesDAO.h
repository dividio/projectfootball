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
*       Version: 1.10                                                          *
******************************************************************************/

#ifndef IPFGAMESTATESDAO_H_
#define IPFGAMESTATESDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfGameStates.h"

#define S_STATE_NEWGAME             "NEW_GAME"
#define S_STATE_PLAYERTEAM          "PLAYER_TEAM"

class IPfGameStatesDAO
{
public:
    IPfGameStatesDAO(){}
    virtual ~IPfGameStatesDAO(){}

    virtual bool deleteReg(CPfGameStates *reg) =0;
    virtual bool insertReg(CPfGameStates *reg) =0;
    virtual bool updateReg(CPfGameStates *reg) =0;

    virtual void freeVector(std::vector<CPfGameStates*>* vector) =0;

    virtual CPfGameStates* findByXState(int XState) =0;
    virtual CPfGameStates* findByXState(const std::string &XState) =0;
    virtual CPfGameStates* findBySState(const std::string &SState) =0;

};
#endif /*IPFGAMESTATESDAO_H_*/
