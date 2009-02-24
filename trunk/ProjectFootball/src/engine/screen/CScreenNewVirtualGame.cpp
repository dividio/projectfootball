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

#include "CScreenNewVirtualGame.h"
#include "../CGameEngine.h"
#include "../../utils/CLog.h"
#include "../../quickPlay/CQuickGame.h"

CScreenNewVirtualGame::CScreenNewVirtualGame()
:CScreen("newVirtualGame.layout")
{
    CLog::getInstance()->debug("CScreenNewManagerGame()");

    m_backButton  = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"NewVirtualGame/BackButton"));
    m_startButton = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"NewVirtualGame/StartButton"));

    // i18n support
    m_backButton ->setText((CEGUI::utf8*)gettext("Back"));
    m_startButton->setText((CEGUI::utf8*)gettext("Start"));

    // Event handle
    m_backButton ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenNewVirtualGame::backButtonClicked, this));
    m_startButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenNewVirtualGame::startButtonClicked, this));
}

CScreenNewVirtualGame::~CScreenNewVirtualGame() {
    // TODO Auto-generated destructor stub
}

void CScreenNewVirtualGame::enter()
{
    CScreen::enter();
}

bool CScreenNewVirtualGame::backButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->previousScreen();
    return true;
}

bool CScreenNewVirtualGame::startButtonClicked(const CEGUI::EventArgs& e)
{
    const CPfUsers *user = CGameEngine::getInstance()->getCurrentUser();

    if( user==NULL || user->getXUser()==0 ){
        CLog::getInstance()->exception("[CScreenVirtualGame::virtualCompetitionButtonClicked] User not defined");
    }

    CGameEngine::getInstance()->loadGame(new CQuickGame(user));
    CGameEngine::getInstance()->save();
    //CGameEngine::getInstance()->previousScreen();
    return true;
}
