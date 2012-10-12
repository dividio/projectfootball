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

#ifndef CSYSTEMOPTIONMANAGER_H_
#define CSYSTEMOPTIONMANAGER_H_

#include "../../utils/COptionManager.h"

class CSystemOptionManager : public COptionManager
{
public:
    /**
     * Destructor
     */
    virtual ~CSystemOptionManager();


    /**
     * Return the unique instance of the option manager
     * @return The unique instance of the option managre
     */
    static CSystemOptionManager* getInstance();


    /**
     * Load the options from the config file
     */
    virtual void loadOptions();


    /**
     * Save the options in the config file
     */
    virtual void saveOptions();


    /**
     * Set the default values of options
     */
    virtual void setDefaultValues();


    /**
     * Get/Set the value of the option
     */
    // General options
    const char *   getGeneralMasterDatebasePath();
    void           setGeneralMasterDatebasePath(const char * masterDatabasePath);

    bool           getGeneralFailSafeMode();
    void           setGeneralFailSafeMode(bool failSafeMode);

    // GUI options
    int            getGUIMouseVelocity();
    void           setGUIMouseVelocity(int mouseVelocity);

    const char *   getGUISkin();
    void           setGUISkin(const char * skin);

    const char *   getGUIShields();
    void           setGUIShields(const char * shields);

    const char *   getGUIFlags();
    void           setGUIFlags(const char * flags);

    const char *   getGUIConfederations();
    void           setGUIConfederations(const char * confederations);

    const char *   getGUIPhotos();
    void           setGUIPhotos(const char * photos);

    const char *   getGUIXMLParser();
    void           setGUIXMLParser(const char * parser);

    // Video options
    const char *   getVideoRenderSystem();
    void           setVideoRenderSystem(const char * renderSystem);

    int            getVideoWidth();
    void           setVideoWidth(int width);

    int            getVideoHeight();
    void           setVideoHeight(int height);

    bool           getVideoFullscreen();
    void           setVideoFullscreen(bool fullscreen);

    bool           getVideoVSync();
    void           setVideoVSync(bool vSync);

    const char *   getVideoRTTPreferredMode();
    void           setVideoRTTPreferredMode(const char * rttPreferredMode);

    //Sound options
    bool           getSoundEnabled();
    void           setSoundEnabled(bool soundEnabled);

    // Simulation options
    int            getSimulationMatchDuration();
    void           setSimulationMatchDuration(int matchDuration);

    int            getSimulationLogicFrequency();
    void           setSimulationLogicFrequency(int logicFrequency);

    int            getSimulationPhysicsFrequency();
    void           setSimulationPhysicsFrequency(int physicsFrequency);

    int            getSimulationMaxBallVelocity();
    void           setSimulationMaxBallVelocity(int maxBallVelocity);

    int            getSimulationMaxPlayerVelocity();
    void           setSimulationMaxPlayerVelocity(int maxPlayerVelocity);

    int            getSimulationMaxKickPower();
    void           setSimulationMaxKickPower(int maxKickPower);

    int            getSimulationMaxKickDistance();
    void           setSimulationMaxKickDistance(int maxKickDistance);

    int            getSimulationNearestPlayerToBallCycles();
    void           setSimulationNearestPlayerToBallCycles(int nearestPlayerToBallCycles);

    int            getSimulationNearestPlayerToBallTime();
    void           setSimulationNearestPlayerToBallTime(int nearestPlayerToBallTime);

private:
	/**
	 * Default constructor
	 */
	CSystemOptionManager();

	bool           createConfigDirectories(const std::string &script);
};

#endif /*CSYSTEMOPTIONMANAGER_H_*/
