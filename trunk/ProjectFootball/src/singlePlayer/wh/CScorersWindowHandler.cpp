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

#include "CScorersWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeams.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../exceptions/PFException.h"
#include "../../utils/CLog.h"


CScorersWindowHandler::CScorersWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("scorers.layout"),
	m_game(game),
	m_initiated(false)
{
    LOG_DEBUG("CScorersWindowHandler()");

    m_lastSeason = NULL;
}

CScorersWindowHandler::~CScorersWindowHandler()
{
    LOG_DEBUG("~CScorersWindowHandler()");

    if( m_initiated ){
		m_scorersList->removeColumnWithID(0);
		m_scorersList->removeColumnWithID(1);
		m_scorersList->removeColumnWithID(2);
		m_scorersList->removeColumnWithID(3);
    }
}

void CScorersWindowHandler::enter()
{
    CPfTeams   *playerTeam = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
    CPfMatches *lastMatch  = m_game.getIDAOFactory()->getIPfMatchesDAO()->findLastTeamMatch(playerTeam->getXTeam_str());
    if(lastMatch->getXMatch() > 0) {
        loadLastSeason();
        CPfPhaseRounds		 *lastPhaseRound	   = m_game.getIDAOFactory()->getIPfPhaseRoundsDAO()->findByXPhaseRound(lastMatch->getXFkPhaseRound_str());
        CPfCompetitionPhases *lastCompetitionPhase = m_game.getIDAOFactory()->getIPfCompetitionPhasesDAO()->findByXCompetitionPhase(lastPhaseRound->getXFkCompetitionPhase());
        CPfCompetitions      *lastCompetition      = m_game.getIDAOFactory()->getIPfCompetitionsDAO()->findByXCompetition(lastCompetitionPhase->getXFkCompetition_str());
        CPfCountries         *lastCountry          = m_game.getIDAOFactory()->getIPfCountriesDAO()->findByXCountry(lastCompetition->getXFkCountry());

        loadConfederations(m_lastSeason->getXSeason(), lastCountry->getXFkConfederation());
        CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
        loadCountries(m_lastSeason->getXSeason(), item->getID(), lastCountry->getXCountry());
        loadCompetitions(m_lastSeason->getXSeason(), lastCountry->getXCountry(), lastCompetition->getXCompetition());
        loadScorers(m_lastSeason->getXSeason(), lastCompetition->getXCompetition());

        delete lastCountry;
        delete lastCompetition;
        delete lastCompetitionPhase;
        delete lastPhaseRound;
    }
    delete lastMatch;
    delete playerTeam;
}

void CScorersWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

    m_confederationsCombobox = static_cast<CEGUI::Combobox*>(windowMngr.getWindow((CEGUI::utf8*)"Scorers/ConfederationCombo"));
    m_countriesCombobox      = static_cast<CEGUI::Combobox*>(windowMngr.getWindow((CEGUI::utf8*)"Scorers/CountryCombo"));
    m_competitionsCombobox   = static_cast<CEGUI::Combobox*>(windowMngr.getWindow((CEGUI::utf8*)"Scorers/CompetitionCombo"));
    m_scorersList            = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"Scorers/ScorersList"));

    m_confederationsCombobox->getEditbox()->setEnabled(false);
    m_countriesCombobox     ->getEditbox()->setEnabled(false);
    m_competitionsCombobox  ->getEditbox()->setEnabled(false);

    m_scorersList->setUserColumnDraggingEnabled(false);
    m_scorersList->setUserColumnSizingEnabled(false);
    m_scorersList->setUserSortControlEnabled(false);

    // i18n support
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Scorers/ScorersLabel"))->setText((CEGUI::utf8*)gettext("Scorers:"));

    // Event handle
    registerEventConnection(m_confederationsCombobox   ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScorersWindowHandler::confederationsComboboxListSelectionChanged, this)));
    registerEventConnection(m_countriesCombobox        ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScorersWindowHandler::countriesComboboxListSelectionChanged, this)));
    registerEventConnection(m_competitionsCombobox     ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScorersWindowHandler::competitionsComboboxListSelectionChanged, this)));

    m_scorersList->addColumn("", 0, CEGUI::UDim(0.10,0));
    m_scorersList->addColumn((CEGUI::utf8*)gettext("Name"), 1, CEGUI::UDim(0.40,0));
    m_scorersList->addColumn((CEGUI::utf8*)gettext("Team"), 2, CEGUI::UDim(0.40,0));
    m_scorersList->addColumn((CEGUI::utf8*)gettext("Goals"), 3, CEGUI::UDim(0.10,0));


    m_initiated = true;
}

void CScorersWindowHandler::leave()
{
    if( m_lastSeason!=NULL ){
        delete m_lastSeason;
        m_lastSeason = NULL;
    }
}

void CScorersWindowHandler::loadConfederations(int XSeason, int XConfederation)
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

void CScorersWindowHandler::loadCountries(int XSeason, int XConfederation, int XCountry)
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

void CScorersWindowHandler::loadCompetitions(int XSeason, int XCountry, int XCompetition)
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

void CScorersWindowHandler::loadScorers(int XSeason, int XCompetition)
{
    m_scorersList->resetList();
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    IDAOFactory                         *daoFactory		= m_game.getIDAOFactory();
    IPfScorersDAO                       *scorersDAO     = daoFactory->getIPfScorersDAO();
    std::vector<CPfScorers*>            *scorersList    = scorersDAO->findScorersByXSeasonAndXCompetition(XSeason, XCompetition);
    std::vector<CPfScorers*>::iterator  it;
    CEGUI::ListboxTextItem *item;
    char position[4];
    int cont = 1;

    for( it=scorersList->begin(); it!=scorersList->end(); it++ ){
        CPfScorers *scorer = (*it);
        sprintf(position, "%d", cont);

        int row_idx = m_scorersList->addRow();

        item = new CEGUI::ListboxTextItem(position);
        item->setSelectionBrushImage(sel_img);
        m_scorersList->setItem(item, 0, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)scorer->getSTeamPlayer().c_str());
        item->setSelectionBrushImage(sel_img);
        m_scorersList->setItem(item, 1, row_idx);

        item = new CEGUI::ListboxTextItem((CEGUI::utf8*)scorer->getSTeam().c_str());
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

void CScorersWindowHandler::loadLastSeason()
{
    if( m_lastSeason!=NULL ){
        delete m_lastSeason;
        m_lastSeason = NULL;
    }

    IPfSeasonsDAO *seasonsDAO = m_game.getIDAOFactory()->getIPfSeasonsDAO();
    m_lastSeason = seasonsDAO->findLastSeason();
    if( m_lastSeason==NULL || m_lastSeason->getXSeason_str()=="" ){
        throw PFEXCEPTION("[CScreenResults::loadLastSeason] Last season not found");
    }
}

bool CScorersWindowHandler::confederationsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
    loadCountries(m_lastSeason->getXSeason(), item->getID());
    item = m_countriesCombobox->getSelectedItem();
    loadCompetitions(m_lastSeason->getXSeason(), item->getID());
    item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadScorers(m_lastSeason->getXSeason(), XCompetition);
    return true;
}

bool CScorersWindowHandler::countriesComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_countriesCombobox->getSelectedItem();
    loadCompetitions(m_lastSeason->getXSeason(), item->getID());
    item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadScorers(m_lastSeason->getXSeason(), XCompetition);
    return true;
}

bool CScorersWindowHandler::competitionsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_competitionsCombobox->getSelectedItem();
    int XCompetition = item->getID();
    loadScorers(m_lastSeason->getXSeason(), XCompetition);
    return true;
}
