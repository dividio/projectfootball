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

#include <stdio.h>

#include "CScreenManager.h"
#include "../utils/CLog.h"


CScreenManager::CScreenManager()
  :m_stack()
{
    CLog::getInstance()->debug("CScreenManager()");
}


CScreenManager* CScreenManager::getInstance()
{
    static CScreenManager instance;
    return &instance;
}


CScreenManager::~CScreenManager()
{
    CLog::getInstance()->debug("~CScreenManager()");
    forcedPopStack();
}


void CScreenManager::forcedPopStack()
{
    while(!m_stack.empty()) {
        m_stack.back()->forcedLeave();
        m_stack.pop_back();
    }
}


bool CScreenManager::frameEnded(const Ogre::FrameEvent& evt)
{
    return true;
}


bool CScreenManager::frameStarted(const Ogre::FrameEvent& evt)
{
    m_timeSinceLastFrame = evt.timeSinceLastFrame;
    if(m_stack.empty()) {
        return false;
    }

    m_stack.back()->update();
    return true;
}


void CScreenManager::popStack()
{
    while(!m_stack.empty() && m_stack.back()->leave()) {
        m_stack.pop_back();
    }
    enterState();
}


void CScreenManager::popState()
{
  // cleanup the current state
  if(!m_stack.empty()) {
      if(m_stack.back()->leave()) {
          m_stack.pop_back();
          enterState();
      }
  }
}


void CScreenManager::popToState(CScreen* state)
{
    while(!m_stack.empty() && m_stack.back()!=state && m_stack.back()->leave()) {
        m_stack.pop_back();
    }
    enterState();
}


void CScreenManager::pushState(CScreen* state)
{
    m_stack.push_back(state);
    enterState();
}


void CScreenManager::enterState()
{
    if(!m_stack.empty()) {
        CScreen *state = m_stack.back();
        state->enter();
    }
}


float CScreenManager::getTimeSinceLastFrame()
{
    return m_timeSinceLastFrame;
}
