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


#ifndef CSCREENSIMULATOR_H_
#define CSCREENSIMULATOR_H_

#include <CEGUI/CEGUI.h>

#include <Ogre.h>
#include <OgreCEGUIRenderer.h>

#include "../../engine/wm/CWindowHandler.h"


//Forward declarations
class CSinglePlayerGame;
class CSimulationManager;
class CPfMatches;


#define SIMULATION_SCENE_MANAGER_NODE_NAME	"Simulation SceneManager"

class CScreenSimulator : public CWindowHandler
{
public:
    CScreenSimulator(CSinglePlayerGame &game);
    virtual ~CScreenSimulator();

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
    bool backButtonClicked(const CEGUI::EventArgs& e);
    bool continueButtonClicked(const CEGUI::EventArgs& e);
    bool startButtonClicked(const CEGUI::EventArgs& e);
    bool zoomButtonClicked(const CEGUI::EventArgs& e);
    bool formation433ButtonClicked(const CEGUI::EventArgs& e);
    bool formation442ButtonClicked(const CEGUI::EventArgs& e);
    bool frameWindowCloseClicked(const CEGUI::EventArgs& e);
    bool view2DButtonClicked(const CEGUI::EventArgs& e);
    bool view3DButtonClicked(const CEGUI::EventArgs& e);

    CEGUI::PushButton		*m_continueButton;
    CEGUI::PushButton		*m_startButton;
    CEGUI::PushButton		*m_zoomButton;
    CEGUI::PushButton		*m_formation433Button;
    CEGUI::PushButton		*m_formation442Button;
    CEGUI::FrameWindow		*m_frameWindow;
    CEGUI::PushButton		*m_view2DButton;
    CEGUI::PushButton		*m_view3DButton;
    CEGUI::PushButton		*m_frameStartButtom;

    CEGUI::Listbox          *m_logHistoryList;
    CEGUI::Listbox          *m_logHistoryListShort;
    CEGUI::MultiColumnList  *m_teamPlayersList;
    CEGUI::Window           *m_groundImage;
    CEGUI::Window           *m_groundFrameImage;
    CEGUI::Window           *m_teamNames;
    CEGUI::Window           *m_score;
    CEGUI::Window           *m_frameHomeName;
    CEGUI::Window           *m_frameAwayName;
    CEGUI::Window           *m_frameHomeScore;
    CEGUI::Window           *m_frameAwayScore;

    Ogre::Camera            *m_cam2D;
    Ogre::Camera            *m_cam3D;
    Ogre::SceneNode         *m_cam2DNode;
    Ogre::SceneNode         *m_cam3DNode;
    Ogre::Vector3            m_direction;
    Ogre::SceneManager      *m_sceneMngr;    // The simulation SceneManager
    Ogre::SceneNode         *m_camNode;     // The SceneNode the camera is currently attached to
    Ogre::RenderTexture     *m_renderTexture;

    CSimulationManager      *m_simulator;
    CSinglePlayerGame		&m_game;

    double                   m_previousUpdateTime;
    bool					 m_initiated;

    void loadTeamPlayers();
    void toogleZoom();
    void setup2DView();
};

#endif // CSCREENSIMULATOR_H_
