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

#ifndef CAPPLICATION_H_
#define CAPPLICATION_H_

#include <Ogre.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

// Forward declarations
class CInputManager;

class CApplication
{
public:
    ~CApplication();
    static CApplication* getInstance();

    void go();
    const Ogre::RenderSystemList getRenderSystemList();
    void addFrameListener(Ogre::FrameListener* frameListener);
    void removeFrameListener(Ogre::FrameListener* frameListener);
    void takeScreenshot();

protected:
  CApplication();

private:

    Ogre::Root 					*m_root;
    Ogre::RenderWindow          *m_window;
    CEGUI::OgreRenderer 		*m_renderer;
    CEGUI::System 				*m_system;
    CInputManager               *m_inputManager;

    void setupAudioSystem();
    void createRoot();
    void defineResources();
    void setupRenderSystem();
    void createRenderWindow();
    void initializeResourceGroups();
    void setupScene();
    void setupInputSystem();
    void setupLUA();
    void setupCEGUI();
    void createFrameListeners();
    void startRenderLoop();

    bool keyDownEvent(const CEGUI::EventArgs &e);
    bool mouseOverAudioEvent(const CEGUI::EventArgs &e);
    bool clickAudioEvent(const CEGUI::EventArgs &e);

};


#endif // CAPPLICATION_H_
