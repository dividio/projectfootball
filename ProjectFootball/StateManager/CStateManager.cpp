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

CStateManager* CStateManager::m_instance = NULL;

CStateManager::CStateManager(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
{
//    m_stateMainMenu = new CStateMainMenu(mouse, keyboard);
//    m_stateCredits = new CStateCredits(mouse, keyboard);
    m_stateMainMenu = CStateMainMenu::getInstance(mouse, keyboard);
    m_stateCredits = CStateCredits::getInstance(mouse, keyboard);
    m_stateMonitor = CStateMonitor::getInstance(mouse, keyboard);

    pushState(m_stateMainMenu);
}


CStateManager* CStateManager::getInstance(OIS::Mouse *mouse, OIS::Keyboard *keyboard)
{
    if(m_instance == NULL && mouse != NULL && keyboard != NULL ) {
        m_instance = new CStateManager(mouse, keyboard);
    }

    return  m_instance;
}


CStateManager::~CStateManager()
{

    forcedPopStack();

    if(m_stateMainMenu != NULL) {
        delete m_stateMainMenu;
    }
    if(m_stateCredits != NULL) {
        delete m_stateCredits;
    }
    if(m_stateMonitor != NULL) {
            delete m_stateMonitor;
    }
}


void CStateManager::forcedPopStack()
{
    while(!m_stack.empty()) {
        m_stack.back()->forcedLeave();
        m_stack.pop_back();
    }
}


bool CStateManager::frameEnded(const FrameEvent& evt)
{

    return true;
}


bool CStateManager::frameStarted(const FrameEvent& evt)
{
    bool ingame = true;
    if(!m_stack.empty()) {
        m_stack.back()->update();
    } else {
        ingame = false;
    }
    return ingame;
}


void CStateManager::popStack()
{
    while(!m_stack.empty()) {
        m_stack.back()->leave();
        m_stack.pop_back();
    }
}


void CStateManager::popState()
{
  // cleanup the current state
  if(!m_stack.empty()) {
      m_stack.back()->leave();
      m_stack.pop_back();
  }

  // enter previous state
  if(!m_stack.empty()) {
      m_stack.back()->enter();
  }
}


void CStateManager::popToState(CState* state)
{

}


void CStateManager::pushState(CState* state)
{
    m_stack.push_back(state);
    m_stack.back()->enter();
}
