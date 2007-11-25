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



using namespace Ogre;


class CStateManager : public FrameListener
{

public:
    ~CStateManager();
    static CStateManager* getInstance(OIS::Mouse *mouse = NULL,
                                      OIS::Keyboard *keyboard = NULL);

    void forcedPopStack();
    bool frameEnded(const FrameEvent& evt);
    bool frameStarted(const FrameEvent& evt);
    void popStack();
    void popState();
    void popToState(CState* state);
    void pushState(CState* state);

protected:
    CStateManager(OIS::Mouse *mouse, OIS::Keyboard *keyboard);
private:
    CStateMainMenu *m_stateMainMenu;
    CStateCredits *m_stateCredits;
    std::vector<CState*> m_stack;

    static CStateManager* m_instance;

};
#endif // __CStateManager_H__
