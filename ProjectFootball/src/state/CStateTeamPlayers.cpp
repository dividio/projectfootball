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

#include "CStateTeamPlayers.h"
#include "../engine/CGameEngine.h"
#include "../utils/CLog.h"

CStateTeamPlayers::CStateTeamPlayers()
    :CState()
{
    CLog::getInstance()->debug("CStateTeamPlayers()");
    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"teamPlayers.layout");

    m_teamPlayersList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"TeamPlayers/TeamPlayersList"));

    m_teamPlayersList->addColumn("Name", 0, CEGUI::UDim(1.0,0));

    m_teamPlayersList->setUserColumnDraggingEnabled(false);
    m_teamPlayersList->setUserColumnSizingEnabled(false);
    m_teamPlayersList->setUserSortControlEnabled(false);
}

CStateTeamPlayers* CStateTeamPlayers::getInstance()
{
    static CStateTeamPlayers instance;
    return &instance;
}

CStateTeamPlayers::~CStateTeamPlayers()
{
    CLog::getInstance()->debug("~CStateTeamPlayers()");
}

void CStateTeamPlayers::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    loadTeamPlayers();
}

void CStateTeamPlayers::forcedLeave()
{

}

bool CStateTeamPlayers::leave()
{
    return true;
}

void CStateTeamPlayers::update()
{
}

void CStateTeamPlayers::loadTeamPlayers()
{
    m_teamPlayersList->resetList();

    CPfTeams                                *team               = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayersDAO                       *teamPlayersDAO     = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamPlayersDAO();
    std::vector<CPfTeamPlayers*>            *teamPlayersList    = teamPlayersDAO->findActiveTeamPlayersByXFkTeam(team->getXTeam());
    std::vector<CPfTeamPlayers*>::iterator  it;

    for( it=teamPlayersList->begin(); it!=teamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);

        int row_idx = m_teamPlayersList->addRow();
        m_teamPlayersList->setItem(new CEGUI::ListboxTextItem(teamPlayer->getSName()), 0, row_idx);
    }
    teamPlayersDAO->freeVector(teamPlayersList);
    delete team;

    m_teamPlayersList->getHorzScrollbar()->setVisible(false);
}
