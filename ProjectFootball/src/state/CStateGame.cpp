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

#include "CStateGame.h"

#include "../utils/CLog.h"
#include "../engine/CGameEngine.h"

CStateGame::CStateGame()
    :CState()
{
    CLog::getInstance()->debug("CStateGame()");
    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"game.layout");

    m_playerTeamText    = static_cast<CEGUI::Window*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Game/PlayerTeamText"));
    m_nextMatchText     = static_cast<CEGUI::Window*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Game/NextMatchText"));
    m_playButton        = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Game/PlayButton"));
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

    CPfTeams    *playerTeam = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
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
