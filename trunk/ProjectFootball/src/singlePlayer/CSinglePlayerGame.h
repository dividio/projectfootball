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
class IDAOFactory;
class CSinglePlayerOptionManager;
class CSinglePlayerReportRegister;
class CSinglePlayerEventStrategy;


class CSinglePlayerGame : public IGame
{
public:
    CSinglePlayerGame(const CPfUsers *user, const char *gameName);
    CSinglePlayerGame(const CPfGames *game);
    virtual ~CSinglePlayerGame();

    IDAOFactory*           			getIDAOFactory();
    CSinglePlayerEventStrategy*  	getEventStrategy();
    CSinglePlayerReportRegister*	getReportRegister();
    CSinglePlayerOptionManager*    	getOptionManager();

    // IScreen
    virtual void enter();
    virtual void leave();
    virtual void update();

    // IGame
    virtual CPfGames* save();

    virtual void exit();
    virtual void previousScreen();
    virtual void nextScreen(IScreen* screen);

    IScreen* getGameScreen();
    IScreen* getMatchResultScreen();
    IScreen* getRankingScreen();
    IScreen* getResultsScreen();
    IScreen* getSelectTeamScreen();
    IScreen* getSimulatorScreen();
    IScreen* getTeamPlayersScreen();

private:
    void setGameOptionsDefaultValues();
    void createSinglePlayerScreens();

protected:
    CPfGames                    *m_game;
    IDAOFactory					*m_daoFactory;
    CSinglePlayerEventStrategy  *m_eventStrategy;
    CSinglePlayerReportRegister *m_reportRegister;
    CSinglePlayerOptionManager  *m_optionManager;

    std::vector<IScreen*> 	 	m_screenStack;

    IScreen						*m_gameScreen;
    IScreen						*m_matchResultScreen;
    IScreen						*m_rankingScreen;
    IScreen						*m_resultsScreen;
    IScreen						*m_selectTeamScreen;
    IScreen						*m_simulatorScreen;
    IScreen						*m_teamPlayersScreen;
};

#endif /*CSINGLEPLAYERGAME_H_*/
