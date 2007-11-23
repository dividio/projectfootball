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


CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}

CStateMainMenu::CStateMainMenu(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
{
    m_mouse = mouse;
    m_keyboard = keyboard;
    m_root = Ogre::Root::getSingletonPtr();
    m_system = CEGUI::System::getSingletonPtr();
    m_renderer = (CEGUI::OgreCEGUIRenderer *) m_system->getRenderer();
    m_continue = true;
}



CStateMainMenu::~CStateMainMenu()
{
}





void CStateMainMenu::enter()
{
    m_mouse->setEventCallback(this);
    //m_keyboard->setEventCallback(this);

    CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
    m_system->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
    m_system->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");
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

//bool CStateMainMenu::frameEnded(const Ogre::FrameEvent& evt)
//{
//
//  return true;
//}
//
//
//bool CStateMainMenu::frameStarted(const Ogre::FrameEvent& evt)
//{
//    m_keyboard->capture();
//    m_mouse->capture();
//
//    return m_continue && !m_keyboard->isKeyDown(OIS::KC_ESCAPE);
//}


bool CStateMainMenu::keyPressed(const OIS::KeyEvent& e)
{
//	CEGUI::System *sys = CEGUI::System::getSingletonPtr();
//	sys->injectKeyDown(arg.key);
//	sys->injectChar(arg.text);


    m_system->injectKeyDown(e.key);
    m_system->injectChar(e.text);

    return true;
}


bool CStateMainMenu::keyReleased(const OIS::KeyEvent& e)
{

    m_system->injectKeyUp(e.key);
    return true;
}


bool CStateMainMenu::leave()
{
    return false;
}


bool CStateMainMenu::mouseMoved(const OIS::MouseEvent& e)
{
    m_system->injectMouseMove(e.state.X.rel, e.state.Y.rel);
    return true;
}


bool CStateMainMenu::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
    m_system->injectMouseButtonDown(convertButton(id));
    return true;
}


bool CStateMainMenu::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
    m_system->injectMouseButtonUp(convertButton(id));
    return true;
}


void CStateMainMenu::update()
{
    //m_keyboard->capture();
    m_mouse->capture();

}
