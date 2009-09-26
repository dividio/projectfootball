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

#ifndef CINPUTMANAGER_H_
#define CINPUTMANAGER_H_

#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>


class CInputManager :
    public OIS::MouseListener, public OIS::KeyListener
{
public:
    CInputManager(std::string windowHnd, unsigned int width, unsigned int height);
    ~CInputManager();

    void capture();

    bool keyPressed(const OIS::KeyEvent& e);
    bool keyReleased(const OIS::KeyEvent& e);
    bool mouseMoved(const OIS::MouseEvent& e);
    bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);

protected:
    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

private:
    CEGUI::System     *m_system;
    OIS::InputManager *m_inputManager;
    OIS::Mouse        *m_mouse;
    OIS::Keyboard     *m_keyboard;

    /**
     * This attribute ensures there is only one instance of this class but
     * it isn't accesible from anywhere. This check is at runtime instead
     * of compile time like classic singleton.
     */
    static bool        m_instantiated;
};

#endif /*CINPUTMANAGER_H_*/
