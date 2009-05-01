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

#include "CScreenResults.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../exceptions/PFException.h"
#include "../../utils/CLog.h"


CScreenResults::CScreenResults(CSinglePlayerGame *game)
    :CScreen("results.layout")
{
    LOG_DEBUG("CScreenResults()");

    m_game       = game;
    m_lastSeason = NULL;

    m_confederationsCombobox    = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/ConfederationCombo"));
    m_countriesCombobox         = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/CountryCombo"));
    m_competitionsCombobox      = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/CompetitionCombo"));
    m_competitionPhasesCombobox = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/CompetitionPhaseCombo"));
    m_resultsList               = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/ResultsList"));
    m_backButton                = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/BackButton"));
    m_gameMenuButton            = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/GameMenuButton"));
    m_rankingButton             = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/RankingButton"));
    m_teamPlayersButton	        = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/TeamPlayersButton"));
    m_resultsButton	            = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/ResultsButton"));

    m_confederationsCombobox   ->getEditbox()->setEnabled(false);
    m_countriesCombobox        ->getEditbox()->setEnabled(false);
    m_competitionsCombobox     ->getEditbox()->setEnabled(false);
    m_competitionPhasesCombobox->getEditbox()->setEnabled(false);

    m_resultsList->setUserColumnDraggingEnabled(false);
    m_resultsList->setUserColumnSizingEnabled(false);
    m_resultsList->setUserSortControlEnabled(false);
    m_resultsList->setWantsMultiClickEvents(true);

    // i18n support
    m_backButton        ->setTooltipText((CEGUI::utf8*)gettext("Back"));
    m_gameMenuButton    ->setTooltipText((CEGUI::utf8*)gettext("Game Menu"));
    m_rankingButton     ->setText((CEGUI::utf8*)gettext("Ranking"));
    m_teamPlayersButton ->setText((CEGUI::utf8*)gettext("Team Players"));
    m_resultsButton     ->setText((CEGUI::utf8*)gettext("Results"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Results/ResultsLabel"))->setText((CEGUI::utf8*)gettext("Results:"));

    // Event handle
    m_confederationsCombobox   ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenResults::confederationsComboboxListSelectionChanged, this));
    m_countriesCombobox        ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenResults::countriesComboboxListSelectionChanged, this));
    m_competitionsCombobox     ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenResults::competitionsComboboxListSelectionChanged, this));
    m_competitionPhasesCombobox->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenResults::competitionPhasesComboboxListSelectionChanged, this));
    m_backButton               ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenResults::backButtonClicked, this));
    m_gameMenuButton           ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenResults::gameMenuButtonClicked, this));
    m_rankingButton            ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenResults::rankingButtonClicked, this));
    m_teamPlayersButton        ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenResults::teamPlayersButtonClicked, this));
    m_resultsButton            ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenResults::resultsButtonClicked, this));

    m_resultsList->addColumn((CEGUI::utf8*)gettext("Home Team"),   0, CEGUI::UDim(0.4,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Goals"),       1, CEGUI::UDim(0.1,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Away Team"),   2, CEGUI::UDim(0.4,0));
    m_resultsList->addColumn((CEGUI::utf8*)gettext("Goals"),       3, CEGUI::UDim(0.1,0));
}

CScreenResults::~CScreenResults()
{
    LOG_DEBUG("~CScreenResults()");
}

void CScreenResults::enter()
{
	CScreen::enter();

	CPfTeams             *playerTeam           = m_game->getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game->getOptionManager()->getGamePlayerTeam());
	CPfMatches           *lastMatch            = m_game->getIDAOFactory()->getIPfMatchesDAO()->findLastTeamMatch(playerTeam->getXTeam_str());
	if(lastMatch->getXMatch() > 0) {
        loadLastSeason();
	    CPfCompetitionPhases *lastCompetitionPhase = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO()->findByXCompetitionPhase(lastMatch->getXFkCompetitionPhase_str());
        CPfCompetitions      *lastCompetition      = m_game->getIDAOFactory()->getIPfCompetitionsDAO()->findByXCompetition(lastCompetitionPhase->getXFkCompetition_str());
        CPfCountries         *lastCountry          = m_game->getIDAOFactory()->getIPfCountriesDAO()->findByXCountry(lastCompetition->getXFkCountry());


        loadConfederations(m_lastSeason->getXSeason(), lastCountry->getXFkConfederation());
        CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
        loadCountries(m_lastSeason->getXSeason(), item->getID(), lastCountry->getXCountry());
        loadCompetitions(m_lastSeason->getXSeason(), lastCountry->getXCountry(), lastCompetition->getXCompetition());
        loadCompetitionPhases(lastCompetition->getXCompetition(), lastCompetitionPhase->getXCompetitionPhase());
        loadResultsList(lastCompetitionPhase->getXCompetitionPhase());
        delete lastCountry;
        delete lastCompetition;
        delete lastCompetitionPhase;
	}
	delete lastMatch;
	delete playerTeam;
}

void CScreenResults::leave()
{
    if( m_lastSeason!=NULL ){
        delete m_lastSeason;
        m_lastSeason = NULL;
    }
}

void CScreenResults::loadConfederations(int XSeason, int XConfederation)
{
    m_confederationsCombobox->clearAllSelections();
    m_confederationsCombobox->resetList();
    m_confederationsCombobox->getEditbox()->setText("");
    IPfConfederationsDAO *confederationsDAO = m_game->getIDAOFactory()->getIPfConfederationsDAO();
    int selectedConfederation = -1;

    std::vector<CPfConfederations*> *confederationsList = confederationsDAO->findByXFKSeasonWithLeague(XSeason);

    std::vector<CPfConfederations*>::iterator it;
    for(it = confederationsList->begin(); it != confederationsList->end(); it++) {
        CPfConfederations      *confederation = (*it);
        CEGUI::ListboxTextItem *item          = new CEGUI::ListboxTextItem((CEGUI::utf8*)confederation->getSConfederation().c_str(), confederation->getXConfederation());
        m_confederationsCombobox->addItem(item);
        if(confederation->getXConfederation() == XConfederation) {
            m_confederationsCombobox->setText((CEGUI::utf8*)confederation->getSConfederation().c_str());
            item->setSelected(true);
            selectedConfederation = confederation->getXConfederation();
        }
    }

    if(selectedConfederation == -1) {
        m_confederationsCombobox->setText((CEGUI::utf8*)confederationsList->front()->getSConfederation().c_str());
        CEGUI::ListboxItem *item = m_confederationsCombobox->getListboxItemFromIndex(0);
        item->setSelected(true);
        selectedConfederation = confederationsList->front()->getXConfederation();
    }

    confederationsDAO->freeVector(confederationsList);

}

void CScreenResults::loadCountries(int XSeason, int XConfederation, int XCountry)
{
    m_countriesCombobox->clearAllSelections();
    m_countriesCombobox->resetList();
    m_countriesCombobox->getEditbox()->setText("");
    IPfCountriesDAO *countriesDAO = m_game->getIDAOFactory()->getIPfCountriesDAO();
    int selectedCountry = -1;

    std::vector<CPfCountries*> *countriesList = countriesDAO->findByXFkConfederationAndXFKSeasonWithLeague(XConfederation, XSeason);

    if(!countriesList->empty()) {
        std::vector<CPfCountries*>::iterator it;
        for(it = countriesList->begin(); it != countriesList->end(); it++) {
            CPfCountries           *country = (*it);
            CEGUI::ListboxTextItem *item    = new CEGUI::ListboxTextItem((CEGUI::utf8*)country->getSShortName().c_str(), country->getXCountry());
            m_countriesCombobox->addItem(item);
            if(country->getXCountry() == XCountry) {
                m_countriesCombobox->setText((CEGUI::utf8*)country->getSShortName().c_str());
                item->setSelected(true);
                selectedCountry = country->getXCountry();
            }
        }

        if(selectedCountry == -1) {
            m_countriesCombobox->setText((CEGUI::utf8*)countriesList->front()->getSShortName().c_str());
            CEGUI::ListboxItem *item = m_countriesCombobox->getListboxItemFromIndex(0);
            item->setSelected(true);
            selectedCountry = countriesList->front()->getXCountry();
        }

    } else {
        m_countriesCombobox->setText((CEGUI::utf8*)gettext("No countries"));
    }

    countriesDAO->freeVector(countriesList);

}

void CScreenResults::loadCompetitions(int XSeason, int XCountry, int XCompetition)
{
    m_competitionsCombobox->clearAllSelections();
    m_competitionsCombobox->resetList();
    m_competitionsCombobox->getEditbox()->setText("");
    bool selected = false;

    IPfCompetitionsDAO                      *competitionsDAO    = m_game->getIDAOFactory()->getIPfCompetitionsDAO();
    std::vector<CPfCompetitions*>           *competitionsList   = competitionsDAO->findByXFkCountryAndXFKSeason(XCountry, XSeason);
    std::vector<CPfCompetitions*>::iterator it;

    for( it=competitionsList->begin(); it!=competitionsList->end(); it++ ){
        CPfCompetitions *competition = (*it);
        CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)competition->getSCompetition().c_str(), competition->getXCompetition());
        m_competitionsCombobox->addItem(item);
        if(competition->getXCompetition() == XCompetition) {
            m_competitionsCombobox->setText((CEGUI::utf8*)competition->getSCompetition().c_str());
            selected = true;
            item->setSelected(true);
        }
    }
    if(!selected) {
        m_competitionsCombobox->setText((CEGUI::utf8*)competitionsList->front()->getSCompetition().c_str());
        CEGUI::ListboxItem *item = m_competitionsCombobox->getListboxItemFromIndex(0);
        item->setSelected(true);
    }

    competitionsDAO->freeVector(competitionsList);
}

void CScreenResults::loadCompetitionPhases(int XCompetition, int XCompetitionPhase)
{
    m_competitionPhasesCombobox->clearAllSelections();
    m_competitionPhasesCombobox->resetList();
    m_competitionPhasesCombobox->getEditbox()->setText("");
    bool selected = false;

        IPfCompetitionPhasesDAO                         *competitionPhasesDAO   = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO();
        std::vector<CPfCompetitionPhases*>              *competitionPhasesList  = competitionPhasesDAO->findByXFkCompetition(XCompetition);
        std::vector<CPfCompetitionPhases*>::iterator    it;

        for( it=competitionPhasesList->begin(); it!=competitionPhasesList->end(); it++ ){
            CPfCompetitionPhases *competitionPhase = (*it);
            CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)competitionPhase->getSCompetitionPhase().c_str(),
                                                                                    competitionPhase->getXCompetitionPhase());
            m_competitionPhasesCombobox->addItem(item);
            if(competitionPhase->getXCompetitionPhase() == XCompetitionPhase) {
                m_competitionPhasesCombobox->setText((CEGUI::utf8*)competitionPhase->getSCompetitionPhase().c_str());
                selected = true;
                item->setSelected(true);
            }
        }
        if(!selected) {
            m_competitionPhasesCombobox->setText((CEGUI::utf8*)competitionPhasesList->front()->getSCompetitionPhase().c_str());
            CEGUI::ListboxItem *item = m_competitionPhasesCombobox->getListboxItemFromIndex(0);
            item->setSelected(true);
        }

        competitionPhasesDAO->freeVector(competitionPhasesList);
}

void CScreenResults::loadResultsList(int XCompetitionPhase)
{
    m_resultsList->resetList();


        IPfMatchesDAO *matchesDAO = m_game->getIDAOFactory()->getIPfMatchesDAO();
        IPfTeamsDAO   *teamsDAO   = m_game->getIDAOFactory()->getIPfTeamsDAO();
        IPfGoalsDAO   *goalsDAO   = m_game->getIDAOFactory()->getIPfGoalsDAO();

        CPfTeams      *playerTeam = teamsDAO->findByXTeam(m_game->getOptionManager()->getGamePlayerTeam());
        CPfMatches    *lastMatch  = matchesDAO->findLastTeamMatch(playerTeam->getXTeam_str());

        std::vector<CPfMatches*> *matchesList = matchesDAO->findByXFkCompetitionPhaseAndXFkSeason(XCompetitionPhase, lastMatch->getXFkSeason());
        std::vector<CPfMatches*>::iterator  it;

        for( it=matchesList->begin(); it!=matchesList->end(); it++ ){
            CPfMatches  *match      = (*it);
            CPfTeams    *teamHome   = teamsDAO->findByXTeam(match->getXFkTeamHome());
            CPfTeams    *teamAway   = teamsDAO->findByXTeam(match->getXFkTeamAway());

            int row_idx = m_resultsList->addRow();
            if( match->getLPlayed() ){
                std::vector<CPfGoals*>  *homeGoalsList  = goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), match->getXFkTeamHome());
                std::vector<CPfGoals*>  *awayGoalsList  = goalsDAO->findByXFkMatchAndXFkTeamScorer(match->getXMatch(), match->getXFkTeamAway());

                std::ostringstream nHomeGoals;
                nHomeGoals << homeGoalsList->size();

                std::ostringstream nAwayGoals;
                nAwayGoals << awayGoalsList->size();

                m_resultsList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)teamHome->getSTeam().c_str()),	0, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)nHomeGoals.str().c_str()),		1, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)teamAway->getSTeam().c_str()),	2, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)nAwayGoals.str().c_str()),		3, row_idx);

                goalsDAO->freeVector(homeGoalsList);
                goalsDAO->freeVector(awayGoalsList);
            }else{
                m_resultsList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)teamHome->getSTeam().c_str()),	0, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)"-"),							1, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)teamAway->getSTeam().c_str()),	2, row_idx);
                m_resultsList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)"-"),							3, row_idx);
            }

            delete teamHome;
            delete teamAway;
        }

        matchesDAO->freeVector(matchesList);
        delete lastMatch;
        delete playerTeam;

    m_resultsList->getHorzScrollbar()->setVisible(false);
}

void CScreenResults::loadLastSeason()
{
    if( m_lastSeason!=NULL ){
        delete m_lastSeason;
        m_lastSeason = NULL;
    }

    IPfSeasonsDAO *seasonsDAO = m_game->getIDAOFactory()->getIPfSeasonsDAO();
    m_lastSeason = seasonsDAO->findLastSeason();
    if( m_lastSeason==NULL || m_lastSeason->getXSeason_str()=="" ){
        throw PFEXCEPTION("[CScreenResults::loadLastSeason] Last season not found");
    }
}

bool CScreenResults::confederationsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
    loadCountries(m_lastSeason->getXSeason(), item->getID());
    item = m_countriesCombobox->getSelectedItem();
    loadCompetitions(m_lastSeason->getXSeason(), item->getID());
    item = m_competitionsCombobox->getSelectedItem();
    CPfCompetitionPhases *lastCompetitionPhase = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO()->findLastCompetitionPhase(item->getID(), m_lastSeason->getXSeason());
    if(lastCompetitionPhase->getXCompetitionPhase() == 0) {
        lastCompetitionPhase = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO()->findLastCompetitionPhase(item->getID(), m_lastSeason->getXSeason() - 1);
    }
    loadCompetitionPhases(item->getID(), lastCompetitionPhase->getXCompetitionPhase());
    item = m_competitionPhasesCombobox->getSelectedItem();
    if (item != NULL) {
        loadResultsList(item->getID());
    }
    return true;
}

bool CScreenResults::countriesComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_countriesCombobox->getSelectedItem();
    loadCompetitions(m_lastSeason->getXSeason(), item->getID());
    item = m_competitionsCombobox->getSelectedItem();
    CPfCompetitionPhases *lastCompetitionPhase = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO()->findLastCompetitionPhase(item->getID(), m_lastSeason->getXSeason());
    if(lastCompetitionPhase->getXCompetitionPhase() == 0) {
        lastCompetitionPhase = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO()->findLastCompetitionPhase(item->getID(), m_lastSeason->getXSeason() - 1);
    }
    loadCompetitionPhases(item->getID(), lastCompetitionPhase->getXCompetitionPhase());
    item = m_competitionPhasesCombobox->getSelectedItem();
    if (item != NULL) {
        loadResultsList(item->getID());
    }
    return true;
}

bool CScreenResults::competitionsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_competitionsCombobox->getSelectedItem();
    CPfCompetitionPhases *lastCompetitionPhase = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO()->findLastCompetitionPhase(item->getID(), m_lastSeason->getXSeason());
    if(lastCompetitionPhase->getXCompetitionPhase() == 0) {
        lastCompetitionPhase = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO()->findLastCompetitionPhase(item->getID(), m_lastSeason->getXSeason() - 1);
    }
    loadCompetitionPhases(item->getID(), lastCompetitionPhase->getXCompetitionPhase());
    item = m_competitionPhasesCombobox->getSelectedItem();
    if (item != NULL) {
        loadResultsList(item->getID());
    }
    return true;
}

bool CScreenResults::competitionPhasesComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_competitionPhasesCombobox->getSelectedItem();
    loadResultsList(item->getID());
    return true;
}

bool CScreenResults::backButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->previousScreen();
	return true;
}

bool CScreenResults::gameMenuButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->nextScreen(m_game->getGameScreen());
    return true;
}

bool CScreenResults::rankingButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getRankingScreen());
	return true;
}

bool CScreenResults::teamPlayersButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getTeamPlayersScreen());
	return true;
}

bool CScreenResults::resultsButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getResultsScreen());
	return true;
}
