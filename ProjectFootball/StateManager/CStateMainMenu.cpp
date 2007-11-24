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


CStateMainMenu::CStateMainMenu(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
 :CState(mouse, keyboard)
{
    m_continue = true;
}


CStateMainMenu::~CStateMainMenu()
{

}


void CStateMainMenu::enter()
{
    m_mouse->setEventCallback(this);
    //m_keyboard->setEventCallback(this);

    CEGUI::WindowManager *win = CEGUI::WindowManager::getSingletonPtr();
    CEGUI::Window *sheet = win->createWindow("DefaultGUISheet", "CEGUIDemo/Sheet");

    CEGUI::Window *quit = win->createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

    sheet->addChildWindow(quit);
    m_system->setGUISheet(sheet);

    quit->subscribeEvent(CEGUI::PushButton::EventClicked,
               CEGUI::Event::Subscriber(&CStateMainMenu::quit, this));

}


bool CStateMainMenu::quit(const CEGUI::EventArgs &e)
{
        m_continue = false;
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
