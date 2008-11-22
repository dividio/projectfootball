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


#include <vector>
#include <list>

#include "CDataGenerator.h"

#include "db/bean/CPfTeams.h"
#include "db/bean/CPfCompetitions.h"
#include "db/bean/CPfCompetitionPhases.h"
#include "../utils/CDate.h"

CDataGenerator::CDataGenerator(IDAOFactory *daoFactory)
{
    m_daoFactory = daoFactory;
}

CDataGenerator::~CDataGenerator()
{
}

void CDataGenerator::generateDataBase()
{
    m_daoFactory->beginTransaction();

    m_daoFactory->executeScriptFile("data/database/scripts/tables.sql");
    m_daoFactory->executeScriptFile("data/database/scripts/view_ranking.sql");
    m_daoFactory->executeScriptFile("data/database/scripts/indexes.sql");
    m_daoFactory->executeScriptFile("data/database/scripts/inserts_gameoptions.sql");
    m_daoFactory->executeScriptFile("data/database/scripts/inserts_countries.sql");
    m_daoFactory->executeScriptFile("data/database/scripts/inserts_teams.sql");
    m_daoFactory->executeScriptFile("data/database/scripts/inserts_teamplayers.sql");
    m_daoFactory->executeScriptFile("data/database/scripts/inserts_competitions.sql");
    m_daoFactory->executeScriptFile("data/database/scripts/inserts_registeredteams.sql");

    //Matches generation
    std::vector<CPfCompetitions*> *competitions = m_daoFactory->getIPfCompetitionsDAO()->findCompetitions();
    std::vector<CPfCompetitions*>::iterator it;
    CDate date(31, 8, 2008, 17, 0, 0); // TODO: Remove magical numbers

    for(it = competitions->begin(); it != competitions->end(); it++) {
        generateCompetitionMatches((*it), date);
    }

    m_daoFactory->commit();
    m_daoFactory->getIPfCompetitionsDAO()->freeVector(competitions);
}

void CDataGenerator::generateCompetitionMatches(CPfCompetitions *competition, CDate date)
{
    std::vector<CPfTeams*>              *teams = m_daoFactory->getIPfTeamsDAO()->findTeamsByXCompetition(competition->getXCompetition());
    std::vector<CPfCompetitionPhases*>  *phases = m_daoFactory->getIPfCompetitionPhasesDAO()->findByXFkCompetition(competition->getXCompetition_str());
    int numTeams = teams->size();
    int numPhases = phases->size();
    int returnOffset = numPhases/2;
    CDate returnDate = date;
    returnDate += (7*returnOffset);

    std::list<CPfTeams*> *homeList = new std::list<CPfTeams*>();
    std::list<CPfTeams*> *awayList = new std::list<CPfTeams*>();
    std::list<CPfTeams*> *auxList;

    int count;
    std::vector<CPfTeams*>::iterator it;
    for(count = 0, it = teams->begin(); it!=teams->end(); count++, it++) {
        if(count<numTeams/2) {
            homeList->push_back((*it));
        } else {
            awayList->push_back((*it));
        }
    }

    generateMatches(homeList, awayList, phases->operator[](0)->getXCompetitionPhase(), date);
    generateMatches(awayList, homeList, phases->operator[](returnOffset)->getXCompetitionPhase(), returnDate);
    for(count=1; count < numPhases/2; count++) {
        date += 7;
        returnDate += 7;

        if(count % 2 != 0) {
            auxList = homeList;
            homeList = awayList;
            awayList = auxList;

            CPfTeams* auxTeam = awayList->back();
            awayList->pop_back();
            awayList->push_front(auxTeam);
        } else {
            auxList = homeList;
            homeList = awayList;
            awayList = auxList;

            CPfTeams* homeFront = homeList->front();
            homeList->pop_front();
            CPfTeams* awayFront = awayList->front();
            awayList->pop_front();
            CPfTeams* homeBack = homeList->back();
            homeList->pop_back();

            homeList->push_back(homeFront);
            homeList->push_front(awayFront);
            awayList->push_back(homeBack);
        }

        generateMatches(homeList, awayList, phases->operator[](count)->getXCompetitionPhase(), date);
        generateMatches(awayList, homeList, phases->operator[](count + returnOffset)->getXCompetitionPhase(), returnDate);
    }

    delete awayList;
    delete homeList;
    m_daoFactory->getIPfCompetitionPhasesDAO()->freeVector(phases);
    m_daoFactory->getIPfTeamsDAO()->freeVector(teams);

}

void CDataGenerator::generateMatches(std::list<CPfTeams*>* homeList, std::list<CPfTeams*>* awayList, int XCompetitionPhase, const CDate &date)
{
    CPfMatches match;
    IPfMatchesDAO *matchesDAO= m_daoFactory->getIPfMatchesDAO();
    std::list<CPfTeams*>::iterator itHome;
    std::list<CPfTeams*>::iterator itAway;
    for(itHome = homeList->begin(), itAway = awayList->begin(); itHome != homeList->end(); itHome++, itAway++) {
        CPfTeams *homeTeam = (*itHome);
        CPfTeams *awayTeam = (*itAway);

        match.setDMatch(date);
        match.setLPlayed(false);
        match.setXFkCompetitionPhase(XCompetitionPhase);
        match.setXFkTeamAway(awayTeam->getXTeam());
        match.setXFkTeamHome(homeTeam->getXTeam());
        matchesDAO->insertReg(&match);
    }
}

