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

#include "CApplication.h"
#include <stdio.h>

ExitListener::ExitListener(OIS::Keyboard *keyboard)
	: m_Keyboard(keyboard)
{
}

bool ExitListener::frameStarted(const FrameEvent& evt)
{
    m_Keyboard->capture();
    return true;
//    return !m_Keyboard->isKeyDown(OIS::KC_ESCAPE);
}


CApplication::CApplication()
{
    printf("--> CApplication()\n");

    createRoot();
    defineResources();
    setupRenderSystem();
    createRenderWindow();
    initializeResourceGroups();
    setupScene();
    setupInputSystem();
    setupCEGUI();
    createFrameListener();
}

CApplication::~CApplication()
{
    printf("<-- ~CApplication()\n");

    m_inputManager->destroyInputObject(m_keyboard);
    m_inputManager->destroyInputObject(m_mouse);
    OIS::InputManager::destroyInputSystem(m_inputManager);

    if(m_system != NULL)
      delete m_system;

    if(m_renderer != NULL)
      delete m_renderer;

    delete m_listener;
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
    m_root = new Root();
}

void CApplication::defineResources()
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

void CApplication::setupRenderSystem()
{
    if (!m_root->restoreConfig() && !m_root->showConfigDialog()) {
        throw Exception(52, "User canceled the config dialog!", "Application::setupRenderSystem()");
    }

}

void CApplication::createRenderWindow()
{
    m_root->initialise(true, "Project Football");

}

void CApplication::initializeResourceGroups()
{
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void CApplication::setupScene()
{
    SceneManager *mgr = m_root->createSceneManager(ST_GENERIC, "Default SceneManager");
    Camera *cam = mgr->createCamera("Camera");
    Viewport *vp = m_root->getAutoCreatedWindow()->addViewport(cam);
    vp->setSkiesEnabled(false);
}

void CApplication::setupInputSystem()
{
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    OIS::ParamList pl;
    RenderWindow *win = m_root->getAutoCreatedWindow();

    win->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    m_inputManager = OIS::InputManager::createInputSystem(pl);

    try
    {
        m_keyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
        m_mouse = static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
        //mJoy = static_cast<OIS::JoyStick*>(mInputManager->createInputObject(OIS::OISJoyStick, false));
    }
    catch (const OIS::Exception &e)
    {
        throw new Exception(42, e.eText, "Application::setupInputSystem");
    }
}

void CApplication::setupCEGUI()
{
    SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    RenderWindow *win = m_root->getAutoCreatedWindow();

    // CEGUI setup
    m_renderer = new CEGUI::OgreCEGUIRenderer(win, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, mgr);
    CEGUI::System::setDefaultXMLParserName("TinyXMLParser");
    m_system = new CEGUI::System(m_renderer);

    // Other CEGUI setup here.
    CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
    CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"WindowsLook.scheme");
    //CEGUI::ImagesetManager::getSingletonPtr()->createImageset( "MenuBackground.imageset");
    m_system->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
    m_system->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");
}

void CApplication::createFrameListener()
{
    m_listener = new ExitListener(m_keyboard);
//    m_root->addFrameListener(m_listener);
    m_root->addFrameListener(CStateManager::getInstance());
}

void CApplication::startRenderLoop()
{
    m_root->startRendering();
//	while( m_root->renderOneFrame() ){
//		m_mouse->capture();
//		m_keyboard->capture();
//	}
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
        CApplication *app = CApplication::getInstance();
        app->go();
    }
    catch(Exception &e){
		#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        	MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred in Ogre!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		#else
        	fprintf(stderr, "An exception has occurred in Ogre: %s\n", e.getFullDescription().c_str());
		#endif
    }
    catch(CEGUI::Exception &e){
		#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        	MessageBoxA(NULL, e.getMessage().c_str(), "An exception has occurred in CEGUI!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		#else
        	fprintf(stderr, "An exception has occurred in CEGUI: %s\n", e.getMessage().c_str());
		#endif
    }
    catch(...){
		#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBoxA(NULL, "", "Unexpected exception!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		#else
			fprintf(stderr, "Unexpected exception!");
		#endif
    }

    return 0;
}
