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

#include <stdio.h>

#include "CStateQuickPlay.h"
#include "CStateMonitor.h"
#include "../db/sqlite/dao/factory/CDAOFactorySQLite.h"
#include "../engine/CGameEngine.h"
#include "../utils/CLog.h"

CStateQuickPlay::CStateQuickPlay()
    :CState()
{
    CLog::getInstance()->debug("CStateQuickPlay()");
}

CStateQuickPlay::~CStateQuickPlay()
{
    CLog::getInstance()->debug("~CStateQuickPlay()");
}

CStateQuickPlay* CStateQuickPlay::getInstance()
{
    static CStateQuickPlay instance;
    return &instance;
}

void CStateQuickPlay::enter()
{
    newQuickGame();
    CStateMonitor::getInstance()->enter();
}

void CStateQuickPlay::forcedLeave()
{
    CStateMonitor::getInstance()->forcedLeave();
    CGameEngine::getInstance()->unloadCurrentGame();
    deleteQuickGames();
}

bool CStateQuickPlay::leave()
{
    if( CStateMonitor::getInstance()->leave() ){
        CGameEngine::getInstance()->unloadCurrentGame();
        deleteQuickGames();
        return true;
    }else{
        return false;
    }
}
void CStateQuickPlay::update()
{
    CStateMonitor::getInstance()->update();
}

void CStateQuickPlay::newQuickGame()
{
    // To create a new quickGame, first create a new game
    IMasterDAOFactory *masterDatabase = CGameEngine::getInstance()->getCMasterDAOFactory();
    const CPfUsers *user = CGameEngine::getInstance()->getCurrentUser();

    if( user==NULL || user->getXUser()==0 ){
        CLog::getInstance()->exception("[CStateQuickPlay::newQuickGame] User not defined");
    }

    const char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string filename = "data/database/savedgames/";

    srand(time(NULL));
    for( int i=0; i<8; i++ ){
        filename += str[rand()%52];
    }
    filename += ".sql3";

    std::string gameName = "QUICK_PLAY - ";
    while( gameName.length()<50 ){
        gameName += str[rand()%52];
    }

    CDate nowDate;
    CPfGames game;
    game.setDLastSaved(nowDate);
    game.setSDriverName("SQLite");
    game.setSConnectionString(filename);
    game.setSGameName(gameName);
    game.setSGameType(S_GAME_TYPE_QUICKPLAY);
    game.setXFkUser(user->getXUser());
    masterDatabase->getIPfGamesDAO()->insertReg(&game);

    CDAOFactorySQLite *daoFactory = new CDAOFactorySQLite(filename);
    daoFactory->beginTransaction();
    daoFactory->executeScriptFile("data/database/scripts/tables.sql");
    daoFactory->executeScriptFile("data/database/scripts/view_ranking.sql");
    daoFactory->executeScriptFile("data/database/scripts/indexes.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_countries.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_teams.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_teamplayers.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_competitions.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_registeredteams.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_matches.sql");
    daoFactory->executeScriptFile("data/database/scripts/inserts_gameoptions.sql");
    daoFactory->commit();

    IPfGameStatesDAO    *gameStateDAO   = daoFactory->getIPfGameStatesDAO();
    IPfTeamsDAO         *teamsDAO       = daoFactory->getIPfTeamsDAO();

    std::vector<CPfTeams*> *teamsList = teamsDAO->findTeams();
    if( teamsList->empty() ){
        CLog::getInstance()->exception("[CStateQuickPlay::newQuickGame] Teams list is empty");
    }
    CPfGameStates playerTeam;
    playerTeam.setSState(S_STATE_PLAYERTEAM);
    playerTeam.setSValue(teamsList->operator[](rand()%20)->getXTeam_str());
    gameStateDAO->insertReg(&playerTeam);

    CPfGameStates newGameState;
    newGameState.setSState(S_STATE_NEWGAME);
    newGameState.setSValue("false");
    gameStateDAO->insertReg(&newGameState);

    teamsDAO->freeVector(teamsList);
    delete daoFactory;

    // Second, test that this new game is correctly created
    std::vector<CPfGames*> *gamesList = masterDatabase->getIPfGamesDAO()->findBySGameName(gameName);
    if( gamesList->size()!=1){
        CLog::getInstance()->exception("[CStateQuickPlay::newQuickGame] New game isn't correctly created [gamesList->size():%d]", gamesList->size());
    }

    // Third, load the quick game
    CGameEngine::getInstance()->loadGame(gamesList->operator[](0)->getXGame());
    masterDatabase->getIPfGamesDAO()->freeVector(gamesList);
}

void CStateQuickPlay::deleteQuickGames()
{
    IPfGamesDAO                         *gamesDAO   = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    std::vector<CPfGames*>              *gamesList  = gamesDAO->findBySGameType(S_GAME_TYPE_QUICKPLAY);
    std::vector<CPfGames*>::iterator    it;
    for( it=gamesList->begin(); it!=gamesList->end(); it++ ){
        CPfGames *game = (*it);
        if( game->getSDriverName()=="SQLite" ){
            remove(game->getSConnectionString().c_str());
        }
        gamesDAO->deleteReg(game);
    }
    gamesDAO->freeVector(gamesList);
}
