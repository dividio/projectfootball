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

#ifndef CSELECTTEAMWINDOWHANDLER_H_
#define CSELECTTEAMWINDOWHANDLER_H_

#include "../../engine/wm/CWindowHandler.h"

#include <CEGUI/CEGUI.h>

//Forward declarations
class CSinglePlayerGame;
class CPfConfederations;
class CPfCountries;
class CPfCompetitions;
class CPfSeasons;
class CPfTeams;
class CPfTeamPlayers;


class CSelectTeamWindowHandler : public CWindowHandler
{
public:
    CSelectTeamWindowHandler(CSinglePlayerGame &game);
    virtual ~CSelectTeamWindowHandler();

    virtual void init();
    virtual void enter();
    virtual void leave();

private:
    bool confederationsComboboxListSelectionChanged(const CEGUI::EventArgs& e);
    bool countriesComboboxListSelectionChanged(const CEGUI::EventArgs& e);
    bool competitionsComboboxListSelectionChanged  (const CEGUI::EventArgs& e);
    bool teamsListboxSelectionChanged(const CEGUI::EventArgs& e);
    bool teamsListboxMouseDoubleClick(const CEGUI::EventArgs& e);
    bool selectButtonClicked(const CEGUI::EventArgs& e);
    bool backButtonClicked(const CEGUI::EventArgs& e);

    void loadLastSeason();
    int  loadConfederationsList();
    int  loadCountriesList     (int XConfederation);
    int  loadCompetitionsList  (int XCountry);
    void loadTeamList          (int XCompetition);

    void loadTeamInfo          (CPfTeams *team);
    void loadTeamPlayersList   (CPfTeams *team);
    void addPlayerToList       (CPfTeamPlayers *player);
    void clearTeamInfo         ();

    CEGUI::PushButton				*m_backButton;
    CEGUI::PushButton               *m_selectButton;
    CEGUI::ItemListbox              *m_guiTeamsList;
    CEGUI::Window                   *m_guiTeamName;
    CEGUI::Window                   *m_guiStadiumName;
    CEGUI::Window                   *m_guiStadiumCapacity;
    CEGUI::Window                   *m_guiTeamBudget;
    CEGUI::Window                   *m_guiTeamAverage;
    CEGUI::Window                   *m_guiTeamBadge;
    CEGUI::Window                   *m_guiConfederationImage;
    CEGUI::Window                   *m_guiCountryImage;
    CEGUI::Combobox                 *m_confederationsCombobox;
    CEGUI::Combobox                 *m_countriesCombobox;
    CEGUI::Combobox                 *m_competitionsCombobox;
    CEGUI::MultiColumnList          *m_teamPlayersList;

    std::vector<CPfConfederations*> *m_confederationsList;
    std::vector<CPfCountries*>      *m_countriesList;
    std::vector<CPfCompetitions*>   *m_competitionsList;
    std::vector<CPfTeams*>			*m_teamsList;
    CPfSeasons						*m_lastSeason;

    CSinglePlayerGame				&m_game;
    bool                            m_initiated;
};

#endif /*CSELECTTEAMWINDOWHANDLER_H_*/
