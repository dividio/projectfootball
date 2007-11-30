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

#ifndef __CStateCredits_H__
#define __CStateCredits_H__

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "CState.h"

class CStateCredits : public CState
{
public:
    static CStateCredits* getInstance(OIS::Mouse *mouse = NULL,
                                      OIS::Keyboard *keyboard = NULL);

    virtual ~CStateCredits();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

    bool back(const CEGUI::EventArgs &e);

protected:
    CStateCredits(OIS::Mouse *mouse, OIS::Keyboard *keyboard);

private:
    static CStateCredits* m_instance;

};

#endif // __CStateCredits_H__