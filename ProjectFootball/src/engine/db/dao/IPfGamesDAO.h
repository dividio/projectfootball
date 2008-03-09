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
*       Version: 1.11                                                          *
******************************************************************************/

#ifndef IPFGAMESDAO_H_
#define IPFGAMESDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfGames.h"

class IPfGamesDAO
{
public:
    IPfGamesDAO(){}
    virtual ~IPfGamesDAO(){}

    virtual bool deleteReg(CPfGames *reg) =0;
    virtual bool insertReg(CPfGames *reg) =0;
    virtual bool updateReg(CPfGames *reg) =0;

    virtual void freeVector(std::vector<CPfGames*>* vector) =0;

    virtual std::vector<CPfGames*>* findByXFkUser(int XFkUser) =0;
    virtual std::vector<CPfGames*>* findByXFkUser(const std::string &XFkUser) =0;
    virtual CPfGames* findByXGame(int XGame) =0;
    virtual CPfGames* findByXGame(const std::string &XGame) =0;

};
#endif /*IPFGAMESDAO_H_*/
