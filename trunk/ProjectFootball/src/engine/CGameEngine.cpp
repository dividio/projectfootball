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

#include <time.h>
#include <stdlib.h>
#include <boost/filesystem.hpp>

#include "CGameEngine.h"
#include "option/CSystemOptionManager.h"
#include "utils/CClock.h"
#include "../utils/CLog.h"

#include "wh/CConfigWindowHandler.h"
#include "wh/CCreditsWindowHandler.h"
#include "wh/CIntroWindowHandler.h"
#include "wh/CLoadGameWindowHandler.h"
#include "wh/CMainMenuWindowHandler.h"
#include "wh/CNewManagerGameWindowHandler.h"
#include "wh/CNewVirtualGameWindowHandler.h"

#include "../singlePlayer/screen/CGNSWindowHandler.h"
#include "../singlePlayer/screen/CScreenSelectTeam.h"

CGameEngine* CGameEngine::m_instance = NULL;

CGameEngine::CGameEngine()// : m_screenStack()
: m_windowHandlers()
{
    m_clock = new CClock();
    m_game	= NULL;
    m_exit	= false;

    m_windowManager = new CWindowManager();

    const char *masterDatabasePath = CSystemOptionManager::getInstance()->getGeneralMasterDatebasePath();
    if( boost::filesystem::exists(masterDatabasePath) ){
    	m_masterDatabase = new CMasterDAOFactorySQLite(masterDatabasePath);
    }
    else{
    	m_masterDatabase = new CMasterDAOFactorySQLite(masterDatabasePath);
    	m_masterDatabase->executeScriptFile("data/database/scripts/master/tables.sql");
        m_masterDatabase->executeScriptFile("data/database/scripts/master/indexes.sql");
        m_masterDatabase->executeScriptFile("data/database/scripts/master/inserts_version.sql");
        m_masterDatabase->executeScriptFile("data/database/scripts/master/inserts_users.sql");
    }

    m_user = NULL;
    setUser(DEFAULT_USER);
}

CGameEngine::~CGameEngine()
{
    if( m_game!=NULL ){
        unloadCurrentGame();
    }

    if( m_user!=NULL ){
        delete m_user;
    }

    if( !m_windowHandlers.empty() ){
    	std::vector<IWindowHandler*>::iterator itWindowHandlers;
    	for( itWindowHandlers=m_windowHandlers.begin(); itWindowHandlers!=m_windowHandlers.end(); itWindowHandlers++ ){
    		delete (*itWindowHandlers);
    	}
    	m_windowHandlers.clear();
    }
    delete m_windowManager;

    m_masterDatabase->save();
    delete m_masterDatabase;
    delete m_clock;

    m_instance = NULL;
}

CGameEngine* CGameEngine::getInstance()
{
    if( m_instance==NULL ){
        m_instance = new CGameEngine();

        m_instance->m_windowHandlers.push_back(new CIntroWindowHandler());
        m_instance->m_windowHandlers.push_back(new CMainMenuWindowHandler());
        m_instance->m_windowHandlers.push_back(new CLoadGameWindowHandler());
        m_instance->m_windowHandlers.push_back(new CNewManagerGameWindowHandler());
        m_instance->m_windowHandlers.push_back(new CNewVirtualGameWindowHandler());
        m_instance->m_windowHandlers.push_back(new CConfigWindowHandler());
        m_instance->m_windowHandlers.push_back(new CCreditsWindowHandler());
    }

    return m_instance;
}

CWindowManager* CGameEngine::getWindowManager()
{
	return m_windowManager;
}

void CGameEngine::setUser(int xUser)
{
    if( m_user!=NULL ){
        delete m_user;
        m_user = NULL;
    }
    m_user = m_masterDatabase->getIPfUsersDAO()->findByXUser(xUser);
}

const CPfUsers* CGameEngine::getCurrentUser()
{
    return m_user;
}

IGame* CGameEngine::getCurrentGame()
{
    return m_game;
}

IMasterDAOFactory* CGameEngine::getCMasterDAOFactory()
{
    return m_masterDatabase;
}

void CGameEngine::loadGame(IGame *game)
{
    unloadCurrentGame();
    m_game = game;
    getWindowManager()->nextScreen(m_game->getFirstScreenName());
}

void CGameEngine::save()
{
    if( m_game!=NULL ){
        CPfGames *game = m_game->save();
        if( game->getXGame()==0 ){
            m_masterDatabase->getIPfGamesDAO()->insertReg(game);
        }else{
            m_masterDatabase->getIPfGamesDAO()->updateReg(game);
        }
        m_masterDatabase->save();
    }
}

void CGameEngine::unloadCurrentGame()
{
    if( m_game!=NULL ){
        m_windowManager->nextScreen("MainMenu");
        m_windowManager->clearHistory();

        delete m_game;
        m_game = NULL;
    }
}

bool CGameEngine::frameEnded(const Ogre::FrameEvent& evt)
{
    return true;
}


bool CGameEngine::frameStarted(const Ogre::FrameEvent& evt)
{
    ((CClock*)m_clock)->addTime(evt.timeSinceLastFrame);
    CEGUI::System::getSingleton().injectTimePulse( evt.timeSinceLastFrame );
    if( m_exit ){
        LOG_INFO("-== Stopping Main Loop ==-");
        return false;
    }else{
    	m_windowManager->update();
        return true;
    }
}

IClock& CGameEngine::getClock()
{
    return *m_clock;
}

void CGameEngine::exit()
{
	m_exit = true;
}
