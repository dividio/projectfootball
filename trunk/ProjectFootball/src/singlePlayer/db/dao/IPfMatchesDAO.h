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
*       Version: 1.20                                                         *
******************************************************************************/

#ifndef IPFMATCHESDAO_H_
#define IPFMATCHESDAO_H_

#include <string>
#include <vector>

#include "../bean/CPfMatches.h"

class IPfMatchesDAO
{
public:
    IPfMatchesDAO(){}
    virtual ~IPfMatchesDAO(){}

    virtual bool deleteReg(CPfMatches *reg) =0;
    virtual bool insertReg(CPfMatches *reg) =0;
    virtual bool updateReg(CPfMatches *reg) =0;

    virtual void freeVector(std::vector<CPfMatches*>* vector) =0;

    virtual std::vector<CPfMatches*>* findByXFkCompetitionPhase(int XFkCompetitionPhase) =0;
    virtual std::vector<CPfMatches*>* findByXFkCompetitionPhase(const std::string &XFkCompetitionPhase) =0;
    virtual CPfMatches* findByXFkTeamHome(int XFkTeamHome) =0;
    virtual CPfMatches* findByXFkTeamHome(const std::string &XFkTeamHome) =0;
    virtual CPfMatches* findByXMatch(int XMatch) =0;
    virtual CPfMatches* findByXMatch(const std::string &XMatch) =0;
    virtual CPfMatches* findByXFkTeamAway(int XFkTeamAway) =0;
    virtual CPfMatches* findByXFkTeamAway(const std::string &XFkTeamAway) =0;
    virtual std::vector<CPfMatches*>* findMatches() =0;
    virtual std::vector<CPfMatches*>* findMatchesNotPlayed() =0;
    virtual CPfMatches* findNextTeamMatch(int XTeam) =0;
    virtual CPfMatches* findNextTeamMatch(const std::string &XTeam) =0;
    virtual CPfMatches* findLastTeamMatch(int XTeam) =0;
    virtual CPfMatches* findLastTeamMatch(const std::string &XTeam) =0;

};
#endif /*IPFMATCHESDAO_H_*/
