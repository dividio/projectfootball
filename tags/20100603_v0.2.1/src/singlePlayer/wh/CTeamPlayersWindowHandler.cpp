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

#include "CTeamPlayersWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeamPlayers.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"


CTeamPlayersWindowHandler::CTeamPlayersWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("teamPlayers.layout"),
	m_game(game),
	m_initiated(false)
{
    LOG_DEBUG("CTeamPlayersWindowHandler()");
}

CTeamPlayersWindowHandler::~CTeamPlayersWindowHandler()
{
    LOG_DEBUG("~CTeamPlayersWindowHandler()");

    if( m_initiated ){
		m_teamPlayersList->removeColumnWithID(0);
		m_teamPlayersList->removeColumnWithID(1);
		m_teamPlayersList->removeColumnWithID(2);
		m_teamPlayersList->removeColumnWithID(3);
		m_teamPlayersList->removeColumnWithID(4);
    }
}

void CTeamPlayersWindowHandler::enter()
{
    loadTeamPlayersList();
}

void CTeamPlayersWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

	m_teamPlayersList = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayers/TeamPlayersList"));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Name"), 0, CEGUI::UDim(0.35,0));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Country"), 1, CEGUI::UDim(0.20,0));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Speed"), 2, CEGUI::UDim(0.15,0));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Shot power"), 3, CEGUI::UDim(0.15,0));
	m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Average"), 4, CEGUI::UDim(0.15,0));
	m_teamPlayersList->setUserColumnDraggingEnabled(false);
    m_teamPlayersList->setUserColumnSizingEnabled(false);
    m_teamPlayersList->setUserSortControlEnabled(true);
    m_teamPlayersList->setSelectionMode(CEGUI::MultiColumnList::RowMultiple);

    m_teamName				= static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayers/TeamName"));
    m_teamAverage			= static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayers/TeamAverage"));
    m_teamBadge				= static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayers/TeamBadge"));

    // i18n support
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayers/TeamPlayersLabel")->setText((CEGUI::utf8*)gettext("Team Players:"));
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayers/TeamAverageLabel")->setText((CEGUI::utf8*)gettext("Average:"));

    // events
    registerEventConnection(m_teamPlayersList->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged, CEGUI::Event::Subscriber(&CTeamPlayersWindowHandler::teamPlayersListboxSelectionChanged, this)));

    m_initiated = true;
}

void CTeamPlayersWindowHandler::leave()
{

}

void CTeamPlayersWindowHandler::loadTeamPlayersList()
{
    m_teamPlayersList   ->resetList();

    std::string                     currentTimestamp            = m_game.getCurrentTime().getTimestamp();
    CPfTeams                        *team                       = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
    IPfTeamPlayersDAO               *teamPlayersDAO             = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();
    IPfTeamAveragesDAO              *teamAveragesDAO            = m_game.getIDAOFactory()->getIPfTeamAveragesDAO();
    std::vector<CPfTeamPlayers*>    *lineUpTeamPlayersList      = teamPlayersDAO->findLineUpByXFkTeam(team->getXTeam(), currentTimestamp);
    std::vector<CPfTeamPlayers*>    *alternateTeamPlayersList   = teamPlayersDAO->findAlternateByXFkTeam(team->getXTeam(), currentTimestamp);
    std::vector<CPfTeamPlayers*>    *notLineUpTeamPlayersList   = teamPlayersDAO->findNotLineUpByXFkTeam(team->getXTeam(), currentTimestamp);

    std::vector<CPfTeamPlayers*>::iterator it;
    for( it=lineUpTeamPlayersList->begin(); it!=lineUpTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);
        addPlayerToList(teamPlayer, m_teamPlayersList);
    }
    for( it=alternateTeamPlayersList->begin(); it!=alternateTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);
        addPlayerToList(teamPlayer, m_teamPlayersList);
    }
    for( it=notLineUpTeamPlayersList->begin(); it!=notLineUpTeamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);
        addPlayerToList(teamPlayer, m_teamPlayersList);
    }

    CPfTeamAverages *teamAverage = teamAveragesDAO->findByXTeam(team->getXTeam_str(), currentTimestamp);
    m_teamName   ->setText((CEGUI::utf8*)team->getSTeam().c_str());
    std::ostringstream average;
    average << teamAverage->getNTotal();
    m_teamAverage->setText((CEGUI::utf8*)average.str().c_str());
    delete teamAverage;

    //Loading Shield
    m_teamBadge->setProperty("Image", "set:"+ team->getSLogo() +" image:"+team->getSLogo()+"_b");

    teamPlayersDAO->freeVector(lineUpTeamPlayersList);
    teamPlayersDAO->freeVector(alternateTeamPlayersList);
    teamPlayersDAO->freeVector(notLineUpTeamPlayersList);
    delete team;

    m_teamPlayersList->getHorzScrollbar()->setVisible(false);
    m_teamPlayersList->getVertScrollbar()->setVisible(true);
}

void CTeamPlayersWindowHandler::addPlayerToList(CPfTeamPlayers *player, CEGUI::MultiColumnList *list)
{
    const CEGUI::Image* sel_img = &CEGUI::ImagesetManager::getSingleton().getImageset("WidgetsImageset")->getImage("MultiListSelectionBrush");

    int row_idx = list->addRow();
    int XTeamPlayer = player->getXTeamPlayer();
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getSShortName().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 0, row_idx);

    CPfCountries *country = m_game.getIDAOFactory()->getIPfCountriesDAO()->findByXCountry(player->getXFkCountry());
    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)gettext(country->getSShortName().c_str()), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 1, row_idx);
    delete country;

    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNSpeed_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 2, row_idx);

    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)player->getNKickPower_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 3, row_idx);

    CPfTeamPlayerAverages *playerAverage = m_game.getIDAOFactory()->getIPfTeamPlayerAveragesDAO()->findByXTeamPlayer(player->getXTeamPlayer_str());
    item = new CEGUI::ListboxTextItem((CEGUI::utf8*)playerAverage->getNTotal_str().c_str(), XTeamPlayer);
    item->setSelectionBrushImage(sel_img);
    list->setItem(item, 4, row_idx);
    delete playerAverage;
}

bool CTeamPlayersWindowHandler::teamPlayersListboxSelectionChanged(const CEGUI::EventArgs& e)
{
    selectChanged(m_teamPlayersList);
    return true;
}

void CTeamPlayersWindowHandler::selectChanged(CEGUI::MultiColumnList *list)
{
    CEGUI::ListboxItem *currentItem = list->getFirstSelectedItem();

    if( currentItem != NULL ) {
        int currentRow  = list->getItemRowIndex(currentItem);
        IPfTeamPlayersDAO *teamPlayersDAO = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();
        int xTeamPlayer = currentItem->getID();
        CPfTeamPlayers *selectedPlayer = teamPlayersDAO->findByXTeamPlayer(xTeamPlayer);
        m_game.setSelectedTeamPlayer(selectedPlayer);
        CGameEngine::getInstance()->getWindowManager()->nextScreen("TeamPlayerDetails");
        delete selectedPlayer;
    }
}
