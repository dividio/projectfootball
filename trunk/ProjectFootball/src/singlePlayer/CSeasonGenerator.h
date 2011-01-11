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

#ifndef CSEASONGENERATOR_H_
#define CSEASONGENERATOR_H_

#include "../utils/CDate.h"

#include <vector>

// Forward declarations
class CSinglePlayerGame;
class CPfCompetitionPhasesBySeason;
class CPfTeams;

class CSeasonGenerator {
public:
	virtual ~CSeasonGenerator();

	static void generateSeason(CSinglePlayerGame &game);

protected:
	CSeasonGenerator();

private:
	static void generateLeagueMatches(CSinglePlayerGame &game, const CPfCompetitionPhasesBySeason &competitionBySeason, const std::vector<CPfTeams*> *teamsList);

	static CDate getSameWeekDayOneYearLater(const CDate &date);
};

#endif /* CSEASONGENERATOR_H_ */
