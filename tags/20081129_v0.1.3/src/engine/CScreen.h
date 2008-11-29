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


#ifndef CSCREEN_H_
#define CSCREEN_H_

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>
#include "IScreen.h"


class CScreen : public IScreen
{

public:
    virtual ~CScreen();

    virtual void enter();
    virtual void leave();
    virtual void update();

protected:
    Ogre::Root					*m_root;
    CEGUI::OgreCEGUIRenderer	*m_renderer;
    CEGUI::System 				*m_system;
    CEGUI::Window				*m_layout;
    CEGUI::WindowManager 		*m_windowMngr;

    CScreen(const char *layout);
};
#endif // CSCREEN_H_
