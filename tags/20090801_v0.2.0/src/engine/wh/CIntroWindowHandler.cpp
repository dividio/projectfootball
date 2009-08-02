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

#include "CIntroWindowHandler.h"
#include "../CGameEngine.h"
#include "../utils/CTimer.h"
#include "../../utils/CLog.h"


CIntroWindowHandler::CIntroWindowHandler()
 :CWindowHandler("intro.layout")
{
    LOG_DEBUG("CIntroWindowHandler()");
}

CIntroWindowHandler::~CIntroWindowHandler()
{
    LOG_DEBUG("~CIntroWindowHandler()");
    delete m_timer;
}

void CIntroWindowHandler::enter()
{
    CWindowHandler::enter();

    m_timer->reset();
    m_elapsedTime = 0;
}

void CIntroWindowHandler::init()
{
	CWindowHandler::init();

    m_timer = new CTimer(1);
    m_introTime = 5;
    m_elapsedTime = 0;

    m_mainWindow = static_cast<CEGUI::Window*>(CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"Intro"));
    registerEventConnection(m_mainWindow->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&CIntroWindowHandler::buttonClicked, this)));
}

void CIntroWindowHandler::update()
{
    if(m_timer->nextTick()) {
        m_elapsedTime++;
        if(m_elapsedTime == m_introTime) {
            CGameEngine::getInstance()->getWindowManager()->nextScreen("MainMenu");
        }
    }
}

bool CIntroWindowHandler::buttonClicked(const CEGUI::EventArgs& e)
{
	CGameEngine::getInstance()->getWindowManager()->nextScreen("MainMenu");
	return true;
}
