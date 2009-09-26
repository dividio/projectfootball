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

#include "CInputManager.h"

#include "../exceptions/PFException.h"

bool CInputManager::m_instantiated = false;

CInputManager::CInputManager(std::string windowHnd, unsigned int width, unsigned int height)
{
    // Check if this class has been already instantiated
    if(m_instantiated == true) {
        throw PFEXCEPTION("[CInputManager::CInputManager] CInputManager already instantiated");
    }

    m_system = CEGUI::System::getSingletonPtr();

    OIS::ParamList pl;

    pl.insert(std::make_pair(std::string("WINDOW"), windowHnd));
    //Disable mouse and keyboard grab for debug
//    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
//    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));

    try {

        m_inputManager = OIS::InputManager::createInputSystem(pl);

        m_keyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
        m_mouse    = static_cast<OIS::Mouse*>   (m_inputManager->createInputObject(OIS::OISMouse, true));
        //m_joy      = static_cast<OIS::JoyStick*>(m_inputManager->createInputObject(OIS::OISJoyStick, false));

        m_keyboard->setEventCallback(this);
        m_mouse   ->setEventCallback(this);


        // Set mouse region
        const OIS::MouseState &mouseState = m_mouse->getMouseState();
        mouseState.width  = width;
        mouseState.height = height;

        m_instantiated = true;

    } catch (const OIS::Exception &e) {
        throw PFEXCEPTION("OIS Exception: %s", e.eText);
    }

}


CInputManager::~CInputManager()
{
    m_inputManager->destroyInputObject(m_keyboard);
    m_inputManager->destroyInputObject(m_mouse);
    OIS::InputManager::destroyInputSystem(m_inputManager);

    m_instantiated = false;
}


void CInputManager::capture()
{
    m_mouse->capture();
    m_keyboard->capture();
}


bool CInputManager::keyPressed(const OIS::KeyEvent& e)
{
    m_system->injectKeyDown(e.key);
    m_system->injectChar(e.text);
    return true;
}


bool CInputManager::keyReleased(const OIS::KeyEvent& e)
{    m_system->injectKeyUp(e.key);
    return true;
}


bool CInputManager::mouseMoved(const OIS::MouseEvent& e)
{
    m_system->injectMouseMove(e.state.X.rel, e.state.Y.rel);
    return true;
}


bool CInputManager::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
    m_system->injectMouseButtonDown(convertButton(id));
    return true;
}


bool CInputManager::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
    m_system->injectMouseButtonUp(convertButton(id));
    return true;
}


CEGUI::MouseButton CInputManager::convertButton(OIS::MouseButtonID buttonID)
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
