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


#ifndef __CFootballPlayer_H__
#define __CFootballPlayer_H__


#include <Ogre.h>
#include <string>

#include "CObject.h"


class CFootballPlayer: public CObject
{
public:
    CFootballPlayer(int number, std::string teamName, Ogre::SceneManager *scnMgr, int x, int y, int z, bool sideLeft);
    ~CFootballPlayer();

    void update();
    bool canDoActions();
    btVector3 getDirection() const;
    std::string getIdent() const;
    std::string getTeamName() const;
    bool isTeamLeft() const;
    void changeSide();


    //Low-Level Skills
    void turnBodyToPoint(btVector3 pos, int cycles = 1);

    //Intermediate Level Skills
    void turnBodyToObject(CObject o);
    void moveToPos(btVector3 pos, int angle);


private:
    bool m_canDoActions;
    int m_strategicX;
    int m_strategicZ;
    bool m_sideLeft;
    std::string m_teamName;
    int m_number;
    std::string m_ident;
    btVector3 m_direction;
    btQuaternion m_rotation;

};

#endif // __CFootballPlayer_H__
