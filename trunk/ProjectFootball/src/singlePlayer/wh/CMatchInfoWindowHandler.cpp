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

#include "CMatchInfoWindowHandler.h"

#include <libintl.h>
#include "../CSinglePlayerGame.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

CMatchInfoWindowHandler::CMatchInfoWindowHandler(CSinglePlayerGame &game)
: CWindowHandler("matchInfo.layout"), m_game(game)
{}

CMatchInfoWindowHandler::~CMatchInfoWindowHandler()
{}

void CMatchInfoWindowHandler::enter()
{
	updateMatchInfo();
}

void CMatchInfoWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();
	m_informationBanner			= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/InformationBanner"));
    m_competitionCountryFlag	= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/CompetitionCountryFlag"));
    m_homeTeamName				= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/HomeTeamName"));
    m_awayTeamName				= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/AwayTeamName"));
    m_homeTeamAverage			= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/HomeTeamAverage"));
    m_awayTeamAverage			= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/AwayTeamAverage"));
    m_homeTeamBadge				= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/HomeTeamBadge"));
    m_awayTeamBadge				= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/AwayTeamBadge"));
    m_homeTeamCoach             = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/HomeTeamCoach"));
    m_awayTeamCoach             = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"MatchInfo/AwayTeamCoach"));
}

void CMatchInfoWindowHandler::updateMatchInfo()
{
    const CPfMatches  *match = m_game.getCurrentMatch();
    std::string currentTimestamp = m_game.getCurrentTime().getTimestamp();
    if( match==NULL ) {
        IPfTeamAveragesDAO	 *teamAveragesDAO	= m_game.getIDAOFactory()->getIPfTeamAveragesDAO();
        IPfTeamsDAO			 *teamsDAO			= m_game.getIDAOFactory()->getIPfTeamsDAO();
        IPfCoachesDAO        *coachesDAO        = m_game.getIDAOFactory()->getIPfCoachesDAO();
        IPfCoachContractsDAO *coachContractsDAO = m_game.getIDAOFactory()->getIPfCoachContractsDAO();


    	// General information
        m_informationBanner->setText((CEGUI::utf8*)gettext("No info about the match!"));
        m_competitionCountryFlag->setProperty("Image", "set: image:full_image");

        // Home team info
        CPfTeams			*homeTeam		   = teamsDAO->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
        CPfTeamAverages		*homeTeamAverage   = teamAveragesDAO->findByXTeam(homeTeam->getXTeam_str(), currentTimestamp);
        CPfCoachContracts   *homeCoachContract = coachContractsDAO->findActiveByXFkTeam(homeTeam->getXTeam_str(), currentTimestamp);
        CPfCoaches          *homeCoach         = coachesDAO->findByXCoach(homeCoachContract->getXFkCoach_str());
        std::ostringstream	homeAverage;
        homeAverage << homeTeamAverage->getNTotal();
        m_homeTeamName		->setText((CEGUI::utf8*)homeTeam->getSTeam().c_str());
        m_homeTeamAverage	->setText((CEGUI::utf8*)homeAverage.str().c_str());
        m_homeTeamBadge		->setProperty("Image", "set:"+ homeTeam->getSLogo() +" image:"+homeTeam->getSLogo()+"_b");
        m_homeTeamCoach     ->setText((CEGUI::utf8*)homeCoach->getSShortName().c_str());
        delete homeCoach;
        delete homeCoachContract;
        delete homeTeamAverage;
        delete homeTeam;

        // Away team info
        m_awayTeamName		->setText("");
        m_awayTeamAverage	->setText("");
        m_awayTeamBadge		->setProperty("Image", "set: image:full_image");
        m_awayTeamCoach     ->setText("");

    } else {
        IDAOFactory             *daoFactory				= m_game.getIDAOFactory();
        IPfCountriesDAO         *countriesDAO			= daoFactory->getIPfCountriesDAO();
        IPfSeasonsDAO			*seasonsDAO				= daoFactory->getIPfSeasonsDAO();
        IPfCompetitionsDAO      *competitionsDAO		= daoFactory->getIPfCompetitionsDAO();
        IPfCompetitionPhasesDAO *competitionPhasesDAO	= daoFactory->getIPfCompetitionPhasesDAO();
        IPfPhaseRoundsDAO 		*phaseRoundsDAO			= daoFactory->getIPfPhaseRoundsDAO();
        IPfTeamsDAO             *teamsDAO				= daoFactory->getIPfTeamsDAO();
        IPfTeamAveragesDAO		*teamAveragesDAO		= daoFactory->getIPfTeamAveragesDAO();
        IPfCoachesDAO           *coachesDAO             = daoFactory->getIPfCoachesDAO();
        IPfCoachContractsDAO    *coachContractsDAO      = daoFactory->getIPfCoachContractsDAO();

        // General information
        CPfSeasons				*season				= seasonsDAO->findByXSeason(match->getXFkSeason());
        CPfPhaseRounds    		*phaseRound			= phaseRoundsDAO->findByXPhaseRound(match->getXFkPhaseRound());
        CPfCompetitionPhases    *competitionPhase	= competitionPhasesDAO->findByXCompetitionPhase(phaseRound->getXFkCompetitionPhase());
        CPfCompetitions         *competition		= competitionsDAO->findByXCompetition(competitionPhase->getXFkCompetition());
        CPfCountries            *country			= countriesDAO->findByXCountry(competition->getXFkCountry_str());
    	m_informationBanner->setText((CEGUI::utf8*)gettext("Competition:"));
    	m_informationBanner->appendText((CEGUI::utf8*)competition->getSCompetition().c_str());
    	m_informationBanner->appendText((CEGUI::utf8*)gettext(", Season:"));
    	m_informationBanner->appendText((CEGUI::utf8*)season->getSSeason().c_str());
    	m_informationBanner->appendText((CEGUI::utf8*)gettext(", Phase:"));
    	m_informationBanner->appendText((CEGUI::utf8*)competitionPhase->getSCompetitionPhase().c_str());
    	m_informationBanner->appendText((CEGUI::utf8*)gettext(", Round:"));
		m_informationBanner->appendText((CEGUI::utf8*)phaseRound->getSPhaseRound().c_str());
        m_competitionCountryFlag->setProperty("Image", "set:"+ country->getSFlag() +" image:"+country->getSFlag() + "_mo_flag");
        delete country;
        delete competition;
        delete competitionPhase;
        delete phaseRound;
        delete season;

    	// Home team info
        CPfTeams            *homeTeam		   = teamsDAO->findByXTeam(match->getXFkTeamHome());
        CPfTeamAverages    	*homeTeamAverage   = teamAveragesDAO->findByXTeam(homeTeam->getXTeam_str(), currentTimestamp);
        CPfCoachContracts   *homeCoachContract = coachContractsDAO->findActiveByXFkTeam(homeTeam->getXTeam_str(), currentTimestamp);
        CPfCoaches          *homeCoach         = coachesDAO->findByXCoach(homeCoachContract->getXFkCoach_str());
        std::ostringstream 	homeAverage;
        homeAverage << homeTeamAverage->getNTotal();
        m_homeTeamName		->setText((CEGUI::utf8*)homeTeam->getSTeam().c_str());
        m_homeTeamAverage	->setText((CEGUI::utf8*)homeAverage.str().c_str());
        m_homeTeamBadge		->setProperty("Image", "set:"+ homeTeam->getSLogo() +" image:"+homeTeam->getSLogo()+"_b");
        m_homeTeamCoach     ->setText((CEGUI::utf8*)homeCoach->getSShortName().c_str());
        delete homeCoach;
        delete homeCoachContract;
        delete homeTeamAverage;
        delete homeTeam;

        // Away team info
        CPfTeams            *awayTeam		   = teamsDAO->findByXTeam(match->getXFkTeamAway());
        CPfTeamAverages		*awayTeamAverage   = teamAveragesDAO->findByXTeam(awayTeam->getXTeam_str(), currentTimestamp);
        CPfCoachContracts   *awayCoachContract = coachContractsDAO->findActiveByXFkTeam(awayTeam->getXTeam_str(), currentTimestamp);
        CPfCoaches          *awayCoach         = coachesDAO->findByXCoach(awayCoachContract->getXFkCoach_str());
        std::ostringstream  awayAverage;
        awayAverage << awayTeamAverage->getNTotal();
        m_awayTeamName		->setText((CEGUI::utf8*)awayTeam->getSTeam().c_str());
        m_awayTeamAverage	->setText((CEGUI::utf8*)awayAverage.str().c_str());
        m_awayTeamBadge		->setProperty("Image", "set:"+ awayTeam->getSLogo() +" image:"+awayTeam->getSLogo()+"_b");
        m_awayTeamCoach     ->setText((CEGUI::utf8*)awayCoach->getSShortName().c_str());
        delete awayCoach;
        delete awayCoachContract;
        delete awayTeamAverage;
        delete awayTeam;
    }
}
