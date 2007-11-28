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

#include "CStateCredits.h"
#include "CStateManager.h"


CStateCredits* CStateCredits::m_instance = NULL;


CStateCredits::CStateCredits(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
 :CState(mouse, keyboard)
{

//    CEGUI::WindowManager *win = CEGUI::WindowManager::getSingletonPtr();
//    m_sheet = win->createWindow("DefaultGUISheet", "CEGUIDemo/Sheet2");
//
//    CEGUI::Window *back = win->createWindow("TaharezLook/Button", "CEGUIDemo/BackButton");
//    back->setText("Back");
//    back->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
//
//    m_sheet->addChildWindow(back);
//
//    back->subscribeEvent(CEGUI::PushButton::EventClicked,
//               CEGUI::Event::Subscriber(&CStateCredits::back, this));
    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"credits.layout");
    CEGUI::PushButton *back = (CEGUI::PushButton *)CEGUI::WindowManager::getSingleton().getWindow("Credits/BackButton");
    back->subscribeEvent(CEGUI::PushButton::EventClicked,
               CEGUI::Event::Subscriber(&CStateCredits::back, this));
}


CStateCredits* CStateCredits::getInstance(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
{
    if(m_instance == NULL && mouse != NULL && keyboard != NULL ) {
        m_instance = new CStateCredits(mouse, keyboard);
    }

    return  m_instance;
}


CStateCredits::~CStateCredits()
{

}


void CStateCredits::enter()
{
    m_mouse->setEventCallback(this);
    //m_keyboard->setEventCallback(this);
    m_system->setGUISheet(m_sheet);

    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

}


bool CStateCredits::back(const CEGUI::EventArgs &e)
{
        CStateManager::getInstance()->popState();
        return true;
}


void CStateCredits::forcedLeave()
{

}


bool CStateCredits::leave()
{
    return false;
}


void CStateCredits::update()
{
    //m_keyboard->capture();
    m_mouse->capture();
}
