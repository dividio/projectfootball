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

#ifndef CGAMEENGINE_H_
#define CGAMEENGINE_H_

#define S_GAME_TYPE_SINGLEPLAYER	"SINGLE_PLAYER"
#define S_GAME_TYPE_FRIENDLYMATCH	"FRIENDLY_MATCH"

#include <string>
#include <vector>
#include <Ogre.h>

#include "event/CEventManager.h"

#include "time/CTimeManager.h"

#include "wm/CWindowManager.h"
#include "wm/IWindowHandler.h"

#include "IGame.h"
#include "db/sqlite/dao/factory/CMasterDAOFactorySQLite.h"

#include "utils/IClock.h"

class CGameEngine : public Ogre::FrameListener
{
public:
    virtual ~CGameEngine();
    static CGameEngine* getInstance();

    CEventManager*		getEventManager();
    CTimeManager*		getTimeManager();
    CWindowManager*		getWindowManager();

    IGame*        		getCurrentGame();
    IMasterDAOFactory* 	getCMasterDAOFactory();

    void setUser(int xUser);
    const CPfUsers* getCurrentUser();

    void exit();
    void loadGame(IGame* game);
    void save();
    void unloadCurrentGame();

    IClock& getClock();

    // Ogre
    virtual bool frameEnded(const Ogre::FrameEvent& evt);
    virtual bool frameStarted(const Ogre::FrameEvent& evt);

private:
    CGameEngine();

    static CGameEngine				*m_instance;
    bool							m_exit;

    IClock							*m_clock;
    CPfUsers                		*m_user;
    IGame              				*m_game;
    CMasterDAOFactorySQLite 		*m_masterDatabase;

    CEventManager					*m_eventManager;
    CTimeManager					*m_timeManager;
    CWindowManager					*m_windowManager;
    std::vector<IWindowHandler*>	m_windowHandlers;
};

#endif /*CGAMEENGINE_H_*/
