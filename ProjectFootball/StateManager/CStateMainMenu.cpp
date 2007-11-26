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

#include <iostream.h>

#include "CStateMainMenu.h"
#include "CStateManager.h"


CStateMainMenu* CStateMainMenu::m_instance = NULL;

CStateMainMenu::CStateMainMenu(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
 :CState(mouse, keyboard)
{
//    CEGUI::WindowManager *win = CEGUI::WindowManager::getSingletonPtr();
//    m_sheet = win->createWindow("DefaultGUISheet", "CEGUIDemo/Sheet");
//
//    CEGUI::Window *quit = win->createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
//    quit->setText("Quit");
//    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
//
//    m_sheet->addChildWindow(quit);
//
//
//    quit->subscribeEvent(CEGUI::PushButton::EventClicked,
//               CEGUI::Event::Subscriber(&CStateMainMenu::quit, this));
//
//
//    CEGUI::Window *credits = win->createWindow("TaharezLook/Button", "CEGUIDemo/CreditsButton");
//    credits->setText("Credits");
//    credits->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
//    credits->setPosition(CEGUI::UVector2(CEGUI::UDim(0.55, 0),CEGUI::UDim(0.55, 0)));
//
//    m_sheet->addChildWindow(credits);
//
//    credits->subscribeEvent(CEGUI::PushButton::EventClicked,
//               CEGUI::Event::Subscriber(&CStateMainMenu::credits, this));

    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"mainMenu.layout");

    CEGUI::PushButton *quit =
      (CEGUI::PushButton *)CEGUI::WindowManager::getSingleton().getWindow("MainMenu/QuitButton");

    quit->subscribeEvent(CEGUI::PushButton::EventClicked,
               CEGUI::Event::Subscriber(&CStateMainMenu::quit, this));

    CEGUI::PushButton *credits =
      (CEGUI::PushButton *)CEGUI::WindowManager::getSingleton().getWindow("MainMenu/CreditsButton");

    credits->subscribeEvent(CEGUI::PushButton::EventClicked,
               CEGUI::Event::Subscriber(&CStateMainMenu::credits, this));



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
}


CStateMainMenu* CStateMainMenu::getInstance(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
{
    if(m_instance == NULL && mouse != NULL && keyboard != NULL ) {
        m_instance = new CStateMainMenu(mouse, keyboard);
    }

    return  m_instance;
}


CStateMainMenu::~CStateMainMenu()
{

}


void CStateMainMenu::enter()
{
    m_mouse->setEventCallback(this);
    //m_keyboard->setEventCallback(this);

    m_system->setGUISheet(m_sheet);
}


bool CStateMainMenu::quit(const CEGUI::EventArgs &e)
{
    CStateManager::getInstance()->popState();
    return true;
}


bool CStateMainMenu::credits(const CEGUI::EventArgs &e)
{
    CStateManager::getInstance()->pushState(CStateCredits::getInstance());
    return true;
}

bool CStateMainMenu::clickAudioEvent(const CEGUI::EventArgs &e)
{
    cout << "CLICK" << endl;
    return true;
}

void CStateMainMenu::forcedLeave()
{

}


bool CStateMainMenu::leave()
{
    return false;
}


void CStateMainMenu::update()
{
    //m_keyboard->capture();
    m_mouse->capture();
}
