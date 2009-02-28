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

#include "../../engine/CScreen.h"

//Forward declarations
class CPfTeams;
class CSinglePlayerGame;


class CScreenRanking : public CScreen
{
public:
    CScreenRanking(CSinglePlayerGame *game);
	virtual ~CScreenRanking();

    virtual void enter();

private:
    void loadRanking();
    bool backButtonClicked(const CEGUI::EventArgs& e);
    bool gameMenuButtonClicked(const CEGUI::EventArgs& e);
    bool rankingButtonClicked               (const CEGUI::EventArgs& e);
	  bool teamPlayersButtonClicked           (const CEGUI::EventArgs& e);
	  bool resultsButtonClicked               (const CEGUI::EventArgs& e);
    
    // TODO Ranking for all competitions
    bool isInSameCompetition(std::vector<CPfTeams*> *teams, std::string STeam);

    CEGUI::MultiColumnList  *m_rankingList;
    CEGUI::PushButton		*m_backButton;
    CEGUI::PushButton       *m_gameMenuButton;
    CEGUI::PushButton	*m_rankingButton;
    CEGUI::PushButton	*m_teamPlayersButton;
    CEGUI::PushButton	*m_resultsButton;

    CSinglePlayerGame		*m_game;
};

#endif /*CSCREENRANKING_H_*/
