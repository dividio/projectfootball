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


#ifndef __CStateManager_H__
#define __CStateManager_H__

#include <Ogre.h>
#include <vector>
#include <iostream>


#include "CState.h"
#include "CStateMainMenu.h"
#include "CStateCredits.h"
#include "CStateMonitor.h"



class CStateManager : public Ogre::FrameListener
{

public:
    ~CStateManager();
    static CStateManager* getInstance();

    void forcedPopStack();
    bool frameEnded(const Ogre::FrameEvent& evt);
    bool frameStarted(const Ogre::FrameEvent& evt);
    void popStack();
    void popState();
    void popToState(CState* state);
    void pushState(CState* state);

protected:
    CStateManager();
private:
  void enterState();

    std::vector<CState*> m_stack;
};
#endif // __CStateManager_H__
