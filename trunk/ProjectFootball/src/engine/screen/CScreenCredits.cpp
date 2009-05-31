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

#include <libintl.h>

#include "CScreenCredits.h"
#include "../CGameEngine.h"
#include "../../utils/CLog.h"


CScreenCredits::CScreenCredits()
: CWindowHandler("credits.layout")
{
    LOG_DEBUG("CScreenCredits()");
}


CScreenCredits::~CScreenCredits()
{
    LOG_DEBUG("~CScreenCredits()");
}

void CScreenCredits::init()
{
	CEGUI::WindowManager *windowMngr = CEGUI::WindowManager::getSingletonPtr();

    m_backButton = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/BackButton"));
    registerEventConnection(m_backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenCredits::backButtonClicked, this)));

    // i18n support
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/ApplicationLabel"))->setText((CEGUI::utf8*)gettext("Application Design :"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/CodeLabel"))->setText((CEGUI::utf8*)gettext("Programming:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/GraphicLabel"))->setText((CEGUI::utf8*)gettext("Graphic Design:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/3DLabel"))->setText((CEGUI::utf8*)gettext("3D Modeling:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/DatabaseLabel"))->setText((CEGUI::utf8*)gettext("Database Information :"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/TexturesLabel"))->setText((CEGUI::utf8*)gettext("Textures:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/SoundLabel"))->setText((CEGUI::utf8*)gettext("Sound Effects:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/BasedLabel"))->setText((CEGUI::utf8*)gettext("Based on:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/ThanksLabel"))->setText((CEGUI::utf8*)gettext("Thanks to:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/AllUsersLabel"))->setText((CEGUI::utf8*)gettext("... all the users who participated on website and game forums and,\n    of course, to all the users who tested the game"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/StaffTextLabel"))->setText((CEGUI::utf8*)gettext("All the people who have spent our time and efforts\n with this humble football manager, we are looking\n    forward to you enjoying our work, because\n from the beginning we have always chased a goal :"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Credits/GoalLabel"))->setText((CEGUI::utf8*)gettext(" MAKING FOOTBALL FANS TO ENJOY "));
    m_backButton->setText((CEGUI::utf8*)gettext("Back"));
}

bool CScreenCredits::backButtonClicked(const CEGUI::EventArgs& e)
{
	CGameEngine::getInstance()->getWindowManager()->previousScreen();
	return true;
}
