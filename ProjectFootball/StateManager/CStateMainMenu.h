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


#ifndef __CStateMainMenu_H__
#define __CStateMainMenu_H__

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "IState.h"


class CStateMainMenu : public IState
{

public:
    CStateMainMenu(OIS::Mouse *mouse, OIS::Keyboard *keyboard);
    virtual ~CStateMainMenu();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();


//    virtual bool frameEnded(const Ogre::FrameEvent& evt);
//    virtual bool frameStarted(const Ogre::FrameEvent& evt);

    virtual bool keyPressed(const OIS::KeyEvent& e);
    virtual bool keyReleased(const OIS::KeyEvent& e);

    virtual bool mouseMoved(const OIS::MouseEvent& e);
    virtual bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
    virtual void update();

    bool quit(const CEGUI::EventArgs &e);


protected:
    OIS::Mouse*    m_mouse;
    OIS::Keyboard* m_keyboard;
    Ogre::Root*    m_root;
    CEGUI::OgreCEGUIRenderer *m_renderer;
    CEGUI::System *m_system;
    bool m_continue;

};
#endif // __CStateMainMenu_H__
