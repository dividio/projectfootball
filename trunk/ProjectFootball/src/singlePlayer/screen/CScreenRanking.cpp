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

#include "CScreenRanking.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeams.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../exceptions/PFException.h"
#include "../../utils/CLog.h"


CScreenRanking::CScreenRanking(CSinglePlayerGame *game)
    :CScreen("ranking.layout")
{
    LOG_DEBUG("CScreenRanking()");

    m_game = game;
    m_lastSeason = NULL;

    m_confederationsCombobox = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/ConfederationCombo"));
    m_countriesCombobox      = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/CountryCombo"));
    m_competitionsCombobox   = static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/CompetitionCombo"));
    m_rankingList            = static_cast<CEGUI::MultiColumnList*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/RankingList"));
    m_backButton             = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/BackButton"));
    m_gameMenuButton         = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/GameMenuButton"));
    m_rankingButton          = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/RankingButton"));
    m_teamPlayersButton	     = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/TeamPlayersButton"));
    m_resultsButton	         = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/ResultsButton"));

    m_confederationsCombobox->getEditbox()->setEnabled(false);
    m_countriesCombobox     ->getEditbox()->setEnabled(false);
    m_competitionsCombobox  ->getEditbox()->setEnabled(false);

    m_rankingList->setUserColumnDraggingEnabled(false);
    m_rankingList->setUserColumnSizingEnabled(false);
    m_rankingList->setUserSortControlEnabled(false);

    // i18n support
    m_backButton       ->setTooltipText((CEGUI::utf8*)gettext("Back"));
    m_gameMenuButton   ->setTooltipText((CEGUI::utf8*)gettext("Game Menu"));
    m_rankingButton    ->setText((CEGUI::utf8*)gettext("Ranking"));
    m_teamPlayersButton->setText((CEGUI::utf8*)gettext("Team Players"));
    m_resultsButton    ->setText((CEGUI::utf8*)gettext("Results"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Ranking/RankingLabel"))->setText((CEGUI::utf8*)gettext("Ranking:"));

    // Event handle
    m_confederationsCombobox   ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenRanking::confederationsComboboxListSelectionChanged, this));
    m_countriesCombobox        ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenRanking::countriesComboboxListSelectionChanged, this));
    m_competitionsCombobox     ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenRanking::competitionsComboboxListSelectionChanged, this));
    m_backButton       ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::backButtonClicked, this));
    m_gameMenuButton   ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::gameMenuButtonClicked, this));
    m_rankingButton    ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::rankingButtonClicked, this));
    m_teamPlayersButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::teamPlayersButtonClicked, this));
    m_resultsButton    ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenRanking::resultsButtonClicked, this));

    m_rankingList->addColumn("",     0, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn((CEGUI::utf8*)gettext("Team"), 1, CEGUI::UDim(0.60,0));
    m_rankingList->addColumn("PT",   2, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("PM",   3, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("WM",   4, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("DM",   5, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("LM",   6, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("GF",   7, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn("GA",   8, CEGUI::UDim(0.05,0));

}

CScreenRanking::~CScreenRanking()
{
    LOG_DEBUG("~CScreenRanking()");
}

void CScreenRanking::enter()
{
	CScreen::enter();

    CPfTeams   *playerTeam = m_game->getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game->getOptionManager()->getGamePlayerTeam());
    CPfMatches *lastMatch  = m_game->getIDAOFactory()->getIPfMatchesDAO()->findLastTeamMatch(playerTeam->getXTeam_str());
    if(lastMatch->getXMatch() > 0) {
        loadLastSeason();
        CPfCompetitionPhases *lastCompetitionPhase = m_game->getIDAOFactory()->getIPfCompetitionPhasesDAO()->findByXCompetitionPhase(lastMatch->getXFkCompetitionPhase_str());
        CPfCompetitions      *lastCompetition      = m_game->getIDAOFactory()->getIPfCompetitionsDAO()->findByXCompetition(lastCompetitionPhase->getXFkCompetition_str());
        CPfCountries         *lastCountry          = m_game->getIDAOFactory()->getIPfCountriesDAO()->findByXCountry(lastCompetition->getXFkCountry());

        loadConfederations(m_lastSeason->getXSeason(), lastCountry->getXFkConfederation());
        CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
        loadCountries(m_lastSeason->getXSeason(), item->getID(), lastCountry->getXCountry());
        loadCompetitions(m_lastSeason->getXSeason(), lastCountry->getXCountry(), lastCompetition->getXCompetition());
        loadRanking(m_lastSeason->getXSeason(), lastCompetition->getXCompetition());

        delete lastCompetitionPhase;
    }
    delete lastMatch;
    delete playerTeam;
}

void CScreenRanking::leave()
{
    if( m_lastSeason!=NULL ){
        delete m_lastSeason;
        m_lastSeason = NULL;
    }
}

void CScreenRanking::loadConfederations(int XSeason, int XConfederation)
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

void CScreenRanking::loadCountries(int XSeason, int XConfederation, int XCountry)
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

void CScreenRanking::loadCompetitions(int XSeason, int XCountry, int XCompetition)
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

void CScreenRanking::loadRanking(int XSeason, int XCompetition)
{
    m_rankingList->resetList();
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    IDAOFactory                         *daoFactory		= m_game->getIDAOFactory();
    IPfRankingDAO                       *rankingDAO     = daoFactory->getIPfRankingDAO();
    std::vector<CPfRanking*>            *rankingList    = rankingDAO->findRankingByXSeasonAndXCompetition(XSeason, XCompetition);
    std::vector<CPfRanking*>::iterator  it;
    CEGUI::ListboxTextItem *item;
    char position[4];
    int cont = 1;

    for( it=rankingList->begin(); it!=rankingList->end(); it++ ){
        CPfRanking *ranking = (*it);
        sprintf(position, "%d", cont);

        int row_idx = m_rankingList->addRow();

        item = new CEGUI::ListboxTextItem(position);
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 0, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getSTeam().c_str());
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 1, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNPoints_str().c_str());
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 2, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNPlayed_str().c_str());
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 3, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNWins_str().c_str());
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 4, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNDraws_str().c_str());
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 5, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNLosses_str().c_str());
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 6, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNGoalsFor_str().c_str());
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 7, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)ranking->getNGoalsAgainst_str().c_str());
        item->setSelectionBrushImage(sel_img);
        m_rankingList->setItem(item, 8, row_idx);

        cont++;
    }
    rankingDAO->freeVector(rankingList);

    m_rankingList->getHorzScrollbar()->setVisible(false);
}

void CScreenRanking::loadLastSeason()
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

bool CScreenRanking::confederationsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
    loadCountries(m_lastSeason->getXSeason(), item->getID());
    item = m_countriesCombobox->getSelectedItem();
    loadCompetitions(m_lastSeason->getXSeason(), item->getID());
    item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadRanking(m_lastSeason->getXSeason(), XCompetition);
    return true;
}

bool CScreenRanking::countriesComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_countriesCombobox->getSelectedItem();
    loadCompetitions(m_lastSeason->getXSeason(), item->getID());
    item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadRanking(m_lastSeason->getXSeason(), XCompetition);
    return true;
}

bool CScreenRanking::competitionsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadRanking(m_lastSeason->getXSeason(), XCompetition);
    return true;
}

bool CScreenRanking::backButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->previousScreen();
	return true;
}

bool CScreenRanking::gameMenuButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->nextScreen(m_game->getGameScreen());
    return true;
}

bool CScreenRanking::rankingButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getRankingScreen());
	return true;
}

bool CScreenRanking::teamPlayersButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getTeamPlayersScreen());
	return true;
}

bool CScreenRanking::resultsButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getResultsScreen());
	return true;
}
