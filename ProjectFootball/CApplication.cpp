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

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "StateManager/CStateManager.h"

using namespace Ogre;

class ExitListener : public FrameListener
{
public:
    ExitListener(OIS::Keyboard *keyboard)
        : m_Keyboard(keyboard)
    {
    }

    bool frameStarted(const FrameEvent& evt)
    {
        m_Keyboard->capture();
        return !m_Keyboard->isKeyDown(OIS::KC_ESCAPE);
    }

private:
    OIS::Keyboard *m_Keyboard;
};

class CApplication
{
public:
    void go()
    {
        createRoot();
        defineResources();
        setupRenderSystem();
        createRenderWindow();
        initializeResourceGroups();
        setupScene();
        setupInputSystem();
        setupCEGUI();
        createFrameListener();
        startRenderLoop();
    }

    ~CApplication()
    {
        m_InputManager->destroyInputObject(m_Keyboard);
        m_InputManager->destroyInputObject(m_Mouse);
        OIS::InputManager::destroyInputSystem(m_InputManager);

        delete m_Renderer;
        delete m_System;

        delete m_StateManager;
        delete m_Listener;
        delete m_Root;
    }

private:
    Root *m_Root;
    OIS::Keyboard *m_Keyboard;
    OIS::Mouse *m_Mouse;
    OIS::InputManager *m_InputManager;
    CEGUI::OgreCEGUIRenderer *m_Renderer;
    CEGUI::System *m_System;
    ExitListener *m_Listener;
    CStateManager *m_StateManager;

    void createRoot()
    {
        m_Root = new Root();
    }

    void defineResources()
    {
        String secName, typeName, archName;
        ConfigFile cf;
        cf.load("resources.cfg");

        ConfigFile::SectionIterator seci = cf.getSectionIterator();
        while (seci.hasMoreElements()) {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i) {
                typeName = i->first;
                archName = i->second;
                ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
            }
        }
    }

    void setupRenderSystem()
    {
        if (!m_Root->restoreConfig() && !m_Root->showConfigDialog()) {
            throw Exception(52, "User canceled the config dialog!", "Application::setupRenderSystem()");
        }

    }

    void createRenderWindow()
    {
        m_Root->initialise(true, "Project Football");

    }

    void initializeResourceGroups()
    {
        TextureManager::getSingleton().setDefaultNumMipmaps(5);
        ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    }

    void setupScene()
    {
        SceneManager *mgr = m_Root->createSceneManager(ST_GENERIC, "Default SceneManager");
        Camera *cam = mgr->createCamera("Camera");
        Viewport *vp = m_Root->getAutoCreatedWindow()->addViewport(cam);
        vp->setSkiesEnabled(false);
    }

    void setupInputSystem()
    {
        size_t windowHnd = 0;
        std::ostringstream windowHndStr;
        OIS::ParamList pl;
        RenderWindow *win = m_Root->getAutoCreatedWindow();

        win->getCustomAttribute("WINDOW", &windowHnd);
        windowHndStr << windowHnd;
        pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
        m_InputManager = OIS::InputManager::createInputSystem(pl);

        try
        {
            m_Keyboard = static_cast<OIS::Keyboard*>(m_InputManager->createInputObject(OIS::OISKeyboard, false));
            m_Mouse = static_cast<OIS::Mouse*>(m_InputManager->createInputObject(OIS::OISMouse, false));
            //mJoy = static_cast<OIS::JoyStick*>(mInputManager->createInputObject(OIS::OISJoyStick, false));
        }
        catch (const OIS::Exception &e)
        {
            throw new Exception(42, e.eText, "Application::setupInputSystem");
        }
    }

    void setupCEGUI()
    {
        SceneManager *mgr = m_Root->getSceneManager("Default SceneManager");
        RenderWindow *win = m_Root->getAutoCreatedWindow();

        // CEGUI setup
        m_Renderer = new CEGUI::OgreCEGUIRenderer(win, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, mgr);
        CEGUI::System::setDefaultXMLParserName("TinyXMLParser");
        m_System = new CEGUI::System(m_Renderer);

        // Other CEGUI setup here.
    }

    void createFrameListener()
    {
        m_Listener = new ExitListener(m_Keyboard);
        m_StateManager = new CStateManager();
        m_Root->addFrameListener(m_Listener);
        m_Root->addFrameListener(m_StateManager);
    }

    void startRenderLoop()
    {
        m_Root->startRendering();

        //// Do not add this to the application
        //while (mRoot->renderOneFrame())
        //{
        //    // Do some things here, like sleep for x milliseconds or perform other actions.
        //}
    }
};

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
    try
    {
        CApplication app;
        app.go();
    }
    catch(Exception& e)
    {
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        fprintf(stderr, "An exception has occurred: %s\n",
            e.getFullDescription().c_str());
#endif
    }

    return 0;
}
