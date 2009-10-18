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

#ifndef CMATCHINFOWINDOWHANDLER_H_
#define CMATCHINFOWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>
#include "../../engine/wm/CWindowHandler.h"

// forward declarations
class CSinglePlayerGame;

class CMatchInfoWindowHandler: public CWindowHandler {
public:
	CMatchInfoWindowHandler(CSinglePlayerGame &game);
	virtual ~CMatchInfoWindowHandler();

	virtual void enter();
	virtual void init();

	void updateMatchInfo();

private:
	CEGUI::Window		*m_informationBanner;
    CEGUI::Window       *m_competitionCountryFlag;
    CEGUI::Window     	*m_homeTeamName;
    CEGUI::Window     	*m_awayTeamName;
    CEGUI::Window       *m_homeTeamAverage;
    CEGUI::Window       *m_awayTeamAverage;
    CEGUI::Window       *m_homeTeamBadge;
    CEGUI::Window       *m_awayTeamBadge;
    CEGUI::Window       *m_homeTeamCoach;
    CEGUI::Window       *m_awayTeamCoach;

	CSinglePlayerGame	&m_game;
};

#endif /* CMATCHINFOWINDOWHANDLER_H_ */
