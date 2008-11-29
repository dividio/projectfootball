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
#include "../CApplication.h"
#include "../engine/CGameEngine.h"

CInputManager::CInputManager()
{
    m_system = CEGUI::System::getSingletonPtr();
}


CInputManager::~CInputManager()
{
}


CInputManager* CInputManager::getInstance()
{
    static CInputManager instance;
    return &instance;
}


void CInputManager::capture()
{
    CApplication::getInstance()->getMouse()->capture();
    CApplication::getInstance()->getKeyboard()->capture();
}


bool CInputManager::keyPressed(const OIS::KeyEvent& e)
{
    if(e.key==OIS::KC_ESCAPE) {
//    	CGameEngine::getInstance()->previousScreen();
    } else if(e.key==OIS::KC_F12) {
        CApplication::getInstance()->takeScreenshot();
    } else {
        m_system->injectKeyDown(e.key);
        m_system->injectChar(e.text);
    }
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
