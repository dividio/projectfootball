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
	m_initiated(false)
{
    LOG_DEBUG("CSimulatorWindowHandler()");
}


CSimulatorWindowHandler::~CSimulatorWindowHandler()
{
    LOG_DEBUG("~CSimulatorWindowHandler()");

    if( m_initiated ){
		CEGUI::ImagesetManager::getSingleton().destroyImageset("RttImageset");
		Ogre::TextureManager::getSingleton().remove("RttTex");
		Ogre::Root::getSingleton().destroySceneManager(m_sceneMngr);
		delete m_simulator;
    }
}


bool CSimulatorWindowHandler::keyDownHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& ke = static_cast<const CEGUI::KeyEventArgs&>(e);
    float move = 15;
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
    return true;
}


bool CSimulatorWindowHandler::keyUpHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& ke = static_cast<const CEGUI::KeyEventArgs&>(e);
    float move = 15;
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
        if(m_direction.y == -move) {
            m_direction.y += move;
        }
        break;
    case CEGUI::Key::PageUp:
        m_direction.y -= move;
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

    // create the 3D camera node/pitch node
    m_cam3DNode = m_sceneMngr->getRootSceneNode()->createChildSceneNode("3D_Camera_Node", Ogre::Vector3(0, 25, 60));
    m_cam3DNode->pitch(Ogre::Degree(0));
    m_cam3DNode->attachObject(m_cam3D);

    // Create the 2D camera node and make it look towards origin
    m_cam2DNode = m_sceneMngr->getRootSceneNode()->createChildSceneNode("2D_Camera_Node", Ogre::Vector3(0, 100, 0));
    m_cam2DNode->pitch(Ogre::Degree(-90));
    m_cam2DNode->attachObject(m_cam2D);

    setup2DView();
    loadTeamPlayers();
    IPfTeamsDAO *teamsDAO = m_game.getIDAOFactory()->getIPfTeamsDAO();
    std::string homeName = teamsDAO->findByXTeam(match->getXFkTeamHome())->getSShortName();
    std::string awayName = teamsDAO->findByXTeam(match->getXFkTeamAway())->getSShortName();
    std::ostringstream names;
    names << homeName.c_str() << " vs " << awayName.c_str();
    m_teamNames->setText((CEGUI::utf8*)names.str().c_str());
    m_score->setText("0 - 0");
    m_frameHomeName->setText((CEGUI::utf8*)homeName.c_str());
    m_frameAwayName->setText((CEGUI::utf8*)awayName.c_str());
    m_frameHomeScore->setText("0");
    m_frameAwayScore->setText("0");
}


void CSimulatorWindowHandler::init()
{
	CEGUI::WindowManager	&windowMngr = CEGUI::WindowManager::getSingleton();

    m_continueButton			= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/ContinueButton"));
    m_startButton				= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/StartButton"));
    m_zoomButton				= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/ZoomButton"));
    m_formation433Button		= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/433Button"));
    m_formation442Button		= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/442Button"));
    m_frameWindow				= static_cast<CEGUI::FrameWindow*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/FrameWindow"));
    m_view2DButton				= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/2DButton"));
    m_view3DButton				= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/3DButton"));
    m_frameStartButtom			= static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/StartButton"));

    m_logHistoryList            = static_cast<CEGUI::Listbox*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Log"));
    m_logHistoryListShort       = static_cast<CEGUI::Listbox*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/Log"));
    m_teamPlayersList           = static_cast<CEGUI::MultiColumnList*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/TeamPlayersList"));
    m_groundImage               = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Image"));
    m_groundFrameImage          = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/Image"));
    m_teamNames                 = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/TeamNames"));
    m_score                     = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Score"));
    m_frameHomeName             = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/HomeName"));
    m_frameAwayName             = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/AwayName"));
    m_frameHomeScore            = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/HomeScore"));
    m_frameAwayScore            = static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/Frame/AwayScore"));

    // i18n support
    m_continueButton->setText((CEGUI::utf8*)gettext("Continue"));
    m_startButton->setText((CEGUI::utf8*)gettext("Start"));
    m_zoomButton->setText((CEGUI::utf8*)gettext("Zoom"));
    m_frameWindow->setText((CEGUI::utf8*)gettext("Simulation View"));
    m_view2DButton->setText((CEGUI::utf8*)gettext("2D View"));
    m_view3DButton->setText((CEGUI::utf8*)gettext("3D View"));
    m_frameStartButtom->setText((CEGUI::utf8*)gettext("Start"));
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/TeamTab"))->setText((CEGUI::utf8*)gettext("Team"));
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/FormationTab"))->setText((CEGUI::utf8*)gettext("Formation"));
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/LogTab"))->setText((CEGUI::utf8*)gettext("Log"));
    static_cast<CEGUI::Window*>(windowMngr.getWindow((CEGUI::utf8*)"Simulator/StatisticsTab"))->setText((CEGUI::utf8*)gettext("Statistics"));

    // Event handle
    registerEventConnection(m_continueButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::continueButtonClicked, this)));
    registerEventConnection(m_startButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::startButtonClicked, this)));
    registerEventConnection(m_zoomButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::zoomButtonClicked, this)));
    registerEventConnection(m_formation433Button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::formation433ButtonClicked, this)));
    registerEventConnection(m_formation442Button->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::formation442ButtonClicked, this)));
    registerEventConnection(m_frameWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::frameWindowCloseClicked, this)));
    registerEventConnection(m_view2DButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::view2DButtonClicked, this)));
    registerEventConnection(m_view3DButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::view3DButtonClicked, this)));
    registerEventConnection(m_frameStartButtom->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::startButtonClicked, this)));
    registerEventConnection(windowMngr.getWindow("Simulator")->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::keyDownHandler, this)));
    registerEventConnection(windowMngr.getWindow("Simulator")->subscribeEvent(CEGUI::Window::EventKeyUp, CEGUI::Event::Subscriber(&CSimulatorWindowHandler::keyUpHandler, this)));

    m_direction = Ogre::Vector3::ZERO;
    m_sceneMngr = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, SIMULATION_SCENE_MANAGER_NODE_NAME);

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
            2/(right-left), 0, 0, -(right+left)/(right-left),
            0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom),
            0, 0, -2/(farZ-nearZ), -(farZ+nearZ)/(farZ-nearZ),
            0, 0, 0, 1
            );
    m_cam2D->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    m_cam2D->setCustomProjectionMatrix(true, projectionMatrix);

    m_cam3D = m_sceneMngr->createCamera("3D_Camera");
    m_cam3D->setProjectionType(Ogre::PT_PERSPECTIVE);
    m_cam3D->setCustomProjectionMatrix(false);
    m_cam3D->setNearClipDistance(5);

    Ogre::TexturePtr texturePtr = Ogre::TextureManager::getSingleton().createManual("RttTex",
                    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,
                    (int)m_groundImage->getPixelSize().d_width, (int)m_groundImage->getPixelSize().d_height,
                    0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);
    m_renderTexture = texturePtr->getBuffer()->getRenderTarget();

    CEGUI::Texture  *cTex = static_cast<CEGUI::OgreCEGUIRenderer*>(CEGUI::System::getSingleton().getRenderer())->createTexture((CEGUI::utf8*)"RttTex");
    CEGUI::Imageset *imageSet = CEGUI::ImagesetManager::getSingleton().createImageset((CEGUI::utf8*)"RttImageset", cTex);
    imageSet->defineImage((CEGUI::utf8*)"RttImage",
        CEGUI::Point(0.0f, 0.0f),
        CEGUI::Size(cTex->getWidth(), cTex->getHeight()),
        CEGUI::Point(0.0f,0.0f));

    m_groundImage->setProperty(     "Image", CEGUI::PropertyHelper::imageToString(&imageSet->getImage((CEGUI::utf8*)"RttImage")));
    m_groundFrameImage->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet->getImage((CEGUI::utf8*)"RttImage")));
    m_groundFrameImage->disable();

    m_initiated = true;
}


void CSimulatorWindowHandler::leave()
{
    if(m_simulator != NULL) {
        delete m_simulator;
        m_simulator = NULL;
        m_logHistoryList->resetList();
        m_logHistoryListShort->resetList();
    }
}


void CSimulatorWindowHandler::update()
{
    static btVector3 ballPositionOld = m_simulator->getBallPosition();

    double currentTime = CGameEngine::getInstance()->getClock().getCurrentTime();
    double timeLapse = currentTime - m_previousUpdateTime;
    m_previousUpdateTime = currentTime;
    Ogre::Vector3 pos = m_cam3DNode->getPosition();
    if(pos.y <= 5 && m_direction.y < 0) {
        m_direction.y = 0;
    }
    m_cam3DNode->translate(m_direction * timeLapse, Ogre::Node::TS_LOCAL);

    btVector3 ballPosition = m_simulator->getBallPosition();
    ballPosition.setY(0.0);
    btVector3 lookAtPoint = ballPosition;
    lookAtPoint-=ballPositionOld;
    lookAtPoint/=50;
    lookAtPoint+=ballPositionOld;
    m_cam3D->lookAt(lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z());
    ballPositionOld = lookAtPoint;

    updateScore();
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
    unsigned int historySize = 7;
    unsigned int shortHistorySize = 3;
    std::ostringstream message;
    // If there's text then add it
    if(text.size()) {
        message << m_simulator->getReferee()->getMinute() << "' - " << text.c_str();
        // Add the Editbox text to the history Listbox
        CEGUI::ListboxTextItem* logItem;
        if(m_logHistoryList->getItemCount() == historySize) {
            /* We have reached the capacity of the Listbox so re-use the first Listbox item.
               This code is a little crafty.  By default the ListboxTextItem is created with
               the auto-delete flag set to true, which results in its automatic deletion when
               removed from the Listbox.  So we change that flag to false, extract the item
               from the Listbox, change its text, put the auto-delete flag back to true, and
               finally put the item back into the Listbox. */
            logItem = static_cast<CEGUI::ListboxTextItem*>(m_logHistoryList->getListboxItemFromIndex(0));
            logItem->setAutoDeleted(false);
            m_logHistoryList->removeItem(logItem);
            logItem->setAutoDeleted(true);
            logItem->setText((CEGUI::utf8*)message.str().c_str());
        } else {
            // Create a new listbox item
            logItem = new CEGUI::ListboxTextItem((CEGUI::utf8*)message.str().c_str());
        }
        m_logHistoryList->addItem(logItem);
        m_logHistoryList->ensureItemIsVisible(m_logHistoryList->getItemCount());

        if(m_logHistoryListShort->getItemCount() == shortHistorySize) {
            logItem = static_cast<CEGUI::ListboxTextItem*>(m_logHistoryListShort->getListboxItemFromIndex(0));
            logItem->setAutoDeleted(false);
            m_logHistoryListShort->removeItem(logItem);
            logItem->setAutoDeleted(true);
            logItem->setText((CEGUI::utf8*)message.str().c_str());
        } else {
            logItem = new CEGUI::ListboxTextItem((CEGUI::utf8*)message.str().c_str());
        }
        m_logHistoryListShort->addItem(logItem);
        m_logHistoryListShort->ensureItemIsVisible(m_logHistoryListShort->getItemCount());
    }
}


void CSimulatorWindowHandler::loadTeamPlayers()
{
    m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Name"), 0, CEGUI::UDim(1.0,0));
    m_teamPlayersList->resetList();

    CPfTeams                                *team               = m_game.getIDAOFactory()->getIPfTeamsDAO()->findByXTeam(m_game.getOptionManager()->getGamePlayerTeam());
    IPfTeamPlayersDAO                       *teamPlayersDAO     = m_game.getIDAOFactory()->getIPfTeamPlayersDAO();
    std::vector<CPfTeamPlayers*>            *teamPlayersList    = teamPlayersDAO->findLineUpByXFkTeam(team->getXTeam());
    std::vector<CPfTeamPlayers*>::iterator  it;

    int cont = 0;
    for( it=teamPlayersList->begin(); it!=teamPlayersList->end() && cont<11; it++ ){
        CPfTeamPlayers *teamPlayer = (*it);

        int row_idx = m_teamPlayersList->addRow();
        m_teamPlayersList->setItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)teamPlayer->getSName().c_str()), 0, row_idx);
        cont++;
    }
    teamPlayersDAO->freeVector(teamPlayersList);
    delete team;

    m_teamPlayersList->getHorzScrollbar()->setVisible(false);
}


void CSimulatorWindowHandler::toogleZoom()
{
    if(m_frameWindow->isVisible()) {
        m_frameWindow->setVisible(false);
        m_frameWindow->deactivate();
        m_frameWindow->disable();
        setup2DView();
    } else {
        m_frameWindow->setVisible(true);
        m_frameWindow->activate();
        m_frameWindow->enable();
    }
}


void CSimulatorWindowHandler::setup2DView()
{
    m_renderTexture->removeAllViewports();
    Ogre::Viewport *viewport = m_renderTexture->addViewport(m_cam2D);
    viewport->setOverlaysEnabled(false);
    viewport->setClearEveryFrame(true);
    viewport->setBackgroundColour(Ogre::ColourValue::Black);
}


void CSimulatorWindowHandler::updateScore()
{
    CReferee *referee = m_simulator->getReferee();
    int homeScore = referee->getHomeScore();
    int awayScore = referee->getAwayScore();
    std::ostringstream score;
    score << homeScore << " - " << awayScore;
    m_score->setText((CEGUI::utf8*)score.str().c_str());
    score.str("");
    score << homeScore;
    m_frameHomeScore->setText((CEGUI::utf8*)score.str().c_str());
    score.str("");
    score << awayScore;
    m_frameAwayScore->setText((CEGUI::utf8*)score.str().c_str());
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

bool CSimulatorWindowHandler::zoomButtonClicked(const CEGUI::EventArgs& e)
{
    toogleZoom();
    return true;
}

bool CSimulatorWindowHandler::formation433ButtonClicked(const CEGUI::EventArgs& e)
{
    m_simulator->changeFormationEvent(0);
    return true;
}

bool CSimulatorWindowHandler::formation442ButtonClicked(const CEGUI::EventArgs& e)
{
    m_simulator->changeFormationEvent(1);
    return true;
}

bool CSimulatorWindowHandler::frameWindowCloseClicked(const CEGUI::EventArgs& e)
{
    toogleZoom();
    return true;
}

bool CSimulatorWindowHandler::view2DButtonClicked(const CEGUI::EventArgs& e)
{
    setup2DView();
    return true;
}

bool CSimulatorWindowHandler::view3DButtonClicked(const CEGUI::EventArgs& e)
{
    m_renderTexture->removeAllViewports();
    Ogre::Viewport *viewport = m_renderTexture->addViewport(m_cam3D);
    viewport->setOverlaysEnabled(false);
    viewport->setClearEveryFrame(true);
    viewport->setBackgroundColour(Ogre::ColourValue::Black);

    return true;
}
