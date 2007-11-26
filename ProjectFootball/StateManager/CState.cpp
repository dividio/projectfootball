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

#include "iostream.h"

#include "CState.h"


CState::CState(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
{
    m_mouse = mouse;
    m_keyboard = keyboard;
    m_root = Ogre::Root::getSingletonPtr();
    m_system = CEGUI::System::getSingletonPtr();
    m_renderer = (CEGUI::OgreCEGUIRenderer *) m_system->getRenderer();
}


CState::~CState()
{

}


bool CState::keyPressed(const OIS::KeyEvent& e)
{
    m_system->injectKeyDown(e.key);
    m_system->injectChar(e.text);

    return true;
}


bool CState::keyReleased(const OIS::KeyEvent& e)
{
    m_system->injectKeyUp(e.key);
    return true;
}



bool CState::mouseMoved(const OIS::MouseEvent& e)
{
    m_system->injectMouseMove(e.state.X.rel, e.state.Y.rel);
    return true;
}


bool CState::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
    m_system->injectMouseButtonDown(convertButton(id));
    return true;
}


bool CState::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
    m_system->injectMouseButtonUp(convertButton(id));
    return true;
}


CEGUI::MouseButton CState::convertButton(OIS::MouseButtonID buttonID)
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
