/******************************************************************************
* Copyright (C) 2008 - Ikaro Games   www.ikarogames.com                       *
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

#include "CStateMonitor.h"
#include "CStateManager.h"
#include "../utils/CLog.h"
#include "../engine/CGameEngine.h"


CStateMonitor::CStateMonitor()
 :CState()
{
    CLog::getInstance()->debug("CStateMonitor()");

    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"monitor.layout");

    m_sceneMgr = m_root->createSceneManager(Ogre::ST_GENERIC, "Simulation SceneManager");
    m_cam = m_sceneMgr->createCamera("RttCam");
    m_cam->setNearClipDistance(1);
    m_direction = Ogre::Vector3::ZERO;


    CEGUI::Window *si = CEGUI::WindowManager::getSingleton().getWindow("Monitor/Image");
    renderImage(m_cam, si);

    si = CEGUI::WindowManager::getSingleton().getWindow("Monitor/Frame/Image");
    int width = (int)si->getPixelSize().d_width;
    int height = (int)si->getPixelSize().d_height;
    printf("FrameWindowSize %d x %d\n", width, height);
    CEGUI::Imageset *imageSet = CEGUI::ImagesetManager::getSingleton().getImageset("RttImageset");
    si->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet->getImage((CEGUI::utf8*)"RttImage")));
    si->disable();

    CEGUI::Window *w = CEGUI::WindowManager::getSingleton().getWindow("Monitor");
    w->subscribeEvent(CEGUI::Window::EventKeyDown,
            CEGUI::Event::Subscriber(&CStateMonitor::keyDownHandler, this));
    w->subscribeEvent(CEGUI::Window::EventKeyUp,
            CEGUI::Event::Subscriber(&CStateMonitor::keyUpHandler, this));

}


CStateMonitor* CStateMonitor::getInstance()
{
    static CStateMonitor instance;
    return &instance;
}


CStateMonitor::~CStateMonitor()
{
    CLog::getInstance()->debug("~CStateMonitor()");
    if(m_simulator != NULL) {
        delete m_simulator;
    }
}


bool CStateMonitor::keyDownHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& ke = static_cast<const CEGUI::KeyEventArgs&>(e);
    int move = 15;
    if(m_mode3D) {
        switch (ke.scancode)
        {
        case CEGUI::Key::W:
            m_direction.z -= move;
            break;
        case CEGUI::Key::S:
            m_direction.z += move;
            break;
        case CEGUI::Key::A:
            m_direction.x -= move;
            break;
        case CEGUI::Key::D:
            m_direction.x += move;
            break;
        case CEGUI::Key::PageDown:
            m_direction.y -= move;
            break;
        case CEGUI::Key::PageUp:
            m_direction.y += move;
            break;
        default:
            return false;
        }
    }
    return true;
}


bool CStateMonitor::keyUpHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& ke = static_cast<const CEGUI::KeyEventArgs&>(e);
    int move = 15;
    if(m_mode3D) {
        switch (ke.scancode)
        {
        case CEGUI::Key::W:
            m_direction.z += move;
            break;
        case CEGUI::Key::S:
            m_direction.z -= move;
            break;
        case CEGUI::Key::A:
            m_direction.x += move;
            break;
        case CEGUI::Key::D:
            m_direction.x -= move;
            break;
        case CEGUI::Key::PageDown:
            m_direction.y += move;
            break;
        case CEGUI::Key::PageUp:
            m_direction.y -= move;
            break;
        default:
            return false;
        }
    }
    return true;
}


void CStateMonitor::enter()
{
    Ogre::SceneNode* node;
    m_system->setGUISheet(m_sheet);

    m_sceneMgr->clearScene();
    m_simulator = new CSimulationManager();

    m_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

    // Create the scene node
    node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2D", Ogre::Vector3(0, 100, 0));
    // Make it look towards origin
    node->pitch(Ogre::Degree(-90));

    node->attachObject(m_cam);

    // create the second camera node/pitch node
    node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("CamNode3D", Ogre::Vector3(0, 25, 100));
    node->pitch(Ogre::Degree(0));

    switchTo2DView();

    loadTeamPlayers();
}


void CStateMonitor::renderImage(Ogre::Camera *cam, CEGUI::Window *si)
{
    int width = (int)si->getPixelSize().d_width;
    int height = (int)si->getPixelSize().d_height;
    printf("%d x %d\n", width, height);
    Ogre::RenderTexture *tex = m_root->getRenderSystem()->createRenderTexture("RttTex", width, height, Ogre::TEX_TYPE_2D, Ogre::PF_R8G8B8);

    Ogre::Viewport *v = tex->addViewport(cam);
    v->setOverlaysEnabled(false);
    v->setClearEveryFrame(true);
    v->setBackgroundColour(Ogre::ColourValue::Black);

    CEGUI::Texture *cTex = m_renderer->createTexture((CEGUI::utf8*)"RttTex");

    CEGUI::Imageset *imageSet = CEGUI::ImagesetManager::getSingleton().createImageset((CEGUI::utf8*)"RttImageset", cTex);
    imageSet->defineImage((CEGUI::utf8*)"RttImage",
        CEGUI::Point(0.0f, 0.0f),
        CEGUI::Size(cTex->getWidth(), cTex->getHeight()),
        CEGUI::Point(0.0f,0.0f));

    si->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet->getImage((CEGUI::utf8*)"RttImage")));

}


void CStateMonitor::forcedLeave()
{
    if(m_simulator != NULL) {
        delete m_simulator;
    }
}


bool CStateMonitor::leave()
{
    if(m_simulator != NULL) {
        delete m_simulator;
        m_simulator = NULL;
        CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
        CEGUI::Listbox* logHistory = static_cast<CEGUI::Listbox*> (winMgr.getWindow("Monitor/Log"));
        logHistory->resetList();
    }
    return true;
}


void CStateMonitor::update()
{
    float t = CStateManager::getInstance()->getTimeSinceLastFrame();
    m_camNode->translate(m_direction * t, Ogre::Node::TS_LOCAL);
    updateScore();
    m_simulator->update();
}


void CStateMonitor::toogleSimulationView()
{
    CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
    CEGUI::FrameWindow* frameWindow = static_cast<CEGUI::FrameWindow*> (winMgr.getWindow("Monitor/FrameWindow"));
    if(frameWindow->isVisible()) {
        frameWindow->setVisible(false);
        frameWindow->deactivate();
        frameWindow->disable();
        switchTo2DView();
    } else {
        frameWindow->setVisible(true);
        frameWindow->activate();
        frameWindow->enable();
    }
}


void CStateMonitor::switchTo2DView()
{
    int width = 120;
    int height = 90;
    m_mode3D = false;
    double  right = width/2.0,
            left = -width/2.0,
            top = height/2.0,
            bottom = -height/2.0,
            farZ = 100.0,
            nearZ = 10.0;
    Ogre::Matrix4 projectionMatrix(
            2/(right-left), 0, 0, -(right+left)/(right-left),
            0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom),
            0, 0, -2/(farZ-nearZ), -(farZ+nearZ)/(farZ-nearZ),
            0, 0, 0, 1
            );
    m_cam->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    m_cam->setCustomProjectionMatrix(true, projectionMatrix);

    m_cam->getParentSceneNode()->detachObject(m_cam);
    m_camNode = m_sceneMgr->getSceneNode("CamNode2D");
    m_camNode->attachObject(m_cam);
}


void CStateMonitor::switchTo3DView()
{
    m_mode3D = true;
    m_cam->setProjectionType(Ogre::PT_PERSPECTIVE);
    m_cam->setCustomProjectionMatrix(false);
    m_cam->setNearClipDistance(5);
    m_cam->getParentSceneNode()->detachObject(m_cam);
    m_camNode = m_sceneMgr->getSceneNode("CamNode3D");
    m_camNode->attachObject(m_cam);
}


CSimulationManager* CStateMonitor::getSimulationManager()
{
    return m_simulator;
}


Ogre::SceneManager* CStateMonitor::getSimulationSceneManager()
{
    return m_sceneMgr;
}


void CStateMonitor::addToLog(std::string text)
{
    CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Listbox* logHistory = static_cast<CEGUI::Listbox*> (winMgr.getWindow("Monitor/Log"));
    int historySize = 6;
    char message[30];
    // If there's text then add it
    if(text.size()) {
        sprintf(message,"%d' - %s", m_simulator->getReferee()->getMinute(), text.c_str());
        // Add the Editbox text to the history Listbox
        CEGUI::ListboxTextItem* logItem;
        if(logHistory->getItemCount() == historySize) {
            /* We have reached the capacity of the Listbox so re-use the first Listbox item.
               This code is a little crafty.  By default the ListboxTextItem is created with
               the auto-delete flag set to true, which results in its automatic deletion when
               removed from the Listbox.  So we change that flag to false, extract the item
               from the Listbox, change its text, put the auto-delete flag back to true, and
               finally put the item back into the Listbox. */
            logItem = static_cast<CEGUI::ListboxTextItem*>(logHistory->getListboxItemFromIndex(0));
            logItem->setAutoDeleted(false);
            logHistory->removeItem(logItem);
            logItem->setAutoDeleted(true);
            logItem->setText(message);
        } else {
            // Create a new listbox item
            logItem = new CEGUI::ListboxTextItem(message);
        }
        logHistory->addItem(logItem);
        logHistory->ensureItemIsVisible(logHistory->getItemCount());
    }
}


void CStateMonitor::loadTeamPlayers()
{
    CEGUI::MultiColumnList *playersList = static_cast<CEGUI::MultiColumnList*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Monitor/TeamPlayersList"));
    playersList->addColumn("Name", 0, CEGUI::UDim(1.0,0));
    playersList->resetList();

    CPfTeams                                *team               = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayersDAO                       *teamPlayersDAO     = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamPlayersDAO();
    std::vector<CPfTeamPlayers*>            *teamPlayersList    = teamPlayersDAO->findActiveTeamPlayersByXFkTeam(team->getXTeam());
    std::vector<CPfTeamPlayers*>::iterator  it;

    int cont = 0;
    for( it=teamPlayersList->begin(); it!=teamPlayersList->end(); it++ ){
        CPfTeamPlayers *teamPlayer = (*it);

        if(cont < 11) {
            int row_idx = playersList->addRow();
            playersList->setItem(new CEGUI::ListboxTextItem(teamPlayer->getSName()), 0, row_idx);
        }
        cont++;
    }
    teamPlayersDAO->freeVector(teamPlayersList);
    delete team;

    playersList->getHorzScrollbar()->setVisible(false);
}


void CStateMonitor::updateScore()
{
//    CEGUI::Window *w = CEGUI::WindowManager::getSingleton().getWindow("Monitor/TabControl2/Tab1");
//    m_simulator->getReferee()->getGameModeString();
}
