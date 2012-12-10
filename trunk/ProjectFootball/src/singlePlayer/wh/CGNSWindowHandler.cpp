/*******************************************************************************
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

#include "CGNSWindowHandler.h"

#include <libintl.h>
#include "../CSinglePlayerGame.h"
#include "../option/CSinglePlayerOptionManager.h"
#include "../../engine/CGameEngine.h"
#include "../../engine/wh/CGNSGenericWindowHandler.h"
#include "../../utils/CLog.h"

CGNSWindowHandler::CGNSWindowHandler(CSinglePlayerGame &game) :
	CGNSGenericWindowHandler("Game", "ConfigGame"), m_game(game)
{}

CGNSWindowHandler::~CGNSWindowHandler()
{}

void CGNSWindowHandler::enter()
{
	if( std::string("Game")==CGameEngine::getInstance()->getWindowManager()->getCurrentScreen() ){
		m_noButtonsBackground->setVisible(true);
		m_buttonsBackground->setVisible(false);
		m_homeButton->setVisible(false);
		m_homeButton->setEnabled(false);
		m_nextScreenButton->setVisible(false);
		m_nextScreenButton->setEnabled(false);
		m_previousScreenButton->setVisible(false);
		m_previousScreenButton->setEnabled(false);
	} else {
		m_noButtonsBackground->setVisible(false);
		m_buttonsBackground->setVisible(true);
		m_homeButton->setVisible(true);
		m_homeButton->setEnabled(true);
		m_nextScreenButton->setVisible(true);
		m_nextScreenButton->setEnabled(true);
		m_previousScreenButton->setVisible(true);
		m_previousScreenButton->setEnabled(true);
	}

	CEGUI::RadioButton *button = m_changingRoomRadio->getSelectedButtonInGroup();

	if( button==m_changingRoomRadio ){
        if(m_game.getCurrentMatch() != NULL) {
            m_action4Button->setEnabled(true);
        } else {
            m_action4Button->setEnabled(false);
        }
	}

	//Forcing the GNS selection change event
	button->setSelected(false);
	button->setSelected(true);
}

bool CGNSWindowHandler::gnsSelectionChanged(const CEGUI::EventArgs &e)
{
	CEGUI::RadioButton *button = m_changingRoomRadio->getSelectedButtonInGroup();
	if( button==m_changingRoomRadio ){
		m_action1Button->setText((CEGUI::utf8*)gettext("Line Up"));
		m_action1Button->setUserString("screen", "LineUp");
		m_action1Button->setEnabled(true);
		m_action2Button->setText((CEGUI::utf8*)gettext("Team Players"));
		m_action2Button->setUserString("screen", "TeamPlayers");
		m_action2Button->setEnabled(true);
		m_action3Button->setText((CEGUI::utf8*)gettext("Formation"));
		m_action3Button->setUserString("screen", "Formation");
		m_action3Button->setEnabled(true);
		m_action4Button->setText((CEGUI::utf8*)gettext("View Opponent"));
		m_action4Button->setUserString("screen", "ViewOpponent");

		if(m_game.getCurrentMatch() != NULL) {
		    m_action4Button->setEnabled(true);
		} else {
		    m_action4Button->setEnabled(false);
		}

		m_action5Button->setText("");
		m_action5Button->setUserString("screen", "");
		m_action5Button->setEnabled(false);
		m_action6Button->setText("");
		m_action6Button->setUserString("screen", "");
		m_action6Button->setEnabled(false);
		m_action7Button->setText("");
		m_action7Button->setUserString("screen", "");
		m_action7Button->setEnabled(false);
		m_action8Button->setText("");
		m_action8Button->setUserString("screen", "");
		m_action8Button->setEnabled(false);

	} else if( button==m_statisticsRadio ) {
		m_action1Button->setText((CEGUI::utf8*)gettext("Results"));
		m_action1Button->setUserString("screen", "Results");
		m_action1Button->setEnabled(true);
		m_action2Button->setText((CEGUI::utf8*)gettext("Ranking"));
		m_action2Button->setUserString("screen", "Ranking");
		m_action2Button->setEnabled(true);
		m_action3Button->setText((CEGUI::utf8*)gettext("Scorers"));
		m_action3Button->setUserString("screen", "Scorers");
		m_action3Button->setEnabled(true);
		m_action4Button->setText("");
		m_action4Button->setUserString("screen", "");
		m_action4Button->setEnabled(false);
		m_action5Button->setText("");
		m_action5Button->setUserString("screen", "");
		m_action5Button->setEnabled(false);
		m_action6Button->setText("");
		m_action6Button->setUserString("screen", "");
		m_action6Button->setEnabled(false);
		m_action7Button->setText("");
		m_action7Button->setUserString("screen", "");
		m_action7Button->setEnabled(false);
		m_action8Button->setText("");
		m_action8Button->setUserString("screen", "");
		m_action8Button->setEnabled(false);

	}  else if( button==m_historyRadio ) {
        m_action1Button->setText((CEGUI::utf8*)gettext("Career"));
        m_action1Button->setUserString("screen", "SeasonsHistory");
        m_action1Button->setEnabled(true);
        m_action2Button->setText("");
        m_action2Button->setUserString("screen", "");
        m_action2Button->setEnabled(false);
        m_action3Button->setText("");
        m_action3Button->setUserString("screen", "");
        m_action3Button->setEnabled(false);
        m_action4Button->setText("");
        m_action4Button->setUserString("screen", "");
        m_action4Button->setEnabled(false);
        m_action5Button->setText("");
        m_action5Button->setUserString("screen", "");
        m_action5Button->setEnabled(false);
        m_action6Button->setText("");
        m_action6Button->setUserString("screen", "");
        m_action6Button->setEnabled(false);
        m_action7Button->setText("");
        m_action7Button->setUserString("screen", "");
        m_action7Button->setEnabled(false);
        m_action8Button->setText("");
        m_action8Button->setUserString("screen", "");
        m_action8Button->setEnabled(false);

    } else {
		m_action1Button->setText("");
		m_action1Button->setUserString("screen", "");
		m_action1Button->setEnabled(false);
		m_action2Button->setText("");
		m_action2Button->setUserString("screen", "");
		m_action2Button->setEnabled(false);
		m_action3Button->setText("");
		m_action3Button->setUserString("screen", "");
		m_action3Button->setEnabled(false);
		m_action4Button->setText("");
		m_action4Button->setUserString("screen", "");
		m_action4Button->setEnabled(false);
		m_action5Button->setText("");
		m_action5Button->setUserString("screen", "");
		m_action5Button->setEnabled(false);
		m_action6Button->setText("");
		m_action6Button->setUserString("screen", "");
		m_action6Button->setEnabled(false);
		m_action7Button->setText("");
		m_action7Button->setUserString("screen", "");
		m_action7Button->setEnabled(false);
		m_action8Button->setText("");
		m_action8Button->setUserString("screen", "");
		m_action8Button->setEnabled(false);
	}

	return true;
}

bool CGNSWindowHandler::playButtonClicked(const CEGUI::EventArgs &e)
{
	if( m_game.getCurrentMatch()==NULL ){
		m_game.setGameState(CSinglePlayerGame::SimulatingUntilTheNextEvent);
		CGameEngine::getInstance()->getTimeManager()->start();
	}
	else{
		if( m_game.getOptionManager()->getMatchResultMode() ){
			m_game.simulateMatch(*m_game.getCurrentMatch());
			m_game.setGameState(CSinglePlayerGame::PlayingMatch);
			CGameEngine::getInstance()->getTimeManager()->start();
		}else{
			CGameEngine::getInstance()->getWindowManager()->nextScreen("Simulator");
		}
	}
	return true;
}

bool CGNSWindowHandler::quickSaveButtonClicked(const CEGUI::EventArgs &e)
{
    try {
        CGameEngine::getInstance()->save();
        CGameEngine::getInstance()->getWindowManager()->alert(gettext("The game has been saved"));
    } catch(...) {
        CGameEngine::getInstance()->getWindowManager()->alert(gettext("ATTENTION: Game can not be saved"));
    }
	return true;
}
