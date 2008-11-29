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

#ifndef CSCREENRESULTS_H_
#define CSCREENRESULTS_H_

#include "../../engine/CScreen.h"

//Forward declarations
class CSinglePlayerGame;


class CScreenResults : public CScreen
{
public:
    CScreenResults(CSinglePlayerGame *game);
	virtual ~CScreenResults();

	virtual void enter();

private:
    bool competitionsComboboxListSelectionChanged(const CEGUI::EventArgs& e);
    bool competitionPhasesComboboxListSelectionChanged(const CEGUI::EventArgs& e);
    bool backButtonClicked(const CEGUI::EventArgs& e);

    void loadCompetitions();
    void loadCompetitionPhases();
    void loadResultsList();

    CEGUI::Combobox         *m_competitionsCombobox;
    CEGUI::Combobox         *m_competitionPhasesCombobox;
    CEGUI::MultiColumnList  *m_resultsList;
    CEGUI::PushButton		*m_backButton;

    CSinglePlayerGame		*m_game;
};

#endif /*CSCREENRESULTS_H_*/
