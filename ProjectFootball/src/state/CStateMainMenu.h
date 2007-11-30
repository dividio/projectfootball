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

#include "CState.h"


class CStateMainMenu : public CState
{

public:
    static CStateMainMenu* getInstance(OIS::Mouse *mouse = NULL,
                                       OIS::Keyboard *keyboard = NULL);
    virtual ~CStateMainMenu();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

protected:
    CStateMainMenu(OIS::Mouse *mouse, OIS::Keyboard *keyboard);
    bool quit(const CEGUI::EventArgs &e);
    bool credits(const CEGUI::EventArgs &e);
    bool play(const CEGUI::EventArgs &e);
    bool clickAudioEvent(const CEGUI::EventArgs &e);


private:
    static CStateMainMenu* m_instance;

};
#endif // __CStateMainMenu_H__
