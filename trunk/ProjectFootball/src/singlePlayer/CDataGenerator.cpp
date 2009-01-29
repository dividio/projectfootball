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

#include "CDataGenerator.h"

#include <vector>
#include <sstream>
#include <stdlib.h>

#include "db/dao/factory/IDAOFactory.h"
#include "db/bean/CPfTeams.h"
#include "db/bean/CPfTeamPlayers.h"
#include "db/bean/CPfCompetitions.h"
#include "db/bean/CPfCompetitionPhases.h"
#include "../utils/CDate.h"

CDataGenerator::CDataGenerator(IDAOFactory *daoFactory)
{
    m_daoFactory = daoFactory;
    m_numPlayers = 1;
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


    //Players Generation
    generateTeamPlayers();

    //Matches Generation
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

void CDataGenerator::generateTeamPlayers()
{
    std::vector<CPfTeams*>  *teams = m_daoFactory->getIPfTeamsDAO()->findTeams();

    std::vector<CPfTeams*>::iterator it;
    for(it = teams->begin(); it != teams->end(); it++) {
        std::vector<CPfTeamPlayers*> *teamPlayers = m_daoFactory->getIPfTeamPlayersDAO()->findActiveByXFkTeam((*it)->getXTeam_str());
        int contractedPlayers = teamPlayers->size();
        int neededPlayers = 20 - contractedPlayers; //TODO define MAXPLAYERS
        for( int i = 0; i < neededPlayers; i++) {
            generatePlayer((*it), contractedPlayers+i+1);
        }

        m_daoFactory->getIPfTeamPlayersDAO()->freeVector(teamPlayers);
    }


    m_daoFactory->getIPfTeamsDAO()->freeVector(teams);
}

void CDataGenerator::generatePlayer(CPfTeams *team, int lineUpOrder)
{
    //Generate player
    CPfTeamPlayers player;
    IPfTeamPlayersDAO *playersDAO= m_daoFactory->getIPfTeamPlayersDAO();
    generateRandomPlayer(player);
    player.setXFkCountry_str(team->getXFkCountry_str());
    playersDAO->insertReg(&player);


    //Generate player contract
    CPfTeamPlayerContracts contract;
    CDate date(15, 8, 2008, 17, 0, 0); // TODO: Remove magical numbers
    IPfTeamPlayerContractsDAO *contractsDAO= m_daoFactory->getIPfTeamPlayerContractsDAO();

    contract.setXFkTeam_str(team->getXTeam_str());
    contract.setXFkTeamPlayer_str(player.getXTeamPlayer_str());
    contract.setNLineupOrder(lineUpOrder);
    contract.setDBegin(date);
    contractsDAO->insertReg(&contract);
}

void CDataGenerator::generateRandomPlayer(CPfTeamPlayers &player)
{
    std::ostringstream stream;
    stream << "Team Player " << m_numPlayers; // TODO Generate real names
    player.setSName(stream.str());
    stream.str("");
    stream << "TP" << m_numPlayers++;
    player.setSShortName(stream.str());

    player.setXFkCountry_str("1");
    player.setNKickPower((rand()%49)+50);
    player.setNVelocity((rand()%49)+50);
}
