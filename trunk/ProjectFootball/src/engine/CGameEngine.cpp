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

#include "CGameEngine.h"
#include "option/CSystemOptionManager.h"
#include "utils/CClock.h"
#include "../utils/CLog.h"

#include "screen/CScreenIntro.h"
#include "screen/CScreenMainMenu.h"
#include "screen/CScreenLoadGame.h"
#include "screen/CScreenConfig.h"
#include "screen/CScreenCredits.h"

CGameEngine* CGameEngine::m_instance = NULL;

CGameEngine::CGameEngine() : m_screenStack()
{
    m_clock = new CClock();
    m_game	= NULL;

    const char *masterDatabasePath = CSystemOptionManager::getInstance()->getGeneralMasterDatebasePath();
    m_masterDatabase = new CMasterDAOFactorySQLite(masterDatabasePath);

    m_user = NULL;
    setUser(DEFAULT_USER);

    m_introScreen		= NULL;
    m_mainMenuScreen	= NULL;
    m_loadGameScreen	= NULL;
    m_configScreen		= NULL;
    m_creditsScreen		= NULL;
}

CGameEngine::~CGameEngine()
{
    if( m_game!=NULL ){
        unloadCurrentGame();
    }

    if( m_user!=NULL ){
        delete m_user;
    }

    delete m_introScreen;
    delete m_mainMenuScreen;
    delete m_loadGameScreen;
    delete m_configScreen;
    delete m_creditsScreen;

    m_masterDatabase->save();
    delete m_masterDatabase;
    delete m_clock;

    m_instance = NULL;
}

CGameEngine* CGameEngine::getInstance()
{
    if( m_instance==NULL ){
        m_instance = new CGameEngine();
    }

    return m_instance;
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
    nextScreen(m_game);
}

void CGameEngine::save()
{
    if( m_game!=NULL ){
        CPfGames *game = m_game->save();
        if( game->getXGame_str()=="" ){
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
        nextScreen(m_mainMenuScreen);

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
    if( m_screenStack.empty() ){
        CLog::getInstance()->info("-== Stopping Main Loop ==-");
        return false;
    }else{
        m_screenStack.back()->update();
        return true;
    }
}

IClock& CGameEngine::getClock()
{
    return *m_clock;
}

void CGameEngine::exit()
{
    while( !m_screenStack.empty() ){
        m_screenStack.back()->leave();
        m_screenStack.pop_back();
    }
    enterScreen();
}

void CGameEngine::previousScreen()
{
    CLog::getInstance()->debug("CGameEngine::previousScreen()");
    // cleanup the current state
    if(!m_screenStack.empty()) {
        m_screenStack.back()->leave();
        m_screenStack.pop_back();
        enterScreen();
    }
}

void CGameEngine::nextScreen(IScreen* screen)
{
    CLog::getInstance()->debug("CGameEngine::nextScreen()");
    bool found = false;
    for( int i=m_screenStack.size()-1; i>=0 && !found; i-- ){
        if( m_screenStack[i]==screen ){
            found = true;
        }
    }

    if( found ){
        while( !m_screenStack.empty() ){
            if( m_screenStack.back()!=screen ){
                m_screenStack.back()->leave();
                m_screenStack.pop_back();
            }else{
                m_screenStack.back()->enter();
                break;
            }
        }
    }else{
        m_screenStack.push_back(screen);
        m_screenStack.back()->enter();
    }
}

IScreen* CGameEngine::getIntroScreen()
{
    if( m_introScreen==NULL ){
        m_introScreen = new CScreenIntro();
    }
    return m_introScreen;
}

IScreen* CGameEngine::getMainMenuScreen()
{
    if( m_mainMenuScreen==NULL ){
        m_mainMenuScreen = new CScreenMainMenu();
    }
    return m_mainMenuScreen;
}

IScreen* CGameEngine::getLoadGameScreen()
{
    if( m_loadGameScreen==NULL ){
        m_loadGameScreen = new CScreenLoadGame();
    }
    return m_loadGameScreen;
}

IScreen* CGameEngine::getConfigScreen()
{
    if( m_configScreen==NULL ){
        m_configScreen = new CScreenConfig();
    }
    return m_configScreen;
}

IScreen* CGameEngine::getCreditsScreen()
{
    if( m_creditsScreen==NULL ){
        m_creditsScreen = new CScreenCredits();
    }
    return m_creditsScreen;
}

void CGameEngine::enterScreen()
{
    if(!m_screenStack.empty()) {
        m_screenStack.back()->enter();
    }
}
