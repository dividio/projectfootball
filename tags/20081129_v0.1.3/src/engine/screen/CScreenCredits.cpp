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
	:CScreen("credits.layout")
{
    CLog::getInstance()->debug("CScreenCredits()");

    m_backButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Credits/BackButton"));
    m_backButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenCredits::backButtonClicked, this));

    // i18n support
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Credits/BasedLabel"))->setText((CEGUI::utf8*)gettext("Based on:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Credits/CodedLabel"))->setText((CEGUI::utf8*)gettext("Designed and coded by:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Credits/ThanksLabel"))->setText((CEGUI::utf8*)gettext("Thanks to:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Credits/AllUsersLabel"))->setText((CEGUI::utf8*)gettext("... and to all users who tested the game ;-)"));
    m_backButton->setText((CEGUI::utf8*)gettext("Back"));
}


CScreenCredits::~CScreenCredits()
{
    CLog::getInstance()->debug("~CScreenCredits()");
}

bool CScreenCredits::backButtonClicked(const CEGUI::EventArgs& e)
{
	CGameEngine::getInstance()->previousScreen();
	return true;
}
