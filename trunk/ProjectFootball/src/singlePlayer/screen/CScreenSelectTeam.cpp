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

#include "CScreenSelectTeam.h"

#include <libintl.h>

#include "CScreenGame.h"
#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeams.h"
#include "../db/bean/CPfConfederations.h"
#include "../db/bean/CPfCountries.h"
#include "../db/bean/CPfCompetitions.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../utils/CLog.h"


CScreenSelectTeam::CScreenSelectTeam(CSinglePlayerGame *game)
    :CScreen("selectTeam.layout")
{
    CLog::getInstance()->debug("CScreenSelectTeam()");

    m_game = game;
    m_confederationsList	= NULL;
    m_countriesList			= NULL;
    m_competitionsList		= NULL;
    m_teamsList				= NULL;

    m_selectButton        		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/SelectButton"));
    m_backButton				= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/BackButton"));
    m_guiTeamsList        		= static_cast<CEGUI::Listbox*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/TeamsList"));
    m_guiTeamName         		= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/TeamName"));
    m_guiTeamBudget       		= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/TeamBudget"));
    m_guiTeamShield             = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/TeamShield"));
    m_guiConfederationImage     = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/ConfederationImage"));
    m_guiCountryImage           = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/CountryImage"));
    m_guiTeamAverage            = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/TeamAverage"));
    m_confederationsCombobox	= static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/Confederation"));
    m_countriesCombobox      	= static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/Country"));
    m_competitionsCombobox   	= static_cast<CEGUI::Combobox*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/Competition"));

    m_confederationsCombobox->getEditbox()->setEnabled(false);
    m_countriesCombobox     ->getEditbox()->setEnabled(false);
    m_competitionsCombobox  ->getEditbox()->setEnabled(false);
    m_guiTeamsList->setWantsMultiClickEvents(true);

    // i18n support
    m_backButton  ->setText((CEGUI::utf8*)gettext("Back"));
    m_selectButton->setText((CEGUI::utf8*)gettext("Select Team"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/SelectTeamLabel"))->setText((CEGUI::utf8*)gettext("Please, select your team:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/NameLabel"))->setText((CEGUI::utf8*)gettext("Name:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/BudgetLabel"))->setText((CEGUI::utf8*)gettext("Budget:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/AverageLabel"))->setText((CEGUI::utf8*)gettext("Average:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/ConfederationLabel"))->setText((CEGUI::utf8*)gettext("Confederation:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/CountryLabel"))->setText((CEGUI::utf8*)gettext("Country:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"SelectTeam/CompetitionLabel"))->setText((CEGUI::utf8*)gettext("Competition:"));

    // Event handle
    m_confederationsCombobox->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenSelectTeam::confederationsComboboxListSelectionChanged, this));
    m_countriesCombobox     ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenSelectTeam::countriesComboboxListSelectionChanged, this));
    m_competitionsCombobox  ->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted, CEGUI::Event::Subscriber(&CScreenSelectTeam::competitionsComboboxListSelectionChanged, this));
    m_guiTeamsList->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&CScreenSelectTeam::teamsListboxSelectionChanged, this));
    m_guiTeamsList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick, CEGUI::Event::Subscriber(&CScreenSelectTeam::teamsListboxMouseDoubleClick, this));
    m_selectButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenSelectTeam::selectButtonClicked, this));
    m_backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenSelectTeam::backButtonClicked, this));

}

CScreenSelectTeam::~CScreenSelectTeam()
{
    CLog::getInstance()->debug("~CScreenSelectTeam()");
}

void CScreenSelectTeam::enter()
{
    CScreen::enter();

    int confederation = loadConfederationsList();
    int country       = loadCountriesList(confederation);
    int competition   = loadCompetitionsList(country);
    loadTeamList(competition);

    m_selectButton->setEnabled(false);
}

void CScreenSelectTeam::leave()
{
    if(m_confederationsList!=NULL) {
        m_game->getIDAOFactory()->getIPfConfederationsDAO()->freeVector(m_confederationsList);
        m_confederationsList = NULL;
    }
    if(m_countriesList!=NULL) {
        m_game->getIDAOFactory()->getIPfCountriesDAO()->freeVector(m_countriesList);
        m_countriesList = NULL;
    }
    if(m_competitionsList!=NULL) {
        m_game->getIDAOFactory()->getIPfCompetitionsDAO()->freeVector(m_competitionsList);
        m_competitionsList = NULL;
    }
    if(m_teamsList!=NULL) {
        m_game->getIDAOFactory()->getIPfTeamsDAO()->freeVector(m_teamsList);
        m_teamsList = NULL;
    }

    m_confederationsCombobox->resetList();
    m_countriesCombobox     ->resetList();
    m_competitionsCombobox  ->resetList();
    m_guiTeamsList			->resetList();
    clearTeamInfo();
}

int CScreenSelectTeam::loadConfederationsList()
{
    IPfConfederationsDAO *confederationsDAO = m_game->getIDAOFactory()->getIPfConfederationsDAO();
    if(m_confederationsList!=NULL) {
        confederationsDAO->freeVector(m_confederationsList);
    }
    m_confederationsList = confederationsDAO->findConfederationsWithLeague();


    std::vector<CPfConfederations*>::iterator it;
    for(it = m_confederationsList->begin(); it != m_confederationsList->end(); it++) {
        CPfConfederations *confederation = (*it);
        m_confederationsCombobox->addItem(new CEGUI::ListboxTextItem
                ((CEGUI::utf8*)confederation->getSConfederation().c_str(), confederation->getXConfederation()));
    }

    CPfConfederations *conf = m_confederationsList->front();
    m_confederationsCombobox->setText((CEGUI::utf8*)conf->getSConfederation().c_str());
    m_guiConfederationImage->setProperty("Image", "set:"+ conf->getSLogo() +" image:"+conf->getSLogo()+"_map");
    return m_confederationsList->front()->getXConfederation();
}

int CScreenSelectTeam::loadCountriesList(int XConfederation)
{
    IPfCountriesDAO *countriesDAO = m_game->getIDAOFactory()->getIPfCountriesDAO();

    if(m_countriesList!=NULL) {
        countriesDAO->freeVector(m_countriesList);
    }
    m_countriesList = countriesDAO->findByXFkConfederationWithLeague(XConfederation);
    int selectedCountry = -1;

    if(!m_countriesList->empty()) {
        std::vector<CPfCountries*>::iterator it;
        for(it = m_countriesList->begin(); it != m_countriesList->end(); it++) {
            CPfCountries *country = (*it);
            m_countriesCombobox->addItem(new CEGUI::ListboxTextItem
                    ((CEGUI::utf8*)country->getSShortName().c_str(), country->getXCountry()));
        }
        CPfCountries *country = m_countriesList->front();
        m_countriesCombobox->setText((CEGUI::utf8*)country->getSShortName().c_str());
        m_guiCountryImage->setProperty("Image", "set:"+ country->getSFlag() +" image:"+country->getSFlag()+"_map");

        selectedCountry = m_countriesList->front()->getXCountry();
    } else {
        m_countriesCombobox->setText((CEGUI::utf8*)gettext("No countries"));
    }

    return selectedCountry;
}

int CScreenSelectTeam::loadCompetitionsList(int XCountry)
{
    IPfCompetitionsDAO *competitionsDAO = m_game->getIDAOFactory()->getIPfCompetitionsDAO();
    if(m_competitionsList!=NULL) {
        competitionsDAO->freeVector(m_competitionsList);
    }
    m_competitionsList = competitionsDAO->findByXFkCountry(XCountry);
    int selectedCompetition = -1;

    if(!m_competitionsList->empty()) {
        std::vector<CPfCompetitions*>::iterator it;
        for(it = m_competitionsList->begin(); it != m_competitionsList->end(); it++) {
            CPfCompetitions *competition = (*it);
            m_competitionsCombobox->addItem(new CEGUI::ListboxTextItem
                    ((CEGUI::utf8*)competition->getSCompetition().c_str(), competition->getXCompetition()));
        }
        m_competitionsCombobox->setText((CEGUI::utf8*)m_competitionsList->front()->getSCompetition().c_str());
        selectedCompetition = m_competitionsList->front()->getXCompetition();
    } else {
        m_competitionsCombobox->setText((CEGUI::utf8*)gettext("No competitions"));
    }

    return selectedCompetition;
}

void CScreenSelectTeam::loadTeamList(int XCompetition)
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("ListboxSelectionBrush");

    IPfTeamsDAO* teamsDAO = m_game->getIDAOFactory()->getIPfTeamsDAO();

    if(m_teamsList!=NULL) {
        teamsDAO->freeVector(m_teamsList);
    }
    m_teamsList = teamsDAO->findTeamsByXCompetition(XCompetition);

    if(!m_teamsList->empty()) {
        std::vector<CPfTeams*>::iterator it;
        for( it=m_teamsList->begin(); it!=m_teamsList->end(); it++ ){
            CPfTeams *team = (*it);

            CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)team->getSTeam().c_str());
            item->setSelectionBrushImage(sel_img);
            item->setID(team->getXTeam());
            m_guiTeamsList->addItem(item);
        }
    }
}

bool CScreenSelectTeam::teamsListboxSelectionChanged(const CEGUI::EventArgs& e)
{
    if(m_guiTeamsList->getFirstSelectedItem()!=0 && m_teamsList!=0) {
        m_selectButton->setEnabled(true);
        CEGUI::ListboxItem* item = m_guiTeamsList->getFirstSelectedItem();
        int xTeam = item->getID();

        std::vector<CPfTeams*>::iterator it;
        bool found=false;
        it=m_teamsList->begin();
        while(it!=m_teamsList->end() && !found) {
            CPfTeams *team = (*it);
            if(team->getXTeam() == xTeam) {
                loadTeamInfo(team);
                found = true;
            }
            it++;
        }
    } else {
        m_selectButton->setEnabled(false);
        clearTeamInfo();
    }
    return true;
}

bool CScreenSelectTeam::confederationsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_confederationsCombobox->getSelectedItem();
    if(item!=0) {
        IPfConfederationsDAO *confederationsDAO = m_game->getIDAOFactory()->getIPfConfederationsDAO();
        CPfConfederations    *conf = confederationsDAO->findByXConfederation(item->getID());

        m_confederationsCombobox->setText(item->getText());
        m_guiConfederationImage->setProperty("Image", "set:"+ conf->getSLogo() +" image:"+conf->getSLogo()+"_map");
        m_countriesCombobox->clearAllSelections();
        m_countriesCombobox->resetList();
        m_countriesCombobox->getEditbox()->setText("");
        m_guiCountryImage->setProperty("Image", "set: image:full_image");
        m_competitionsCombobox->clearAllSelections();
        m_competitionsCombobox->resetList();
        m_competitionsCombobox->getEditbox()->setText("");
        m_guiTeamsList->resetList();
        m_selectButton->setEnabled(false);
        clearTeamInfo();

        int country     = loadCountriesList(item->getID());
        int competition = loadCompetitionsList(country);
        loadTeamList(competition);
    }
    return true;
}

bool CScreenSelectTeam::countriesComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_countriesCombobox->getSelectedItem();
    if(item!=0) {
        IPfCountriesDAO *countriesDAO = m_game->getIDAOFactory()->getIPfCountriesDAO();
        CPfCountries    *country = countriesDAO->findByXCountry(item->getID());

        m_countriesCombobox->setText(item->getText());
        m_guiCountryImage->setProperty("Image", "set:"+ country->getSFlag() +" image:"+country->getSFlag()+"_map");
        m_competitionsCombobox->clearAllSelections();
        m_competitionsCombobox->resetList();
        m_competitionsCombobox->getEditbox()->setText("");
        m_guiTeamsList->resetList();
        m_selectButton->setEnabled(false);
        clearTeamInfo();

        int competition = loadCompetitionsList(item->getID());
        loadTeamList(competition);
    }
    return true;
}

bool CScreenSelectTeam::competitionsComboboxListSelectionChanged(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_competitionsCombobox->getSelectedItem();
    if(item!=0) {
        m_competitionsCombobox->setText(item->getText());
        m_guiTeamsList->resetList();
        m_selectButton->setEnabled(false);
        clearTeamInfo();

        loadTeamList(item->getID());
    }
    return true;
}

bool CScreenSelectTeam::teamsListboxMouseDoubleClick(const CEGUI::EventArgs& e)
{
    if(m_guiTeamsList->getFirstSelectedItem()!=0) {
        selectButtonClicked(e);
    }
    return true;
}

bool CScreenSelectTeam::selectButtonClicked(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem* item = m_guiTeamsList->getFirstSelectedItem();
    std::ostringstream xTeam;
    xTeam << item->getID();

    IPfGameStatesDAO *gameStateDAO = m_game->getIDAOFactory()->getIPfGameStatesDAO();

    CPfGameStates playerTeam;
    playerTeam.setSState(S_STATE_PLAYERTEAM);
    playerTeam.setSValue(xTeam.str());
    gameStateDAO->insertReg(&playerTeam);

    CPfGameStates *newGameState = gameStateDAO->findBySState(S_STATE_NEWGAME);
    newGameState->setSValue("false");
    gameStateDAO->updateReg(newGameState);
    delete newGameState;

    m_game->nextScreen(m_game->getGameScreen());
    return true;
}

bool CScreenSelectTeam::backButtonClicked(const CEGUI::EventArgs& e)
{
    m_game->previousScreen();
    return true;
}

void CScreenSelectTeam::loadTeamInfo(CPfTeams *team)
{
    // TODO Add more team information
    m_guiTeamName->setProperty("Text", (CEGUI::utf8*)team->getSTeam().c_str());
    std::ostringstream budget;
    budget << team->getNBudget();
    m_guiTeamBudget->setProperty("Text", (CEGUI::utf8*)budget.str().c_str());

    IPfTeamAveragesDAO *teamAveragesDAO = m_game->getIDAOFactory()->getIPfTeamAveragesDAO();
    CPfTeamAverages    *teamAverage     = teamAveragesDAO->findByXTeam(team->getXTeam_str());
    std::ostringstream average;
    average << teamAverage->getNTotal();
    m_guiTeamAverage->setProperty("Text", (CEGUI::utf8*)average.str().c_str());
    delete teamAverage;

    //Loading Shield
    m_guiTeamShield->setProperty("Image", "set:"+ team->getSLogo() +" image:"+team->getSLogo()+"_b");
}

void CScreenSelectTeam::clearTeamInfo()
{
    // TODO Clear all team information
    m_guiTeamName   ->setProperty("Text", "");
    m_guiTeamBudget ->setProperty("Text", "");
    m_guiTeamAverage->setProperty("Text", "");
    m_guiTeamShield ->setProperty("Image", "");
}
