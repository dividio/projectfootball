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
#include <libintl.h>

// TODO: Remove CScreenManager dependency
#include "CScreenSimulator.h"
#include "../../engine/CScreenManager.h"
#include "../utils/CLog.h"
#include "../engine/CGameEngine.h"


CScreenSimulator::CScreenSimulator()
 :CScreen()
{
    CLog::getInstance()->debug("CScreenSimulator()");

    CEGUI::WindowManager *ceguiWM = &(CEGUI::WindowManager::getSingleton());
    m_sheet = ceguiWM->loadWindowLayout((CEGUI::utf8*)"simulator.layout");

    m_frameWindow               = static_cast<CEGUI::FrameWindow*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/FrameWindow"));
    m_logHistoryList            = static_cast<CEGUI::Listbox*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Log"));
    m_logHistoryListShort       = static_cast<CEGUI::Listbox*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Frame/Log"));
    m_teamPlayersList           = static_cast<CEGUI::MultiColumnList*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/TeamPlayersList"));
    m_groundImage               = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Image"));
    m_groundFrameImage          = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Frame/Image"));
    m_teamNames                 = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/TeamNames"));
    m_score                     = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Score"));
    m_frameHomeName             = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Frame/HomeName"));
    m_frameAwayName             = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Frame/AwayName"));
    m_frameHomeScore            = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Frame/HomeScore"));
    m_frameAwayScore            = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/Frame/AwayScore"));
    m_continueButton            = static_cast<CEGUI::PushButton*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/ContinueButton"));
    m_backButton                = static_cast<CEGUI::PushButton*>(ceguiWM->getWindow((CEGUI::utf8*)"Simulator/BackButton"));

    // i18n support
    m_frameWindow   ->setText((CEGUI::utf8*)gettext("Simulation View"));
    m_continueButton->setText((CEGUI::utf8*)gettext("Continue"));
    m_backButton    ->setText((CEGUI::utf8*)gettext("Back"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/StartButton"))->setText((CEGUI::utf8*)gettext("Start"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/ZoomButton"))->setText((CEGUI::utf8*)gettext("Zoom"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/TeamTab"))->setText((CEGUI::utf8*)gettext("Team"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/FormationTab"))->setText((CEGUI::utf8*)gettext("Formation"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/LogTab"))->setText((CEGUI::utf8*)gettext("Log"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/StatisticsTab"))->setText((CEGUI::utf8*)gettext("Statistics"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/Frame/2DButton"))->setText((CEGUI::utf8*)gettext("2D View"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/Frame/3DButton"))->setText((CEGUI::utf8*)gettext("3D View"));
    static_cast<CEGUI::Window*>(ceguiWM->getWindow(
            (CEGUI::utf8*)"Simulator/Frame/StartButton"))->setText((CEGUI::utf8*)gettext("Start"));

    m_direction = Ogre::Vector3::ZERO;

    m_sceneMgr = m_root->createSceneManager(Ogre::ST_GENERIC, "Simulation SceneManager");

    m_cam2D = m_sceneMgr->createCamera("2D_Camera");
    m_cam2D->setNearClipDistance(1);
    int width = 120;
    int height = 90;
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
    m_cam2D->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
    m_cam2D->setCustomProjectionMatrix(true, projectionMatrix);

    m_cam3D = m_sceneMgr->createCamera("3D_Camera");
    m_cam3D->setProjectionType(Ogre::PT_PERSPECTIVE);
    m_cam3D->setCustomProjectionMatrix(false);
    m_cam3D->setNearClipDistance(5);

    Ogre::TexturePtr texturePtr = Ogre::TextureManager::getSingleton().createManual("RttTex",
                    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,
                    (int)m_groundImage->getPixelSize().d_width, (int)m_groundImage->getPixelSize().d_height,
                    0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);
    m_renderTexture = texturePtr->getBuffer()->getRenderTarget();

    CEGUI::Texture  *cTex = m_renderer->createTexture((CEGUI::utf8*)"RttTex");
    CEGUI::Imageset *imageSet = CEGUI::ImagesetManager::getSingleton().createImageset((CEGUI::utf8*)"RttImageset", cTex);
    imageSet->defineImage((CEGUI::utf8*)"RttImage",
        CEGUI::Point(0.0f, 0.0f),
        CEGUI::Size(cTex->getWidth(), cTex->getHeight()),
        CEGUI::Point(0.0f,0.0f));

    m_groundImage->setProperty(     "Image", CEGUI::PropertyHelper::imageToString(&imageSet->getImage((CEGUI::utf8*)"RttImage")));
    m_groundFrameImage->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet->getImage((CEGUI::utf8*)"RttImage")));
    m_groundFrameImage->disable();

    CEGUI::Window *w = ceguiWM->getWindow("Simulator");
    w->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&CScreenSimulator::keyDownHandler, this));
    w->subscribeEvent(CEGUI::Window::EventKeyUp, CEGUI::Event::Subscriber(&CScreenSimulator::keyUpHandler, this));

    m_match = NULL;
}


CScreenSimulator* CScreenSimulator::getInstance()
{
    static CScreenSimulator instance;
    return &instance;
}


CScreenSimulator::~CScreenSimulator()
{
    CLog::getInstance()->debug("~CScreenSimulator()");
    if(m_simulator != NULL) {
        delete m_simulator;
    }
}


bool CScreenSimulator::keyDownHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& ke = static_cast<const CEGUI::KeyEventArgs&>(e);
    int move = 15;
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


bool CScreenSimulator::keyUpHandler(const CEGUI::EventArgs& e)
{
    const CEGUI::KeyEventArgs& ke = static_cast<const CEGUI::KeyEventArgs&>(e);
    int move = 15;
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
        if(m_direction.y = -move) {
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


void CScreenSimulator::enter()
{
    m_system->setGUISheet(m_sheet);
    m_sceneMgr->clearScene();
    m_direction = Ogre::Vector3::ZERO;

    m_continueButton->setEnabled(false);
    m_backButton->setEnabled(true);

    IDAOFactory *daoFactory = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory();
    IPfMatchesDAO *matchesDAO = daoFactory->getIPfMatchesDAO();
    m_match = matchesDAO->findNextPlayerTeamMatch();
    m_simulator = new CSimulationManager(m_match->getXMatch());
    m_sceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

    // create the 3D camera node/pitch node
    m_cam3DNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode("3D_Camera_Node", Ogre::Vector3(0, 25, 60));
    m_cam3DNode->pitch(Ogre::Degree(0));
    m_cam3DNode->attachObject(m_cam3D);

    // Create the 2D camera node and make it look towards origin
    m_cam2DNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode("2D_Camera_Node", Ogre::Vector3(0, 100, 0));
    m_cam2DNode->pitch(Ogre::Degree(-90));
    m_cam2DNode->attachObject(m_cam2D);

    switchTo2DView();
    loadTeamPlayers();
    IPfTeamsDAO *teamsDAO = daoFactory->getIPfTeamsDAO();
    std::string homeName = teamsDAO->findByXTeam(m_match->getXFkTeamHome())->getSTeam();
    std::string awayName = teamsDAO->findByXTeam(m_match->getXFkTeamAway())->getSTeam();
    char names[40];
    sprintf(names, "%s vs %s", homeName.c_str(), awayName.c_str());
    m_teamNames->setProperty("Text", names);
    m_score->setProperty("Text", "0 - 0");
    m_frameHomeName->setProperty("Text", homeName.c_str());
    m_frameAwayName->setProperty("Text", awayName.c_str());
    m_frameHomeScore->setProperty("Text", "0");
    m_frameAwayScore->setProperty("Text", "0");
}


void CScreenSimulator::forcedLeave()
{
    if(m_simulator != NULL) {
        delete m_simulator;
        m_simulator = NULL;
        m_logHistoryList->resetList();
    }
    if( m_match!=NULL ){
        delete m_match;
        m_match = NULL;
    }
}


bool CScreenSimulator::leave()
{
    if(m_simulator != NULL) {
        delete m_simulator;
        m_simulator = NULL;
        m_logHistoryList->resetList();
        m_logHistoryListShort->resetList();
    }
    if( m_match!=NULL ){
        delete m_match;
        m_match = NULL;
    }
    return true;
}


void CScreenSimulator::update()
{
    static btVector3 ballPositionOld = m_simulator->getBallPosition();

    float t = CScreenManager::getInstance()->getTimeSinceLastFrame();
    Ogre::Vector3 pos = m_cam3DNode->getPosition();
    if(pos.y <= 5 && m_direction.y < 0) {
        m_direction.y = 0;
    }
    m_cam3DNode->translate(m_direction * t, Ogre::Node::TS_LOCAL);

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


void CScreenSimulator::toogleSimulationView()
{
    if(m_frameWindow->isVisible()) {
        m_frameWindow->setVisible(false);
        m_frameWindow->deactivate();
        m_frameWindow->disable();
        switchTo2DView();
    } else {
        m_frameWindow->setVisible(true);
        m_frameWindow->activate();
        m_frameWindow->enable();
    }
}


void CScreenSimulator::switchTo2DView()
{
    m_renderTexture->removeAllViewports();
    Ogre::Viewport *viewport = m_renderTexture->addViewport(m_cam2D);
    viewport->setOverlaysEnabled(false);
    viewport->setClearEveryFrame(true);
    viewport->setBackgroundColour(Ogre::ColourValue::Black);
}


void CScreenSimulator::switchTo3DView()
{
    m_renderTexture->removeAllViewports();
    Ogre::Viewport *viewport = m_renderTexture->addViewport(m_cam3D);
    viewport->setOverlaysEnabled(false);
    viewport->setClearEveryFrame(true);
    viewport->setBackgroundColour(Ogre::ColourValue::Black);
}


CSimulationManager* CScreenSimulator::getSimulationManager()
{
    return m_simulator;
}


Ogre::SceneManager* CScreenSimulator::getSimulationSceneManager()
{
    return m_sceneMgr;
}


void CScreenSimulator::addToLog(std::string text)
{
    int historySize = 7;
    int shortHistorySize = 3;
    char message[30];
    // If there's text then add it
    if(text.size()) {
        sprintf(message,"%d' - %s", m_simulator->getReferee()->getMinute(), text.c_str());
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
            logItem->setText(message);
        } else {
            // Create a new listbox item
            logItem = new CEGUI::ListboxTextItem(message);
        }
        m_logHistoryList->addItem(logItem);
        m_logHistoryList->ensureItemIsVisible(m_logHistoryList->getItemCount());

        if(m_logHistoryListShort->getItemCount() == shortHistorySize) {
            logItem = static_cast<CEGUI::ListboxTextItem*>(m_logHistoryListShort->getListboxItemFromIndex(0));
            logItem->setAutoDeleted(false);
            m_logHistoryListShort->removeItem(logItem);
            logItem->setAutoDeleted(true);
            logItem->setText(message);
        } else {
            logItem = new CEGUI::ListboxTextItem(message);
        }
        m_logHistoryListShort->addItem(logItem);
        m_logHistoryListShort->ensureItemIsVisible(m_logHistoryListShort->getItemCount());
    }
}


void CScreenSimulator::loadTeamPlayers()
{
    m_teamPlayersList->addColumn((CEGUI::utf8*)gettext("Name"), 0, CEGUI::UDim(1.0,0));
    m_teamPlayersList->resetList();

    CPfTeams                                *team               = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayersDAO                       *teamPlayersDAO     = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamPlayersDAO();
    std::vector<CPfTeamPlayers*>            *teamPlayersList    = teamPlayersDAO->findLineUpByXFkTeam(team->getXTeam());
    std::vector<CPfTeamPlayers*>::iterator  it;

    int cont = 0;
    for( it=teamPlayersList->begin(); it!=teamPlayersList->end() && cont<11; it++ ){
        CPfTeamPlayers *teamPlayer = (*it);

        int row_idx = m_teamPlayersList->addRow();
        m_teamPlayersList->setItem(new CEGUI::ListboxTextItem(teamPlayer->getSName()), 0, row_idx);
        cont++;
    }
    teamPlayersDAO->freeVector(teamPlayersList);
    delete team;

    m_teamPlayersList->getHorzScrollbar()->setVisible(false);
}


void CScreenSimulator::updateScore()
{
    CReferee *referee = m_simulator->getReferee();
    int homeScore = referee->getHomeScore();
    int awayScore = referee->getAwayScore();
    char score[8];
    sprintf(score, "%d - %d", homeScore, awayScore);
    m_score->setProperty("Text", score);
    sprintf(score, "%d", homeScore);
    m_frameHomeScore->setProperty("Text", score);
    sprintf(score, "%d", awayScore);
    m_frameAwayScore->setProperty("Text", score);
}


void CScreenSimulator::endMatchEvent()
{
    //TODO Check if game mode is QuickPlay
    //m_backButton->setEnabled(false);
    m_continueButton->setEnabled(true);
}
