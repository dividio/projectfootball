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

#include "CStateGame.h"
#include "CStateManager.h"
#include "CStateMonitor.h"
#include "CStateMatchResult.h"
#include "../utils/CLog.h"
#include "../engine/CGameEngine.h"

CStateGame::CStateGame()
    :CState()
{
    CLog::getInstance()->debug("CStateGame()");

    CEGUI::WindowManager *ceguiWM = &(CEGUI::WindowManager::getSingleton());
    m_sheet = ceguiWM->loadWindowLayout((CEGUI::utf8*)"game.layout");

    m_playerTeamText     = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Game/PlayerTeamText"));
    m_nextMatchText      = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Game/NextMatchText"));
    m_playButton         = static_cast<CEGUI::PushButton*>(ceguiWM->getWindow((CEGUI::utf8*)"Game/PlayButton"));
    m_resultModeCheckBox = static_cast<CEGUI::Checkbox*>(ceguiWM->getWindow((CEGUI::utf8*)"Game/ResultMode"));

    // i18n support
    m_playButton->setText((CEGUI::utf8*)gettext("Play Match"));
    m_resultModeCheckBox->setText((CEGUI::utf8*)gettext("Result Mode"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Game/SaveButton"))->setText((CEGUI::utf8*)gettext("Save"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Game/MainMenuButton"))->setText((CEGUI::utf8*)gettext("Return to Main Menu"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Game/RankingButton"))->setText((CEGUI::utf8*)gettext("Ranking"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Game/TeamPlayersButton"))->setText((CEGUI::utf8*)gettext("Team Players"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Game/ResultsButton"))->setText((CEGUI::utf8*)gettext("Results"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Game/PlayerTeamLabel"))->setText((CEGUI::utf8*)gettext("Your Team:"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Game/NextMatchLabel"))->setText((CEGUI::utf8*)gettext("Next Match:"));
}

CStateGame* CStateGame::getInstance()
{
    static CStateGame instance;
    return &instance;
}

CStateGame::~CStateGame()
{
    CLog::getInstance()->debug("~CStateGame()");
}

void CStateGame::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    IDAOFactory         *daoFactory = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory();
    IPfGameOptionsDAO   *optionsDAO = daoFactory->getIPfGameOptionsDAO();

    CPfGameOptions *resultMode = optionsDAO->findBySCategoryAndSAttribute("Match", "ResultMode");
    if(resultMode->getSValue() == "true") { //result mode
        m_resultModeCheckBox->setSelected(true);
    } else {
        m_resultModeCheckBox->setSelected(false);
    }
    delete resultMode;

    CPfTeams    *playerTeam = daoFactory->getIPfTeamsDAO()->findPlayerTeam();
    m_playerTeamText->setText(playerTeam->getSTeam());
    delete playerTeam;

    CPfMatches  *nextMatch  = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfMatchesDAO()->findNextPlayerTeamMatch();
    if( nextMatch==NULL ){
        m_nextMatchText->setText("No Match");
        m_playButton->setEnabled(false);
    }else{
        IPfTeamsDAO *teamsDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO();
        CPfTeams    *homeTeam = teamsDAO->findByXTeam(nextMatch->getXFkTeamHome());
        CPfTeams    *awayTeam = teamsDAO->findByXTeam(nextMatch->getXFkTeamAway());

        std::string text;
        text += homeTeam->getSTeam()+" - "+awayTeam->getSTeam();
        m_nextMatchText->setText(text);
        m_playButton->setEnabled(true);

        delete homeTeam;
        delete awayTeam;
        delete nextMatch;
    }
}

void CStateGame::forcedLeave()
{
    CGameEngine::getInstance()->unloadCurrentGame();
}

bool CStateGame::leave()
{
    // TODO: Confirm current game unload
    CGameEngine::getInstance()->unloadCurrentGame();
    return true;
}

void CStateGame::update()
{
}

void CStateGame::saveGame()
{
    CGameEngine::getInstance()->getCurrentGame()->save();
}

void CStateGame::resultModeEvent()
{
    IDAOFactory         *daoFactory = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory();
    IPfGameOptionsDAO   *optionsDAO = daoFactory->getIPfGameOptionsDAO();

    CPfGameOptions *resultMode = optionsDAO->findBySCategoryAndSAttribute("Match", "ResultMode");

    if(m_resultModeCheckBox->isSelected()) {
        resultMode->setSValue("true");
    } else {
        resultMode->setSValue("false");
    }
    optionsDAO->updateReg(resultMode);
    delete resultMode;
}

void CStateGame::playButtonEvent()
{
    IDAOFactory         *daoFactory = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory();
    IPfGameOptionsDAO   *optionsDAO = daoFactory->getIPfGameOptionsDAO();

    CPfGameOptions *resultMode = optionsDAO->findBySCategoryAndSAttribute("Match", "ResultMode");

    if(resultMode->getSValue() == "true") {
        CStateManager::getInstance()->pushState(CStateMatchResult::getInstance());
    } else {
        CStateManager::getInstance()->pushState(CStateMonitor::getInstance());
    }
    delete resultMode;
}
