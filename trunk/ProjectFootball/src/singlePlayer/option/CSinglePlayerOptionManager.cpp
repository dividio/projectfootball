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

#include "CSinglePlayerOptionManager.h"
#include "../../utils/CLog.h"

CSinglePlayerOptionManager::CSinglePlayerOptionManager(IPfGameOptionsDAO *gameOptionsDAO)
: m_gameOptionsDAO(gameOptionsDAO), COptionManager()
{
	cleanOptions();
	setDefaultValues();
	loadOptions();

    CLog::getInstance()->info("Game Option manager initialized");
}


CSinglePlayerOptionManager::~CSinglePlayerOptionManager()
{
	cleanOptions();

    CLog::getInstance()->info("Game Option manager deinitialized");
}


void CSinglePlayerOptionManager::loadOptions()
{
    std::vector<CPfGameOptions*>            *gameOptionsVector  = m_gameOptionsDAO->findAll();
    std::vector<CPfGameOptions*>::iterator  itGameOptions;

    for( itGameOptions=gameOptionsVector->begin(); itGameOptions!=gameOptionsVector->end(); itGameOptions++ ){
        CPfGameOptions *gameOption = (*itGameOptions);
        setStringOption(gameOption->getSCategory().c_str(), gameOption->getSAttribute().c_str(), gameOption->getSValue().c_str());
    }

    m_gameOptionsDAO->freeVector(gameOptionsVector);

    CLog::getInstance()->info("Game Options loaded");
}


void CSinglePlayerOptionManager::saveOptions()
{
    std::map<const char *, std::map<const char *, const char *>* >::iterator itCategories;

    for( itCategories=m_categoriesList.begin(); itCategories!=m_categoriesList.end(); itCategories++ ){
        const char *category = itCategories->first;
        std::map<const char *, const char *> *optionsList = itCategories->second;
        std::map<const char *, const char *>::iterator itOptions;

        for( itOptions = optionsList->begin(); itOptions != optionsList->end(); itOptions++ ){
            const char *option = itOptions->first;
            const char *value  = itOptions->second;

            CPfGameOptions *gameOption = m_gameOptionsDAO->findBySCategoryAndSAttribute(category, option);
            if( gameOption->getXOption()==0 ){
                // Don't exists this option
                gameOption->setSCategory(category);
                gameOption->setSAttribute(option);
                gameOption->setSValue(value);
                m_gameOptionsDAO->insertReg(gameOption);
            }else{
                // Exists this option
                gameOption->setSValue(value);
                m_gameOptionsDAO->updateReg(gameOption);
            }
            delete gameOption;
        }
    }

    CLog::getInstance()->info("Game Options saved");
}


void CSinglePlayerOptionManager::setDefaultValues()
{
    setMatchResultMode(false);
}


int	CSinglePlayerOptionManager::getGamePlayerTeam()
{
	return getIntOption("Game", "PlayerTeam");
}
void CSinglePlayerOptionManager::setGamePlayerTeam(int xPlayerTeam)
{
	setIntOption("Game", "PlayerTeam", xPlayerTeam);
}

bool CSinglePlayerOptionManager::getGameNew()
{
	return getBooleanOption("Game", "New");;
}
void CSinglePlayerOptionManager::setGameNew(bool newGame)
{
	setBooleanOption("Game", "New", newGame);
}

bool CSinglePlayerOptionManager::getMatchResultMode()
{
	return getBooleanOption("Match", "ResultMode");
}
void CSinglePlayerOptionManager::setMatchResultMode(bool mode)
{
	setBooleanOption("Match", "ResultMode", mode);
}
