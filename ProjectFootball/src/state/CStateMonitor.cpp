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

#include "CStateMonitor.h"
#include "CStateManager.h"
#include "../utils/CLog.h"
#include <stdio.h>


CStateMonitor::CStateMonitor()
 :CState()
{
	CLog::getInstance()->debug("CStateMonitor()");

    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"monitor.layout");
    CEGUI::PushButton *back = (CEGUI::PushButton *)CEGUI::WindowManager::getSingleton().getWindow("Monitor/BackButton");
    back->subscribeEvent(CEGUI::PushButton::EventClicked,
               CEGUI::Event::Subscriber(&CStateMonitor::back, this));

    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    Ogre::Camera *cam = mgr->createCamera("RttCam");
    cam->setPosition(0, 250, 0);
    cam->lookAt(0, 0, -1);

    CEGUI::Window *si = CEGUI::WindowManager::getSingleton().getWindow("Monitor/Image");
    renderImage(cam, si);

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
        1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
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


void CStateMonitor::enter()
{
    m_system->setGUISheet(m_sheet);

    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    mgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
    //mgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
    Ogre::Entity* ogreHead = mgr->createEntity("Cube", "Cube.mesh");
    Ogre::SceneNode* node1 = mgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, 0));
    node1->attachObject(ogreHead);
    node1->scale( 6, 6, 6 );
    Ogre::Entity* ent = mgr->createEntity("GroundEntity", "ground");
    mgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
    //ent->setMaterialName("Examples/GrassFloor");
    ent->setCastShadows(false);

}


bool CStateMonitor::back(const CEGUI::EventArgs &e)
{
        CStateManager::getInstance()->popState();
        return true;
}


void CStateMonitor::renderImage(Ogre::Camera *cam, CEGUI::Window *si)
{
  Ogre::RenderTexture *tex = m_root->getRenderSystem()->createRenderTexture("RttTex", 512, 512, Ogre::TEX_TYPE_2D, Ogre::PF_R8G8B8);

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
}
