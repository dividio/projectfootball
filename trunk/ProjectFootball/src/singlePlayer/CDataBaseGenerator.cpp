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

#include "CDataBaseGenerator.h"

#include <vector>
#include <sstream>
#include <stdlib.h>

#include "db/dao/factory/IDAOFactory.h"
#include "db/bean/CPfTeams.h"
#include "db/bean/CPfTeamPlayers.h"
#include "db/bean/CPfCompetitions.h"
#include "db/bean/CPfCompetitionPhases.h"

#include "../utils/CDate.h"

int CDataBaseGenerator::m_numPlayers = 1;
int CDataBaseGenerator::m_numCoaches = 1;

CDataBaseGenerator::CDataBaseGenerator()
{
}

CDataBaseGenerator::~CDataBaseGenerator()
{
}

void CDataBaseGenerator::generateDataBase(IDAOFactory *daoFactory)
{
    m_numPlayers = 1;
    m_numCoaches = 1;

	daoFactory->beginTransaction();

	// Database scripts parsing
	daoFactory->executeScriptFile("data/database/scripts/singleplayer/tables.sql");
	daoFactory->executeScriptFile("data/database/scripts/singleplayer/indexes.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_gameoptions.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_countries.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_stadiums.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_teams.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_roles.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_formations.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_coaches.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_teamplayers.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_roles_by_team_players.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_competitions.sql");
    daoFactory->executeScriptFile("data/database/scripts/singleplayer/inserts_seasons.sql");


    // Random coaches and players generation
    generateCoaches(daoFactory);
    generateTeamPlayers(daoFactory);

    daoFactory->commit();
}

void CDataBaseGenerator::generateTeamPlayers(IDAOFactory *daoFactory)
{
    std::vector<CPfTeams*>  *teams = daoFactory->getIPfTeamsDAO()->findAll();

    std::vector<CPfTeams*>::iterator it;
    CDate currentDate;
    for(it = teams->begin(); it != teams->end(); it++) {
        std::vector<CPfTeamPlayers*> *teamPlayers = daoFactory->getIPfTeamPlayersDAO()->findActiveByXFkTeam((*it)->getXTeam_str(), currentDate.getTimestamp());
        int contractedPlayers = teamPlayers->size();
        int neededPlayers = 17 - contractedPlayers; //TODO define MAXPLAYERS
        for( int i = 0; i < neededPlayers; i++) {
            generatePlayer(daoFactory, (*it), contractedPlayers+i+1);
        }

        daoFactory->getIPfTeamPlayersDAO()->freeVector(teamPlayers);
    }


    daoFactory->getIPfTeamsDAO()->freeVector(teams);
}

void CDataBaseGenerator::generatePlayer(IDAOFactory *daoFactory, CPfTeams *team, int lineUpOrder)
{
    //Generate player
    CPfTeamPlayers player;
    IPfTeamPlayersDAO *playersDAO= daoFactory->getIPfTeamPlayersDAO();
    generateRandomPlayer(player, lineUpOrder);
    player.setXFkCountry_str(team->getXFkCountry_str());
    playersDAO->insertReg(&player);


    //Generate player contract
    CPfTeamPlayerContracts contract;
    CDate date(15, 8, 2007, 17, 0, 0); // TODO: Remove magical numbers
    IPfTeamPlayerContractsDAO *contractsDAO= daoFactory->getIPfTeamPlayerContractsDAO();

    contract.setXFkTeam_str(team->getXTeam_str());
    contract.setXFkTeamPlayer_str(player.getXTeamPlayer_str());
    contract.setDBegin(date);
    contractsDAO->insertReg(&contract);
}

void CDataBaseGenerator::generateRandomPlayer(CPfTeamPlayers &player, int lineUpOrder)
{
    std::ostringstream stream;
    stream << "Team Player " << m_numPlayers; // TODO Generate real names
    player.setSName(stream.str());
    stream.str("");
    stream << "TP" << m_numPlayers++;
    player.setSShortName(stream.str());
    player.setNLineupOrder(lineUpOrder);

    player.setXFkCountry_str("1");
    player.setNKickPower((rand()%49)+50);
    player.setNSpeed((rand()%49)+50);
    player.setNWeight(78);
    player.setNHeight(180);
    player.setDBirthday_str("1985-01-16 10:30:09");
    player.setSPhoto("p_unknown");
    player.setNFortitude(50);
    player.setNMoral(90);
}

void CDataBaseGenerator::generateCoaches(IDAOFactory *daoFactory)
{
    std::vector<CPfTeams*>  *teams = daoFactory->getIPfTeamsDAO()->findAll();

    std::vector<CPfTeams*>::iterator it;
    CDate currentDate;
    for(it = teams->begin(); it != teams->end(); it++) {
        CPfCoachContracts *contract = daoFactory->getIPfCoachContractsDAO()->findActiveByXFkTeam((*it)->getXTeam_str(), currentDate.getTimestamp());
        if(contract->getXFkCoach() == 0) {
            generateCoach(daoFactory, (*it));
        }

        delete contract;
    }

    daoFactory->getIPfTeamsDAO()->freeVector(teams);
}

void CDataBaseGenerator::generateCoach(IDAOFactory *daoFactory, CPfTeams *team)
{
    //Generate coach
    CPfCoaches coach;
    IPfCoachesDAO *coachesDAO= daoFactory->getIPfCoachesDAO();
    std::ostringstream stream;
    stream << "Coach " << m_numCoaches; // TODO Generate real names
    coach.setSName(stream.str());
    stream.str("");
    stream << "CH" << m_numCoaches++;
    coach.setSShortName(stream.str());
    coach.setDBirthday_str("1985-01-16 10:30:09");
    coach.setSPhoto("p_unknown");
    coach.setXFkCountry_str(team->getXFkCountry_str());
    coach.setXFkFormationSelected(1);
    coachesDAO->insertReg(&coach);


    //Generate coach contract
    CPfCoachContracts contract;
    CDate date(15, 8, 2007, 17, 0, 0); // TODO: Remove magical numbers
    IPfCoachContractsDAO *contractsDAO= daoFactory->getIPfCoachContractsDAO();

    contract.setXFkTeam_str(team->getXTeam_str());
    contract.setXFkCoach_str(coach.getXCoach_str());
    contract.setDBegin(date);
    contractsDAO->insertReg(&contract);
}
