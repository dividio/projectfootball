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

#include "CSinglePlayerGame.h"

#include <vector>
#include <boost/filesystem.hpp>

#include "CDataGenerator.h"

#include "db/bean/CPfMatches.h"
#include "db/dao/factory/IDAOFactory.h"
#include "db/sqlite/dao/factory/CDAOFactorySQLite.h"

#include "event/IGameEvent.h"
#include "event/CEventsQueue.h"
#include "event/CEventConsumer.h"
#include "event/match/CMatchEvent.h"

#include "option/CSinglePlayerOptionManager.h"
#include "report/CSinglePlayerReportRegister.h"

#include "screen/CScreenGame.h"
#include "screen/CScreenMatchResult.h"
#include "screen/CScreenRanking.h"
#include "screen/CScreenResults.h"
#include "screen/CScreenSelectTeam.h"
#include "screen/CScreenSimulator.h"
#include "screen/CScreenTeamPlayers.h"

#include "../engine/CGameEngine.h"
#include "../engine/db/bean/CPfGames.h"
#include "../engine/db/bean/CPfUsers.h"

#include "../utils/CLog.h"
#include "../utils/CDate.h"

CSinglePlayerGame::CSinglePlayerGame(const CPfUsers *user, const char *gameName) : m_screenStack()
{
    CLog::getInstance()->debug("CSinglePlayerGame::CSinglePlayerGame");

    const char *str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string filename = "";

    srand(time(NULL));
    do{
    	filename = "data/database/savedgames/";
    	for( int i=0; i<8; i++ ){
    		filename += str[rand()%52];
    	}
    	filename += ".sql3";
    }while(boost::filesystem::exists(filename));

    CDate nowDate;

    m_game = new CPfGames();
    m_game->setXGame_str("");
    m_game->setDLastSaved(nowDate);
    m_game->setSDriverName("SQLite");
    m_game->setSConnectionString(filename);
    m_game->setSGameName(gameName);
    m_game->setSGameType(S_GAME_TYPE_SINGLEPLAYER);
    m_game->setXFkUser(user->getXUser());

    m_daoFactory = new CDAOFactorySQLite(m_game->getSConnectionString());
    CDataGenerator dataGenerator(m_daoFactory);
    dataGenerator.generateDataBase();

    m_reportRegister        = new CSinglePlayerReportRegister();
    m_eventsQueue			= new CEventsQueue();
    m_eventConsumer			= new CEventConsumer(this);

    m_optionManager         = new CSinglePlayerOptionManager(m_daoFactory->getIPfGameOptionsDAO());
    m_optionManager->setGameNew(true);
    CDate date(15, 8, 2008, 0, 0, 0); // 15/08/2008 0:00:00
    m_optionManager->setGameCurrentDate(date);

    createSinglePlayerScreens();
    loadGameEvents();
}

CSinglePlayerGame::CSinglePlayerGame(const CPfGames *game) : m_screenStack()
{
    CLog::getInstance()->debug("CSinglePlayerGame::CSinglePlayerGame");

    m_game					= new CPfGames(*game);
    m_daoFactory			= new CDAOFactorySQLite(m_game->getSConnectionString());
    m_reportRegister        = new CSinglePlayerReportRegister();
    m_eventsQueue			= new CEventsQueue();
    m_eventConsumer			= new CEventConsumer(this);
    m_optionManager         = new CSinglePlayerOptionManager(m_daoFactory->getIPfGameOptionsDAO());

    createSinglePlayerScreens();
    loadGameEvents();
}

CSinglePlayerGame::~CSinglePlayerGame()
{
    CLog::getInstance()->debug("CSinglePlayerGame::~CSinglePlayerGame");

    delete m_gameScreen;
    delete m_matchResultScreen;
    delete m_rankingScreen;
    delete m_resultsScreen;
    delete m_selectTeamScreen;
    delete m_simulatorScreen;
    delete m_teamPlayersScreen;

    delete m_optionManager;
    delete m_reportRegister;
    delete m_eventsQueue;
    delete m_daoFactory;
    delete m_game;
}

IDAOFactory* CSinglePlayerGame::getIDAOFactory()
{
    return m_daoFactory;
}

CSinglePlayerReportRegister* CSinglePlayerGame::getReportRegister()
{
    return m_reportRegister;
}

CSinglePlayerOptionManager* CSinglePlayerGame::getOptionManager()
{
    return m_optionManager;
}

CEventsQueue* CSinglePlayerGame::getEventsQueue()
{
	return m_eventsQueue;
}

CEventConsumer* CSinglePlayerGame::getEventConsumer()
{
	return m_eventConsumer;
}

void CSinglePlayerGame::enter()
{
    // Test if this game is a new game
	if( m_optionManager->getGameNew() ){
        nextScreen(m_selectTeamScreen);
    }else{
        nextScreen(m_gameScreen);
    }
}

void CSinglePlayerGame::leave()
{
    while( !m_screenStack.empty() ){
        m_screenStack.back()->leave();
        m_screenStack.pop_back();
    }
}

void CSinglePlayerGame::update()
{
    if( !m_screenStack.empty() ){
        m_screenStack.back()->update();
    }else{
        exit();
    }
}

IGame* CSinglePlayerGame::newGame(const CPfUsers *user, const char *gameName)
{
	return new CSinglePlayerGame(user, gameName);
}

IGame* CSinglePlayerGame::load(const CPfGames *game)
{
	return new CSinglePlayerGame(game);
}

CPfGames* CSinglePlayerGame::save()
{
	m_optionManager->saveOptions();
    m_daoFactory->save();

    CDate nowDate;
    m_game->setDLastSaved(nowDate);
    return m_game;
}

void CSinglePlayerGame::exit()
{
    // TODO: Confirm current game unload
    CLog::getInstance()->debug("CSinglePlayerGame::exit()");
    CGameEngine::getInstance()->unloadCurrentGame();
}

void CSinglePlayerGame::previousScreen()
{
    CLog::getInstance()->debug("CSinglePlayerGame::previousScreen()");
    // cleanup the current state
    if(!m_screenStack.empty()) {
        m_screenStack.back()->leave();
        m_screenStack.pop_back();

        if( !m_screenStack.empty() ){
        	m_screenStack.back()->enter();
        }
    }
}

void CSinglePlayerGame::nextScreen(IScreen* screen)
{
    CLog::getInstance()->debug("CSinglePlayerGame::nextScreen()");
    bool found = false;
    for( int i=m_screenStack.size()-1; i>=0 && !found; i-- ){
        if( m_screenStack[i]==screen ){
            found = true;
        }
    }

    if( found ){
        while( !m_screenStack.empty() ){
            if( m_screenStack.back()!=screen ){
                m_screenStack.back()->leave();
                m_screenStack.pop_back();
            }else{
            	m_screenStack.back()->enter();
                break;
            }
        }
    }else{
        m_screenStack.push_back(screen);
        m_screenStack.back()->enter();
    }
}

IScreen* CSinglePlayerGame::getGameScreen()
{
    return m_gameScreen;
}

IScreen* CSinglePlayerGame::getMatchResultScreen()
{
    return m_matchResultScreen;
}

IScreen* CSinglePlayerGame::getRankingScreen()
{
    return m_rankingScreen;
}

IScreen* CSinglePlayerGame::getResultsScreen()
{
    return m_resultsScreen;
}

IScreen* CSinglePlayerGame::getSelectTeamScreen()
{
    return m_selectTeamScreen;
}

IScreen* CSinglePlayerGame::getSimulatorScreen()
{
    return m_simulatorScreen;
}

IScreen* CSinglePlayerGame::getTeamPlayersScreen()
{
    return m_teamPlayersScreen;
}

void CSinglePlayerGame::setGameOptionsDefaultValues()
{
	getOptionManager()->setDefaultValues();
}

void CSinglePlayerGame::createSinglePlayerScreens()
{
    m_gameScreen		= new CScreenGame(this);
    m_matchResultScreen	= new CScreenMatchResult(this);
    m_rankingScreen		= new CScreenRanking(this);
    m_resultsScreen		= new CScreenResults(this);
    m_selectTeamScreen	= new CScreenSelectTeam(this);
    m_simulatorScreen	= new CScreenSimulator(this);
    m_teamPlayersScreen	= new CScreenTeamPlayers(this);
}

void CSinglePlayerGame::loadGameEvents()
{
	// Load match events
	IPfMatchesDAO *matchesDAO = m_daoFactory->getIPfMatchesDAO();

	std::vector<CPfMatches*>* 			matchesList = matchesDAO->findMatchesNotPlayed();
	std::vector<CPfMatches*>::iterator 	itMatches;

	for( itMatches=matchesList->begin(); itMatches!=matchesList->end(); itMatches++ ){
		CPfMatches*	match 	= *itMatches;

		CDate		date	= match->getDMatch();
		date.setHour(0);
		date.setMin(0);
		date.setSec(0);

		m_eventsQueue->push(new CMatchEvent(date, match->getXMatch()));
	}

	matchesDAO->freeVector(matchesList);
}
