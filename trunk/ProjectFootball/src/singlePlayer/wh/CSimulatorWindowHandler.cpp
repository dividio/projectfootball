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

#include "CSimulatorWindowHandler.h"

#include <stdio.h>
#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../db/bean/CPfMatches.h"
#include "../option/CSinglePlayerOptionManager.h"
#include "../sim/CSimulationManager.h"
#include "../sim/entity/CReferee.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"


CSimulatorWindowHandler::CSimulatorWindowHandler(CSinglePlayerGame &game) :
	CWindowHandler("simulator.layout"),
	m_sceneMngr(NULL),
	m_simulator(NULL),
	m_game(game),
	m_cam2DEnabled(true),
	m_previousCamera(NULL)
{
    LOG_DEBUG("CSimulatorWindowHandler()");
}


CSimulatorWindowHandler::~CSimulatorWindowHandler()
{
    LOG_DEBUG("~CSimulatorWindowHandler()");
}


bool CSimulatorWindowHandler::keyDownHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& ke = static_cast<const CEGUI::KeyEventArgs&>(e);
    float move = 15;
    switch (ke.scancode)
    {
    case CEGUI::Key::W:
        m_direction.z = -move;
        break;
    case CEGUI::Key::S:
        m_direction.z = +move;
        break;
    case CEGUI::Key::A:
        m_direction.x = -move;
        break;
    case CEGUI::Key::D:
        m_direction.x = +move;
        break;
    case CEGUI::Key::PageDown:
        m_direction.y = -move;
        break;
    case CEGUI::Key::PageUp:
        m_direction.y = +move;
        break;
    default:
        return false;
    }
    return true;
}


bool CSimulatorWindowHandler::keyUpHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& ke = static_cast<const CEGUI::KeyEventArgs&>(e);
    switch (ke.scancode)
    {
    case CEGUI::Key::W: case CEGUI::Key::S:
        m_direction.z = 0;
        break;
    case CEGUI::Key::A: case CEGUI::Key::D:
        m_direction.x = 0;
        break;
    case CEGUI::Key::PageDown: case CEGUI::Key::PageUp:
        m_direction.y = 0;
        break;
    default:
        return false;
    }
    return true;
}


void CSimulatorWindowHandler::enter()
{
    m_sceneMngr->clearScene();
    m_direction = Ogre::Vector3::ZERO;
    m_previousUpdateTime = CGameEngine::getInstance()->getClock().getCurrentTime();

    m_continueButton->setEnabled(false);

    const CPfMatches *match	= m_game.getCurrentMatch();
    m_simulator = new CSimulationManager(match->getXMatch(), m_game, *this);
    m_sceneMngr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	Ogre::RenderTarget *renderTarget = Ogre::Root::getSingleton().getRenderTarget("Project Football");
	m_previousCamera = renderTarget->getViewport(0)->getCamera();

    // Create the 2D camera
    m_cam2D = m_sceneMngr->createCamera("2D_Camera");
    m_cam2D->setNearClipDistance(1);
    int width = 120;
    int height = 90;
    double  right = width/2.0,
            left = -width/2.0,
            top = height/2.0,
            bottom = -height/2.0,
            farZ = 150.0,
            nearZ = 10.0;
    Ogre::Matrix4 projectionMatrix(
            2/(right-left), 0, 0,  -(right+left)/(right-left),
            0, 2/(top-bottom), 0,  -(top+bottom)/(top-bottom),
            0, 0, -2/(farZ-nearZ), -(farZ+nearZ)/(farZ-nearZ),
            0, 0, 0, 1
            );
    m_cam2D->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    m_cam2D->setCustomProjectionMatrix(true, projectionMatrix);

    // Create the 2D camera node and make it look towards origin
    Ogre::SceneNode *cam2DNode;
    cam2DNode = m_sceneMngr->getRootSceneNode()->createChildSceneNode("2D_Camera_Node", Ogre::Vector3(0, 100, 0));
    cam2DNode->pitch(Ogre::Degree(-90));
    cam2DNode->attachObject(m_cam2D);

    // Create the 3D camera
    m_cam3D = m_sceneMngr->createCamera("3D_Camera");
    m_cam3D->setProjectionType(Ogre::PT_PERSPECTIVE);
    m_cam3D->setCustomProjectionMatrix(false);
    m_cam3D->setNearClipDistance(5);

    // Create the 3D camera node/pitch node
    Ogre::SceneNode *cam3DNode;
    cam3DNode = m_sceneMngr->getRootSceneNode()->createChildSceneNode("3D_Camera_Node", Ogre::Vector3(0, 25, 60));
    cam3DNode->pitch(Ogre::Degree(0));
    cam3DNode->attachObject(m_cam3D);

    m_logHistoryList->resetList();

    setup2DView();
    updateScore();
}


void CSimulatorWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

    m_continueButton			= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/ContinueButton"));
    m_startButton				= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/StartButton"));
    m_toggleCameraButton		= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/ToggleCameraButton"));

    m_logHistoryList            = static_cast<CEGUI::Listbox*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Log"));
    m_score                     = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Score"));
    m_time						= static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Time"));

    // i18n support
    m_continueButton->setText((CEGUI::utf8*)gettext("Continue"));
    m_startButton->setText((CEGUI::utf8*)gettext("Start"));
    m_toggleCameraButton->setText((CEGUI::utf8*)gettext("Toggle Camera"));

    // Event handle
    registerEventConnection(m_continueButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::continueButtonClicked, this)));
    registerEventConnection(m_startButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::startButtonClicked, this)));
    registerEventConnection(m_toggleCameraButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::toggleCameraButtonClicked, this)));
    registerEventConnection(windowMngr.getWindow("Simulator")->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::keyDownHandler, this)));
    registerEventConnection(windowMngr.getWindow("Simulator")->subscribeEvent(CEGUI::Window::EventKeyUp, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::keyUpHandler, this)));

    m_direction = Ogre::Vector3::ZERO;
    m_sceneMngr = Ogre::Root::getSingleton().getSceneManager("Default SceneManager");
}


void CSimulatorWindowHandler::leave()
{
    if(m_simulator != NULL) {
        delete m_simulator;
        m_simulator = NULL;
    }

	Ogre::RenderTarget *renderTarget = Ogre::Root::getSingleton().getRenderTarget("Project Football");
	if( m_previousCamera!=NULL ){
		renderTarget->getViewport(0)->setCamera(m_previousCamera);
		m_previousCamera = NULL;
	}

    if( m_cam2D!=NULL ){
    	m_sceneMngr->destroyCamera(m_cam2D);
    	m_cam2D = NULL;
    }
    if( m_cam3D!=NULL ){
    	m_sceneMngr->destroyCamera(m_cam3D);
    	m_cam3D = NULL;
    }

    m_sceneMngr->clearScene();
}


void CSimulatorWindowHandler::update()
{
	if( !m_cam2DEnabled ){
		static btVector3 ballPositionOld = m_simulator->getBallPosition();

		double currentTime = CGameEngine::getInstance()->getClock().getCurrentTime();
		double timeLapse = currentTime - m_previousUpdateTime;
		m_previousUpdateTime = currentTime;
		Ogre::Vector3 pos = m_cam3D->getParentNode()->getPosition();
		if(pos.y <= 5 && m_direction.y < 0) {
			m_direction.y = 0;
		}
		m_cam3D->getParentNode()->translate(m_direction * timeLapse, Ogre::Node::TS_LOCAL);

		btVector3 ballPosition = m_simulator->getBallPosition();
		ballPosition.setY(0.0);
		btVector3 lookAtPoint = ballPosition;
		lookAtPoint-=ballPositionOld;
		lookAtPoint/=50;
		lookAtPoint+=ballPositionOld;
		m_cam3D->lookAt(lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z());
		ballPositionOld = lookAtPoint;
	}

    std::ostringstream message;
    message << m_simulator->getReferee()->getMinute() << ":00";
	m_time->setText((CEGUI::utf8*)message.str().c_str());
    m_simulator->update();
}


CSimulationManager* CSimulatorWindowHandler::getSimulationManager()
{
    return m_simulator;
}


Ogre::SceneManager* CSimulatorWindowHandler::getSimulationSceneManager()
{
    return m_sceneMngr;
}


void CSimulatorWindowHandler::addToLog(const std::string &text)
{
    std::ostringstream message;
    // If there's text then add it
    if(text.size()) {
        message << m_simulator->getReferee()->getMinute() << "' - " << text.c_str();
        // Add the Editbox text to the history Listbox
        CEGUI::ListboxTextItem* logItem = new CEGUI::ListboxTextItem((CEGUI::utf8*)message.str().c_str());
        m_logHistoryList->addItem(logItem);
        m_logHistoryList->ensureItemIsVisible(m_logHistoryList->getItemCount());
    }
}


void CSimulatorWindowHandler::setup2DView()
{
	m_cam2DEnabled = true;

	Ogre::RenderTarget *renderTarget = Ogre::Root::getSingleton().getRenderTarget("Project Football");
	renderTarget->getViewport(0)->setCamera(m_cam2D);
}


void CSimulatorWindowHandler::setup3DView()
{
	m_cam2DEnabled = false;

	Ogre::RenderTarget *renderTarget = Ogre::Root::getSingleton().getRenderTarget("Project Football");
	renderTarget->getViewport(0)->setCamera(m_cam3D);
}


void CSimulatorWindowHandler::updateScore()
{
    CReferee *referee = m_simulator->getReferee();
    const CPfMatches *match	= m_game.getCurrentMatch();

    IPfTeamsDAO *teamsDAO = m_game.getIDAOFactory()->getIPfTeamsDAO();
    std::string homeName = teamsDAO->findByXTeam(match->getXFkTeamHome())->getSShortName();
    std::string awayName = teamsDAO->findByXTeam(match->getXFkTeamAway())->getSShortName();
    std::ostringstream names;
    names << homeName << " " << referee->getHomeScore() << " - " << referee->getAwayScore() << " " << awayName;
    m_score->setText((CEGUI::utf8*)names.str().c_str());
}


void CSimulatorWindowHandler::endMatchEvent()
{
    m_continueButton->setEnabled(true);
}


bool CSimulatorWindowHandler::continueButtonClicked(const CEGUI::EventArgs& e)
{
	m_game.setGameState(CSinglePlayerGame::PlayingMatch);
	CGameEngine::getInstance()->getTimeManager()->start();
    return true;
}


bool CSimulatorWindowHandler::startButtonClicked(const CEGUI::EventArgs& e)
{
    m_simulator->startMatch();
    return true;
}


bool CSimulatorWindowHandler::toggleCameraButtonClicked(const CEGUI::EventArgs& e)
{
	if( m_cam2DEnabled ){
		setup3DView();
	}
	else{
		setup2DView();
	}

	return true;
}
