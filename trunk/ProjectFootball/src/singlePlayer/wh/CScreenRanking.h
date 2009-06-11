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

#ifndef CSCREENRANKING_H_
#define CSCREENRANKING_H_

#include <CEGUI/CEGUI.h>
#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CPfTeams;
class CPfSeasons;
class CSinglePlayerGame;


class CScreenRanking : public CWindowHandler
{
public:
    CScreenRanking(CSinglePlayerGame &game);
	virtual ~CScreenRanking();

    virtual void enter();
    virtual void init();
    virtual void leave();

private:

    bool confederationsComboboxListSelectionChanged (const CEGUI::EventArgs& e);
    bool countriesComboboxListSelectionChanged      (const CEGUI::EventArgs& e);
    bool competitionsComboboxListSelectionChanged   (const CEGUI::EventArgs& e);

	void loadRanking        (int XSeason, int XCompetition);
    void loadConfederations (int XSeason, int XConfederation = -1);
    void loadCountries      (int XSeason, int XConfederation, int XCountry = -1);
    void loadCompetitions   (int XSeason, int XCountry, int XCompetition = -1);
    void loadLastSeason     ();

    CEGUI::Combobox         *m_confederationsCombobox;
    CEGUI::Combobox         *m_countriesCombobox;
    CEGUI::Combobox         *m_competitionsCombobox;
    CEGUI::MultiColumnList  *m_rankingList;

    CPfSeasons              *m_lastSeason;
    CSinglePlayerGame		&m_game;
};

#endif /*CSCREENRANKING_H_*/
