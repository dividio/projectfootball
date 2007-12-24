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


#ifndef __CStateMonitor_H__
#define __CStateMonitor_H__

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "CState.h"

class CStateMonitor : public CState
{
public:
    static CStateMonitor* getInstance();

    virtual ~CStateMonitor();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

protected:
    CStateMonitor();

private:
    //Ogre::RenderTexture *m_tex;

    Ogre::Camera *m_cam;
    Ogre::Vector3 m_direction;

    void renderImage(Ogre::Camera *cam, CEGUI::Window *si);
    bool keyDownHandler(const CEGUI::EventArgs& e);
    bool keyUpHandler(const CEGUI::EventArgs& e);

};

#endif // __CStateMonitor_H__
