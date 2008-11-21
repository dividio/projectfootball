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

#include "CScreen.h"
#include "../utils/CLog.h"


CScreen::CScreen(const char *layout)
{
    CLog::getInstance()->debug("CScreen()");

    m_root			= Ogre::Root::getSingletonPtr();
    m_system		= CEGUI::System::getSingletonPtr();
    m_renderer		= (CEGUI::OgreCEGUIRenderer *) m_system->getRenderer();
    m_windowMngr	= CEGUI::WindowManager::getSingletonPtr();
    m_layout		= m_windowMngr->loadWindowLayout((CEGUI::utf8*)layout);
}


CScreen::~CScreen()
{
  CLog::getInstance()->debug("~CScreen()");
  m_windowMngr->destroyWindow(m_layout);
}

void CScreen::enter()
{
    m_system->setGUISheet(m_layout);
    m_root->getSceneManager("Default SceneManager")->clearScene();
}

bool CScreen::leave()
{
	return true;
}

void CScreen::update()
{
	// Nothing to do
}
