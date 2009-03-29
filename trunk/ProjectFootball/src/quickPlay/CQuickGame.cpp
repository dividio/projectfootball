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

#include "../singlePlayer/CSinglePlayerGame.h"
#include "../singlePlayer/db/dao/factory/IDAOFactory.h"
#include "../singlePlayer/option/CSinglePlayerOptionManager.h"
#include "../utils/CLog.h"


CQuickGame::CQuickGame(const CPfUsers *user)
{
    CLog::getInstance()->debug("CQuickGame::CQuickGame");
    m_game = static_cast<CSinglePlayerGame*>(CSinglePlayerGame::newGame(user, "[-= QUICK GAME =-]"));

    IPfTeamsDAO	*teamsDAO	= m_game->getIDAOFactory()->getIPfTeamsDAO();

    std::vector<CPfTeams*> *teamsList = teamsDAO->findAll();
    if( teamsList->empty() ){
        CLog::getInstance()->exception("[CQuickGame::CQuickGame] Teams list is empty");
    }

    m_game->getOptionManager()->setGamePlayerTeam(teamsList->at(rand()%teamsList->size())->getXTeam());
    m_game->getOptionManager()->setGameNew(false);

    teamsDAO->freeVector(teamsList);
}

CQuickGame::~CQuickGame()
{
    CLog::getInstance()->debug("CQuickGame::~CQuickGame");
    delete m_game;
}

CPfGames* CQuickGame::save()
{
	CPfGames *game = m_game->save();
	game->setSGameType(S_GAME_TYPE_QUICKPLAY);
	return game;
}

void CQuickGame::enter()
{
	m_game->enter();
    m_game->nextScreen(m_game->getSimulatorScreen());
}

void CQuickGame::leave()
{
	m_game->leave();

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

void CQuickGame::update()
{
	m_game->update();
}
