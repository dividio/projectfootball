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

class CScreenResults : public CScreen
{
public:
	static CScreenResults* getInstance();
	virtual ~CScreenResults();

	virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

private:
    CScreenResults();

    bool handleCompetitionChange(const CEGUI::EventArgs& e);
    bool handleCompetitionPhaseChange(const CEGUI::EventArgs& e);

    void loadCompetitions();
    void loadCompetitionPhases();
    void loadResultsList();

    CEGUI::Combobox         *m_competitionsCombo;
    CEGUI::Combobox         *m_competitionPhasesCombo;
    CEGUI::MultiColumnList  *m_resultsList;
};

#endif /*CSCREENRESULTS_H_*/
