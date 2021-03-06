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

#define CONFIG_FILE		"./data/ProjectFootball.ini"
#define	LINE_LENGTH		256

#include <sstream>
#include <stdlib.h>
#include <string.h>

#include "CSystemOptionManager.h"
#include "../../utils/CLog.h"
#include "optionsUtil.h"

CSystemOptionManager::CSystemOptionManager()
   : m_categoriesList()
{
    loadOptions();

    CLog::getInstance()->info("System Option manager initialized");
}


CSystemOptionManager::~CSystemOptionManager()
{
    saveOptions();
    cleanOptions();

    CLog::getInstance()->info("System Option manager deinitialized");
}


CSystemOptionManager* CSystemOptionManager::getInstance()
{
  static CSystemOptionManager instance;
  return &instance;
}


void CSystemOptionManager::loadOptions()
{
    cleanOptions();
    setDefaultValues();

    // Open the config file
    FILE *file = fopen( CONFIG_FILE, "r" );
    if( file==NULL ){
      CLog::getInstance()->error("Config file not found: %s", CONFIG_FILE);
        return;
    }

    char category[LINE_LENGTH];
    char option[LINE_LENGTH];
    char value[LINE_LENGTH];

    // Default category
    strcpy(category, "Others");

    char line[LINE_LENGTH];
    char sentence[LINE_LENGTH];

    while( fgets( line, LINE_LENGTH, file ) ){

        getSentence( sentence, line );

        // If it's not a empty sentence
        if( strlen(sentence) > 0 ){
          // If it's a category
            if( sentence[0] == '[' ){
              // Copy the sentence without the '[',']'
                sentence[strlen(sentence)-1] = '\0';
                if( strlen(sentence) > 0 ){
                    strcpy( category, &(sentence[1]) );
                }else{
                  CLog::getInstance()->warning("Malformed category label '%s' into config file '%s'", sentence, CONFIG_FILE);
                }
            }else{
              // else, then it's a assignment
              getAssignment(option, value, sentence);
              setStringOption(category, option, value);
           }
        }
    }

    // Close the config file
    fclose( file );

    CLog::getInstance()->info("System Options loaded: --> \"%s\"", CONFIG_FILE);
}


void CSystemOptionManager::saveOptions()
{
    // To save the options, is iterate across categories and
    // options while it's written in the config file

    // Open the config file
    FILE *file = fopen( CONFIG_FILE, "w" );
    if( file == NULL ){
      CLog::getInstance()->exception("Error at open the config file: %s", CONFIG_FILE);
    }

    fprintf( file, "# Autogenerated config file by ProjectFootball. Modify at your risk.\n\n\n" );


    std::map< const char *, std::map<const char *, const char *>* >::iterator itCategories;

    for( itCategories = m_categoriesList.begin(); itCategories != m_categoriesList.end(); itCategories++ ){

        const char *category = itCategories->first;
        std::map<const char *, const char *> *optionsList = itCategories->second;
        fprintf( file, "[%s]\n", category );

        std::map<const char *, const char *>::iterator itOptions;
        for( itOptions = optionsList->begin(); itOptions != optionsList->end(); itOptions++ ){

            const char *option = itOptions->first;
            const char *value  = itOptions->second;

            fprintf( file, "  %s = %s\n", option, value );
        }

        fprintf( file, "\n" );
    }

    // Close config file
    fclose( file );

    CLog::getInstance()->info("System Options saved: --> \"%s\"", CONFIG_FILE);
}


// General options
const char * CSystemOptionManager::getGeneralMasterDatebasePath()
{
    return getStringOption("General", "MasterDatabasePath");
}
void CSystemOptionManager::setGeneralMasterDatebasePath(const char * masterDatabasePath)
{
    setStringOption("General", "MasterDatabasePath", masterDatabasePath);
}

bool CSystemOptionManager::getGeneralFailSafeMode()
{
    return getBooleanOption("General", "FailSafeMode");
}
void CSystemOptionManager::setGeneralFailSafeMode(bool failSafeMode)
{
    setBooleanOption("General", "FailSafeMode", failSafeMode);
}

// GUI options
int CSystemOptionManager::getGUIMouseVelocity()
{
    return getIntOption("GUI", "MouseVelocity");
}
void CSystemOptionManager::setGUIMouseVelocity(int mouseVelocity)
{
    setIntOption("GUI", "MouseVelocity", mouseVelocity);
}

const char * CSystemOptionManager::getGUISkin()
{
    return getStringOption("GUI", "Skin");
}
void CSystemOptionManager::setGUISkin(const char * skin)
{
    setStringOption("GUI", "Skin", skin);
}

const char * CSystemOptionManager::getGUIXMLParser()
{
    return getStringOption("GUI", "XMLParser");
}
void CSystemOptionManager::setGUIXMLParser(const char * parser)
{
    setStringOption("GUI", "XMLParser", parser);
}

// Video options
const char * CSystemOptionManager::getVideoRenderSystem()
{
    return getStringOption("Video", "RenderSystem");
}
void CSystemOptionManager::setVideoRenderSystem(const char * renderSystem)
{
    setStringOption("Video", "RenderSystem", renderSystem);
}

int CSystemOptionManager::getVideoWidth()
{
    return getIntOption("Video", "Width");
}
void CSystemOptionManager::setVideoWidth(int width)
{
    setIntOption("Video", "Width", width);
}

int CSystemOptionManager::getVideoHeight()
{
    return getIntOption("Video", "Height");
}
void CSystemOptionManager::setVideoHeight(int height)
{
    setIntOption("Video", "Height", height);
}

bool CSystemOptionManager::getVideoFullscreen()
{
    return getBooleanOption("Video", "Fullscreen");
}
void CSystemOptionManager::setVideoFullscreen(bool fullscreen)
{
    setBooleanOption("Video", "Fullscreen", fullscreen);
}

bool CSystemOptionManager::getVideoVSync()
{
    return getBooleanOption("Video", "VSync");
}
void CSystemOptionManager::setVideoVSync(bool vSync)
{
    setBooleanOption("Video", "VSync", vSync);
}

const char * CSystemOptionManager::getVideoRTTPreferredMode()
{
    return getStringOption("Video", "RTTPreferredMode");
}
void CSystemOptionManager::setVideoRTTPreferredMode(const char* rttPreferredMode)
{
    setStringOption("Video", "RTTPreferredMode", rttPreferredMode);
}

// Simulation options
int CSystemOptionManager::getSimulationMatchDuration()
{
    return getIntOption("Simulation", "MatchDuration");
}
void CSystemOptionManager::setSimulationMatchDuration(int matchDuration)
{
    setIntOption("Simulation", "MatchDuration", matchDuration);
}

int CSystemOptionManager::getSimulationLogicFrequency()
{
    return getIntOption("Simulation", "LogicFrequency");
}
void CSystemOptionManager::setSimulationLogicFrequency(int logicFrequency)
{
    setIntOption("Simulation", "LogicFrequency", logicFrequency);
}

int CSystemOptionManager::getSimulationPhysicsFrequency()
{
    return getIntOption("Simulation", "PhysicsFrequency");
}
void CSystemOptionManager::setSimulationPhysicsFrequency(int physicsFrequency)
{
    setIntOption("Simulation", "PhysicsFrequency", physicsFrequency);
}

int CSystemOptionManager::getSimulationMaxBallVelocity()
{
    return getIntOption("Simulation", "MaxBallVelocity");
}
void CSystemOptionManager::setSimulationMaxBallVelocity(int maxBallVelocity)
{
    setIntOption("Simulation", "MaxBallVelocity", maxBallVelocity);
}

int CSystemOptionManager::getSimulationMaxKickPower()
{
    return getIntOption("Simulation", "MaxKickPower");
}
void CSystemOptionManager::setSimulationMaxKickPower(int maxKickPower)
{
    setIntOption("Simulation", "MaxKickPower", maxKickPower);
}


void CSystemOptionManager::cleanOptions()
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


void CSystemOptionManager::setDefaultValues()
{
    setGeneralMasterDatebasePath("data/database/master.sql3");
    setGeneralFailSafeMode(false);

    setGUIMouseVelocity(150);
    setGUISkin("DefaultSkin");
    setGUIXMLParser("TinyXMLParser");

    setVideoRenderSystem("OpenGL Rendering Subsystem");
    setVideoWidth(1024);
    setVideoHeight(768);
    setVideoFullscreen(true);
    setVideoVSync(true);
    setVideoRTTPreferredMode("Copy");

    setSimulationMatchDuration(2000);
    setSimulationLogicFrequency(30);
    setSimulationPhysicsFrequency(60);
    setSimulationMaxBallVelocity(25);
    setSimulationMaxKickPower(25);
}


const char * CSystemOptionManager::getStringOption( const char *category, const char *option )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSystemOptionManager::getStringOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSystemOptionManager::getStringOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Return the option value
    return optionsList->operator[](o);
}


int CSystemOptionManager::getIntOption( const char *category, const char *option )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSystemOptionManager::getIntOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSystemOptionManager::getIntOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Return the option value
    return atoi(optionsList->operator[](o));
}


bool CSystemOptionManager::getBooleanOption( const char *category, const char *option )
{
    // First, search the category
    std::map<const char *, const char *> *optionsList = searchCategory( category );
    if( optionsList == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSystemOptionManager::getBooleanOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Now, search the option
    const char *o = searchOption( optionsList, option );
    if( o == NULL ){
        // If not found then throw exception
        CLog::getInstance()->exception("[CSystemOptionManager::getBooleanOption] Option not found: Category: '%s', Option: '%s'", category, option);
    }

    // Return the option value
    return strcmp( optionsList->operator[](o), "true" ) == 0;
}


void CSystemOptionManager::setStringOption( const char *category, const char *option, const char *value )
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


void CSystemOptionManager::setIntOption( const char *category, const char *option, int value )
{
    char buffer[50];
    sprintf( buffer, "%d", value );

    setStringOption( category, option, buffer );
}


void CSystemOptionManager::setBooleanOption( const char *category, const char *option, bool value )
{
    if( value ){
        setStringOption( category, option, "true" );
    }else{
        setStringOption( category, option, "false" );
    }
}


std::map<const char *, const char *> * CSystemOptionManager::searchCategory( const char *category )
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


const char * CSystemOptionManager::searchOption( std::map<const char *, const char *> *map, const char *option )
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


std::map<const char *, const char *> * CSystemOptionManager::createCategory( const char *category )
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


const char * CSystemOptionManager::createOption( std::map<const char *, const char *> *map, const char *option, const char *value )
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
