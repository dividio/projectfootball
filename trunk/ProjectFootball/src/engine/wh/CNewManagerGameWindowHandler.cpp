/******************************************************************************
* Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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
#include <libintl.h>

#include "CScreenNewManagerGame.h"
#include "../CGameEngine.h"
#include "../../exceptions/PFException.h"
#include "../../singlePlayer/CSinglePlayerGame.h"
#include "../../utils/CLog.h"

CScreenNewManagerGame::CScreenNewManagerGame()
: CWindowHandler("newManagerGame.layout")
{
    LOG_DEBUG("CScreenNewManagerGame()");
}

CScreenNewManagerGame::~CScreenNewManagerGame()
{
    LOG_DEBUG("~CScreenNewManagerGame()");
}

void CScreenNewManagerGame::enter()
{
    m_newGameButton->setEnabled(false);
    m_newGameEditbox->setText("");
}

void CScreenNewManagerGame::init()
{
	CEGUI::WindowManager *windowMngr = CEGUI::WindowManager::getSingletonPtr();

    m_backButton		   = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"NewManagerGame/BackButton"));
    m_newGameButton        = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"NewManagerGame/NewGameButton"));
    m_newGameEditbox       = static_cast<CEGUI::Editbox*>(windowMngr->getWindow((CEGUI::utf8*)"NewManagerGame/NewGameEdit"));

    // i18n support
    m_newGameButton       ->setText((CEGUI::utf8*)gettext("New Game"));
    m_backButton          ->setText((CEGUI::utf8*)gettext("Back"));

    // Event handle
    registerEventConnection(m_backButton         ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenNewManagerGame::backButtonClicked, this)));
    registerEventConnection(m_newGameButton      ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenNewManagerGame::newGameButtonClicked, this)));
    registerEventConnection(m_newGameEditbox     ->subscribeEvent(CEGUI::Editbox::EventTextChanged, CEGUI::Event::Subscriber(&CScreenNewManagerGame::newGameEditboxTextChanged, this)));
}

bool CScreenNewManagerGame::newGameEditboxTextChanged(const CEGUI::EventArgs& e)
{
    if( m_newGameEditbox->getText().compare("")!=0 ){
        m_newGameButton->setEnabled(true);
    }else{
        m_newGameButton->setEnabled(false);
    }
}

bool CScreenNewManagerGame::backButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->getWindowManager()->previousScreen();
    return true;
}

bool CScreenNewManagerGame::newGameButtonClicked(const CEGUI::EventArgs& e)
{
    IMasterDAOFactory *masterDatabase = CGameEngine::getInstance()->getCMasterDAOFactory();
    const CPfUsers *user = CGameEngine::getInstance()->getCurrentUser();

    if( user==NULL || user->getXUser()==0 ){
        throw PFEXCEPTION("[CScreenNewManagerGame::newGameButtonClicked] User not defined");
    }

    CGameEngine::getInstance()->loadGame(CSinglePlayerGame::newGame(*user, m_newGameEditbox->getText().c_str()));

    m_newGameEditbox->setText("");

    return true;
}
