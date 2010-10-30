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
#include "../../exceptions/PFException.h"
#include "../../utils/CLog.h"


char * trim( char *s )
{
    int i = 0, j = 0;
	char *end = s;
	char c;

    // From the beggining of the string iterate forward to
    // the first character that not validate isspace(). The
    // rest of the string is copied to the beginning except
	// the last whitespaces.
    while( s[i]!='\0' && isspace(s[i]) ){
    	i++;
    }
    while( s[i]!='\0' ){
    	c = s[j++] = s[i++];

    	// if it's not a whitespace, this could be the last character
    	if( !isspace(c) ){
    		end = &(s[j]);
    	}
    }
    *end = '\0';

    return s;
}


char * getSentence( char *sentence, const char *line )
{
    // First, copy the line to the sentence
    strcpy( sentence, line );
    // Later, detele comments from the sentence
    strtok( sentence, "#" );
    // trim the sentence
    trim( sentence );
    // Finally, if it's a comment line (start with '#'), then
    // return empty string
    if( sentence[0] == '#' ){
        sentence[0] = '\0';
    }

    return sentence;
}


void getAssignment( char *attribute, char *value, const char *sentence )
{
    // First, create temp buffer and copy sentence to it
    char *buffer = new char[strlen(sentence)+1];
    strcpy( buffer, sentence );

    // Copy the attribute
    strcpy( attribute, trim( strtok( buffer, "=" ) ) );
    // Copy the value
    strcpy( value, trim( strtok( NULL, "=" ) ) );

    // Free reserved buffer
    delete[] buffer;
}


CSystemOptionManager::CSystemOptionManager()
 : COptionManager()
{
	cleanOptions();
	setDefaultValues();
	loadOptions();

    LOG_INFO("System Option manager initialized");
}


CSystemOptionManager::~CSystemOptionManager()
{
	saveOptions();
	cleanOptions();

    LOG_INFO("System Option manager deinitialized");
}


CSystemOptionManager* CSystemOptionManager::getInstance()
{
  static CSystemOptionManager instance;
  return &instance;
}


void CSystemOptionManager::loadOptions()
{
    // Open the config file
    FILE *file = fopen( CONFIG_FILE, "r" );
    if( file==NULL ){
      LOG_ERROR("Config file not found: %s", CONFIG_FILE);
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
                  LOG_WARNING("Malformed category label '%s' into config file '%s'", sentence, CONFIG_FILE);
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

    LOG_INFO("System Options loaded: --> \"%s\"", CONFIG_FILE);
}


void CSystemOptionManager::saveOptions()
{
    // To save the options, is iterate across categories and
    // options while it's written in the config file

    // Open the config file
    FILE *file = fopen( CONFIG_FILE, "w" );
    if( file == NULL ){
      throw PFEXCEPTION("Error at open the config file: %s", CONFIG_FILE);
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

    LOG_INFO("System Options saved: --> \"%s\"", CONFIG_FILE);
}


void CSystemOptionManager::setDefaultValues()
{
    setGeneralMasterDatebasePath("data/database/master.sql3");
    setGeneralFailSafeMode(false);

    setGUIMouseVelocity(150);
    setGUISkin("ArridiDesign");
    setGUIShields("default");
    setGUIFlags("default");
    setGUIConfederations("default");
    setGUIPhotos("default");
    setGUIXMLParser("TinyXMLParser");

    setVideoRenderSystem("OpenGL Rendering Subsystem");
    setVideoWidth(1024);
    setVideoHeight(768);
    setVideoFullscreen(true);
    setVideoVSync(true);
    setVideoRTTPreferredMode("Copy");

    setSoundEnabled(true);

    setSimulationMatchDuration(2000);
    setSimulationLogicFrequency(30);
    setSimulationPhysicsFrequency(60);
    setSimulationMaxBallVelocity(25);
    setSimulationMaxPlayerVelocity(10);
    setSimulationMaxKickPower(25);
    setSimulationMaxKickDistance(2);
    setSimulationNearestPlayerToBallCycles(30);
    setSimulationNearestPlayerToBallTime(2);
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

const char * CSystemOptionManager::getGUIShields()
{
    return getStringOption("GUI", "Shields");
}

void CSystemOptionManager::setGUIShields(const char * shields)
{
    setStringOption("GUI", "Shields", shields);
}

const char * CSystemOptionManager::getGUIFlags()
{
    return getStringOption("GUI", "Flags");
}

void CSystemOptionManager::setGUIFlags(const char * flags)
{
    setStringOption("GUI", "Flags", flags);
}

const char * CSystemOptionManager::getGUIConfederations()
{
    return getStringOption("GUI", "Confederations");
}

void CSystemOptionManager::setGUIConfederations(const char * confederations)
{
    setStringOption("GUI", "Confederations", confederations);
}

const char * CSystemOptionManager::getGUIPhotos()
{
    return getStringOption("GUI", "Photos");
}

void CSystemOptionManager::setGUIPhotos(const char * photos)
{
    setStringOption("GUI", "Photos", photos);
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

// Sound options
bool CSystemOptionManager::getSoundEnabled()
{
    return getBooleanOption("Sound", "SoundEnabled");
}
void CSystemOptionManager::setSoundEnabled(bool soundEnabled)
{
    setBooleanOption("Sound", "SoundEnabled", soundEnabled);
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

int CSystemOptionManager::getSimulationMaxPlayerVelocity()
{
    return getIntOption("Simulation", "MaxPlayerVelocity");
}

void CSystemOptionManager::setSimulationMaxPlayerVelocity(int maxPlayerVelocity)
{
    setIntOption("Simulation", "MaxPlayerVelocity", maxPlayerVelocity);
}

int CSystemOptionManager::getSimulationMaxKickPower()
{
    return getIntOption("Simulation", "MaxKickPower");
}

void CSystemOptionManager::setSimulationMaxKickPower(int maxKickPower)
{
    setIntOption("Simulation", "MaxKickPower", maxKickPower);
}

int CSystemOptionManager::getSimulationMaxKickDistance()
{
    return getIntOption("Simulation", "MaxKickDistance");
}

void CSystemOptionManager::setSimulationMaxKickDistance(int maxKickDistance)
{
    setIntOption("Simulation", "MaxKickDistance", maxKickDistance);
}

int CSystemOptionManager::getSimulationNearestPlayerToBallCycles()
{
    return getIntOption("Simulation", "NearestPlayerToBallCycles");
}

void CSystemOptionManager::setSimulationNearestPlayerToBallCycles(int nearestPlayerToBallCycles)
{
    setIntOption("Simulation", "NearestPlayerToBallCycles", nearestPlayerToBallCycles);
}

int CSystemOptionManager::getSimulationNearestPlayerToBallTime()
{
    return getIntOption("Simulation", "NearestPlayerToBallTime");
}

void CSystemOptionManager::setSimulationNearestPlayerToBallTime(int nearestPlayerToBallTime)
{
    setIntOption("Simulation", "NearestPlayerToBallTime", nearestPlayerToBallTime);
}
