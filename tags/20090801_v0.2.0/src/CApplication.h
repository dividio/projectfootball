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
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>


class CApplication
{
public:
    ~CApplication();
    static CApplication* getInstance();

    void go();
    OIS::Mouse* getMouse();
    OIS::Keyboard* getKeyboard();
    Ogre::RenderSystemList* getRenderSystemList();
    void addFrameListener(Ogre::FrameListener* frameListener);
    void removeFrameListener(Ogre::FrameListener* frameListener);
    void takeScreenshot();

protected:
  CApplication();

private:

    Ogre::Root 					*m_root;
    Ogre::RenderWindow          *m_window;
    OIS::Keyboard 				*m_keyboard;
    OIS::Mouse 					*m_mouse;
    OIS::InputManager 			*m_inputManager;
    CEGUI::OgreCEGUIRenderer 	*m_renderer;
    CEGUI::System 				*m_system;

    void createRoot();
    void defineResources();
    void setupRenderSystem();
    void createRenderWindow();
    void initializeResourceGroups();
    void setupScene();
    void setupInputSystem();
    void setupCEGUI();
    void createFrameListeners();
    void startRenderLoop();
};


#endif // CAPPLICATION_H_
