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
#include "audio/AudioSystemTypes.h"

#include "engine/CGameEngine.h"
#include "engine/option/CSystemOptionManager.h"

#include "exceptions/PFException.h"

#include "utils/CInputManager.h"
#include "utils/CLog.h"
#include "utils/CLuaManager.h"
#include "utils/CResourceManager.h"


CApplication::CApplication()
{
	LOG_DEBUG("CApplication()");

	setupAudioSystem();
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
    LOG_DEBUG("~CApplication()");

    delete CGameEngine::getInstance();

    if(m_inputManager != NULL)
        delete m_inputManager;

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
    startRenderLoop();
}

Ogre::RenderSystemList* CApplication::getRenderSystemList()
{
    return m_root->getAvailableRenderers();
}

void CApplication::setupAudioSystem()
{
	CSystemOptionManager *systemOptionManager = CSystemOptionManager::getInstance();
	bool soundEnabled = systemOptionManager->getSoundEnabled();
	if(soundEnabled) {
		CAudioSystem::getInstance()->setAudioSystem(SDL);
	} else {
		CAudioSystem::getInstance()->setAudioSystem(DUMMY);
	}

}

void CApplication::createRoot()
{
    m_root = new Ogre::Root("data/plugins.cfg", "");
}

void CApplication::defineResources()
{
    CResourceManager::getInstance()->defineResources();
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
        throw PFEXCEPTION("Specified render system (%s) not found, exiting...", val.c_str());
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
    Ogre::RenderSystem *renderSystem = m_root->getRenderSystem();
    if(renderSystem->getName() == "OpenGL Rendering Subsystem") {
        renderSystem->setConfigOption("RTT Preferred Mode", RTTMode);
    }
    m_root->initialise(false);
    if(vsync) {
        opts["vsync"] = "true";
        #if OGRE_PLATFORM == PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_LINUX
            // TODO Nvidia and Ati check
            char glSync[22] = "__GL_SYNC_TO_VBLANK=1";
            putenv(glSync);
        #endif
        m_window = m_root->createRenderWindow("Project Football", width, height, fullscreen, &opts);
    } else {
        opts["vsync"] = "false";
        m_window = m_root->createRenderWindow("Project Football", width, height, fullscreen, &opts);
    }
    try {
        LOG_DEBUG("Creating debug texture.");
        Ogre::TexturePtr debugTexture = m_root->getTextureManager()->createManual("DebugText",
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 2, 2,
                0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);
        LOG_DEBUG("Debug texture created.");
    } catch (Ogre::RenderingAPIException &e){
        LOG_ERROR("Error creating debug texture, using Copy mode now. Please restart the application.");
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
    // Get window handler
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    m_window->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << (unsigned int) windowHnd;

    // Get window size
    unsigned int width, height, depth;
    int left, top;
    m_window->getMetrics( width, height, depth, left, top );

    m_inputManager = new CInputManager(windowHndStr.str(), width, height);

}

bool CApplication::clickAudioEvent(const CEGUI::EventArgs &e)
{
    CAudioSystem::getInstance()->click()->play();
    return true;
}

bool CApplication::keyDownEvent(const CEGUI::EventArgs &e)
{
    const CEGUI::KeyEventArgs& keyEvent = static_cast<const CEGUI::KeyEventArgs&>(e);

    if (CEGUI::Key::F12 == keyEvent.scancode) {
        takeScreenshot();
    }

    return true;
}

bool CApplication::mouseOverAudioEvent(const CEGUI::EventArgs &e)
{
    const CEGUI::WindowEventArgs& we = static_cast<const CEGUI::WindowEventArgs&>(e);
    if( (we.window->testClassName( CEGUI::PushButton::EventNamespace  ) ||
         we.window->testClassName( CEGUI::RadioButton::EventNamespace ) ||
         we.window->testClassName( CEGUI::Checkbox::EventNamespace    ))&&
       !we.window->isAutoWindow() ) {
       // It's a push button (and not an auto window, from scrollbars)
        CAudioSystem::getInstance()->mouseOver()->play();
    }
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
    CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"Skin.scheme");
    m_system->setDefaultMouseCursor((CEGUI::utf8*)"WidgetsImageset", (CEGUI::utf8*)"MouseArrow");
    std::string guiName = CSystemOptionManager::getInstance()->getGUISkin();
    std::string tooltipName = guiName + "/Tooltip";
    m_system->setDefaultTooltip((CEGUI::utf8*)tooltipName.c_str());
    m_system->setDefaultFont("DejaVuSans-10");

    int mouseVelocity = CSystemOptionManager::getInstance()->getGUIMouseVelocity();
    float mouseScale = 1.0f + (mouseVelocity/100);
    m_system->setMouseMoveScaling(mouseScale);

    CEGUI::GlobalEventSet::getSingleton().subscribeEvent(
       CEGUI::Window::EventNamespace+"/"+CEGUI::Window::EventKeyDown,
       CEGUI::Event::Subscriber(&CApplication::keyDownEvent, this)
    );

    CEGUI::GlobalEventSet::getSingleton().subscribeEvent(
       CEGUI::PushButton::EventNamespace+"/"+CEGUI::PushButton::EventClicked,
       CEGUI::Event::Subscriber(&CApplication::clickAudioEvent, this)
    );

    CEGUI::GlobalEventSet::getSingleton().subscribeEvent(
       CEGUI::Window::EventNamespace+"/"+CEGUI::Window::EventMouseEnters,
       CEGUI::Event::Subscriber(&CApplication::mouseOverAudioEvent, this)
    );
}

void CApplication::createFrameListeners()
{
    addFrameListener( CGameEngine::getInstance() );
}

void CApplication::addFrameListener( Ogre::FrameListener *frameListener )
{
    m_root->addFrameListener(frameListener);
}

void CApplication::removeFrameListener( Ogre::FrameListener *frameListener )
{
    m_root->removeFrameListener(frameListener);
}

void CApplication::takeScreenshot()
{
    std::ostringstream ss;
    CDate date;
    ss << "screenshot" << "-" << date.getTimestamp() << ".png";
    m_window->writeContentsToFile(ss.str());
}

void CApplication::startRenderLoop()
{
    bool run = true;
    CGameEngine::getInstance()->getWindowManager()->nextScreen("Intro");
    while(run) {
        m_inputManager->capture();

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
        bindtextdomain("projectfootball", "data/i18n");
        textdomain("projectfootball");
        bind_textdomain_codeset("projectfootball", "UTF-8");

        CSystemOptionManager *systemOptionManager = CSystemOptionManager::getInstance();
        if( systemOptionManager->getGeneralFailSafeMode() ) {
            systemOptionManager->setVideoWidth(1024);
            systemOptionManager->setVideoHeight(768);
            systemOptionManager->setGUISkin("ArridiDesign");
            systemOptionManager->setVideoFullscreen(false);
            systemOptionManager->setVideoRTTPreferredMode("Copy");
        }else{
            systemOptionManager->setGeneralFailSafeMode(true);
            systemOptionManager->saveOptions();
        }

        CApplication *app = CApplication::getInstance();
        app->go();

        systemOptionManager->setGeneralFailSafeMode(false);
        systemOptionManager->saveOptions();
    }
    #if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        catch(Ogre::Exception &e){
            MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred in Ogre!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
        }
        catch(CEGUI::Exception &e){
            MessageBoxA(NULL, e.getMessage().c_str(), "An exception has occurred in CEGUI!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
        }
        catch(PFException &e){
            MessageBoxA(NULL, e.what(), "An exception has occurred in ProjectFootball", MB_OK | MB_ICONERROR | MB_TASKMODAL);
        }
        catch(...){
            MessageBoxA(NULL, "", "Unexpected exception!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
        }
    #else
        catch(Ogre::Exception &e){
            LOG_FATAL("An exception has occurred in Ogre: %s", e.getFullDescription().c_str());
        }
        catch(CEGUI::Exception &e){
        	LOG_FATAL("An exception has occurred in CEGUI: %s", e.getMessage().c_str());
        }
        catch(PFException &e){
        	LOG_FATAL("An exception has occurred in ProjectFootball: %s", e.what());
        }
        catch(...){
        	LOG_FATAL("Unexpected exception!");
        }
    #endif

    return 0;
}
