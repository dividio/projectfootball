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

    m_selectButton  = static_cast<CEGUI::PushButton*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/SelectButton"));
    m_guiTeamsList  = static_cast<CEGUI::Listbox*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/TeamsList"));
    m_guiTeamName   = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"SelectTeam/TeamName"));

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
            (CEGUI::utf8*)"SelectTeam/Country"))->setText((CEGUI::utf8*)gettext("Region/Country/Division"));
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

    loadTeamList();

    m_selectButton->setEnabled(false);
}

void CStateSelectTeam::forcedLeave()
{

}

bool CStateSelectTeam::leave()
{
    IPfTeamsDAO* teamsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO();
    teamsDAO->freeVector(m_teamsList);
    clearTeamInfo();
    return true;
}

void CStateSelectTeam::update()
{
}

void CStateSelectTeam::loadTeamList()
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("ListboxSelectionBrush");

    m_guiTeamsList->resetList();

    IPfTeamsDAO* teamsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO();
    m_teamsList = teamsDAO->findTeams();
    std::vector<CPfTeams*>::iterator it;
    for( it=m_teamsList->begin(); it!=m_teamsList->end(); it++ ){
        CPfTeams *team = (*it);

        CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(team->getSTeam());
        item->setSelectionBrushImage(sel_img);
        item->setID(team->getXTeam());
        m_guiTeamsList->addItem(item);
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

    // Pop two state: selectTeam state and loadGame state
    CStateManager::getInstance()->popState();
    CStateManager::getInstance()->popState();
    CStateManager::getInstance()->pushState(CStateGame::getInstance());
}

bool CStateSelectTeam::handleSelectChanged(const CEGUI::EventArgs& e)
{
    if(m_guiTeamsList->getFirstSelectedItem()!=NULL) {
        m_selectButton->setEnabled(true);
        CEGUI::ListboxItem* item = m_guiTeamsList->getFirstSelectedItem();
        uint xTeam = item->getID();

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

bool CStateSelectTeam::handleDoubleClick(const CEGUI::EventArgs& e)
{
    if( m_guiTeamsList->getFirstSelectedItem()!=NULL ){
        selectTeam();
    }
    return true;
}

void CStateSelectTeam::loadTeamInfo(CPfTeams *team)
{
    // TODO Add more team information
    m_guiTeamName->setProperty("Text", team->getSTeam());
}

void CStateSelectTeam::clearTeamInfo()
{
    // TODO Clear all team information
    m_guiTeamName->setProperty("Text", "");
}
