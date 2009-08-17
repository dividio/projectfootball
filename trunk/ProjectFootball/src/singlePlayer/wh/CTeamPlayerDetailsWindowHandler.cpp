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

#include "CTeamPlayerDetailsWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/bean/CPfTeamPlayers.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"


CTeamPlayerDetailsWindowHandler::CTeamPlayerDetailsWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("teamPlayerDetails.layout"),
	m_game(game)
{
    LOG_DEBUG("CTeamPlayerDetailsWindowHandler()");
}

CTeamPlayerDetailsWindowHandler::~CTeamPlayerDetailsWindowHandler()
{
    LOG_DEBUG("~CTeamPlayerDetailsWindowHandler()");
}

void CTeamPlayerDetailsWindowHandler::enter()
{
    m_selectedTeamPlayer = m_game.getSelectedTeamPlayer();
    m_name ->setText((CEGUI::utf8*)m_selectedTeamPlayer->getSName().c_str());
    m_photo->setProperty("Image", "set:"+ m_selectedTeamPlayer->getSPhoto() +" image:"+m_selectedTeamPlayer->getSPhoto()+"_b");
}

void CTeamPlayerDetailsWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

	m_name  = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Name"));
	m_photo = static_cast<CEGUI::Window *>(windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/Photo"));

    // i18n support
    windowMngr.getWindow((CEGUI::utf8*)"TeamPlayerDetails/NameLabel")->setText((CEGUI::utf8*)gettext("Name:"));
}

void CTeamPlayerDetailsWindowHandler::leave()
{

}

