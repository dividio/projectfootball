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

#include "CStateCredits.h"
#include "CStateManager.h"
#include "../utils/CLog.h"


CStateCredits::CStateCredits()
 :CState()
{
    CLog::getInstance()->debug("CStateCredits()");

    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"credits.layout");
}


CStateCredits* CStateCredits::getInstance()
{
    static CStateCredits instance;
    return &instance;
}


CStateCredits::~CStateCredits()
{
    CLog::getInstance()->debug("~CStateCredits()");
}


void CStateCredits::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

}


void CStateCredits::forcedLeave()
{

}


bool CStateCredits::leave()
{
    return true;
}


void CStateCredits::update()
{
}
