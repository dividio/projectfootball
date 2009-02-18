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

#ifndef CSCREENGAME_H_
#define CSCREENGAME_H_

#include "../../engine/CScreen.h"

//Forward declarations
class CSinglePlayerGame;


class CScreenGame : public CScreen
{
public:
    CScreenGame(CSinglePlayerGame *game);
    virtual ~CScreenGame();

    virtual void enter();

    void saveGame();

private:
	bool saveButtonClicked                  (const CEGUI::EventArgs& e);
	bool mainMenuButtonClicked              (const CEGUI::EventArgs& e);
	bool rankingButtonClicked               (const CEGUI::EventArgs& e);
	bool teamPlayersButtonClicked           (const CEGUI::EventArgs& e);
	bool resultsButtonClicked               (const CEGUI::EventArgs& e);
	bool playButtonClicked                  (const CEGUI::EventArgs& e);
	bool resultModeCheckboxCheckStateChanged(const CEGUI::EventArgs& e);
	bool saveConfirmButtonClicked           (const CEGUI::EventArgs& e);
	bool exitConfirmButtonClicked           (const CEGUI::EventArgs& e);
	bool exitCancelButtonClicked            (const CEGUI::EventArgs& e);


    CEGUI::Window       *m_competitionName;
    CEGUI::Window       *m_competitionCountryFlag;
    CEGUI::Window       *m_competitionPhaseName;
    CEGUI::Window       *m_nextCompetitionName;
    CEGUI::Window       *m_nextHomeTeamName;
    CEGUI::Window       *m_nextAwayTeamName;
    CEGUI::Window     	*m_homeTeamName;
    CEGUI::Window     	*m_awayTeamName;
    CEGUI::Window       *m_homeTeamAverage;
    CEGUI::Window       *m_awayTeamAverage;
    CEGUI::Window       *m_homeTeamShield;
    CEGUI::Window       *m_awayTeamShield;

    CEGUI::PushButton	*m_saveButton;
    CEGUI::PushButton	*m_mainMenuButton;
    CEGUI::PushButton	*m_rankingButton;
    CEGUI::PushButton	*m_teamPlayersButton;
    CEGUI::PushButton	*m_resultsButton;
    CEGUI::PushButton 	*m_playButton;
    CEGUI::PushButton   *m_saveConfirmButton;
    CEGUI::PushButton   *m_exitConfirmButton;
    CEGUI::PushButton   *m_exitCancelButton;
    CEGUI::Checkbox   	*m_resultModeCheckbox;
    CEGUI::Window       *m_mainWindow;
    CEGUI::FrameWindow  *m_confirmSaveWindow;
    CEGUI::Window       *m_confirmSaveNote;
    CEGUI::FrameWindow  *m_confirmExitWindow;
    CEGUI::Window       *m_confirmExitNote;


    CSinglePlayerGame	*m_game;
};

#endif /*CSCREENGAME_H_*/
