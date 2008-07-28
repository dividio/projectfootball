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

#include "CStateMainMenu.h"
#include "CStateManager.h"
#include "../utils/CLog.h"


CStateMainMenu::CStateMainMenu()
 :CState()
{
    CLog::getInstance()->debug("CStateMainMenu()");

    CEGUI::WindowManager *ceguiWM = &(CEGUI::WindowManager::getSingleton());
    m_sheet = ceguiWM->loadWindowLayout((CEGUI::utf8*)"mainMenu.layout");

    // i18n support
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"MainMenu/QuickPlayButton"))->setText((CEGUI::utf8*)gettext("Quick Play"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"MainMenu/LoadGameButton"))->setText((CEGUI::utf8*)gettext("New/Load Game"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"MainMenu/ConfigButton"))->setText((CEGUI::utf8*)gettext("Config"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"MainMenu/CreditsButton"))->setText((CEGUI::utf8*)gettext("Credits"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"MainMenu/QuitButton"))->setText((CEGUI::utf8*)gettext("Quit"));
}


CStateMainMenu* CStateMainMenu::getInstance()
{
  static CStateMainMenu instance;
  return &instance;
}


CStateMainMenu::~CStateMainMenu()
{
  CLog::getInstance()->debug("~CStateMainMenu()");
}


void CStateMainMenu::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();
}


void CStateMainMenu::forcedLeave()
{

}


bool CStateMainMenu::leave()
{
    return true;
}


void CStateMainMenu::update()
{
}
