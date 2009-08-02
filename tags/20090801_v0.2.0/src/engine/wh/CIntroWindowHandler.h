/******************************************************************************
* Copyright (C) 2008 - Ikaro Games   www.ikarogames.com                       *
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

#ifndef CINTROWINDOWHANDLER_H_
#define CINTROWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>

#include "../wm/CWindowHandler.h"

class CTimer;

class CIntroWindowHandler: public CWindowHandler {
public:
    CIntroWindowHandler();
    virtual ~CIntroWindowHandler();

    virtual void enter();
    virtual void init();
    virtual void update();

private:
    bool buttonClicked(const CEGUI::EventArgs& e);

    CTimer        *m_timer;
    int            m_introTime;
    int            m_elapsedTime;
    CEGUI::Window *m_mainWindow;
};

#endif /* CINTROWINDOWHANDLER_H_ */
