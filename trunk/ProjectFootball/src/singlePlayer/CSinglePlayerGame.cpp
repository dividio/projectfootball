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

#include "event/CEventsHandler.h"
#include "event/match/CMatchEvent.h"
#include "event/match/CStartMatchEvent.h"
#include "event/match/CGoalMatchEvent.h"
#include "event/match/CEndMatchEvent.h"
#include "event/competition/CStartCompetitionEvent.h"
#include "event/competition/CEndCompetitionEvent.h"
#include "event/season/CStartSeasonEvent.h"
#include "event/season/CEndSeasonEvent.h"

#include "option/CSinglePlayerOptionManager.h"
#include "report/CSinglePlayerReportRegister.h"

#include "wh/CGNSWindowHandler.h"
#include "wh/CMatchInfoWindowHandler.h"
#include "wh/CMatchResultWindowHandler.h"
#include "wh/CRankingWindowHandler.h"
#include "wh/CResultsWindowHandler.h"
#include "wh/CSelectTeamWindowHandler.h"
#include "wh/CSimulatorWindowHandler.h"
#include "wh/CTeamPlayersWindowHandler.h"

#include "../engine/CGameEngine.h"
#include "../engine/db/bean/CPfGames.h"
#include "../engine/db/bean/CPfUsers.h"
#include "../engine/event/IGameEvent.h"
#include "../engine/event/system/CNoMoreEventsToday.h"
#include "../engine/wm/IWindowHandler.h"

#include "../exceptions/PFException.h"

#include "../utils/CLog.h"
#include "../utils/CDate.h"

CSinglePlayerGame::CSinglePlayerGame(const CPfGames &game) :
	m_windowHandlers(),
	m_gameState(Stopped)
{
    LOG_DEBUG("CSinglePlayerGame::CSinglePlayerGame");
	m_game				= new CPfGames(game);
	m_eventsHandler		= new CEventsHandler(*this);

	// If the database doesn't exists (is a new game or the file was deleted)
	// then it will be created a new database and will be generated the new data,
	// otherwise only load the current date from the database
	bool existsDataBase	= boost::filesystem::exists(m_game->getSConnectionString());
	m_daoFactory		= new CDAOFactorySQLite(m_game->getSConnectionString());
	if( !existsDataBase ){ CDataBaseGenerator::generateDataBase(m_daoFactory); }

	m_reportRegister	= new CSinglePlayerReportRegister();
	m_optionManager		= new CSinglePlayerOptionManager(m_daoFactory->getIPfGameOptionsDAO());

	// window handlers
    m_windowHandlers.push_back(new CGNSWindowHandler(*this));
	m_windowHandlers.push_back((m_matchInfoWindowHandler = new CMatchInfoWindowHandler(*this)));
	m_windowHandlers.push_back(new CSelectTeamWindowHandler(*this));
	m_windowHandlers.push_back(new CResultsWindowHandler(*this));
	m_windowHandlers.push_back(new CRankingWindowHandler(*this));
	m_windowHandlers.push_back(new CTeamPlayersWindowHandler(*this));
	m_windowHandlers.push_back(new CMatchResultWindowHandler(*this));
	m_windowHandlers.push_back(new CSimulatorWindowHandler(*this));

    // game progression
    m_currentMatch		= NULL;
}

CSinglePlayerGame::~CSinglePlayerGame()
{
    LOG_DEBUG("CSinglePlayerGame::~CSinglePlayerGame");

    if( !m_windowHandlers.empty() ){
    	std::vector<IWindowHandler*>::iterator itWindowHandlers;
    	for( itWindowHandlers=m_windowHandlers.begin(); itWindowHandlers!=m_windowHandlers.end(); itWindowHandlers++ ){
    		delete (*itWindowHandlers);
    	}
    	m_windowHandlers.clear();
    }

    delete m_optionManager;
    delete m_reportRegister;
    delete m_daoFactory;
    delete m_eventsHandler;
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

IGame* CSinglePlayerGame::newGame(const CPfUsers &user, const std::string &gameName)
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
    game.setXFkUser(user.getXUser());

    // With this way, here we only need to set the initial environment for
    // a new game, forgetting the creation of attributes for a CSinglePlayerGame
    // object. This task rests now on constructor.
	CSinglePlayerGame *singlePlayerGame = new CSinglePlayerGame(game);

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

	CDate date = singlePlayerGame->m_optionManager->getGameCurrentDate();
	CGameEngine::getInstance()->getTimeManager()->setCurrentTime(date);

	date.setHour(23);
	date.setMin(59);
	date.setSec(59);
	CGameEngine::getInstance()->getEventManager()->addEvent(new CNoMoreEventsToday(date));

    return singlePlayerGame;
}

IGame* CSinglePlayerGame::load(const CPfGames &game)
{
    LOG_DEBUG("CSinglePlayerGame::load");

	CSinglePlayerGame *singlePlayerGame = new CSinglePlayerGame(game);
	singlePlayerGame->loadGameEvents();

	CDate date = singlePlayerGame->m_optionManager->getGameCurrentDate();
	CGameEngine::getInstance()->getTimeManager()->setCurrentTime(date);

	date.setHour(23);
	date.setMin(59);
	date.setSec(59);
	CGameEngine::getInstance()->getEventManager()->addEvent(new CNoMoreEventsToday(date));

	return singlePlayerGame;
}

CPfGames* CSinglePlayerGame::save()
{
	m_optionManager->setGameCurrentDate(CGameEngine::getInstance()->getTimeManager()->getCurrentTime());
	m_optionManager->saveOptions();
    m_daoFactory->save();

    CDate nowDate;
    m_game->setDLastSaved(nowDate);
    return m_game;
}

const char* CSinglePlayerGame::getFirstScreenName()
{
    // Test if this game is a new game
	if( m_optionManager->getGameNew() ){
		return "SelectTeam";
    }else{
    	return "Game";
    }
}

void CSinglePlayerGame::setGameState(EGameState state)
{
	m_gameState = state;
}

const CPfMatches* CSinglePlayerGame::getCurrentMatch() const
{
	return m_currentMatch;
}

void CSinglePlayerGame::setCurrentMatch(const CPfMatches *match)
{
	delete m_currentMatch;
	m_currentMatch = (match!=NULL)?new CPfMatches(*match):NULL;

	// FIXME: do this in another way
	m_matchInfoWindowHandler->enter();
}

void CSinglePlayerGame::simulateMatch(const CPfMatches &match)
{
	CEventManager *eventMngr = CGameEngine::getInstance()->getEventManager();

    IPfTeamPlayersDAO  *teamPlayersDAO = m_daoFactory->getIPfTeamPlayersDAO();
    IPfTeamAveragesDAO *teamsAvgDAO    = m_daoFactory->getIPfTeamAveragesDAO();

    eventMngr->addEvent(new CStartMatchEvent(match.getDMatch(), match.getXMatch()));

    int xHomeTeam  = match.getXFkTeamHome();
    int xAwayTeam  = match.getXFkTeamAway();
    CPfTeamAverages *homeTeamAvg = teamsAvgDAO->findByXTeam(xHomeTeam);
    CPfTeamAverages *awayTeamAvg = teamsAvgDAO->findByXTeam(xAwayTeam);
    int nHomeGoals = getRandomNGoals(homeTeamAvg, awayTeamAvg);
    int nAwayGoals = getRandomNGoals(awayTeamAvg, homeTeamAvg);

    delete homeTeamAvg;
    delete awayTeamAvg;

    if( nHomeGoals>0 ){
        std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findLineUpByXFkTeam(xHomeTeam);
        while( nHomeGoals>0 ){
            int numPlayer = rand()%teamPlayesList->size();
            if(numPlayer == 0) { //Goalie don't score
                numPlayer = 10;
            }
            CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](numPlayer);

            int minute = rand()%90;
            CDate eventDate = match.getDMatch();
            eventDate.setMin(eventDate.getMin()+minute);

            eventMngr->addEvent(new CGoalMatchEvent(eventDate, match.getXMatch(), xHomeTeam, teamPlayer->getXTeamPlayer(), minute, false));

            nHomeGoals--;
        }
        teamPlayersDAO->freeVector(teamPlayesList);
    }
    if( nAwayGoals>0 ){
        std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findLineUpByXFkTeam(xAwayTeam);
        while( nAwayGoals>0 ){
            int numPlayer = rand()%teamPlayesList->size();
            if(numPlayer == 0) { //Goalie don't score
                numPlayer = 10;
            }
            CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](numPlayer);

            int minute = rand()%90;
            CDate eventDate = match.getDMatch();
            eventDate.setMin(eventDate.getMin()+minute);

            eventMngr->addEvent(new CGoalMatchEvent(eventDate, match.getXMatch(), xAwayTeam, teamPlayer->getXTeamPlayer(), minute, false));

            nAwayGoals--;
        }
        teamPlayersDAO->freeVector(teamPlayesList);
    }

    CDate eventDate = match.getDMatch();
    eventDate.setMin(eventDate.getMin()+90);

    eventMngr->addEvent(new CEndMatchEvent(eventDate, match.getXMatch()));
}

int CSinglePlayerGame::getRandomNGoals(CPfTeamAverages *attackTeam, CPfTeamAverages *defenseTeam)
{
    int goals = 0;
    int teamFactor = attackTeam->getNTotal() - defenseTeam->getNTotal();

    int n = rand()%100 + teamFactor;

         if( n<25  )         { goals = 0; }
    else if( n>=25 && n<55  ){ goals = 1; }
    else if( n>=55 && n<80  ){ goals = 2; }
    else if( n>=80 && n<96  ){ goals = 3; }
    else if( n>=96 && n<100 ){ goals = 4; }
    else if( n>=100 )        { goals = 5; }
    return goals;
}


void CSinglePlayerGame::loadGameEvents()
{
	int xSeason = m_optionManager->getGameCurrentSeason();

	CEventManager *eventMngr = CGameEngine::getInstance()->getEventManager();

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
				eventMngr->addEvent(new CMatchEvent(match->getDMatch(), match->getXMatch()));
			}
		}
		if( !someMatchPlayed ){
			eventMngr->addEvent(new CStartCompetitionEvent(competitionBySeason->getDBeginCompetition()));
		}
		eventMngr->addEvent(new CEndCompetitionEvent(competitionBySeason->getDEndCompetition()));

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
		eventMngr->addEvent(new CStartSeasonEvent(minDate));
	}
	eventMngr->addEvent(new CEndSeasonEvent(maxDate));

	competitionBySeasonDAO->freeVector(competitionsBySeasonList);
}
