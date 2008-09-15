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
#include <libintl.h>

#include "CApplication.h"
#include "audio/CAudioSystem.h"
#include "state/CStateManager.h"
#include "utils/CInputManager.h"
#include "utils/CLuaManager.h"
#include "engine/option/CSystemOptionManager.h"
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

Ogre::RenderSystemList* CApplication::getRenderSystemList()
{
    return m_root->getAvailableRenderers();
}

void CApplication::createRoot()
{
    m_root = new Ogre::Root("plugins.cfg", "");
}

void CApplication::defineResources()
{
    Ogre::String secName, typeName, archName;
    Ogre::ConfigFile cf;
    cf.load("resources.cfg");

    Ogre::String skin = CSystemOptionManager::getInstance()->getGUISkin();
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();

        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        if(secName == "General" || secName == skin) {
            for (i = settings->begin(); i != settings->end(); ++i) {
                typeName = i->first;
                archName = i->second;
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
            }
        }
    }
}

void CApplication::setupRenderSystem()
{
    Ogre::RenderSystemList *renderSystems = NULL;
    Ogre::RenderSystemList::iterator r_it;

    CSystemOptionManager *op = CSystemOptionManager::getInstance();
    std::string val = op->getVideoRenderSystem();
    renderSystems = m_root->getAvailableRenderers();

    bool renderSystemFound = false;
    for (r_it=renderSystems->begin(); r_it!=renderSystems->end(); r_it++) {
        Ogre:: RenderSystem *tmp = *r_it;
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
    CSystemOptionManager *op = CSystemOptionManager::getInstance();
    int width       = op->getVideoWidth();
    int height      = op->getVideoHeight();
    bool fullscreen = op->getVideoFullscreen();
    bool vsync      = op->getVideoVSync();
    std::string RTTMode  = op->getVideoRTTPreferredMode();
    m_root->getRenderSystem()->setConfigOption("RTT Preferred Mode", RTTMode);
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
    try {
        CLog::getInstance()->debug("Creating debug texture.");
        Ogre::TexturePtr debugTexture = m_root->getTextureManager()->createManual("DebugText",
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 2, 2,
                0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);
        CLog::getInstance()->debug("Debug texture created.");
    } catch (Ogre::RenderingAPIException &e){
        CLog::getInstance()->error("Error creating debug texture, using Copy mode now. Please restart the application.");
        CSystemOptionManager::getInstance()->setVideoRTTPreferredMode("Copy");
    }
}

void CApplication::initializeResourceGroups()
{
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    std::string skin = CSystemOptionManager::getInstance()->getGUISkin();
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(skin.c_str());
}

void CApplication::setupScene()
{
    Ogre::SceneManager *mgr = m_root->createSceneManager(Ogre::ST_GENERIC, "Default SceneManager");
    Ogre::Camera *cam = mgr->createCamera("Camera");
    Ogre::Viewport *vp = m_window->addViewport(cam);
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
    //Disable mouse and keyboard grab for debug
    //pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    //pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
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
        throw new Ogre::Exception(42, e.eText, "Application::setupInputSystem");
    }
}

bool clickAudioEvent(const CEGUI::EventArgs &e)
{
    CAudioSystem::CLICK->play();
    return true;
}

void CApplication::setupCEGUI()
{
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");

    // CEGUI setup
    m_renderer = new CEGUI::OgreCEGUIRenderer(m_window, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, mgr);
    CEGUI::ScriptModule* script_module = CLuaManager::getInstance();
    std::string parser = CSystemOptionManager::getInstance()->getGUIXMLParser();
    CEGUI::System::setDefaultXMLParserName(parser);
    m_system = new CEGUI::System(m_renderer, 0, 0, script_module);

    CEGUI::System::getSingleton().executeScriptFile("initCEGUI.lua");

    // Other CEGUI setup here.
    // TODO Make Cegui initialization in Lua
    CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
    m_system->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

    int mouseVelocity = CSystemOptionManager::getInstance()->getGUIMouseVelocity();
    float mouseScale = 1.0f + (mouseVelocity/100);
    m_system->setMouseMoveScaling(mouseScale);

    CEGUI::GlobalEventSet::getSingleton().subscribeEvent(
       CEGUI::PushButton::EventNamespace+"/"+CEGUI::PushButton::EventClicked,
       CEGUI::Event::Subscriber(&clickAudioEvent)
    );
}

void CApplication::createFrameListeners()
{
    addFrameListener( CStateManager::getInstance() );
}

void CApplication::addFrameListener( Ogre::FrameListener *frameListener )
{
    m_root->addFrameListener(frameListener);
}

void CApplication::removeFrameListener( Ogre::FrameListener *frameListener )
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

        setlocale(LC_ALL, "");
        bindtextdomain("projectfootball", "data/po");
        textdomain("projectfootball");
        bind_textdomain_codeset("projectfootball", "UTF-8");

        CSystemOptionManager *systemOptionManager = CSystemOptionManager::getInstance();
        if( systemOptionManager->getGeneralFailSafeMode() ){
            systemOptionManager->setVideoWidth(800);
            systemOptionManager->setVideoHeight(600);
            systemOptionManager->setVideoFullscreen(false);
            systemOptionManager->setVideoRTTPreferredMode("Copy");
        }else{
            systemOptionManager->setGeneralFailSafeMode(true);
            systemOptionManager->saveOptions();
        }

        CLuaManager* lua = CLuaManager::getInstance();
        CApplication *app = CApplication::getInstance();
        app->go();

        systemOptionManager->setGeneralFailSafeMode(false);
        systemOptionManager->saveOptions();
    }
    catch(Ogre::Exception &e){
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
