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

#include <sstream>
#include <stdlib.h>
#include <string.h>

#include "CSinglePlayerOptionManager.h"
#include "../../utils/CLog.h"

CSinglePlayerOptionManager::CSinglePlayerOptionManager(IPfGameOptionsDAO *gameOptionsDAO)
   : m_categoriesList()
{
    m_gameOptionsDAO = gameOptionsDAO;
    loadOptions();

    CLog::getInstance()->info("Game Option manager initialized");
}


CSinglePlayerOptionManager::~CSinglePlayerOptionManager()
{
    saveOptions();
    cleanOptions();

    CLog::getInstance()->info("Game Option manager deinitialized");
}


void CSinglePlayerOptionManager::loadOptions()
{
    cleanOptions();
    setDefaultValues();

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
            if( gameOption->getXOption_str()=="" ){
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
        }
    }

    CLog::getInstance()->info("Game Options saved");
}


void CSinglePlayerOptionManager::cleanOptions()
{
    std::map< const char *, std::map<const char *, const char *>* >::iterator itCategories;

    for( itCategories = m_categoriesList.begin(); itCategories != m_categoriesList.end(); itCategories++ ){
        const char                                      *category       = itCategories->first;
        std::map<const char *, const char *>            *optionsList    = itCategories->second;
        std::map<const char *, const char *>::iterator  itOptions;

        for( itOptions = optionsList->begin(); itOptions != optionsList->end(); itOptions++ ){
            const char *option = itOptions->first;
            const char *value  = itOptions->second;

            // Free memory
            delete []option;
            delete []value;
        }

        // Free memory
        delete []category;
        optionsList->clear();
        delete optionsList;
    }

    m_categoriesList.clear();
}


void CSinglePlayerOptionManager::setDefaultValues()
{
    // nothing at the moment
}


const char * CSinglePlayerOptionManager::getStringOption( const char *category, const char *option )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSinglePlayerOptionManager::getStringOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSinglePlayerOptionManager::getStringOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Return the option value
    return optionsList->operator[](o);
}


int CSinglePlayerOptionManager::getIntOption( const char *category, const char *option )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSinglePlayerOptionManager::getIntOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSinglePlayerOptionManager::getIntOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Return the option value
    return atoi(optionsList->operator[](o));
}


bool CSinglePlayerOptionManager::getBooleanOption( const char *category, const char *option )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSinglePlayerOptionManager::getBooleanOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSinglePlayerOptionManager::getBooleanOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Return the option value
    return strcmp( optionsList->operator[](o), "true" ) == 0;
}


void CSinglePlayerOptionManager::setStringOption( const char *category, const char *option, const char *value )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then create the category
        optionsList = createCategory( category );
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then create the option
        createOption( optionsList, option, value );
    }else{
        // Else delete old value
        delete [] optionsList->operator[](o);
        // and set the new value
        char *v = new char[strlen(value)+1];
        strcpy( v, value );
        optionsList->operator[](o) = v;
    }
}


void CSinglePlayerOptionManager::setIntOption( const char *category, const char *option, int value )
{
    char buffer[50];
    sprintf( buffer, "%d", value );

    setStringOption( category, option, buffer );
}


void CSinglePlayerOptionManager::setBooleanOption( const char *category, const char *option, bool value )
{
    if( value ){
      setStringOption( category, option, "true" );
    }else{
      setStringOption( category, option, "false" );
    }
}


std::map<const char *, const char *> * CSinglePlayerOptionManager::searchCategory( const char *category )
{
    bool found = false;
    std::map< const char *, std::map<const char *, const char *>* >::iterator it;

    const char *c;

    for( it = m_categoriesList.begin(); it != m_categoriesList.end() && !found; it++ ){

        c = it->first;
        if( strcmp( c, category ) == 0 ){
            found = true;
        }
    }

    if( found ){
        return m_categoriesList[c];
    }else{
        return NULL;
    }
}


const char * CSinglePlayerOptionManager::searchOption( std::map<const char *, const char *> *map, const char *option )
{
    bool found = false;
    std::map<const char *, const char *>::iterator it;

    const char *o;

    for( it = map->begin(); it != map->end() && !found; it++ ){

        o = it->first;
        if( strcmp( o, option ) == 0 ){
            found = true;
        }
    }

    if( found ){
        return o;
    }else{
        return NULL;
    }
}


std::map<const char *, const char *> * CSinglePlayerOptionManager::createCategory( const char *category )
{
    // First, create the new options list
    std::map<const char *, const char *> *optionsList = new std::map<const char *, const char *>();
    // Copy the category name
    char *c = new char[strlen(category)+1];
    strcpy( c, category );
    // Associate the options list with the category inside of the categories list
    m_categoriesList[c] = optionsList;

    // Finally, return the options list of the category
    return optionsList;
}


const char * CSinglePlayerOptionManager::createOption( std::map<const char *, const char *> *map, const char *option, const char *value )
{
    // First, copu the option and the value
    char *o = new char[strlen(option)+1];
    char *v = new char[strlen(value)+1];

    strcpy( o, option );
    strcpy( v ,value );

    // Insert the option in the options list
    map->operator[](o) = v;

    // return the option create
    return o;
}
