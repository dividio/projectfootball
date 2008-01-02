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

#include "CStateMonitor.h"
#include "CStateManager.h"
#include "../utils/CLog.h"


CStateMonitor::CStateMonitor()
 :CState()
{
    CLog::getInstance()->debug("CStateMonitor()");

    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"monitor.layout");

    m_sceneMgr = m_root->getSceneManager("Default SceneManager");
    m_cam = m_sceneMgr->createCamera("RttCam");
    m_cam->setNearClipDistance(5);
    m_direction = Ogre::Vector3::ZERO;


    CEGUI::Window *si = CEGUI::WindowManager::getSingleton().getWindow("Monitor/Image");
    renderImage(m_cam, si);

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
    m_system->setGUISheet(m_sheet);

    m_sceneMgr = m_root->getSceneManager("Default SceneManager");
    m_sceneMgr->clearScene();

    m_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    Ogre::Entity* ogreObject = m_sceneMgr->createEntity("Cylinder", "Cylinder.mesh");
    Ogre::Entity* ogreObject2 = m_sceneMgr->createEntity("Cylinder2", "Cylinder.mesh");
    Ogre::Entity* ogreObject3 = m_sceneMgr->createEntity("Field", "Field.mesh");

    Ogre::SceneNode* node = m_sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));
    node->attachObject(ogreObject);
    node = m_sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-30, 0, -20));
    node->attachObject(ogreObject2);
    node = m_sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 0));
    node->attachObject(ogreObject3);

    // Create the scene node
    node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Ogre::Vector3(0, 100, 0));
    // Make it look towards origin
    node->pitch(Ogre::Degree(-90));

    node->attachObject(m_cam);

    // create the second camera node/pitch node
    node = m_sceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2", Ogre::Vector3(-15, 30, 70));
    node->pitch(Ogre::Degree(-25));

    switchTo2DView();
}


void CStateMonitor::renderImage(Ogre::Camera *cam, CEGUI::Window *si)
{
    int width = (int)si->getPixelSize().d_width;
    int height = (int)si->getPixelSize().d_height;
    printf("%d x %d", width, height);
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

}


bool CStateMonitor::leave()
{
    return true;
}


void CStateMonitor::update()
{
    float t = CStateManager::getInstance()->getTimeSinceLastFrame();
    m_camNode->translate(m_direction * t, Ogre::Node::TS_LOCAL);
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
            far = 100,
            near = 10;
    Ogre::Matrix4 projectionMatrix(
            2/(right-left), 0, 0, -(right+left)/(right-left),
            0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom),
            0, 0, -2/(far-near), -(far+near)/(far-near),
            0, 0, 0, 1
            );
    m_cam->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    m_cam->setCustomProjectionMatrix(true,  projectionMatrix);

    m_cam->getParentSceneNode()->detachObject(m_cam);
    m_camNode = m_sceneMgr->getSceneNode("CamNode1");
    m_camNode->attachObject(m_cam);
}


void CStateMonitor::switchTo3DView()
{
    m_mode3D = true;
    m_cam->setProjectionType(Ogre::PT_PERSPECTIVE);
    m_cam->setCustomProjectionMatrix(false);
    m_cam->setNearClipDistance(5);
    m_cam->getParentSceneNode()->detachObject(m_cam);
    m_camNode = m_sceneMgr->getSceneNode("CamNode2");
    m_camNode->attachObject(m_cam);
}

