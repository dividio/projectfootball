/******************************************************************************
* Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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

#include <stdio.h>
#include <libintl.h>

#include "CNewVirtualGameWindowHandler.h"
#include "../CGameEngine.h"
#include "../../exceptions/PFException.h"
#include "../../friendlyMatch/CFriendlyMatchGame.h"
#include "../../utils/CLog.h"

CNewVirtualGameWindowHandler::CNewVirtualGameWindowHandler()
:CWindowHandler("newVirtualGame.layout")
{
    LOG_DEBUG("CNewVirtualGameWindowHandler()");
}

CNewVirtualGameWindowHandler::~CNewVirtualGameWindowHandler()
{}

void CNewVirtualGameWindowHandler::init()
{
	CEGUI::WindowManager *windowMngr = CEGUI::WindowManager::getSingletonPtr();

    m_backButton  = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"NewVirtualGame/BackButton"));
    m_startButton = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"NewVirtualGame/StartButton"));

    // i18n support
    m_backButton ->setText((CEGUI::utf8*)gettext("Back"));
    m_startButton->setText((CEGUI::utf8*)gettext("Start"));

    // Event handle
    registerEventConnection(m_backButton ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CNewVirtualGameWindowHandler::backButtonClicked, this)));
    registerEventConnection(m_startButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CNewVirtualGameWindowHandler::startButtonClicked, this)));
}

bool CNewVirtualGameWindowHandler::backButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->getWindowManager()->previousScreen();
    return true;
}

bool CNewVirtualGameWindowHandler::startButtonClicked(const CEGUI::EventArgs& e)
{
    const CPfUsers *user = CGameEngine::getInstance()->getCurrentUser();

    if( user==NULL || user->getXUser()==0 ){
        throw PFEXCEPTION("[CScreenVirtualGame::virtualCompetitionButtonClicked] User not defined");
    }

    CGameEngine::getInstance()->loadGame(new CFriendlyMatchGame(*user));
    CGameEngine::getInstance()->save();
    //CGameEngine::getInstance()->previousScreen();
    return true;
}
