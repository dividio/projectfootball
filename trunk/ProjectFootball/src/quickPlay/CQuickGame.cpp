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

#include "CQuickGame.h"
#include "../engine/CGameEngine.h"
#include "../utils/CLog.h"

CQuickGame::CQuickGame(const CPfUsers *user)
: CSinglePlayerGame(user, "[-= QUICK GAME =-]")
{
    CLog::getInstance()->debug("CQuickGame::CQuickGame");

    IPfGameStatesDAO    *gameStateDAO   = m_daoFactory->getIPfGameStatesDAO();
    IPfTeamsDAO         *teamsDAO       = m_daoFactory->getIPfTeamsDAO();

    std::vector<CPfTeams*> *teamsList = teamsDAO->findTeams();
    if( teamsList->empty() ){
        CLog::getInstance()->exception("[CQuickGame::CQuickGame] Teams list is empty");
    }
    CPfGameStates playerTeam;
    playerTeam.setSState(S_STATE_PLAYERTEAM);
    playerTeam.setSValue(teamsList->at(rand()%teamsList->size())->getXTeam_str());
    gameStateDAO->insertReg(&playerTeam);

    CPfGameStates newGameState;
    newGameState.setSState(S_STATE_NEWGAME);
    newGameState.setSValue("false");
    gameStateDAO->insertReg(&newGameState);

    teamsDAO->freeVector(teamsList);

    m_game->setSGameType(S_GAME_TYPE_QUICKPLAY);
    CSinglePlayerGame::save();
}

CQuickGame::~CQuickGame()
{
    CLog::getInstance()->debug("CQuickGame::~CQuickGame");
}

void CQuickGame::enter()
{
    CSinglePlayerGame::enter();
    nextScreen(m_simulatorScreen);
}

void CQuickGame::leave()
{
    CSinglePlayerGame::leave();

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
