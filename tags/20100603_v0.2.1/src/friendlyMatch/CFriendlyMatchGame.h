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

#ifndef CFRIENDLYMATCHGAME_H_
#define CFRIENDLYMATCHGAME_H_

#include "../engine/IGame.h"

// Forward declarations
class CPfGames;
class CPfUsers;
class CSinglePlayerGame;

class CFriendlyMatchGame : public IGame
{
public:
    CFriendlyMatchGame(const CPfUsers &user);
    virtual ~CFriendlyMatchGame();

    // IGame
    virtual CPfGames* save();
    virtual const char* getFirstScreenName();
//
//    // CScreen
//    virtual void enter();
//    virtual void leave();
//    virtual void update();

private:
    CSinglePlayerGame   *m_game;
};

#endif /*CFRIENDLYMATCHGAME_H_*/
