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

#ifndef CSCREENSELECTTEAM_H_
#define CSCREENSELECTTEAM_H_

#include "../../engine/CScreen.h"


//Forward declarations
class CSinglePlayerGame;
class CPfTeams;
class CPfConfederations;
class CPfCountries;
class CPfCompetitions;


class CScreenSelectTeam : public CScreen
{
public:
    CScreenSelectTeam(CSinglePlayerGame *game);
    virtual ~CScreenSelectTeam();

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

    int  loadConfederationsList();
    int  loadCountriesList     (int XConfederation);
    int  loadCompetitionsList  (int XCountry);
    void loadTeamList          (int XCompetition);

    void loadTeamInfo(CPfTeams *team);
    void clearTeamInfo();

    CEGUI::PushButton				*m_backButton;
    CEGUI::PushButton               *m_selectButton;
    CEGUI::Listbox                  *m_guiTeamsList;
    CEGUI::Window                   *m_guiTeamName;
    CEGUI::Window                   *m_guiTeamBudget;
    CEGUI::Window                   *m_guiTeamAverage;
    CEGUI::Window                   *m_guiTeamShield;
    CEGUI::Window                   *m_guiConfederationImage;
    CEGUI::Window                   *m_guiCountryImage;
    CEGUI::Combobox                 *m_confederationsCombobox;
    CEGUI::Combobox                 *m_countriesCombobox;
    CEGUI::Combobox                 *m_competitionsCombobox;

    std::vector<CPfConfederations*> *m_confederationsList;
    std::vector<CPfCountries*>      *m_countriesList;
    std::vector<CPfCompetitions*>   *m_competitionsList;
    std::vector<CPfTeams*>			*m_teamsList;

    CSinglePlayerGame				*m_game;
};

#endif /*CSCREENSELECTTEAM_H_*/
