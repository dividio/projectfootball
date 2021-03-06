/******************************************************************************
* Copyright (C) 2007 - Ikaro Games   www.ikarogames.com                       *
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

#include "CScreenMainMenu.h"
#include "../CGameEngine.h"
#include "../../quickPlay/CQuickGame.h"
#include "../../utils/CLog.h"


CScreenMainMenu::CScreenMainMenu()
 :CScreen("mainMenu.layout")
{
    CLog::getInstance()->debug("CScreenMainMenu()");

    m_quickPlayButton	= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/QuickPlayButton"));
    m_loadGameButton	= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/LoadGameButton"));
    m_configButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/ConfigButton"));
    m_creditsButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/CreditsButton"));
    m_quitButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/QuitButton"));

    // Event handle
    m_quickPlayButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::quickPlayButtonClicked, this));
    m_loadGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::loadGameButtonClicked, this));
    m_configButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::configButtonClicked, this));
    m_creditsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::creditsButtonClicked, this));
    m_quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::quitButtonClicked, this));

    // i18n support
    m_quickPlayButton->setText((CEGUI::utf8*)gettext("Quick Play"));
    m_loadGameButton->setText((CEGUI::utf8*)gettext("Single Player"));
    m_configButton->setText((CEGUI::utf8*)gettext("Config"));
    m_creditsButton->setText((CEGUI::utf8*)gettext("Credits"));
    m_quitButton->setText((CEGUI::utf8*)gettext("Quit"));
}


CScreenMainMenu::~CScreenMainMenu()
{
  CLog::getInstance()->debug("~CScreenMainMenu()");
}

bool CScreenMainMenu::quickPlayButtonClicked(const CEGUI::EventArgs& e)
{
    const CPfUsers *user = CGameEngine::getInstance()->getCurrentUser();

    if( user==NULL || user->getXUser()==0 ){
        CLog::getInstance()->exception("[CScreenMainMenu::quickPlayButtonClicked] User not defined");
    }

    CGameEngine::getInstance()->loadGame(new CQuickGame(user));
    CGameEngine::getInstance()->save();

    return true;
}

bool CScreenMainMenu::loadGameButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getLoadGameScreen());
    return true;
}

bool CScreenMainMenu::configButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getConfigScreen());
    return true;
}

bool CScreenMainMenu::creditsButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getCreditsScreen());
    return true;
}

bool CScreenMainMenu::quitButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->exit();
    return true;
}
