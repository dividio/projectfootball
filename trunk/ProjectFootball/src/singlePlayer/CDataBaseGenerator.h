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
******************************************************************************/


#ifndef CSEASONGENERATOR_H_
#define CSEASONGENERATOR_H_

#include <list>


//Forward declarations
class CDate;
class IDAOFactory;
class CPfCompetitions;
class CPfTeams;
class CPfTeamPlayers;

class CSeasonGenerator
{
public:
    CSeasonGenerator(IDAOFactory *daoFactory);
    virtual ~CSeasonGenerator();

    void generateDataBase();
    void generateCompetitionMatches(CPfCompetitions *competition, CDate date);


private:
    IDAOFactory *m_daoFactory;
    int          m_numPlayers;

    void generateMatches(std::list<CPfTeams*>* homeList, std::list<CPfTeams*>* awayList, int XCompetitionPhase, const CDate &date);
    void generateTeamPlayers();
    void generatePlayer(CPfTeams *team, int lineUpOrder);
    void generateRandomPlayer(CPfTeamPlayers &player);
};

#endif /*CSEASONGENERATOR_H_*/
