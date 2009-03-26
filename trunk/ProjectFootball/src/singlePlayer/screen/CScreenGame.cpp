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

#include "CScreenGame.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../event/CEventConsumer.h"
#include "../option/CSinglePlayerOptionManager.h"

#include "../../engine/CGameEngine.h"
#include "../../engine/option/CSystemOptionManager.h"
#include "../../utils/CLog.h"


CScreenGame::CScreenGame(CSinglePlayerGame *game)
    :CScreen("game.layout")
{
    CLog::getInstance()->debug("CScreenGame()");

    m_game = game;

    m_mainWindow             = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/MainWindow"));
    m_competitionName        = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/CompetitionName"));
    m_competitionCountryFlag = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/CompetitionCountryFlag"));
    m_competitionPhaseName   = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/CompetitionPhase"));
    m_nextCompetitionName    = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/NextCompetitionName"));
    m_nextHomeTeamName       = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/NextHomeTeamName"));
    m_nextAwayTeamName       = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/NextAwayTeamName"));
    m_homeTeamName           = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/HomeTeamName"));
    m_awayTeamName           = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/AwayTeamName"));
    m_homeTeamAverage        = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/HomeTeamAverage"));
    m_awayTeamAverage        = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/AwayTeamAverage"));
    m_homeTeamShield         = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/HomeTeamShield"));
    m_awayTeamShield         = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/AwayTeamShield"));
    m_saveButton             = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/SaveButton"));
    m_mainMenuButton         = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/MainMenuButton"));
    m_gameExitButton         = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/GameExitButton"));
    m_rankingButton          = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/RankingButton"));
    m_teamPlayersButton	     = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/TeamPlayersButton"));
    m_resultsButton	         = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/ResultsButton"));
    m_playButton             = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/PlayButton"));
    m_saveConfirmButton      = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/SaveConfirmationWindow/Confirm"));
    m_exitConfirmButton      = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/ExitConfirmationWindow/YesButton"));
    m_exitCancelButton       = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/ExitConfirmationWindow/NoButton"));
    m_gameExitConfirmButton  = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/GameExitConfirmationWindow/YesButton"));
    m_gameExitCancelButton   = static_cast<CEGUI::PushButton*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/GameExitConfirmationWindow/NoButton"));
    m_resultModeCheckbox     = static_cast<CEGUI::Checkbox*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/ResultMode"));
    m_confirmSaveWindow      = static_cast<CEGUI::FrameWindow*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/SaveConfirmationWindow"));
    m_confirmSaveNote        = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/SaveConfirmationWindow/Note"));
    m_confirmExitWindow      = static_cast<CEGUI::FrameWindow*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/ExitConfirmationWindow"));
    m_confirmExitNote        = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/ExitConfirmationWindow/Note"));
    m_confirmGameExitWindow  = static_cast<CEGUI::FrameWindow*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/GameExitConfirmationWindow"));
    m_confirmGameExitNote    = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/GameExitConfirmationWindow/Note"));

    // GNS windows
    m_gnsStatisticsWindow    = static_cast<CEGUI::FrameWindow*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/GNS_Statistics"));
    m_gnsApparelWindow       = static_cast<CEGUI::FrameWindow*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/GNS_Apparel"));

    // GNS radio buttons
    std::string guiName = CSystemOptionManager::getInstance()->getGUISkin();
    std::string radioButtonName = guiName + "/RadioButton";
    std::string radioGNSName;
    CEGUI::Window* window2 = static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/MainWindow2"));

    m_radioApparelButton = new CEGUI::RadioButton((CEGUI::utf8*)radioButtonName.c_str(), "Game/Apparel");
    window2->addChildWindow(m_radioApparelButton);
    m_radioApparelButton->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.6f, 0 ), CEGUI::UDim( 0.7f, 0 ) ) );
    m_radioApparelButton->setSize( CEGUI::UVector2( CEGUI::UDim( 0.1f, 0 ), CEGUI::UDim( 0.05f, 0 ) ) );
    m_radioApparelButton->setWindowRenderer("Falagard/ToggleButton");
    radioGNSName = guiName + "/GNSApparel";
    m_radioApparelButton->setLookNFeel((CEGUI::utf8*)radioGNSName.c_str());

    m_radioStatisticsButton = new CEGUI::RadioButton((CEGUI::utf8*)radioButtonName.c_str(), "Game/Statistics");
    window2->addChildWindow(m_radioStatisticsButton);
    m_radioStatisticsButton->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.6f, 0 ), CEGUI::UDim( 0.5f, 0 ) ) );
    m_radioStatisticsButton->setSize( CEGUI::UVector2( CEGUI::UDim( 0.1f, 0 ), CEGUI::UDim( 0.05f, 0 ) ) );
    m_radioStatisticsButton->setWindowRenderer("Falagard/ToggleButton");
    radioGNSName = guiName + "/GNSStatistics";
    m_radioStatisticsButton->setLookNFeel((CEGUI::utf8*)radioGNSName.c_str());

    // Group GNS windows
    m_gnsWindowGroup.push_back(m_gnsStatisticsWindow);
    m_gnsWindowGroup.push_back(m_gnsApparelWindow);

    // Bind GNS windows to radio buttons
    m_radioApparelButton   ->setUserData(m_gnsApparelWindow);
    m_radioStatisticsButton->setUserData(m_gnsStatisticsWindow);

    // i18n support
    m_saveButton           ->setTooltipText((CEGUI::utf8*)gettext("Save"));
    m_mainMenuButton       ->setTooltipText((CEGUI::utf8*)gettext("Return to Main Menu"));
    m_gameExitButton       ->setTooltipText((CEGUI::utf8*)gettext("Exit to OS"));
    m_rankingButton        ->setText((CEGUI::utf8*)gettext("Ranking"));
    m_teamPlayersButton    ->setText((CEGUI::utf8*)gettext("Team Players"));
    m_resultsButton        ->setText((CEGUI::utf8*)gettext("Results"));
    m_playButton           ->setTooltipText((CEGUI::utf8*)gettext("Play Match"));
    m_resultModeCheckbox   ->setText((CEGUI::utf8*)gettext("Result Mode"));
    m_confirmSaveNote      ->setText((CEGUI::utf8*)gettext("The game has been saved"));
    m_confirmExitNote      ->setText((CEGUI::utf8*)gettext("Are you sure you want to exit this game?"));
    m_confirmGameExitNote  ->setText((CEGUI::utf8*)gettext("Are you sure you want to exit this game and return to the Operation System?"));
    m_saveConfirmButton    ->setText((CEGUI::utf8*)gettext("Ok"));
    m_exitConfirmButton    ->setText((CEGUI::utf8*)gettext("Yes"));
    m_exitCancelButton     ->setText((CEGUI::utf8*)gettext("No"));
    m_gameExitConfirmButton->setText((CEGUI::utf8*)gettext("Yes"));
    m_gameExitCancelButton ->setText((CEGUI::utf8*)gettext("No"));
    m_radioApparelButton   ->setTooltipText((CEGUI::utf8*)gettext("Apparel"));
    m_radioStatisticsButton->setTooltipText((CEGUI::utf8*)gettext("Statistics"));
    static_cast<CEGUI::Window*>(m_windowMngr->getWindow((CEGUI::utf8*)"Game/NextEventLabel"))->setText((CEGUI::utf8*)gettext("Next event:"));

    // Event handle
    m_saveButton           ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::saveButtonClicked, this));
    m_mainMenuButton       ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::mainMenuButtonClicked, this));
    m_gameExitButton       ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::gameExitButtonClicked, this));
    m_rankingButton        ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::rankingButtonClicked, this));
    m_teamPlayersButton    ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::teamPlayersButtonClicked, this));
    m_resultsButton        ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::resultsButtonClicked, this));
    m_playButton           ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::playButtonClicked, this));
    m_resultModeCheckbox   ->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&CScreenGame::resultModeCheckboxCheckStateChanged, this));
    m_saveConfirmButton    ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::saveConfirmButtonClicked, this));
    m_exitConfirmButton    ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::exitConfirmButtonClicked, this));
    m_exitCancelButton     ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::exitCancelButtonClicked, this));
    m_gameExitConfirmButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::gameExitConfirmButtonClicked, this));
    m_gameExitCancelButton ->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CScreenGame::gameExitCancelButtonClicked, this));
    m_radioApparelButton   ->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged, CEGUI::Event::Subscriber(&CScreenGame::gnsRadioButtonClicked, this));
    m_radioStatisticsButton->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged, CEGUI::Event::Subscriber(&CScreenGame::gnsRadioButtonClicked, this));
}

CScreenGame::~CScreenGame()
{
    CLog::getInstance()->debug("~CScreenGame()");
}

void CScreenGame::enter()
{
	CScreen::enter();

    m_resultModeCheckbox->setSelected(m_game->getOptionManager()->getMatchResultMode());
    m_radioStatisticsButton->setSelected(true);

    updateNextMatch();
}

void CScreenGame::saveGame()
{
    CGameEngine::getInstance()->save();
}

bool CScreenGame::saveButtonClicked(const CEGUI::EventArgs& e)
{
    try {
        CGameEngine::getInstance()->save();
        m_confirmSaveNote->setText((CEGUI::utf8*)gettext("The game has been saved"));
    } catch(...) {
        m_confirmSaveNote->setText((CEGUI::utf8*)gettext("ATTENTION: Game can not be saved"));
    }

    m_mainWindow->disable();
    m_confirmSaveWindow->setVisible(true);
    m_confirmSaveWindow->activate();
    m_confirmSaveWindow->enable();
	return true;
}

bool CScreenGame::mainMenuButtonClicked(const CEGUI::EventArgs& e)
{
    m_mainWindow->disable();
    m_confirmExitWindow->setVisible(true);
    m_confirmExitWindow->activate();
    m_confirmExitWindow->enable();
	return true;
}

bool CScreenGame::gameExitButtonClicked(const CEGUI::EventArgs& e)
{
    m_mainWindow->disable();
    m_confirmGameExitWindow->setVisible(true);
    m_confirmGameExitWindow->activate();
    m_confirmGameExitWindow->enable();
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
	if( m_game->getEventConsumer()->getLastEvent()!=NULL ){
		m_game->getEventConsumer()->consumeLastEvent();
	}else{
		m_game->getEventConsumer()->consumeEvents();
	}

	updateNextMatch();
	return true;
}

bool CScreenGame::resultModeCheckboxCheckStateChanged(const CEGUI::EventArgs& e)
{
    m_game->getOptionManager()->setMatchResultMode(m_resultModeCheckbox->isSelected());

	return true;
}

bool CScreenGame::saveConfirmButtonClicked(const CEGUI::EventArgs& e)
{
    m_confirmSaveWindow->setVisible(false);
    m_confirmSaveWindow->deactivate();
    m_confirmSaveWindow->disable();
    m_mainWindow->enable();

    return true;
}

bool CScreenGame::exitConfirmButtonClicked(const CEGUI::EventArgs& e)
{
    m_confirmExitWindow->setVisible(false);
    m_confirmExitWindow->deactivate();
    m_confirmExitWindow->disable();
    m_mainWindow->enable();
    m_game->exit();
    return true;
}

bool CScreenGame::exitCancelButtonClicked(const CEGUI::EventArgs& e)
{
    m_confirmExitWindow->setVisible(false);
    m_confirmExitWindow->deactivate();
    m_confirmExitWindow->disable();
    m_mainWindow->enable();

    return true;
}

bool CScreenGame::gameExitConfirmButtonClicked(const CEGUI::EventArgs& e)
{
    m_confirmGameExitWindow->setVisible(false);
    m_confirmGameExitWindow->deactivate();
    m_confirmGameExitWindow->disable();
    m_mainWindow->enable();
    m_game->exit();
    CGameEngine::getInstance()->exit();
    return true;
}

bool CScreenGame::gameExitCancelButtonClicked(const CEGUI::EventArgs& e)
{
    m_confirmGameExitWindow->setVisible(false);
    m_confirmGameExitWindow->deactivate();
    m_confirmGameExitWindow->disable();
    m_mainWindow->enable();

    return true;
}

bool CScreenGame::gnsRadioButtonClicked(const CEGUI::EventArgs& e)
{
    CEGUI::RadioButton *button = m_radioApparelButton->getSelectedButtonInGroup();
    CEGUI::FrameWindow *gnsWindow = (CEGUI::FrameWindow*)button->getUserData();
    showGNS(gnsWindow);

    return true;
}

void CScreenGame::showGNS(CEGUI::FrameWindow *gnsWindow)
{

    std::list<CEGUI::FrameWindow*>::iterator it;
    for(it = m_gnsWindowGroup.begin(); it != m_gnsWindowGroup.end(); it++) {
        CEGUI::FrameWindow *w = (*it);
        if(w->getName() == gnsWindow->getName()) {
            w->setVisible(true);
        } else {
            w->setVisible(false);
        }
    }
}

void CScreenGame::updateNextMatch()
{
    CPfMatches  *nextMatch  = m_game->getIDAOFactory()->getIPfMatchesDAO()->findNextTeamMatch(m_game->getOptionManager()->getGamePlayerTeam());
    if( nextMatch==NULL ){
        CPfTeams *playerTeam = m_game->getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game->getOptionManager()->getGamePlayerTeam());
        m_homeTeamName        ->setText((CEGUI::utf8*)playerTeam->getSTeam().c_str());

        IPfTeamAveragesDAO *teamAveragesDAO = m_game->getIDAOFactory()->getIPfTeamAveragesDAO();
        CPfTeamAverages    *teamAverage     = teamAveragesDAO->findByXTeam(playerTeam->getXTeam_str());
        std::ostringstream average;
        average << teamAverage->getNTotal();
        m_homeTeamAverage->setProperty("Text", (CEGUI::utf8*)average.str().c_str());
        average.str("");
        delete teamAverage;

        m_awayTeamName        ->setText("");
        m_awayTeamAverage     ->setText("");
        m_competitionName     ->setText("");
        m_competitionPhaseName->setText("");

        // Team Shields
        m_homeTeamShield->setProperty("Image", "set:"+ playerTeam->getSLogo() +" image:"+playerTeam->getSLogo()+"_b");
        m_awayTeamShield->setProperty("Image", "set: image:full_image");


        delete playerTeam;
        m_playButton->setEnabled(false);
    }else{
        IDAOFactory             *daoFactory           = m_game->getIDAOFactory();
        IPfCompetitionsDAO      *competitionsDAO      = daoFactory->getIPfCompetitionsDAO();
        IPfCountriesDAO         *countriesDAO         = daoFactory->getIPfCountriesDAO();
        IPfCompetitionPhasesDAO *competitionPhasesDAO = daoFactory->getIPfCompetitionPhasesDAO();
        IPfTeamsDAO             *teamsDAO = daoFactory->getIPfTeamsDAO();
        CPfTeams                *homeTeam = teamsDAO->findByXTeam(nextMatch->getXFkTeamHome());
        CPfTeams                *awayTeam = teamsDAO->findByXTeam(nextMatch->getXFkTeamAway());
        CPfCompetitionPhases    *competitionPhase = competitionPhasesDAO->findByXCompetitionPhase(nextMatch->getXFkCompetitionPhase());
        CPfCompetitions         *competition      = competitionsDAO->findByXCompetition(competitionPhase->getXFkCompetition());
        CPfCountries            *country          = countriesDAO->findByXCountry(competition->getXFkCountry_str());

        m_competitionName     ->setText((CEGUI::utf8*)competition->getSCompetition().c_str());
        m_competitionPhaseName->setText((CEGUI::utf8*)competitionPhase->getSCompetitionPhase().c_str());
        m_homeTeamName        ->setText((CEGUI::utf8*)homeTeam->getSTeam().c_str());
        m_awayTeamName        ->setText((CEGUI::utf8*)awayTeam->getSTeam().c_str());

        m_competitionCountryFlag->setProperty("Image", "set:"+ country->getSFlag() +" image:"+country->getSFlag() + "_mo_flag");

        // Team Averages
        IPfTeamAveragesDAO *teamAveragesDAO = m_game->getIDAOFactory()->getIPfTeamAveragesDAO();
        CPfTeamAverages    *teamAverage     = teamAveragesDAO->findByXTeam(homeTeam->getXTeam_str());
        std::ostringstream average;
        average << teamAverage->getNTotal();
        m_homeTeamAverage->setProperty("Text", (CEGUI::utf8*)average.str().c_str());
        average.str("");
        delete teamAverage;

        teamAverage = teamAveragesDAO->findByXTeam(awayTeam->getXTeam_str());
        average << teamAverage->getNTotal();
        m_awayTeamAverage->setProperty("Text", (CEGUI::utf8*)average.str().c_str());
        average.str("");
        delete teamAverage;

        // Team Shields
        m_homeTeamShield->setProperty("Image", "set:"+ homeTeam->getSLogo() +" image:"+homeTeam->getSLogo()+"_b");
        m_awayTeamShield->setProperty("Image", "set:"+ awayTeam->getSLogo() +" image:"+awayTeam->getSLogo()+"_b");

        m_playButton->setEnabled(true);

        delete country;
        delete competition;
        delete competitionPhase;
        delete homeTeam;
        delete awayTeam;
        delete nextMatch;
    }
}
