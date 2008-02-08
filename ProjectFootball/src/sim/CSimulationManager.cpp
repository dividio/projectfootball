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
#include "message/CMessageDispatcher.h"
#include "message/MessageTypes.h"
#include "entity/CField.h"
#include "../utils/CLog.h"
#include "../audio/CAudioSystem.h"

CSimulationManager::CSimulationManager()
{
    CLog::getInstance()->debug("CSimulationManager()");
    m_timer = 1;
    m_homeTeamName = "Luí TM";
    m_awayTeamName = "Aceitunas Pacheco";
    m_simWorld = new CSimulationWorld();

//    for(int i = 0; i < 11; i++) {
//        char auxhome[20];
//        char auxaway[20];
//        sprintf(auxhome,"h%d",i);
//        sprintf(auxaway,"a%d",i);
//        CFootballPlayer *player = new CFootballPlayer(auxhome, scnMgr, i*2, 50, i);
//        m_homePlayers.push_back(player);
//        m_simWorld->addObject((CObject*)player);
//
//        player = new CFootballPlayer(auxaway, scnMgr, -i*2, 0, i);
//        m_awayPlayers.push_back(player);
//        m_simWorld->addObject((CObject*)player);
//    }


    CField *field = new CField();
    m_simWorld->addObject(field);

    m_referee = new CReferee();
    m_simWorld->addObject(m_referee);

    m_ball = new CBall();
    m_simWorld->addObject(m_ball);

    CFootballPlayer *player = new CFootballPlayer(1, m_homeTeamName, -54, 0, 0, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(2, m_homeTeamName, -30, 0, 25, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(3, m_homeTeamName, -30, 0, -25, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(4, m_homeTeamName, -35, 0, 5, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(5, m_homeTeamName, -35, 0, -5, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(6, m_homeTeamName, -20, 0, 0, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(7, m_homeTeamName, -20, 0, 20, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(8, m_homeTeamName, -20, 0, -20, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(9, m_homeTeamName, -10, 0, 0, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(10, m_homeTeamName, -5, 0, 20, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(11, m_homeTeamName, -5, 0, -20, true);
    m_homePlayers.push_back(player);
    m_simWorld->addObject(player);


    player = new CFootballPlayer(1, m_awayTeamName, -54, 0, 0, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(2, m_awayTeamName, -45, 0, 10, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(3, m_awayTeamName, -45, 0, -10, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(4, m_awayTeamName, -40, 0, 20, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(5, m_awayTeamName, -40, 0, -20, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(6, m_awayTeamName, -17, 0, 21, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(7, m_awayTeamName, -17, 0, -21, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(8, m_awayTeamName, -15, 0, 0, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(9, m_awayTeamName, -20, 0, -5, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(10, m_awayTeamName, -5, 0, -20, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    player = new CFootballPlayer(11, m_awayTeamName, -5, 0, 20, false);
    m_awayPlayers.push_back(player);
    m_simWorld->addObject(player);

    setNearestPlayersToBall();

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
    if(m_timer == 1) {
        std::vector<CFootballPlayer*>::iterator it;
        m_referee->update();
        for(it = m_homePlayers.begin(); it!=m_homePlayers.end(); it++) {
            (*it)->update();
        }
        for(it = m_awayPlayers.begin(); it!=m_awayPlayers.end(); it++) {
            (*it)->update();
        }
    } if(m_timer == 3) {
        m_timer = 0;
    }
    m_simWorld->update();
    setNearestPlayersToBall();
    m_timer++;
}


CSimulationWorld* CSimulationManager::getSimulationWorld()
{
    return m_simWorld;
}


CReferee* CSimulationManager::getReferee()
{
    return m_referee;
}


CBall* CSimulationManager::getBall()
{
    return m_ball;
}


void CSimulationManager::changePlayersSide()
{
    std::vector<CFootballPlayer*>::iterator it;
    for(it = m_homePlayers.begin(); it!=m_homePlayers.end(); it++) {
        (*it)->changeSide();
    }

    for(it = m_awayPlayers.begin(); it!=m_awayPlayers.end(); it++) {
        (*it)->changeSide();
    }

}


void CSimulationManager::startMatch()
{
    CMessageDispatcher::getInstance()->dispatchMsg(0, -1, m_referee->getID(), Msg_StartMatch, 0);
}


std::string* CSimulationManager::getHomeTeamName()
{
    return &m_homeTeamName;
}


std::string* CSimulationManager::getAwayTeamName()
{
    return &m_awayTeamName;
}


btVector3 CSimulationManager::getBallPosition() const
{
    return m_ball->getPosition();
}


void CSimulationManager::setNearestPlayersToBall()
{
    btScalar minDist = 1000, teamDist = 1000;
    btScalar auxDist;
    btVector3 playerPos;
    btVector3 ballPos = m_ball->getPosition();
    std::vector<CFootballPlayer*>::iterator it;
    for(it = m_homePlayers.begin(); it!=m_homePlayers.end(); it++) {
        playerPos = (*it)->getPosition();
        auxDist = playerPos.distance(ballPos);
        if(auxDist < minDist) {
            minDist = auxDist;
            m_nearestPlayer = (*it);
        }
        if(auxDist < teamDist) {
            teamDist = auxDist;
            m_homeNearestPlayer = (*it);
        }
    }

    teamDist = 1000;
    for(it = m_awayPlayers.begin(); it!=m_awayPlayers.end(); it++) {
        playerPos = (*it)->getPosition();
        auxDist = playerPos.distance(ballPos);
        if(auxDist < minDist) {
            minDist = auxDist;
            m_nearestPlayer = (*it);
        }
        if(auxDist < teamDist) {
            teamDist = auxDist;
            m_awayNearestPlayer = (*it);
        }
    }
}


bool CSimulationManager::isNearestPlayerToBall(CFootballPlayer* player) const
{
    std::string id = player->getIdent();
    return (m_nearestPlayer->getIdent() == id);
}


bool CSimulationManager::isNearestTeamMatePlayerToBall(CFootballPlayer* player) const
{
    std::string id = player->getIdent();
    std::string team = player->getTeamName();
    if(team == m_homeTeamName && m_homeNearestPlayer != NULL) {
        return (id == m_homeNearestPlayer->getIdent());
    } else if(team == m_awayTeamName && m_awayNearestPlayer != NULL) {
        return (id == m_awayNearestPlayer->getIdent());
    } else {
        CLog::getInstance()->error("Team name \"%s\" unknown in player \"%s\"", team.c_str(), id.c_str());
    }
    return false;
}


void CSimulationManager::dash(CFootballPlayer *player, int power)
{
    btVector3 impulse;
    int maxDash = 100;
    btRigidBody *body = player->getBody();
    if(player->canDoActions() && body->getLinearVelocity().length() < 10) {
        if(power > maxDash) {
            impulse = maxDash * player->getDirection();
        } else {
            impulse = power * player->getDirection();
        }
        body->applyCentralImpulse(impulse);
        //printf("x:%f y:%f z:%f\n", impulse.x(), impulse.y(), impulse.z());

        //body->applyCentralImpulse(btVector3(70,0,0));
    }
}


void CSimulationManager::move(CFootballPlayer *player, int x, int z)
{
    if(m_referee->isMoveLegal()) {
        btRigidBody *body = player->getBody();
        body->clearForces();
        body->setLinearVelocity(btVector3(0,0,0));
        body->setAngularVelocity(btVector3(0,0,0));
        player->setPosition(x,0,z);
    }
}


void CSimulationManager::kick(CFootballPlayer *player, int power, btVector3 direction)
{
    btRigidBody *ballBody = m_ball->getBody();
    btVector3 dir = (direction.normalize() * power) / 10.0;
    ballBody->applyImpulse(dir ,btVector3(0,0,0));
    m_referee->playerKickEvent(player);
    CAudioSystem::LOW_KICK->play();
    //printf("  ----->           LOW_KICK\n");
}


void CSimulationManager::turn(CFootballPlayer *player, int moment)
{
    if(player->canDoActions()) {
        btRigidBody *body = player->getBody();
        body->setAngularVelocity(btVector3(0,moment,0));
    }
}
