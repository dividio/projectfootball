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

#include "CViewOpponentWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeamPlayers.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"


CViewOpponentWindowHandler::CViewOpponentWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("viewOpponent.layout"),
	m_game(game),
	m_initiated(false)
{
    LOG_DEBUG("CViewOpponentWindowHandler()");
}

CViewOpponentWindowHandler::~CViewOpponentWindowHandler()
{
    LOG_DEBUG("~CViewOpponentWindowHandler()");

    if( m_initiated ){
		m_teamPlayersList->removeColumnWithID(0);
		m_teamPlayersList->removeColumnWithID(1);
		m_teamPlayersList->removeColumnWithID(2);
		m_teamPlayersList->removeColumnWithID(3);

        m_opponentTeamPlayersList->removeColumnWithID(0);
        m_opponentTeamPlayersList->removeColumnWithID(1);
        m_opponentTeamPlayersList->removeColumnWithID(2);
        m_opponentTeamPlayersList->removeColumnWithID(3);
    }
}

void CViewOpponentWindowHandler::enter()
{
    const CPfMatches  *match = m_game.getCurrentMatch();
    CPfTeams          *team  = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
    loadTeamInfo(team);
    if(match != NULL) {
        int xTeam = team->getXTeam();
        int auxXTeam = match->getXFkTeamHome();
        if(xTeam == auxXTeam) {
            auxXTeam = match->getXFkTeamAway();
        }
        delete team;
        team = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(auxXTeam);
        loadOpponentTeamInfo(team);
    } else {
        m_opponentTeamName   ->setText("");
        m_opponentTeamAverage->setText("");
        m_opponentTeamBadge  ->setProperty("Image", "set: image:full_image");
    }
    delete team;

    m_teamPlayersList        ->getHorzScrollbar()->setVisible(false);
    m_teamPlayersList        ->getVertScrollbar()->setVisible(false);
    m_opponentTeamPlayersList->getHorzScrollbar()->setVisible(false);
    m_opponentTeamPlayersList->getVertScrollbar()->setVisible(false);
}

void CViewOpponentWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

	m_teamPlayersList = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/TeamPlayersList"));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Name"), 0, CEGUI::UDim(0.55,0));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Speed"), 1, CEGUI::UDim(0.15,0));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Shot power"), 2, CEGUI::UDim(0.15,0));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Average"), 3, CEGUI::UDim(0.15,0));
	m_teamPlayersList->setUserColumnDraggingEnabled(false);
    m_teamPlayersList->setUserColumnSizingEnabled(false);
    m_teamPlayersList->setUserSortControlEnabled(false);
    m_teamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);

    m_opponentTeamPlayersList = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/OpponentTeamPlayersList"));
    m_opponentTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Name"), 0, CEGUI::UDim(0.55,0));
    m_opponentTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Speed"), 1, CEGUI::UDim(0.15,0));
    m_opponentTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Shot power"), 2, CEGUI::UDim(0.15,0));
    m_opponentTeamPlayersList->addColumn((CEGUI::utf8*)gettext("Average"), 3, CEGUI::UDim(0.15,0));
    m_opponentTeamPlayersList->setUserColumnDraggingEnabled(false);
    m_opponentTeamPlayersList->setUserColumnSizingEnabled(false);
    m_opponentTeamPlayersList->setUserSortControlEnabled(false);
    m_opponentTeamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);

    m_teamName				= static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/TeamName"));
    m_teamAverage			= static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/TeamAverage"));
    m_teamBadge				= static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/TeamBadge"));

    m_opponentTeamName      = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/OpponentTeamName"));
    m_opponentTeamAverage   = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/OpponentTeamAverage"));
    m_opponentTeamBadge     = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/OpponentTeamBadge"));

    // i18n support
    windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/TeamLabel")->setText((CEGUI::utf8*)gettext("Your Team:"));
    windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/TeamAverageLabel")->setText((CEGUI::utf8*)gettext("Average:"));

    windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/OpponentTeamLabel")->setText((CEGUI::utf8*)gettext("Opponent Team:"));
    windowMngr.getWindow((CEGUI::utf8*)"ViewOpponent/OpponentTeamAverageLabel")->setText((CEGUI::utf8*)gettext("Average:"));

    m_initiated = true;
}

void CViewOpponentWindowHandler::leave()
{

}

void CViewOpponentWindowHandler::loadTeamInfo(CPfTeams *team)
{
    std::string        currentTimestamp = m_game.getCurrentTime().getTimestamp();
    IPfTeamAveragesDAO *teamAveragesDAO = m_game.getIDAOFactory()->getIPfTeamAveragesDAO();
    CPfTeamAverages    *teamAverage     = teamAveragesDAO->findByXTeam(team->getXTeam_str(), currentTimestamp);

    m_teamName   ->setText((CEGUI::utf8*)team->getSTeam().c_str());
    std::ostringstream average;
    average << teamAverage->getNTotal();
    m_teamAverage->setText((CEGUI::utf8*)average.str().c_str());
    delete teamAverage;

    //Loading Badge
    m_teamBadge->setProperty("Image", "set:"+ team->getSLogo() +" image:"+team->getSLogo()+"_b");

    loadTeamPlayersList(team, m_teamPlayersList);
}

void CViewOpponentWindowHandler::loadOpponentTeamInfo(CPfTeams *team)
{
    std::string        currentTimestamp = m_game.getCurrentTime().getTimestamp();
    IPfTeamAveragesDAO *teamAveragesDAO = m_game.getIDAOFactory()->getIPfTeamAveragesDAO();
    CPfTeamAverages    *teamAverage     = teamAveragesDAO->findByXTeam(team->getXTeam_str(), currentTimestamp);

    m_opponentTeamName   ->setText((CEGUI::utf8*)team->getSTeam().c_str());
    std::ostringstream average;
    average << teamAverage->getNTotal();
    m_opponentTeamAverage->setText((CEGUI::utf8*)average.str().c_str());
    delete teamAverage;

    //Loading Badge
    m_opponentTeamBadge->setProperty("Image", "set:"+ team->getSLogo() +" image:"+team->getSLogo()+"_b");

    loadTeamPlayersList(team, m_opponentTeamPlayersList);
}

void CViewOpponentWindowHandler::loadTeamPlayersList(CPfTeams *team, CEGUI::MultiColumnList *list)
{
    list->resetList();

    std::string                     currentTimestamp            = m_game.getCurrentTime().getTimestamp();
    IPfTeamPlayersDAO               *teamPlayersDAO             = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();
    std::vector<CPfTeamPlayers*>    *lineUpTeamPlayersList      = teamPlayersDAO->findLineUpByXFkTeam(team->getXTeam(), currentTimestamp);

    std::vector<CPfTeamPlayers*>::iterator it;
    for( it=lineUpTeamPlayersList->begin(); it!=lineUpTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);
        addPlayerToList(teamPlayer, list);
    }

    teamPlayersDAO->freeVector(lineUpTeamPlayersList);
}

void CViewOpponentWindowHandler::addPlayerToList(CPfTeamPlayers *player, CEGUI::MultiColumnList *list)
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    int row_idx = list->addRow();
    int XTeamPlayer = player->getXTeamPlayer();
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getSShortName().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 0, row_idx);

    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNSpeed_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 1, row_idx);

    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNKickPower_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 2, row_idx);

    CPfTeamPlayerAverages *playerAverage = m_game.getIDAOFactory()->getIPfTeamPlayerAveragesDAO()->findByXTeamPlayer(player->getXTeamPlayer_str());
    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)playerAverage->getNTotal_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 3, row_idx);
    delete playerAverage;
}

