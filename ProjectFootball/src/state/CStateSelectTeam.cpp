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

#include <libintl.h>

#include "CStateSelectTeam.h"
#include "CStateManager.h"
#include "CStateGame.h"
#include "../utils/CLog.h"
#include "../engine/CGameEngine.h"

CStateSelectTeam::CStateSelectTeam()
    :CState()
{
    CLog::getInstance()->debug("CStateSelectTeam()");

    CEGUI::WindowManager *ceguiWM = &(CEGUI::WindowManager::getSingleton());
    m_sheet = ceguiWM->loadWindowLayout((CEGUI::utf8*)"selectTeam.layout");

    m_selectButton        = static_cast<CEGUI::PushButton*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/SelectButton"));
    m_guiTeamsList        = static_cast<CEGUI::Listbox*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/TeamsList"));
    m_guiTeamName         = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/TeamName"));
    m_guiTeamBudget       = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/Budget"));
    m_guiTeamLogo         = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/TeamLogo"));
    m_confederationsCombo = static_cast<CEGUI::Combobox*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/Confederation"));
    m_countriesCombo      = static_cast<CEGUI::Combobox*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/Country"));
    m_competitionsCombo   = static_cast<CEGUI::Combobox*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/Competition"));

    m_confederationsCombo->getEditbox()->setEnabled(false);
    m_confederationsCombo->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&CStateSelectTeam::handleConfederationChange, this));
    m_countriesCombo     ->getEditbox()->setEnabled(false);
    m_countriesCombo     ->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&CStateSelectTeam::handleCountryChange, this));
    m_competitionsCombo  ->getEditbox()->setEnabled(false);
    m_competitionsCombo  ->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&CStateSelectTeam::handleCompetitionChange, this));


    m_guiTeamsList->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&CStateSelectTeam::handleSelectChanged, this));
    m_guiTeamsList->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick, CEGUI::Event::Subscriber(&CStateSelectTeam::handleDoubleClick, this));
    m_guiTeamsList->setWantsMultiClickEvents(true);

    // i18n support
    m_selectButton->setText((CEGUI::utf8*)gettext("Select Team"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"SelectTeam/SelectTeamLabel"))->setText((CEGUI::utf8*)gettext("Please, select your team:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"SelectTeam/NameLabel"))->setText((CEGUI::utf8*)gettext("Name:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"SelectTeam/BudgetLabel"))->setText((CEGUI::utf8*)gettext("Budget:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"SelectTeam/LevelLabel"))->setText((CEGUI::utf8*)gettext("Level:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"SelectTeam/ConfederationLabel"))->setText((CEGUI::utf8*)gettext("Confederation:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"SelectTeam/CountryLabel"))->setText((CEGUI::utf8*)gettext("Country:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"SelectTeam/CompetitionLabel"))->setText((CEGUI::utf8*)gettext("Competition:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"SelectTeam/BackButton"))->setText((CEGUI::utf8*)gettext("Back"));

}

CStateSelectTeam* CStateSelectTeam::getInstance()
{
    static CStateSelectTeam instance;
    return &instance;
}

CStateSelectTeam::~CStateSelectTeam()
{
    CLog::getInstance()->debug("~CStateSelectTeam()");
}

void CStateSelectTeam::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    int confederation = loadConfederationsList();
    int country       = loadCountriesList(confederation);
    int competition   = loadCompetitionsList(country);
    loadTeamList(competition);

    m_selectButton->setEnabled(false);
}

void CStateSelectTeam::forcedLeave()
{

}

bool CStateSelectTeam::leave()
{
    IDAOFactory          *daoFactory        = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory();
    IPfConfederationsDAO *confederationsDAO = daoFactory->getIPfConfederationsDAO();
    IPfCountriesDAO      *countriesDAO      = daoFactory->getIPfCountriesDAO();
    IPfCompetitionsDAO   *competitionsDAO   = daoFactory->getIPfCompetitionsDAO();
    IPfTeamsDAO          *teamsDAO          = daoFactory->getIPfTeamsDAO();

    if(m_confederationsList!=0) {
        confederationsDAO->freeVector(m_confederationsList);
        m_confederationsList = 0;
    }
    if(m_countriesList!=0) {
        countriesDAO->freeVector(m_countriesList);
        m_countriesList = 0;
    }
    if(m_competitionsList!=0) {
        competitionsDAO->freeVector(m_competitionsList);
        m_competitionsList = 0;
    }
    if(m_teamsList!=0) {
        teamsDAO->freeVector(m_teamsList);
        m_teamsList = 0;
    }

    m_confederationsCombo->resetList();
    m_countriesCombo     ->resetList();
    m_competitionsCombo  ->resetList();
    m_guiTeamsList       ->resetList();
    clearTeamInfo();

    return true;
}

void CStateSelectTeam::update()
{
}

int CStateSelectTeam::loadConfederationsList()
{
    IPfConfederationsDAO *confederationsDAO = CGameEngine::getInstance()->getCurrentGame()
                                            ->getIDAOFactory()->getIPfConfederationsDAO();
    if(m_confederationsList!=0) {
        confederationsDAO->freeVector(m_confederationsList);
    }
    m_confederationsList = confederationsDAO->findConfederations();


    std::vector<CPfConfederations*>::iterator it;
    for(it = m_confederationsList->begin(); it != m_confederationsList->end(); it++) {
        CPfConfederations *confederation = (*it);
        m_confederationsCombo->addItem(new CEGUI::ListboxTextItem
                (confederation->getSConfederation(), confederation->getXConfederation()));
    }
    m_confederationsCombo->setText(m_confederationsList->front()->getSConfederation());
    return m_confederationsList->front()->getXConfederation();
}

int CStateSelectTeam::loadCountriesList(int XConfederation)
{
    IPfCountriesDAO *countriesDAO = CGameEngine::getInstance()->getCurrentGame()
                                            ->getIDAOFactory()->getIPfCountriesDAO();

    if(m_countriesList!=0) {
        countriesDAO->freeVector(m_countriesList);
    }
    m_countriesList = countriesDAO->findByXFkConfederation(XConfederation);
    int selectedCountry = -1;

    if(!m_countriesList->empty()) {
        std::vector<CPfCountries*>::iterator it;
        for(it = m_countriesList->begin(); it != m_countriesList->end(); it++) {
            CPfCountries *country = (*it);
            m_countriesCombo->addItem(new CEGUI::ListboxTextItem
                    (country->getSCountry(), country->getXCountry()));
        }
        m_countriesCombo->setText(m_countriesList->front()->getSCountry());

        selectedCountry = m_countriesList->front()->getXCountry();
    } else {
        m_countriesCombo->setText((CEGUI::utf8*)gettext("No countries"));
    }

    return selectedCountry;
}

int CStateSelectTeam::loadCompetitionsList(int XCountry)
{
    IPfCompetitionsDAO *competitionsDAO = CGameEngine::getInstance()->getCurrentGame()
                                            ->getIDAOFactory()->getIPfCompetitionsDAO();
    if(m_competitionsList!=0) {
        competitionsDAO->freeVector(m_competitionsList);
    }
    m_competitionsList = competitionsDAO->findByXFkCountry(XCountry);
    int selectedCompetition = -1;

    if(!m_competitionsList->empty()) {
        std::vector<CPfCompetitions*>::iterator it;
        for(it = m_competitionsList->begin(); it != m_competitionsList->end(); it++) {
            CPfCompetitions *competition = (*it);
            m_competitionsCombo->addItem(new CEGUI::ListboxTextItem
                    (competition->getSCompetition(), competition->getXCompetition()));
        }
        m_competitionsCombo->setText(m_competitionsList->front()->getSCompetition());
        selectedCompetition = m_competitionsList->front()->getXCompetition();
    } else {
        m_competitionsCombo->setText((CEGUI::utf8*)gettext("No competitions"));
    }

    return selectedCompetition;
}

void CStateSelectTeam::loadTeamList(int XCompetition)
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("ListboxSelectionBrush");

    IPfTeamsDAO* teamsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO();

    if(m_teamsList!=0) {
        teamsDAO->freeVector(m_teamsList);
    }
    m_teamsList = teamsDAO->findTeamsByXCompetition(XCompetition);

    if(!m_teamsList->empty()) {
        std::vector<CPfTeams*>::iterator it;
        for( it=m_teamsList->begin(); it!=m_teamsList->end(); it++ ){
            CPfTeams *team = (*it);

            CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(team->getSTeam());
            item->setSelectionBrushImage(sel_img);
            item->setID(team->getXTeam());
            m_guiTeamsList->addItem(item);
        }
    }
}

void CStateSelectTeam::selectTeam()
{
    CEGUI::ListboxItem* item = m_guiTeamsList->getFirstSelectedItem();
    std::ostringstream xTeam;
    xTeam << item->getID();

    IPfGameStatesDAO *gameStateDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfGameStatesDAO();

    CPfGameStates playerTeam;
    playerTeam.setSState(S_STATE_PLAYERTEAM);
    playerTeam.setSValue(xTeam.str());
    gameStateDAO->insertReg(&playerTeam);

    CPfGameStates *newGameState = gameStateDAO->findBySState(S_STATE_NEWGAME);
    newGameState->setSValue("false");
    gameStateDAO->updateReg(newGameState);
    delete newGameState;

    // Pop two states: selectTeam state and loadGame state
    CStateManager::getInstance()->popState();
    CStateManager::getInstance()->popState();
    CStateManager::getInstance()->pushState(CStateGame::getInstance());
}

bool CStateSelectTeam::handleSelectChanged(const CEGUI::EventArgs& e)
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

bool CStateSelectTeam::handleConfederationChange(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_confederationsCombo->getSelectedItem();
    if(item!=0) {
        m_confederationsCombo->setText(item->getText());
        m_countriesCombo->clearAllSelections();
        m_countriesCombo->resetList();
        m_countriesCombo->getEditbox()->setText("");
        m_competitionsCombo->clearAllSelections();
        m_competitionsCombo->resetList();
        m_competitionsCombo->getEditbox()->setText("");
        m_guiTeamsList->resetList();
        m_selectButton->setEnabled(false);
        clearTeamInfo();

        int country     = loadCountriesList(item->getID());
        int competition = loadCompetitionsList(country);
        loadTeamList(competition);
    }
    return true;
}

bool CStateSelectTeam::handleCountryChange(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_countriesCombo->getSelectedItem();
    if(item!=0) {
        m_countriesCombo->setText(item->getText());
        m_competitionsCombo->clearAllSelections();
        m_competitionsCombo->resetList();
        m_competitionsCombo->getEditbox()->setText("");
        m_guiTeamsList->resetList();
        m_selectButton->setEnabled(false);
        clearTeamInfo();

        int competition = loadCompetitionsList(item->getID());
        loadTeamList(competition);
    }
    return true;
}

bool CStateSelectTeam::handleCompetitionChange(const CEGUI::EventArgs& e)
{
    CEGUI::ListboxItem *item = m_competitionsCombo->getSelectedItem();
    if(item!=0) {
        m_competitionsCombo->setText(item->getText());
        m_guiTeamsList->resetList();
        m_selectButton->setEnabled(false);
        clearTeamInfo();

        loadTeamList(item->getID());
    }
    return true;
}

bool CStateSelectTeam::handleDoubleClick(const CEGUI::EventArgs& e)
{
    if(m_guiTeamsList->getFirstSelectedItem()!=0) {
        selectTeam();
    }
    return true;
}

void CStateSelectTeam::loadTeamInfo(CPfTeams *team)
{
    // TODO Add more team information
    char budget[10];
    m_guiTeamName->setProperty("Text", team->getSTeam());
    sprintf(budget, "%d", team->getNBudget());
    m_guiTeamBudget->setProperty("Text", budget);

    //Loading logo
    CEGUI::String imagesetName = "TeamLogo" + team->getXTeam_str();
    if(!CEGUI::ImagesetManager::getSingleton().isImagesetPresent(imagesetName)) {
        CEGUI::ImagesetManager::getSingleton().createImagesetFromImageFile(imagesetName, team->getSLogo());
    }

    m_guiTeamLogo->setProperty("Image", "set:"+ imagesetName +" image:full_image");
}

void CStateSelectTeam::clearTeamInfo()
{
    // TODO Clear all team information
    m_guiTeamName  ->setProperty("Text", "");
    m_guiTeamBudget->setProperty("Text", "");
    m_guiTeamLogo  ->setProperty("Image", "");
}
