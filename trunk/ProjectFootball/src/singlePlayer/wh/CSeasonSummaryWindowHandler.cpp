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

#include "CSeasonSummaryWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeams.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../exceptions/PFException.h"
#include "../../utils/CLog.h"


CSeasonSummaryWindowHandler::CSeasonSummaryWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("seasonSummary.layout"),
	m_game(game),
	m_initiated(false)
{
    LOG_DEBUG("CSeasonSummaryWindowHandler()");

    m_xLastSeason = 0;
}

CSeasonSummaryWindowHandler::~CSeasonSummaryWindowHandler()
{
    LOG_DEBUG("~CSeasonSummaryWindowHandler()");

    if( m_initiated ){
		m_rankingList->removeColumnWithID(0);
		m_rankingList->removeColumnWithID(1);
		m_rankingList->removeColumnWithID(2);
		m_rankingList->removeColumnWithID(3);
		m_rankingList->removeColumnWithID(4);
		m_rankingList->removeColumnWithID(5);
		m_rankingList->removeColumnWithID(6);
		m_rankingList->removeColumnWithID(7);
		m_rankingList->removeColumnWithID(8);

        m_scorersList->removeColumnWithID(0);
        m_scorersList->removeColumnWithID(1);
        m_scorersList->removeColumnWithID(2);
        m_scorersList->removeColumnWithID(3);
    }
}

void CSeasonSummaryWindowHandler::enter()
{
    CEGUI::WindowManager &windowMngr = CEGUI::WindowManager::getSingleton();

    int XCoach            = m_game.getOptionManager()->getGamePlayerCoach();
    int XSeason           = m_game.getSelectedCompetitionPhaseBySeason()->getXFkSeason();
    int XCompetitionPhase = m_game.getSelectedCompetitionPhaseBySeason()->getXFkCompetitionPhase();

    CPfCompetitionPhases *competitionPhase = m_game.getIDAOFactory()->getIPfCompetitionPhasesDAO()->findByXCompetitionPhase(XCompetitionPhase);
    int XCompetition = competitionPhase->getXFkCompetition();

    loadRanking(XSeason, XCompetition);
    loadScorers(XSeason, XCompetition);

    CPfCompetitions *competition = m_game.getIDAOFactory()->getIPfCompetitionsDAO()->findByXCompetition(XCompetition);
    CPfCountries    *country     = m_game.getIDAOFactory()->getIPfCountriesDAO()->findByXCountry(competition->getXFkCountry());
    loadConfederations(XSeason, country->getXFkConfederation());
    CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
    loadCountries(XSeason, item->getID(), country->getXCountry());
    loadCompetitions(XSeason, country->getXCountry(), competition->getXCompetition());
    delete country;
    delete competition;

    CEGUI::String seasonLabel = gettext("Season");
    CPfSeasons   *season      = m_game.getIDAOFactory()->getIPfSeasonsDAO()->findByXSeason(XSeason);
    seasonLabel = seasonLabel + " " + season->getSSeason();
    delete season;
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonSummary/SeasonLabel"))->setText((CEGUI::utf8*)seasonLabel.c_str());

    loadLastSeason();
}

void CSeasonSummaryWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

    m_confederationsCombobox = static_cast<CEGUI::Combobox*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonSummary/ConfederationCombo"));
    m_countriesCombobox      = static_cast<CEGUI::Combobox*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonSummary/CountryCombo"));
    m_competitionsCombobox   = static_cast<CEGUI::Combobox*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonSummary/CompetitionCombo"));
    m_rankingList            = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonSummary/RankingList"));
    m_scorersList            = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonSummary/ScorersList"));

    m_confederationsCombobox->getEditbox()->setEnabled(false);
    m_countriesCombobox     ->getEditbox()->setEnabled(false);
    m_competitionsCombobox  ->getEditbox()->setEnabled(false);

    m_rankingList->setUserColumnDraggingEnabled(false);
    m_rankingList->setUserColumnSizingEnabled(false);
    m_rankingList->setUserSortControlEnabled(false);
    m_scorersList->setUserColumnDraggingEnabled(false);
    m_scorersList->setUserColumnSizingEnabled(false);
    m_scorersList->setUserSortControlEnabled(false);

    // i18n support
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonSummary/RankingLabel"))->setText((CEGUI::utf8*)gettext("Ranking:"));
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"SeasonSummary/ScorersLabel"))->setText((CEGUI::utf8*)gettext("Scorers:"));

    // Event handle
    registerEventConnection(m_confederationsCombobox   ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CSeasonSummaryWindowHandler::confederationsComboboxListSelectionChanged, this)));
    registerEventConnection(m_countriesCombobox        ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CSeasonSummaryWindowHandler::countriesComboboxListSelectionChanged, this)));
    registerEventConnection(m_competitionsCombobox     ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CSeasonSummaryWindowHandler::competitionsComboboxListSelectionChanged, this)));

    m_rankingList->addColumn("",     0, CEGUI::UDim(0.05,0));
    m_rankingList->addColumn((CEGUI::utf8*)gettext("Team"), 1, CEGUI::UDim(0.46,0));
    m_rankingList->addColumn("PT",   2, CEGUI::UDim(0.07,0));
    m_rankingList->addColumn("PM",   3, CEGUI::UDim(0.07,0));
    m_rankingList->addColumn("WM",   4, CEGUI::UDim(0.07,0));
    m_rankingList->addColumn("DM",   5, CEGUI::UDim(0.07,0));
    m_rankingList->addColumn("LM",   6, CEGUI::UDim(0.07,0));
    m_rankingList->addColumn("GF",   7, CEGUI::UDim(0.07,0));
    m_rankingList->addColumn("GA",   8, CEGUI::UDim(0.07,0));

    m_scorersList->addColumn("", 0, CEGUI::UDim(0.10,0));
    m_scorersList->addColumn((CEGUI::utf8*)gettext("Name"), 1, CEGUI::UDim(0.40,0));
    m_scorersList->addColumn((CEGUI::utf8*)gettext("Team"), 2, CEGUI::UDim(0.35,0));
    m_scorersList->addColumn((CEGUI::utf8*)gettext("Goals"), 3, CEGUI::UDim(0.15,0));

    m_initiated = true;
}

void CSeasonSummaryWindowHandler::leave()
{

}

void CSeasonSummaryWindowHandler::loadConfederations(int XSeason, int XConfederation)
{
    m_confederationsCombobox->clearAllSelections();
    m_confederationsCombobox->resetList();
    m_confederationsCombobox->getEditbox()->setText("");
    IPfConfederationsDAO *confederationsDAO = m_game.getIDAOFactory()->getIPfConfederationsDAO();
    int selectedConfederation = -1;

    std::vector<CPfConfederations*> *confederationsList = confederationsDAO->findByXFKSeasonWithLeague(XSeason);

    std::vector<CPfConfederations*>::iterator it;
    for(it = confederationsList->begin(); it != confederationsList->end(); it++) {
        CPfConfederations      *confederation = (*it);
        CEGUI::ListboxTextItem *item          = new CEGUI::ListboxTextItem((CEGUI::utf8*)gettext(confederation->getSConfederation().c_str()), confederation->getXConfederation());
        m_confederationsCombobox->addItem(item);
        if(confederation->getXConfederation() == XConfederation) {
            m_confederationsCombobox->setText((CEGUI::utf8*)gettext(confederation->getSConfederation().c_str()));
            item->setSelected(true);
            selectedConfederation = confederation->getXConfederation();
        }
    }

    if(selectedConfederation == -1) {
        m_confederationsCombobox->setText((CEGUI::utf8*)gettext(confederationsList->front()->getSConfederation().c_str()));
        CEGUI::ListboxItem *item = m_confederationsCombobox->getListboxItemFromIndex(0);
        item->setSelected(true);
        selectedConfederation = confederationsList->front()->getXConfederation();
    }

    confederationsDAO->freeVector(confederationsList);

}

void CSeasonSummaryWindowHandler::loadCountries(int XSeason, int XConfederation, int XCountry)
{
    m_countriesCombobox->clearAllSelections();
    m_countriesCombobox->resetList();
    m_countriesCombobox->getEditbox()->setText("");
    IPfCountriesDAO *countriesDAO = m_game.getIDAOFactory()->getIPfCountriesDAO();
    int selectedCountry = -1;

    std::vector<CPfCountries*> *countriesList = countriesDAO->findByXFkConfederationAndXFKSeasonWithLeague(XConfederation, XSeason);

    if(!countriesList->empty()) {
        std::vector<CPfCountries*>::iterator it;
        for(it = countriesList->begin(); it != countriesList->end(); it++) {
            CPfCountries           *country = (*it);
            CEGUI::ListboxTextItem *item    = new CEGUI::ListboxTextItem((CEGUI::utf8*)gettext(country->getSShortName().c_str()), country->getXCountry());
            m_countriesCombobox->addItem(item);
            if(country->getXCountry() == XCountry) {
                m_countriesCombobox->setText((CEGUI::utf8*)gettext(country->getSShortName().c_str()));
                item->setSelected(true);
                selectedCountry = country->getXCountry();
            }
        }

        if(selectedCountry == -1) {
            m_countriesCombobox->setText((CEGUI::utf8*)gettext(countriesList->front()->getSShortName().c_str()));
            CEGUI::ListboxItem *item = m_countriesCombobox->getListboxItemFromIndex(0);
            item->setSelected(true);
            selectedCountry = countriesList->front()->getXCountry();
        }

    } else {
        m_countriesCombobox->setText((CEGUI::utf8*)gettext("No countries"));
    }

    countriesDAO->freeVector(countriesList);

}

void CSeasonSummaryWindowHandler::loadCompetitions(int XSeason, int XCountry, int XCompetition)
{
    m_competitionsCombobox->clearAllSelections();
    m_competitionsCombobox->resetList();
    m_competitionsCombobox->getEditbox()->setText("");
    bool selected = false;

    IPfCompetitionsDAO                      *competitionsDAO    = m_game.getIDAOFactory()->getIPfCompetitionsDAO();
    std::vector<CPfCompetitions*>           *competitionsList   = competitionsDAO->findByXFkCountryAndXFKSeason(XCountry, XSeason);
    std::vector<CPfCompetitions*>::iterator it;

    for( it=competitionsList->begin(); it!=competitionsList->end(); it++ ){
        CPfCompetitions *competition = (*it);
        CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)gettext(competition->getSCompetition().c_str()), competition->getXCompetition());
        m_competitionsCombobox->addItem(item);
        if(competition->getXCompetition() == XCompetition) {
            m_competitionsCombobox->setText((CEGUI::utf8*)gettext(competition->getSCompetition().c_str()));
            selected = true;
            item->setSelected(true);
        }
    }
    if(!selected) {
        m_competitionsCombobox->setText((CEGUI::utf8*)gettext(competitionsList->front()->getSCompetition().c_str()));
        CEGUI::ListboxItem *item = m_competitionsCombobox->getListboxItemFromIndex(0);
        item->setSelected(true);
    }

    competitionsDAO->freeVector(competitionsList);
}

void CSeasonSummaryWindowHandler::loadRanking(int XSeason, int XCompetition)
{
    m_rankingList->resetList();
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    IDAOFactory                         *daoFactory		= m_game.getIDAOFactory();
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

void CSeasonSummaryWindowHandler::loadScorers(int XSeason, int XCompetition)
{
    m_scorersList->resetList();
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    IDAOFactory                         *daoFactory     = m_game.getIDAOFactory();
    IPfScorersDAO                       *scorersDAO     = daoFactory->getIPfScorersDAO();
    std::vector<CPfScorers*>            *scorersList    = scorersDAO->findScorersByXSeasonAndXCompetition(XSeason, XCompetition);
    std::vector<CPfScorers*>::iterator  it;
    CEGUI::ListboxTextItem *item;
    char position[4];
    int cont = 1;

    for( it=scorersList->begin(); it!=scorersList->end() && cont <= 5; it++ ){
        CPfScorers *scorer = (*it);
        sprintf(position, "%d", cont);

        int row_idx = m_scorersList->addRow();

        item = new CEGUI::ListboxTextItem(position);
        item->setSelectionBrushImage(sel_img);
        m_scorersList->setItem(item, 0, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)scorer->getSShortTeamPlayerName().c_str());
        item->setSelectionBrushImage(sel_img);
        m_scorersList->setItem(item, 1, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)scorer->getSShortTeamName().c_str());
        item->setSelectionBrushImage(sel_img);
        m_scorersList->setItem(item, 2, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)scorer->getNGoals_str().c_str());
        item->setSelectionBrushImage(sel_img);
        m_scorersList->setItem(item, 3, row_idx);

        cont++;
    }
    scorersDAO->freeVector(scorersList);

    m_scorersList->getHorzScrollbar()->setVisible(false);
}

void CSeasonSummaryWindowHandler::loadLastSeason()
{
    m_xLastSeason = m_game.getSelectedCompetitionPhaseBySeason()->getXFkSeason();
}

bool CSeasonSummaryWindowHandler::confederationsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
    loadCountries(m_xLastSeason, item->getID());
    item = m_countriesCombobox->getSelectedItem();
    loadCompetitions(m_xLastSeason, item->getID());
    item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadRanking(m_xLastSeason, XCompetition);
    loadScorers(m_xLastSeason, XCompetition);
    return true;
}

bool CSeasonSummaryWindowHandler::countriesComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_countriesCombobox->getSelectedItem();
    loadCompetitions(m_xLastSeason, item->getID());
    item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadRanking(m_xLastSeason, XCompetition);
    loadScorers(m_xLastSeason, XCompetition);
    return true;
}

bool CSeasonSummaryWindowHandler::competitionsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadRanking(m_xLastSeason, XCompetition);
    loadScorers(m_xLastSeason, XCompetition);
    return true;
}
