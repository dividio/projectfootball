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

#include "CStateManager.h"
#include "../utils/CLog.h"
#include "../CApplication.h"
#include <stdio.h>

CStateManager::CStateManager()
  :m_stack()
{
  CLog::getInstance()->debug("CStateManager()");
}


CStateManager* CStateManager::getInstance()
{
  static CStateManager instance;
  return &instance;
}


CStateManager::~CStateManager()
{
  CLog::getInstance()->debug("~CStateManager()");
  forcedPopStack();
}


void CStateManager::forcedPopStack()
{
    while(!m_stack.empty()) {
        m_stack.back()->forcedLeave();
        m_stack.pop_back();
    }
}


bool CStateManager::frameEnded(const Ogre::FrameEvent& evt)
{

    return true;
}


bool CStateManager::frameStarted(const Ogre::FrameEvent& evt)
{
  CApplication::getInstance()->getMouse()->capture();
  CApplication::getInstance()->getKeyboard()->capture();

  if( m_stack.empty() ) return false;

  m_stack.back()->update();
    return true;
}


void CStateManager::popStack()
{
    while(!m_stack.empty() && m_stack.back()->leave()) {
        m_stack.pop_back();
    }
    enterState();
}


void CStateManager::popState()
{
  // cleanup the current state
  if(!m_stack.empty()) {
      if( m_stack.back()->leave() ){
          m_stack.pop_back();
          enterState();
      }
  }
}


void CStateManager::popToState(CState* state)
{
    while(!m_stack.empty() && m_stack.back()!=state && m_stack.back()->leave()) {
        m_stack.pop_back();
    }
    enterState();
}


void CStateManager::pushState(CState* state)
{
    m_stack.push_back(state);
    enterState();
}

void CStateManager::enterState()
{
  if( !m_stack.empty() ){
    CState *state = m_stack.back();
    state->enter();
  }
}
