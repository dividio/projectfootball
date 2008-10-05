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


#ifndef CSCREENMANAGER_H_
#define CSCREENMANAGER_H_

#include <Ogre.h>
#include <vector>
#include <iostream>


#include "CScreen.h"


class CScreenManager : public Ogre::FrameListener
{

public:
    ~CScreenManager();
    static CScreenManager* getInstance();

    void forcedPopStack();
    bool frameEnded(const Ogre::FrameEvent& evt);
    bool frameStarted(const Ogre::FrameEvent& evt);
    void popStack();
    void popState();
    void popToState(CScreen* state);
    void pushState(CScreen* state);

    float getTimeSinceLastFrame();

protected:
    CScreenManager();
private:
    void enterState();

    float m_timeSinceLastFrame;
    std::vector<CScreen*> m_stack;
};
#endif // CSCREENMANAGER_H_
