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

#include "CStateMainMenu.h"
#include "CStateManager.h"
#include "../utils/CLog.h"
#include "../utils/CLuaManager.h"


CStateMainMenu::CStateMainMenu()
 :CState()
{
    CLog::getInstance()->debug("CStateMainMenu()");

    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"mainMenu.layout");

    // Maybe using CEGUI::GlobalEventSet ?
    CEGUI::WindowManager::WindowIterator i =  CEGUI::WindowManager::getSingleton().getIterator();

    while (!i.isAtEnd())
    {
        if(i.getCurrentValue()) {
            i.getCurrentValue()->subscribeEvent(CEGUI::PushButton::EventClicked,
                    CEGUI::Event::Subscriber(&CStateMainMenu::clickAudioEvent, this));
        }
        ++i;
    }

//    CEGUI::Imageset* menuImageset = CEGUI::ImagesetManager::getSingletonPtr()->createImagesetFromImageFile("Background","background.tga");
//    menuImageset->defineImage("Background", CEGUI::Point(0.0f,0.0f), CEGUI::Size( 1.0f, 1.0f ), CEGUI::Point(0.0f,0.0f)); // Whole Image
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


bool CStateMainMenu::clickAudioEvent(const CEGUI::EventArgs &e)
{
    //CAudioSystem::CLICK.play();
    //cout << "CLICK" << endl;
    return true;
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
