/******************************************************************************
* Copyright (C) 2007 - Ikaro Games   www.ikarogames.com                       *
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


#ifndef CSIMULATORWINDOWHANDLER_H_
#define CSIMULATORWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>

#include <Ogre.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "../../engine/wm/CWindowHandler.h"


//Forward declarations
class CSinglePlayerGame;
class CSimulationManager;
class CPfMatches;


#define SIMULATION_SCENE_MANAGER_NODE_NAME	"Default SceneManager"

class CSimulatorWindowHandler : public CWindowHandler
{
public:
    CSimulatorWindowHandler(CSinglePlayerGame &game);
    virtual ~CSimulatorWindowHandler();

    virtual void enter();
    virtual void init();
    virtual void leave();
    virtual void update();

    CSimulationManager* getSimulationManager();
    Ogre::SceneManager* getSimulationSceneManager();
    void addToLog(const std::string &text);
    void updateScore();
    void endMatchEvent();

private:
    bool keyDownHandler(const CEGUI::EventArgs& e);
    bool keyUpHandler(const CEGUI::EventArgs& e);
    bool continueButtonClicked(const CEGUI::EventArgs& e);
    bool startButtonClicked(const CEGUI::EventArgs& e);
    bool toggleCameraButtonClicked(const CEGUI::EventArgs& e);

    CEGUI::PushButton		*m_continueButton;
    CEGUI::PushButton		*m_startButton;
    CEGUI::PushButton		*m_toggleCameraButton;

    CEGUI::Listbox          *m_logHistoryList;
    CEGUI::Window           *m_score;
    CEGUI::Window			*m_time;

    Ogre::Camera            *m_cam2D;
    Ogre::Camera            *m_cam3D;
    Ogre::Camera			*m_previousCamera;
    Ogre::Vector3            m_direction;
    Ogre::SceneManager      *m_sceneMngr;    // The simulation SceneManager

    CSimulationManager      *m_simulator;
    CSinglePlayerGame		&m_game;

    double                   m_previousUpdateTime;
    bool					 m_cam2DEnabled;

    void setup2DView();
    void setup3DView();
};

#endif // CSIMULATORWINDOWHANDLER_H_
