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

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "../../engine/CScreen.h"
#include "../sim/CSimulationManager.h"

class CScreenSimulator : public CScreen
{
public:
    static CScreenSimulator* getInstance();

    virtual ~CScreenSimulator();

    virtual void enter();
    virtual void forcedLeave();
    virtual bool leave();
    virtual void update();

    void toogleSimulationView();
    void switchTo2DView();
    void switchTo3DView();
    CSimulationManager* getSimulationManager();
    Ogre::SceneManager* getSimulationSceneManager();
    void addToLog(std::string text);
    void updateScore();
    void endMatchEvent();

protected:
    CScreenSimulator();

private:

    CEGUI::FrameWindow      *m_frameWindow;
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
    CEGUI::PushButton       *m_continueButton;
    CEGUI::PushButton       *m_backButton;

    Ogre::Camera            *m_cam2D;
    Ogre::Camera            *m_cam3D;
    Ogre::SceneNode         *m_cam2DNode;
    Ogre::SceneNode         *m_cam3DNode;
    Ogre::Vector3           m_direction;
    Ogre::RenderTexture     *m_renderTexture;
    Ogre::SceneManager      *m_sceneMgr;    // The simulation SceneManager
    Ogre::SceneNode         *m_camNode;     // The SceneNode the camera is currently attached to

    CSimulationManager      *m_simulator;

    CPfMatches              *m_match;

    bool keyDownHandler(const CEGUI::EventArgs& e);
    bool keyUpHandler(const CEGUI::EventArgs& e);
    void loadTeamPlayers();
};

#endif // CSCREENSIMULATOR_H_
