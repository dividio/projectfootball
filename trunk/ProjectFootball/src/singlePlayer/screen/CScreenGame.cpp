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

#include <libintl.h>

#include "CScreenGame.h"
#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"

CScreenGame::CScreenGame(CSinglePlayerGame *game)
    :CScreen("game.layout")
{
    CLog::getInstance()->debug("CScreenGame()");

    m_game = game;

    m_playerTeamText     	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/PlayerTeamText"));
    m_nextMatchText      	= static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/NextMatchText"));

    m_saveButton			= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/SaveButton"));
    m_mainMenuButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/MainMenuButton"));
    m_rankingButton			= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/RankingButton"));
    m_teamPlayersButton		= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/TeamPlayersButton"));
    m_resultsButton			= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/ResultsButton"));
    m_playButton        	= static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/PlayButton"));
    m_resultModeCheckbox	= static_cast<CEGUI::Checkbox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/ResultMode"));

    // i18n support
    m_saveButton->setText((CEGUI::utf8*)gettext("Save"));
    m_mainMenuButton->setText((CEGUI::utf8*)gettext("Return to Main Menu"));
    m_rankingButton->setText((CEGUI::utf8*)gettext("Ranking"));
    m_teamPlayersButton->setText((CEGUI::utf8*)gettext("Team Players"));
    m_resultsButton->setText((CEGUI::utf8*)gettext("Results"));
    m_playButton->setText((CEGUI::utf8*)gettext("Play Match"));
    m_resultModeCheckbox->setText((CEGUI::utf8*)gettext("Result Mode"));

    // Event handle
    m_saveButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::saveButtonClicked, this));
    m_mainMenuButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::mainMenuButtonClicked, this));
    m_rankingButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::rankingButtonClicked, this));
    m_teamPlayersButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::teamPlayersButtonClicked, this));
    m_resultsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::resultsButtonClicked, this));
    m_playButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::playButtonClicked, this));
    m_resultModeCheckbox->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&CScreenGame::resultModeCheckboxCheckStateChanged, this));

    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/PlayerTeamLabel"))->setText((CEGUI::utf8*)gettext("Your Team:"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/NextMatchLabel"))->setText((CEGUI::utf8*)gettext("Next Match:"));
}

CScreenGame::~CScreenGame()
{
    CLog::getInstance()->debug("~CScreenGame()");
}

void CScreenGame::enter()
{
	CScreen::enter();

    IPfGameOptionsDAO   *optionsDAO = m_game->getIDAOFactory()->getIPfGameOptionsDAO();

    CPfGameOptions *resultMode = optionsDAO->findBySCategoryAndSAttribute("Match", "ResultMode");
    if(resultMode->getSValue() == "true") { //result mode
        m_resultModeCheckbox->setSelected(true);
    } else {
        m_resultModeCheckbox->setSelected(false);
    }
    delete resultMode;

    CPfTeams    *playerTeam = m_game->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    m_playerTeamText->setText(playerTeam->getSTeam());
    delete playerTeam;

    CPfMatches  *nextMatch  = m_game->getIDAOFactory()->getIPfMatchesDAO()->findNextPlayerTeamMatch();
    if( nextMatch==NULL ){
        m_nextMatchText->setText("No Match");
        m_playButton->setEnabled(false);
    }else{
        IPfTeamsDAO *teamsDAO = m_game->getIDAOFactory()->getIPfTeamsDAO();
        CPfTeams    *homeTeam = teamsDAO->findByXTeam(nextMatch->getXFkTeamHome());
        CPfTeams    *awayTeam = teamsDAO->findByXTeam(nextMatch->getXFkTeamAway());

        std::string text;
        text += homeTeam->getSTeam()+" - "+awayTeam->getSTeam();
        m_nextMatchText->setText(text);
        m_playButton->setEnabled(true);

        delete homeTeam;
        delete awayTeam;
        delete nextMatch;
    }
}

void CScreenGame::saveGame()
{
    CGameEngine::getInstance()->save();
}

bool CScreenGame::saveButtonClicked(const CEGUI::EventArgs& e)
{
	CGameEngine::getInstance()->save();
	return true;
}

bool CScreenGame::mainMenuButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->exit();
	return true;
}

bool CScreenGame::rankingButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getRankingScreen());
	return true;
}

bool CScreenGame::teamPlayersButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getTeamPlayersScreen());
	return true;
}

bool CScreenGame::resultsButtonClicked(const CEGUI::EventArgs& e)
{
	m_game->nextScreen(m_game->getResultsScreen());
	return true;
}

bool CScreenGame::playButtonClicked(const CEGUI::EventArgs& e)
{
    CPfGameOptions *resultMode = m_game->getIDAOFactory()->getIPfGameOptionsDAO()->findBySCategoryAndSAttribute("Match", "ResultMode");
    if(resultMode->getSValue() == "true") {
    	m_game->nextScreen(m_game->getMatchResultScreen());
    } else {
    	m_game->nextScreen(m_game->getSimulatorScreen());
    }
    delete resultMode;

	return true;
}

bool CScreenGame::resultModeCheckboxCheckStateChanged(const CEGUI::EventArgs& e)
{
    IPfGameOptionsDAO	*optionsDAO = m_game->getIDAOFactory()->getIPfGameOptionsDAO();
    CPfGameOptions		*resultMode = optionsDAO->findBySCategoryAndSAttribute("Match", "ResultMode");

    if(m_resultModeCheckbox->isSelected()) {
        resultMode->setSValue("true");
    } else {
        resultMode->setSValue("false");
    }
    optionsDAO->updateReg(resultMode);
    delete resultMode;

	return true;
}
