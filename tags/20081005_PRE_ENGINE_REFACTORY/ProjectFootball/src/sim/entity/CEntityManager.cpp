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


#include "CEntityManager.h"
#include "../../utils/CLog.h"

CEntityManager* CEntityManager::getInstance()
{
    static CEntityManager instance;
    return &instance;
}


CEntityManager::CEntityManager()
{
    CLog::getInstance()->debug("CEntityManager()");
}


CEntityManager::~CEntityManager()
{
    CLog::getInstance()->debug("~CEntityManager()");
    reset();
}


void CEntityManager::addEntity(CBaseGameEntity *entity)
{
    m_entityMap.insert(std::make_pair(entity->getID(), entity));
}


void CEntityManager::removeEntity(CBaseGameEntity *entity)
{
    m_entityMap.erase(m_entityMap.find(entity->getID()));
}


CBaseGameEntity* CEntityManager::getEntityFromID(int id) const
{
    std::map<int, CBaseGameEntity*>::const_iterator it = m_entityMap.find(id);
    CBaseGameEntity *value;
    if(it != m_entityMap.end()) {
        value = it->second;
    } else {
        CLog::getInstance()->error("Invalid entity ID: %d", id);
    }

    return value;
}


void CEntityManager::reset()
{
    m_entityMap.clear();
}
