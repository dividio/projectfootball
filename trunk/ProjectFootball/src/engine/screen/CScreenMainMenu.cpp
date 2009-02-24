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

#include "CScreenMainMenu.h"
#include "../CGameEngine.h"
#include "../../utils/CLog.h"
#include "../../singlePlayer/CSinglePlayerGame.h"


CScreenMainMenu::CScreenMainMenu()
 :CScreen("mainMenu.layout")
{
    CLog::getInstance()->debug("CScreenMainMenu()");

    m_virtualCompetitionButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/QuickPlayButton"));
    m_newManagerGameButton	= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/NewManagerGameButton"));
    m_configButton			= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/ConfigButton"));
    m_creditsButton			= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/CreditsButton"));
    m_quickLoadButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/QuickLoadButton"));
    m_loadGameButton	    = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/LoadGameButton"));
    m_quitButton		  	= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/QuitButton"));
    m_currentDate       	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/CurrentDate"));
    m_versionDate       	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/VersionDate"));
    m_version           	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/Version"));

    // Event handle
    m_virtualCompetitionButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::virtualCompetitionButtonClicked, this));
    m_newManagerGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::newManagerGameButtonClicked, this));
    m_configButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::configButtonClicked, this));
    m_creditsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::creditsButtonClicked, this));
    m_loadGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::loadGameButtonClicked, this));
    m_quickLoadButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::quickLoadButtonClicked, this));
    m_quitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenMainMenu::quitButtonClicked, this));

    // i18n support
    m_virtualCompetitionButton->setText((CEGUI::utf8*)gettext("Virtual Championship"));
    m_newManagerGameButton    ->setText((CEGUI::utf8*)gettext("Manager League"));
    m_configButton            ->setText((CEGUI::utf8*)gettext("Config"));
    m_creditsButton           ->setText((CEGUI::utf8*)gettext("Credits"));
    m_quickLoadButton         ->setTooltipText((CEGUI::utf8*)gettext("Quick Load"));
    m_loadGameButton          ->setTooltipText((CEGUI::utf8*)gettext("Load"));
    m_quitButton              ->setTooltipText((CEGUI::utf8*)gettext("Quit"));
    m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/CurrentDateLabel")->setText((CEGUI::utf8*)gettext("Today is:"));
    m_windowMngr->getWindow((CEGUI::utf8*)"MainMenu/VersionDateLabel")->setText((CEGUI::utf8*)gettext("Last update:"));
}


CScreenMainMenu::~CScreenMainMenu()
{
  CLog::getInstance()->debug("~CScreenMainMenu()");
}

void CScreenMainMenu::enter()
{
    CScreen::enter();

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

bool CScreenMainMenu::virtualCompetitionButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getNewVirtualGameScreen());
    return true;
}

bool CScreenMainMenu::newManagerGameButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getNewManagerGameScreen());
    return true;
}

bool CScreenMainMenu::configButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getConfigScreen());
    return true;
}

bool CScreenMainMenu::creditsButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getCreditsScreen());
    return true;
}

bool CScreenMainMenu::loadGameButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->nextScreen(CGameEngine::getInstance()->getLoadGameScreen());
    return true;
}

bool CScreenMainMenu::quickLoadButtonClicked(const CEGUI::EventArgs& e)
{
    IPfGamesDAO*            gamesDAO    = CGameEngine::getInstance()->getCMasterDAOFactory()->getIPfGamesDAO();
    std::vector<CPfGames*> *gamesList   = gamesDAO->findByXFkUser(CGameEngine::getInstance()->getCurrentUser()->getXUser_str());

    if(gamesList != NULL) {
        if(!gamesList->empty()) {
            CPfGames *game = gamesList->front();
            CGameEngine::getInstance()->loadGame(new CSinglePlayerGame(game));
        }
        gamesDAO->freeVector(gamesList);
    }

    return true;
}

bool CScreenMainMenu::quitButtonClicked(const CEGUI::EventArgs& e)
{
    CGameEngine::getInstance()->exit();
    return true;
}
