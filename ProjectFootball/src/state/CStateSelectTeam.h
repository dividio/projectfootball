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

#ifndef CSTATESELECTTEAM_H_
#define CSTATESELECTTEAM_H_

#include "CState.h"
#include "../db/bean/CPfTeams.h"
#include "../db/bean/CPfConfederations.h"
#include "../db/bean/CPfCountries.h"
#include "../db/bean/CPfCompetitions.h"

class CStateSelectTeam : public CState
{
public:
    static CStateSelectTeam* getInstance();
  virtual ~CStateSelectTeam();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

    void selectTeam();

private:
    CStateSelectTeam();

    int  loadConfederationsList();
    int  loadCountriesList     (int XConfederation);
    int  loadCompetitionsList  (int XCountry);
    void loadTeamList          (int XCompetition);

    bool handleSelectChanged      (const CEGUI::EventArgs& e);
    bool handleConfederationChange(const CEGUI::EventArgs& e);
    bool handleCountryChange      (const CEGUI::EventArgs& e);
    bool handleCompetitionChange  (const CEGUI::EventArgs& e);
    bool handleDoubleClick        (const CEGUI::EventArgs& e);

    void loadTeamInfo(CPfTeams *team);
    void clearTeamInfo();

    CEGUI::PushButton                *m_selectButton;
    CEGUI::Listbox                   *m_guiTeamsList;
    CEGUI::Window                    *m_guiTeamName;
    CEGUI::Window                    *m_guiTeamBudget;
    CEGUI::Window                    *m_guiTeamLogo;
    CEGUI::Combobox                  *m_confederationsCombo;
    CEGUI::Combobox                  *m_countriesCombo;
    CEGUI::Combobox                  *m_competitionsCombo;

    std::vector<CPfConfederations*>  *m_confederationsList;
    std::vector<CPfCountries*>       *m_countriesList;
    std::vector<CPfCompetitions*>    *m_competitionsList;
    std::vector<CPfTeams*>           *m_teamsList;
};

#endif /*CSTATESELECTTEAM_H_*/
