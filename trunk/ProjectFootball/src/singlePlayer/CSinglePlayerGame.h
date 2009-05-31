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

#ifndef CSINGLEPLAYERGAME_H_
#define CSINGLEPLAYERGAME_H_

#include <string>
#include <vector>

#include "../engine/IGame.h"

//Forward declarations
class CPfGames;
class CPfUsers;
class CPfMatches;
class IDAOFactory;
class CSinglePlayerOptionManager;
class CSinglePlayerReportRegister;
class IGameEvent;
class CEventsQueue;
class CEventConsumer;
class IWindowHandler;

class CSinglePlayerGame : public IGame
{
public:
    virtual ~CSinglePlayerGame();

    IDAOFactory*           			getIDAOFactory();
    CSinglePlayerReportRegister*	getReportRegister();
    CSinglePlayerOptionManager*    	getOptionManager();
    CEventsQueue*					getEventsQueue();
    CEventConsumer*					getEventConsumer();

    // IGame
    static IGame* newGame(const CPfUsers &user, const std::string &gameName);
    static IGame* load(const CPfGames &game);
    virtual CPfGames* save();
    virtual const char* getFirstScreenName();

    // Game progression
    const CPfMatches* 	getCurrentMatch();
    void				setCurrentMatch(const CPfMatches* match);

protected:
	CSinglePlayerGame(const CPfGames &game);

private:
    void loadGameEvents();

protected:
    CPfGames						*m_game;
    IDAOFactory						*m_daoFactory;
    CEventsQueue					*m_eventsQueue;
    CEventConsumer					*m_eventConsumer;
    CSinglePlayerReportRegister		*m_reportRegister;
    CSinglePlayerOptionManager		*m_optionManager;

    std::vector<IWindowHandler*>	m_windowHandlers;
    IWindowHandler					*m_matchInfoWindowHandler;

    const CPfMatches				*m_currentMatch;
};

#endif /*CSINGLEPLAYERGAME_H_*/
