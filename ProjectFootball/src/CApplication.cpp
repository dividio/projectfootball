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

#include <stdio.h>

#include "CApplication.h"
#include "state/CStateManager.h"
#include "utils/CInputManager.h"
#include "utils/CLuaManager.h"
#include "utils/COptionManager.h"
#include "utils/CLog.h"


CApplication::CApplication()
{
    CLog::getInstance()->debug("CApplication()");

    createRoot();
    defineResources();
    setupRenderSystem();
    createRenderWindow();
    initializeResourceGroups();
    setupScene();
    setupCEGUI();
    setupInputSystem();
    createFrameListeners();
}

CApplication::~CApplication()
{
    CLog::getInstance()->debug("~CApplication()");

    m_inputManager->destroyInputObject(m_keyboard);
    m_inputManager->destroyInputObject(m_mouse);
    OIS::InputManager::destroyInputSystem(m_inputManager);

    if(m_system != NULL)
        delete m_system;

    if(m_renderer != NULL)
        delete m_renderer;

    delete m_root;
}

CApplication* CApplication::getInstance()
{
    static CApplication instance;
    return &instance;
}

void CApplication::go()
{
    CStateManager::getInstance()->pushState(CStateMainMenu::getInstance());
    startRenderLoop();
}

void CApplication::exit()
{
    CStateManager::getInstance()->popStack();
}

OIS::Mouse* CApplication::getMouse()
{
    return m_mouse;
}

OIS::Keyboard* CApplication::getKeyboard()
{
    return m_keyboard;
}

void CApplication::createRoot()
{
    m_root = new Root("plugins.cfg", "");
}

void CApplication::defineResources()
{
    Ogre::String secName, typeName, archName;
    ConfigFile cf;
    cf.load("resources.cfg");

    Ogre::String skin = COptionManager::getInstance()->getStringOption("GUI", "Skin", "DefaultSkin");
    ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();

        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        if(secName == "General" || secName == skin) {
            for (i = settings->begin(); i != settings->end(); ++i) {
                typeName = i->first;
                archName = i->second;
                ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
            }
        }
    }
}

void CApplication::setupRenderSystem()
{
    Ogre::RenderSystemList *renderSystems = NULL;
    Ogre::RenderSystemList::iterator r_it;

    COptionManager *op = COptionManager::getInstance();
    std::string val = op->getStringOption("Video","RenderSystem", "OpenGL Rendering Subsystem");
    renderSystems = m_root->getAvailableRenderers();

    bool renderSystemFound = false;
    for (r_it=renderSystems->begin(); r_it!=renderSystems->end(); r_it++) {
        RenderSystem *tmp = *r_it;
        std::string rName(tmp->getName());

        // returns -1 if string not found
        if ((int) rName.find(val) >= 0) {
            m_root->setRenderSystem(*r_it);
            renderSystemFound = true;
            break;
        }
    }

    if (!renderSystemFound) {
        CLog::getInstance()->exception("Specified render system (%s) not found, exiting...", val.c_str());
    }

}

void CApplication::createRenderWindow()
{
    Ogre::NameValuePairList opts;
    COptionManager *op = COptionManager::getInstance();
    int width = op->getIntOption("Video","Width", 800);
    int height = op->getIntOption("Video","Height", 600);
    bool fullscreen = op->getBooleanOption("Video","Fullscreen", false);
    bool vsync = op->getBooleanOption("Video", "VSync", false);
    m_root->initialise(false);
    if(vsync) {
        opts["vsync"] = "true";
        #if OGRE_PLATFORM == PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_LINUX
            // TODO Nvidia and Ati check
            putenv("__GL_SYNC_TO_VBLANK=1");
        #endif
            m_window = m_root->createRenderWindow("Project Football", width, height, fullscreen, &opts);
    } else {
        opts["vsync"] = "false";
        m_window = m_root->createRenderWindow("Project Football", width, height, fullscreen, &opts);
    }
}

void CApplication::initializeResourceGroups()
{
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    std::string skin = COptionManager::getInstance()->getStringOption("GUI", "Skin", "DefaultSkin");
    ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
    ResourceGroupManager::getSingleton().initialiseResourceGroup(skin.c_str());
}

void CApplication::setupScene()
{
    SceneManager *mgr = m_root->createSceneManager(ST_GENERIC, "Default SceneManager");
    Camera *cam = mgr->createCamera("Camera");
    Viewport *vp = m_window->addViewport(cam);
    vp->setSkiesEnabled(false);
}

void CApplication::setupInputSystem()
{
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    OIS::ParamList pl;

    m_window->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    m_inputManager = OIS::InputManager::createInputSystem(pl);

    try
    {
        m_keyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
        m_mouse = static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
        //mJoy = static_cast<OIS::JoyStick*>(mInputManager->createInputObject(OIS::OISJoyStick, false));

        m_keyboard->setEventCallback(CInputManager::getInstance());
        m_mouse->setEventCallback(CInputManager::getInstance());
    }
    catch (const OIS::Exception &e)
    {
        throw new Exception(42, e.eText, "Application::setupInputSystem");
    }
}

void CApplication::setupCEGUI()
{
    SceneManager *mgr = m_root->getSceneManager("Default SceneManager");

    // CEGUI setup
    m_renderer = new CEGUI::OgreCEGUIRenderer(m_window, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, mgr);
    CEGUI::ScriptModule* script_module = CLuaManager::getInstance();
    CEGUI::System::setDefaultXMLParserName("TinyXMLParser");
    m_system = new CEGUI::System(m_renderer, 0, 0, script_module);

    CEGUI::System::getSingleton().executeScriptFile("initCEGUI.lua");

    // Other CEGUI setup here.
    // TODO Make Cegui initialization in Lua
    CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
    m_system->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

    int mouseVelocity = COptionManager::getInstance()->getIntOption("GUI", "MouseVelocity", 50);
    float mouseScale = 1.0f + (mouseVelocity/100);
    m_system->setMouseMoveScaling(mouseScale);
}

void CApplication::createFrameListeners()
{
    addFrameListener( CStateManager::getInstance() );
}

void CApplication::addFrameListener( FrameListener *frameListener )
{
    m_root->addFrameListener(frameListener);
}

void CApplication::removeFrameListener( FrameListener *frameListener )
{
    m_root->removeFrameListener(frameListener);
}

void CApplication::startRenderLoop()
{
    bool run = true;
    CInputManager* input = CInputManager::getInstance();
    while(run) {
        input->capture();

        Ogre::WindowEventUtilities::messagePump();
        run = m_root->renderOneFrame();
    }
}

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
    try{
        CLuaManager* lua = CLuaManager::getInstance();
        CApplication *app = CApplication::getInstance();
        app->go();
    }
    catch(Exception &e){
    #if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred in Ogre!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    #else
        CLog::getInstance()->error("An exception has occurred in Ogre: %s\n", e.getFullDescription().c_str());
    #endif
    }
    catch(CEGUI::Exception &e){
    #if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, e.getMessage().c_str(), "An exception has occurred in CEGUI!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    #else
        CLog::getInstance()->error("An exception has occurred in CEGUI: %s\n", e.getMessage().c_str());
    #endif
    }
    catch(...){
    #if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, "", "Unexpected exception!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    #else
        CLog::getInstance()->error("Unexpected exception!");
    #endif
    }

    return 0;
}
