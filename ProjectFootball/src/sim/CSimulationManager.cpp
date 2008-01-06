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

#include <stdlib.h>

#include "CSimulationManager.h"
#include "utils/CLog.h"

CSimulationManager::CSimulationManager(Ogre::SceneManager *scnMgr)
{
    CLog::getInstance()->debug("CSimulationManager()");
    m_homeScore = 0;
    m_awayScore = 0;
    m_isPlayOn = false;
    m_isBeforeStart = true;
    m_homeTeamName = "Luí TM";
    m_awayTeamName = "Aceitunas Pacheco";

    m_simWorld = new CSimulationWorld();
    for(int i = 0; i < 11; i++) {
        char auxhome[20];
        char auxaway[20];
        sprintf(auxhome,"h%d",i);
        sprintf(auxaway,"a%d",i);
        CFootballPlayer *player = new CFootballPlayer(auxhome, scnMgr, i*2, 50, i);
        m_homePlayers.push_back(player);
        m_simWorld->addObject((CObject*)player);

        player = new CFootballPlayer(auxaway, scnMgr, -i*2, 0, i);
        m_awayPlayers.push_back(player);
        m_simWorld->addObject((CObject*)player);
    }
}

CSimulationManager::~CSimulationManager()
{
    CLog::getInstance()->debug("~CSimulationManager()");

    if(m_simWorld != NULL) {
        delete m_simWorld;
    }

    //TODO
//    for(int i = 0; i < 11; i++) {
//        CFootballPlayer *aux = m_homePlayers[i];
//        //m_homePlayers.pop_back();
//        delete aux;
//        aux = m_awayPlayers[i];
//        //m_awayPlayers.pop_back();
//        delete aux;
//    }
}

void CSimulationManager::update()
{
    for(int i = 0; i < 11; i++) {
        m_homePlayers[i]->update();
        m_awayPlayers[i]->update();
    }
    if(isPlayOn()) {
        m_simWorld->update();
    }
}


bool CSimulationManager::isPlayOn()
{
    return m_isPlayOn;
}


bool CSimulationManager::isBeforeStart()
{
    return m_isBeforeStart;
}


void CSimulationManager::startMatch()
{
    m_isPlayOn = true;
    m_isBeforeStart = false;
}

void CSimulationManager::dash(CFootballPlayer *player, int power)
{
    int maxDash = 100;
    if(power > maxDash) {

    } else {

    }
}
