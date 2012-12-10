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
#include <libintl.h>

#include "CMainMenuWindowHandler.h"
#include "../CGameEngine.h"
#include "../../utils/CLog.h"
#include "../../singlePlayer/CSinglePlayerGame.h"
#include "../../editor/CGameEditor.h"


CMainMenuWindowHandler::CMainMenuWindowHandler()
 :CWindowHandler("mainMenu.layout")
{
    LOG_DEBUG("CMainMenuWindowHandler()");
}


CMainMenuWindowHandler::~CMainMenuWindowHandler()
{
	LOG_DEBUG("~CMainMenuWindowHandler()");
}

void CMainMenuWindowHandler::enter()
{
    CWindowHandler::enter();
    CGameEngine::getInstance()->getWindowManager()->clearHistory();

    IPfVersionDAO *versionDAO = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfVersionDAO();
    CPfVersion    *version = versionDAO->findByXVersion(1);
    CDate nowDate;
    m_currentDate->setText(nowDate.format("%d/%m/%Y"));
    m_versionDate->setText(version->getDDate().format("%d/%m/%Y"));
    m_version    ->setText(version->getSVersion());

    IPfGamesDAO*            gamesDAO    = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    std::vector<CPfGames*> *gamesList   = gamesDAO->findByXFkUser(CGameEngine::getInstance()->getCurrentUser()->getXUser_str());

    if(gamesList != NULL) {
        if(!gamesList->empty()) {
            m_quickLoadButton->setEnabled(true);
        } else {
            m_quickLoadButton->setEnabled(false);
        }
        gamesDAO->freeVector(gamesList);
    } else {
        m_quickLoadButton->setEnabled(false);
    }

    delete version;

}

void CMainMenuWindowHandler::init()
{
    CEGUI::WindowManager *windowMngr = CEGUI::WindowManager::getSingletonPtr();

    m_OnLineCommunityButton     = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/OnLineCommunityButton"));
    m_virtualChampionshipButton = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/VirtualChampionshipButton"));
    m_newManagerGameButton	    = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/NewManagerGameButton"));
    m_ProfessionalCareerButton  = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/ProfessionalCareerButton"));
    m_EditorButton              = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/EditorButton"));
    m_FootLibraryButton         = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/FootLibraryButton"));
    m_configButton			    = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/ConfigButton"));
    m_creditsButton			    = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/CreditsButton"));
    m_quickLoadButton		    = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/QuickLoadButton"));
    m_loadGameButton	        = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/LoadGameButton"));
    m_quitButton		  	    = static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/QuitButton"));
    m_currentDate       	    = static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/CurrentDate"));
    m_versionDate       	    = static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/VersionDate"));
    m_version           	    = static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"MainMenu/Version"));

    // Event handle
    registerEventConnection(m_virtualChampionshipButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenuWindowHandler::virtualChampionshipButtonClicked, this)));
    registerEventConnection(m_EditorButton             ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenuWindowHandler::editorButtonClicked, this)));
    registerEventConnection(m_newManagerGameButton     ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenuWindowHandler::newManagerGameButtonClicked, this)));
    registerEventConnection(m_configButton             ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenuWindowHandler::configButtonClicked, this)));
    registerEventConnection(m_creditsButton            ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenuWindowHandler::creditsButtonClicked, this)));
    registerEventConnection(m_loadGameButton           ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenuWindowHandler::loadGameButtonClicked, this)));
    registerEventConnection(m_quickLoadButton          ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenuWindowHandler::quickLoadButtonClicked, this)));
    registerEventConnection(m_quitButton               ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CMainMenuWindowHandler::quitButtonClicked, this)));

    // i18n support
    m_OnLineCommunityButton    ->setText((CEGUI::utf8*)gettext("On-line Community"));
    m_virtualChampionshipButton->setText((CEGUI::utf8*)gettext("Virtual Championship"));
    m_newManagerGameButton     ->setText((CEGUI::utf8*)gettext("Manager League"));
    m_ProfessionalCareerButton ->setText((CEGUI::utf8*)gettext("Professional Career"));
    m_EditorButton             ->setText((CEGUI::utf8*)gettext("Editor"));
    m_FootLibraryButton        ->setText((CEGUI::utf8*)gettext("Football Library"));
    m_configButton             ->setText((CEGUI::utf8*)gettext("Configuration"));
    m_creditsButton            ->setText((CEGUI::utf8*)gettext("Credits"));
    m_quickLoadButton          ->setTooltipText((CEGUI::utf8*)gettext("Quick Load"));
    m_loadGameButton           ->setTooltipText((CEGUI::utf8*)gettext("Load"));
    m_quitButton               ->setTooltipText((CEGUI::utf8*)gettext("Quit"));
    windowMngr->getWindow((CEGUI::utf8*)"MainMenu/CurrentDateLabel")->setText((CEGUI::utf8*)gettext("Today is:"));
    windowMngr->getWindow((CEGUI::utf8*)"MainMenu/VersionDateLabel")->setText((CEGUI::utf8*)gettext("Last update:"));
}

bool CMainMenuWindowHandler::virtualChampionshipButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->getWindowManager()->nextScreen("NewVirtualGame");
    return true;
}

bool CMainMenuWindowHandler::editorButtonClicked(const CEGUI::EventArgs& e)
{
	CGameEngine::getInstance()->loadGame(CGameEditor::load());
    CGameEngine::getInstance()->getWindowManager()->nextScreen("Editor");
    return true;
}

bool CMainMenuWindowHandler::newManagerGameButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->getWindowManager()->nextScreen("NewManagerGame");
    return true;
}

bool CMainMenuWindowHandler::configButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->getWindowManager()->nextScreen("Configuration");
    return true;
}

bool CMainMenuWindowHandler::creditsButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->getWindowManager()->nextScreen("Credits");
    return true;
}

bool CMainMenuWindowHandler::loadGameButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->getWindowManager()->nextScreen("LoadGame");
    return true;
}

bool CMainMenuWindowHandler::quickLoadButtonClicked(const CEGUI::EventArgs& e)
{
    IPfGamesDAO*            gamesDAO    = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    std::vector<CPfGames*> *gamesList   = gamesDAO->findByXFkUser(CGameEngine::getInstance()->getCurrentUser()->getXUser_str());

    if(gamesList != NULL) {
        if(!gamesList->empty()) {
            CPfGames *game = gamesList->front();
            CGameEngine::getInstance()->loadGame(CSinglePlayerGame::load(*game));
        }
        gamesDAO->freeVector(gamesList);
    }

    return true;
}

bool CMainMenuWindowHandler::quitButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->exit();
    return true;
}
