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

#ifndef IPFPHASEROUNDSDAO_H_
#define IPFPHASEROUNDSDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfPhaseRounds.h"

class IPfPhaseRoundsDAO
{
public:
    IPfPhaseRoundsDAO(){}
    virtual ~IPfPhaseRoundsDAO(){}

    virtual bool deleteReg(CPfPhaseRounds *reg) =0;
    virtual bool insertReg(CPfPhaseRounds *reg) =0;
    virtual bool updateReg(CPfPhaseRounds *reg) =0;

    virtual void freeVector(std::vector<CPfPhaseRounds*>* vector) =0;

    virtual std::vector<CPfPhaseRounds*>* findByXFkCompetitionPhase(int XFkCompetitionPhase) =0;
    virtual std::vector<CPfPhaseRounds*>* findByXFkCompetitionPhase(const std::string &XFkCompetitionPhase) =0;
    virtual CPfPhaseRounds* findByXPhaseRound(int XPhaseRound) =0;
    virtual CPfPhaseRounds* findByXPhaseRound(const std::string &XPhaseRound) =0;
    virtual std::vector<CPfPhaseRounds*>* findByXFkCompetition(int XFkCompetition) =0;
    virtual std::vector<CPfPhaseRounds*>* findByXFkCompetition(const std::string &XFkCompetition) =0;
    virtual CPfPhaseRounds* findLastPhaseRound(int XFkCompetition, int XSeason) =0;
    virtual CPfPhaseRounds* findLastPhaseRound(const std::string &XFkCompetition, const std::string &XSeason) =0;

};
#endif /*IPFPHASEROUNDSDAO_H_*/