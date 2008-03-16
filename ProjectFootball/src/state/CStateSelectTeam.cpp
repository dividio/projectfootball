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

#include "CStateSelectTeam.h"

#include "CStateManager.h"
#include "CStateGame.h"
#include "../utils/CLog.h"
#include "../engine/CGameEngine.h"

CStateSelectTeam::CStateSelectTeam()
    :CState()
{
    CLog::getInstance()->debug("CStateSelectTeam()");
    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"selectTeam.layout");

    CEGUI::Listbox* ceguiTeamsList = static_cast<CEGUI::Listbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"SelectTeam/TeamsList"));
    ceguiTeamsList->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&CStateSelectTeam::handleSelectChanged, this));
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

    CEGUI::PushButton* selectButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"SelectTeam/SelectButton"));
    selectButton->setEnabled(false);
}

void CStateSelectTeam::forcedLeave()
{

}

bool CStateSelectTeam::leave()
{
    return true;
}

void CStateSelectTeam::update()
{
}

void CStateSelectTeam::loadTeamList()
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("ListboxSelectionBrush");

    CEGUI::Listbox* ceguiTeamsList = static_cast<CEGUI::Listbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"SelectTeam/TeamsList"));
    ceguiTeamsList->resetList();

    IPfTeamsDAO*                    teamsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO();
    std::vector<CPfTeams*>*         teamsList = teamsDAO->findTeams();
    std::vector<CPfTeams*>::iterator it;
    for( it=teamsList->begin(); it!=teamsList->end(); it++ ){
        CPfTeams *team = (*it);

        CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(team->getSTeam());
        item->setSelectionBrushImage(sel_img);
        item->setID(team->getXTeam());
        ceguiTeamsList->addItem(item);
    }
    teamsDAO->freeVector(teamsList);
}

void CStateSelectTeam::selectTeam()
{
    CEGUI::Listbox* teamsList = static_cast<CEGUI::Listbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"SelectTeam/TeamsList"));
    CEGUI::ListboxItem* item = teamsList->getFirstSelectedItem();
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

    CStateManager::getInstance()->popState();
    CStateManager::getInstance()->pushState(CStateGame::getInstance());
}

bool CStateSelectTeam::handleSelectChanged(const CEGUI::EventArgs& e)
{
    CEGUI::Listbox* teamsList = static_cast<CEGUI::Listbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"SelectTeam/TeamsList"));
    CEGUI::ListboxItem* item = teamsList->getFirstSelectedItem();

    CEGUI::PushButton* ceguiSelectButton = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"SelectTeam/SelectButton"));
    ceguiSelectButton->setEnabled(item!=NULL);

    return true;
}
