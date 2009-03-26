/*******************************************************************************
 * Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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

#include "CSeasonGenerator.h"

#include <list>
#include <sstream>

#include "CSinglePlayerGame.h"
#include "db/dao/factory/IDAOFactory.h"

#include "event/CEventsQueue.h"

#include "event/competition/CStartCompetitionEvent.h"
#include "event/competition/CEndCompetitionEvent.h"
#include "event/match/CMatchEvent.h"
#include "event/season/CStartSeasonEvent.h"
#include "event/season/CEndSeasonEvent.h"

#include "option/CSinglePlayerOptionManager.h"

#include "../utils/CDate.h"
#include "../utils/CLog.h"

CSeasonGenerator::CSeasonGenerator()
{
	// Nothing to do
}

CSeasonGenerator::~CSeasonGenerator()
{
	// Nothing to do
}

void CSeasonGenerator::generateSeason(CSinglePlayerGame *game)
{
	IPfSeasonsDAO				*seasonsDAO					= game->getIDAOFactory()->getIPfSeasonsDAO();
	IPfCompetitionsBySeasonDAO	*competitionsBySeasonDAO	= game->getIDAOFactory()->getIPfCompetitionsBySeasonDAO();
	IPfTeamsDAO					*teamsDAO					= game->getIDAOFactory()->getIPfTeamsDAO();
	IPfTeamsByCompetitionsDAO	*teamsByCompetitionsDAO		= game->getIDAOFactory()->getIPfTeamsByCompetitionsDAO();

	CPfSeasons *season = seasonsDAO->findLastSeason();
	if( season==NULL || season->getXSeason_str()=="" ){
		CLog::getInstance()->exception("[CSeasonGenerator::generateSeason] Last season was not found, new season generation is aborted.");
	}

	int year = season->getNYear()+1;
    std::ostringstream sseason;
    sseason << year << "/" << (year+1);

	// the min & max date necesary for the season events
    CDate minDate = CDate::MAX_DATE;
    CDate maxDate = CDate::MIN_DATE;

    // create the new season
	CPfSeasons newSeason;
	newSeason.setNYear(year);
	newSeason.setSSeason(sseason.str());
	game->getIDAOFactory()->getIPfSeasonsDAO()->insertReg(&newSeason);

	// retrieve the competitions associated with the last season
	std::vector<CPfCompetitionsBySeason*>	*competitionsBySeasonList = competitionsBySeasonDAO->findByXFkSeason(season->getXSeason_str());

	// for each competition, create a new competition by season and insert the relevant matches
	std::vector<CPfCompetitionsBySeason*>::iterator itCompetitionsBySeason;
	for( itCompetitionsBySeason=competitionsBySeasonList->begin(); itCompetitionsBySeason!=competitionsBySeasonList->end(); itCompetitionsBySeason++ ){
		CPfCompetitionsBySeason *competitionBySeason = *itCompetitionsBySeason;

		// create the new competition by season
		CPfCompetitionsBySeason *newCompetitionBySeason = new CPfCompetitionsBySeason();
		newCompetitionBySeason->setDBeginCompetition(getSameWeekDayOneYearLater(competitionBySeason->getDBeginCompetition()));
		newCompetitionBySeason->setDEndCompetition(getSameWeekDayOneYearLater(competitionBySeason->getDEndCompetition()));
		newCompetitionBySeason->setXFkCompetition_str(competitionBySeason->getXFkCompetition_str());
		newCompetitionBySeason->setXFkSeason_str(newSeason.getXSeason_str());
		competitionsBySeasonDAO->insertReg(newCompetitionBySeason);

		// retrieve the teams registered in previous season on the same competition
		std::vector<CPfTeams*> 				*teamsList = teamsDAO->findByXFKCompetitionAndXFKSeason(competitionBySeason->getXFkCompetition_str(), competitionBySeason->getXFkSeason_str());
		std::vector<CPfTeams*>::iterator 	itTeams;
		for( itTeams=teamsList->begin(); itTeams!=teamsList->end(); itTeams++ ){
			CPfTeams *team = *itTeams;

			// the team will be associate with the competition for the new season
			CPfTeamsByCompetitions *newTeamByCompetition = new CPfTeamsByCompetitions();
			newTeamByCompetition->setXFkCompetitionBySeason_str(newCompetitionBySeason->getXCompetitionBySeason_str());
			newTeamByCompetition->setXFkTeam_str(team->getXTeam_str());
			teamsByCompetitionsDAO->insertReg(newTeamByCompetition);

			delete newTeamByCompetition;
		}

		game->getEventsQueue()->push(new CStartCompetitionEvent(newCompetitionBySeason->getDBeginCompetition()));
		generateLeagueMatches(game, newCompetitionBySeason, teamsList); // TODO: Maybe not all competitions are leagues
		game->getEventsQueue()->push(new CEndCompetitionEvent(newCompetitionBySeason->getDEndCompetition()));

		// Retrieve the min & max date for the season events
		if( newCompetitionBySeason->getDBeginCompetition()<minDate ){
			minDate = newCompetitionBySeason->getDBeginCompetition();
		}
		if( newCompetitionBySeason->getDEndCompetition()>maxDate ){
			maxDate = newCompetitionBySeason->getDEndCompetition();
		}

		teamsDAO->freeVector(teamsList);
		delete newCompetitionBySeason;
	}

	minDate.setSec(minDate.getSec()-1);
	maxDate.setSec(maxDate.getSec()+1);

	// enqueue the start & end season events
	game->getEventsQueue()->push(new CStartSeasonEvent(minDate));
	game->getEventsQueue()->push(new CEndSeasonEvent(maxDate));
	game->getOptionManager()->setGameCurrentSeason(newSeason.getXSeason());

	competitionsBySeasonDAO->freeVector(competitionsBySeasonList);
	delete season;
}

void CSeasonGenerator::generateLeagueMatches(CSinglePlayerGame *game, const CPfCompetitionsBySeason *competitionBySeason, const std::vector<CPfTeams*> *teamsList)
{
	IPfCompetitionPhasesDAO	*competitionPhasesDAO 	= game->getIDAOFactory()->getIPfCompetitionPhasesDAO();
	IPfMatchesDAO			*matchesDAO				= game->getIDAOFactory()->getIPfMatchesDAO();

	std::vector<CPfCompetitionPhases*>	*phasesList	= competitionPhasesDAO->findByXFkCompetition(competitionBySeason->getXFkCompetition());

	int i;
	int nTeams 	= teamsList->size();
	int nPhases	= phasesList->size();
	int halfNTeams	= nTeams/2;
	int halfNPhases	= nPhases/2;

	if( nTeams%2!=0 ){
		CLog::getInstance()->exception("Number of teams must be a multiple of two: #teams:%d", nTeams);
	}
	if( nPhases%2!=0 ){
		CLog::getInstance()->exception("Number of phases must be a multiple of two: #phases:%d", nPhases);
	}

	std::list<CPfTeams*> 				*homeTeamsList	= new std::list<CPfTeams*>();
	std::list<CPfTeams*>				*awayTeamsList	= new std::list<CPfTeams*>();
	std::vector<CPfTeams*>::iterator	itTeams;
	for( i=0; i<nTeams; i++ ){
		if( i<(halfNTeams) ){
			homeTeamsList->push_back(teamsList->at(i));
		}else{
			awayTeamsList->push_back(teamsList->at(i));
		}
	}

	CDate	goDate(competitionBySeason->getDBeginCompetition());
	goDate.setHour(17);
	goDate.setMin(0);
	goDate.setSec(0);

	CDate 	returnDate(competitionBySeason->getDBeginCompetition());
	returnDate.setDay(returnDate.getDay()+halfNPhases*7);
	returnDate.setHour(17);
	returnDate.setMin(0);
	returnDate.setSec(0);

	for( i=0; i<halfNPhases; ){
		CPfCompetitionPhases *goPhase		= phasesList->at(i);
		CPfCompetitionPhases *returnPhase	= phasesList->at(i+halfNPhases);

		// insert the matches for the current phase and the corresponding return phase
	    std::list<CPfTeams*>::iterator itHomeTeams;
	    std::list<CPfTeams*>::iterator itAwayTeams;
	    for( itHomeTeams=homeTeamsList->begin(), itAwayTeams=awayTeamsList->begin(); itHomeTeams!=homeTeamsList->end() && itAwayTeams!=awayTeamsList->end(); itHomeTeams++, itAwayTeams++) {

	        CPfTeams *homeTeam = *itHomeTeams;
	        CPfTeams *awayTeam = *itAwayTeams;

	        CPfMatches 	*match = new CPfMatches();

	        match->setDMatch(goDate);
	        match->setLPlayed(false);
	        match->setXFkSeason_str(competitionBySeason->getXFkSeason_str());
	        match->setXFkCompetitionPhase_str(goPhase->getXCompetitionPhase_str());
	        match->setXFkTeamHome_str(homeTeam->getXTeam_str());
	        match->setXFkTeamAway_str(awayTeam->getXTeam_str());
	        matchesDAO->insertReg(match);
	        game->getEventsQueue()->push(new CMatchEvent(goDate, match->getXMatch()));

	        match->setDMatch(returnDate);
	        match->setLPlayed(false);
	        match->setXFkSeason_str(competitionBySeason->getXFkSeason_str());
	        match->setXFkCompetitionPhase_str(returnPhase->getXCompetitionPhase_str());
	        match->setXFkTeamHome_str(awayTeam->getXTeam_str());
	        match->setXFkTeamAway_str(homeTeam->getXTeam_str());
	        matchesDAO->insertReg(match);
	        game->getEventsQueue()->push(new CMatchEvent(returnDate, match->getXMatch()));

	        delete match;
	    }

		// increment the match date and the return match date
	    goDate.setDay(goDate.getDay()+7);
	    returnDate.setDay(returnDate.getDay()+7);

	    // swap home and away team list
	    std::list<CPfTeams*>	*auxTeamsList;
	    auxTeamsList	= homeTeamsList;
		homeTeamsList	= awayTeamsList;
		awayTeamsList	= auxTeamsList;

		// increment the i index and shuffle the teams lists
		i++;
		if( i%2!=0) {
			CPfTeams* auxTeam = awayTeamsList->back();
			awayTeamsList->pop_back();
			awayTeamsList->push_front(auxTeam);
		}
		else{
			CPfTeams* homeFront = homeTeamsList->front();
			homeTeamsList->pop_front();
			CPfTeams* awayFront = awayTeamsList->front();
			awayTeamsList->pop_front();
			CPfTeams* homeBack = homeTeamsList->back();
			homeTeamsList->pop_back();

			homeTeamsList->push_back(homeFront);
			homeTeamsList->push_front(awayFront);
			awayTeamsList->push_back(homeBack);
		}
	}

	delete homeTeamsList;
	delete awayTeamsList;

	competitionPhasesDAO->freeVector(phasesList);
}

CDate CSeasonGenerator::getSameWeekDayOneYearLater(const CDate &date)
{
	// To match the same week day one year later
	// is necesary to look for leap years

	CDate newDate = date;
	newDate.setYear(newDate.getYear()+1);

	if( CDate::isLeap(date.getYear()) ){
		CDate Feb29(29, 02, date.getYear(), 23, 59, 59);
		if( date<=Feb29 ){
			newDate.setDay(newDate.getDay()-2);
		}
		else{
			newDate.setDay(newDate.getDay()-1);
		}
	}
	else{
		if( CDate::isLeap(date.getYear()+1) ){
			CDate Feb29(29, 02, date.getYear()+1, 23, 59, 59);
			if( newDate>Feb29 ){
				newDate.setDay(newDate.getDay()-2);
			}
			else{
				newDate.setDay(newDate.getDay()-1);
			}
		}
		else{
			newDate.setDay(newDate.getDay()-1);
		}
	}

	return newDate;
}
