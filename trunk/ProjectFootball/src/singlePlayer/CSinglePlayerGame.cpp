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

#include "CDataBaseGenerator.h"

#include "db/bean/CPfMatches.h"
#include "db/dao/factory/IDAOFactory.h"
#include "db/sqlite/dao/factory/CDAOFactorySQLite.h"

#include "event/IGameEvent.h"
#include "event/CEventsQueue.h"
#include "event/CEventConsumer.h"
#include "event/match/CMatchEvent.h"
#include "event/competition/CStartCompetitionEvent.h"
#include "event/competition/CEndCompetitionEvent.h"
#include "event/season/CStartSeasonEvent.h"
#include "event/season/CEndSeasonEvent.h"

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

#include "../exceptions/PFException.h"

#include "../utils/CLog.h"
#include "../utils/CDate.h"

CSinglePlayerGame::CSinglePlayerGame(const CPfGames *game)
: m_screenStack()
{
    LOG_DEBUG("CSinglePlayerGame::CSinglePlayerGame");
	m_game				= new CPfGames(*game);

	// If the database doesn't exists (is a new game or the file was deleted)
	// then it will be created a new database and will be generated the new data,
	// otherwise only load the current date from the database
	bool existsDataBase	= boost::filesystem::exists(m_game->getSConnectionString());
	m_daoFactory		= new CDAOFactorySQLite(m_game->getSConnectionString());
	if( !existsDataBase ){ CDataBaseGenerator::generateDataBase(m_daoFactory); }

	m_reportRegister	= new CSinglePlayerReportRegister();
	m_eventsQueue		= new CEventsQueue();
	m_eventConsumer		= new CEventConsumer(this);
	m_optionManager		= new CSinglePlayerOptionManager(m_daoFactory->getIPfGameOptionsDAO());

	// screens
    m_gameScreen		= new CScreenGame(this);
    m_matchResultScreen	= new CScreenMatchResult(this);
    m_rankingScreen		= new CScreenRanking(this);
    m_resultsScreen		= new CScreenResults(this);
    m_selectTeamScreen	= new CScreenSelectTeam(this);
    m_simulatorScreen	= new CScreenSimulator(this);
    m_teamPlayersScreen	= new CScreenTeamPlayers(this);

    // game progression
    m_currentMatch		= NULL;
}

CSinglePlayerGame::~CSinglePlayerGame()
{
    LOG_DEBUG("CSinglePlayerGame::~CSinglePlayerGame");

    delete m_gameScreen;
    delete m_matchResultScreen;
    delete m_rankingScreen;
    delete m_resultsScreen;
    delete m_selectTeamScreen;
    delete m_simulatorScreen;
    delete m_teamPlayersScreen;

    delete m_optionManager;
    delete m_reportRegister;
    delete m_eventConsumer;
    delete m_eventsQueue;
    delete m_daoFactory;
    delete m_game;

    delete m_currentMatch;
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
    LOG_DEBUG("CSinglePlayerGame::newGame");

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
    CPfGames game;
    game.setDLastSaved(nowDate);
    game.setSDriverName("SQLite");
    game.setSConnectionString(filename);
    game.setSGameName(gameName);
    game.setSGameType(S_GAME_TYPE_SINGLEPLAYER);
    game.setXFkUser(user->getXUser());

    // With this way, here we only need to set the initial environment for
    // a new game, forgetting the creation of attributes for a CSinglePlayerGame
    // object. This task rests now on constructor.
	CSinglePlayerGame *singlePlayerGame = new CSinglePlayerGame(&game);

    // retrieve the last season in the database and the end date of the itself
    CDate		maxDate = CDate::MIN_DATE;
    CPfSeasons *season	= singlePlayerGame->m_daoFactory->getIPfSeasonsDAO()->findLastSeason();
    if( season->getXSeason()==0 ){
    	throw PFEXCEPTION("The last season is NULL");
    }

	IPfCompetitionsBySeasonDAO 						*competitionBySeasonDAO		= singlePlayerGame->m_daoFactory->getIPfCompetitionsBySeasonDAO();
	std::vector<CPfCompetitionsBySeason*> 			*competitionsBySeasonList	= competitionBySeasonDAO->findByXFkSeason(season->getXSeason_str());
	std::vector<CPfCompetitionsBySeason*>::iterator itCompetitionsBySeason;
	for( itCompetitionsBySeason=competitionsBySeasonList->begin(); itCompetitionsBySeason!=competitionsBySeasonList->end(); itCompetitionsBySeason++ ){
		CPfCompetitionsBySeason *competitionBySeason = *itCompetitionsBySeason;
		if( competitionBySeason->getDEndCompetition()>maxDate ){
			maxDate = competitionBySeason->getDEndCompetition();
		}
	}

	singlePlayerGame->m_optionManager->setGameNew(true);
	singlePlayerGame->m_optionManager->setGameCurrentDate(maxDate);
	singlePlayerGame->m_optionManager->setGameCurrentSeason(season->getXSeason());

	competitionBySeasonDAO->freeVector(competitionsBySeasonList);
    delete season;

    singlePlayerGame->loadGameEvents();

    return singlePlayerGame;
}

IGame* CSinglePlayerGame::load(const CPfGames *game)
{
    LOG_DEBUG("CSinglePlayerGame::load");

	CSinglePlayerGame *singlePlayerGame = new CSinglePlayerGame(game);
	singlePlayerGame->loadGameEvents();

	return singlePlayerGame;
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
    LOG_DEBUG("CSinglePlayerGame::exit()");
    CGameEngine::getInstance()->unloadCurrentGame();
}

void CSinglePlayerGame::previousScreen()
{
    LOG_DEBUG("CSinglePlayerGame::previousScreen()");
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
    LOG_DEBUG("CSinglePlayerGame::nextScreen()");
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

const CPfMatches* CSinglePlayerGame::getCurrentMatch()
{
	return m_currentMatch;
}

void CSinglePlayerGame::setCurrentMatch(const CPfMatches *match)
{
	delete m_currentMatch;
	m_currentMatch = (match!=NULL)?new CPfMatches(*match):NULL;
}

void CSinglePlayerGame::loadGameEvents()
{
	int xSeason = m_optionManager->getGameCurrentSeason();

	IPfCompetitionsBySeasonDAO	*competitionBySeasonDAO = m_daoFactory->getIPfCompetitionsBySeasonDAO();
	IPfMatchesDAO				*matchesDAO				= m_daoFactory->getIPfMatchesDAO();

	// the min & max date necesary for the season events
    CDate minDate = CDate::MAX_DATE;
    CDate maxDate = CDate::MIN_DATE;

	// retrieve the competitions for the current season
	std::vector<CPfCompetitionsBySeason*> *competitionsBySeasonList = competitionBySeasonDAO->findByXFkSeason(xSeason);
	std::vector<CPfCompetitionsBySeason*>::iterator itCompetitionsBySeason;
	bool someCompetitionStarted = false;
	for( itCompetitionsBySeason=competitionsBySeasonList->begin(); itCompetitionsBySeason!=competitionsBySeasonList->end(); itCompetitionsBySeason++ ){
		CPfCompetitionsBySeason *competitionBySeason = *itCompetitionsBySeason;

		// for each competition are retrieved the respective matches
		std::vector<CPfMatches*> *matchesList = matchesDAO->findByXFkCompetitionAndXFkSeason(competitionBySeason->getXFkCompetition_str(), competitionBySeason->getXFkSeason_str());
		std::vector<CPfMatches*>::iterator itMatches;
		bool someMatchPlayed = false;
		for( itMatches=matchesList->begin(); itMatches!=matchesList->end(); itMatches++ ){
			CPfMatches *match = *itMatches;
			if( match->getLPlayed() ){
				someMatchPlayed = true;
				someCompetitionStarted = true;
			}else{
				m_eventsQueue->push(new CMatchEvent(match->getDMatch(), match->getXMatch()));
			}
		}
		if( !someMatchPlayed ){
			m_eventsQueue->push(new CStartCompetitionEvent(competitionBySeason->getDBeginCompetition()));
		}
		m_eventsQueue->push(new CEndCompetitionEvent(competitionBySeason->getDEndCompetition()));

		// Retrieve the min & max date for the season events
		if( competitionBySeason->getDBeginCompetition()<minDate ){
			minDate = competitionBySeason->getDBeginCompetition();
		}
		if( competitionBySeason->getDEndCompetition()>maxDate ){
			maxDate = competitionBySeason->getDEndCompetition();
		}

		matchesDAO->freeVector(matchesList);
	}

	minDate.setSec(minDate.getSec()-1);
	maxDate.setSec(maxDate.getSec()+1);

	// enqueue the start & end season events
	if( !someCompetitionStarted ){
		m_eventsQueue->push(new CStartSeasonEvent(minDate));
	}
	m_eventsQueue->push(new CEndSeasonEvent(maxDate));

	competitionBySeasonDAO->freeVector(competitionsBySeasonList);
}
