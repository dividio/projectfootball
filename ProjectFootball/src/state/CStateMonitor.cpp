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

    CEGUI::WindowManager *ceguiWM = &(CEGUI::WindowManager::getSingleton());

    m_sheet = ceguiWM->loadWindowLayout((CEGUI::utf8*)"monitor.layout");

    m_frameWindow       = static_cast<CEGUI::FrameWindow*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/FrameWindow"));
    m_logHistoryList    = static_cast<CEGUI::Listbox*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Log"));
    m_logHistoryListShort    = static_cast<CEGUI::Listbox*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Frame/Log"));
    m_teamPlayersList   = static_cast<CEGUI::MultiColumnList*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/TeamPlayersList"));
    m_groundImage       = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Image"));
    m_groundFrameImage  = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Frame/Image"));
    m_teamNames  = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/TeamNames"));
    m_score  = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Score"));
    m_frameHomeName  = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Frame/HomeName"));
    m_frameAwayName  = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Frame/AwayName"));
    m_frameHomeScore  = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Frame/HomeScore"));
    m_frameAwayScore  = static_cast<CEGUI::Window*>(ceguiWM->getWindow((CEGUI::utf8*)"Monitor/Frame/AwayScore"));

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

    m_renderTexture = m_root->getRenderSystem()->createRenderTexture("RttTex", (int)m_groundImage->getPixelSize().d_width, (int)m_groundImage->getPixelSize().d_height, Ogre::TEX_TYPE_2D, Ogre::PF_R8G8B8);

    CEGUI::Texture  *cTex = m_renderer->createTexture((CEGUI::utf8*)"RttTex");
    CEGUI::Imageset *imageSet = CEGUI::ImagesetManager::getSingleton().createImageset((CEGUI::utf8*)"RttImageset", cTex);
    imageSet->defineImage((CEGUI::utf8*)"RttImage",
        CEGUI::Point(0.0f, 0.0f),
        CEGUI::Size(cTex->getWidth(), cTex->getHeight()),
        CEGUI::Point(0.0f,0.0f));

    m_groundImage->setProperty(     "Image", CEGUI::PropertyHelper::imageToString(&imageSet->getImage((CEGUI::utf8*)"RttImage")));
    m_groundFrameImage->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet->getImage((CEGUI::utf8*)"RttImage")));
    m_groundFrameImage->disable();

    CEGUI::Window *w = ceguiWM->getWindow("Monitor");
    w->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&CStateMonitor::keyDownHandler, this));
    w->subscribeEvent(CEGUI::Window::EventKeyUp, CEGUI::Event::Subscriber(&CStateMonitor::keyUpHandler, this));

    m_match = NULL;
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


bool CStateMonitor::keyUpHandler(const CEGUI::EventArgs& e)
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
        m_direction.y += move;
        break;
    case CEGUI::Key::PageUp:
        m_direction.y -= move;
        break;
    default:
        return false;
    }
    return true;
}


void CStateMonitor::enter()
{
    m_system->setGUISheet(m_sheet);
    m_sceneMgr->clearScene();

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
    m_score->setProperty("Text", "  0 - 0");
    m_frameHomeName->setProperty("Text", homeName.c_str());
    m_frameAwayName->setProperty("Text", awayName.c_str());
    m_frameHomeScore->setProperty("Text", "  0");
    m_frameAwayScore->setProperty("Text", "  0");
}


void CStateMonitor::forcedLeave()
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


bool CStateMonitor::leave()
{
    simulateOthersMatches();

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


void CStateMonitor::update()
{
    static btVector3 ballPositionOld = m_simulator->getBallPosition();

    float t = CStateManager::getInstance()->getTimeSinceLastFrame();
    m_cam3DNode->translate(m_direction * t, Ogre::Node::TS_LOCAL);

    btVector3 ballPosition = m_simulator->getBallPosition();
    btVector3 lookAtPoint = ballPosition;
    lookAtPoint-=ballPositionOld;
    lookAtPoint/=50;
    lookAtPoint+=ballPositionOld;
    m_cam3D->lookAt(lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z());
    ballPositionOld = lookAtPoint;

    updateScore();
    m_simulator->update();
}


void CStateMonitor::toogleSimulationView()
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


void CStateMonitor::switchTo2DView()
{
    m_renderTexture->removeAllViewports();
    Ogre::Viewport *viewport = m_renderTexture->addViewport(m_cam2D);
    viewport->setOverlaysEnabled(false);
    viewport->setClearEveryFrame(true);
    viewport->setBackgroundColour(Ogre::ColourValue::Black);
}


void CStateMonitor::switchTo3DView()
{
    m_renderTexture->removeAllViewports();
    Ogre::Viewport *viewport = m_renderTexture->addViewport(m_cam3D);
    viewport->setOverlaysEnabled(false);
    viewport->setClearEveryFrame(true);
    viewport->setBackgroundColour(Ogre::ColourValue::Black);
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
    int historySize = 6;
    int shortHistorySize = 2;
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


void CStateMonitor::loadTeamPlayers()
{
    m_teamPlayersList->addColumn("Name", 0, CEGUI::UDim(1.0,0));
    m_teamPlayersList->resetList();

    CPfTeams                                *team               = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamsDAO()->findPlayerTeam();
    IPfTeamPlayersDAO                       *teamPlayersDAO     = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamPlayersDAO();
    std::vector<CPfTeamPlayers*>            *teamPlayersList    = teamPlayersDAO->findActiveTeamPlayersByXFkTeam(team->getXTeam());
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


void CStateMonitor::updateScore()
{
    CReferee *referee = m_simulator->getReferee();
    int homeScore = referee->getHomeScore();
    int awayScore = referee->getAwayScore();
    char score[8];
    sprintf(score, "  %d - %d", homeScore, awayScore);
    m_score->setProperty("Text", score);
    sprintf(score, "  %d", homeScore);
    m_frameHomeScore->setProperty("Text", score);
    sprintf(score, "  %d", awayScore);
    m_frameAwayScore->setProperty("Text", score);
}


void CStateMonitor::simulateOthersMatches()
{
    if( m_match!=NULL ){
        srand(time(NULL));

        IPfMatchesDAO       *matchesDAO     = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfMatchesDAO();
        IPfTeamPlayersDAO   *teamPlayersDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamPlayersDAO();

        std::vector<CPfMatches*>*           matchesList = matchesDAO->findByXFkCompetitionPhase(m_match->getXFkCompetitionPhase());
        std::vector<CPfMatches*>::iterator  it;
        for( it=matchesList->begin(); it!=matchesList->end(); it++ ){
            CPfMatches *match = (*it);
            if( match->getXMatch()!=m_match->getXMatch() ){
                CStartMatchEvent    startMatchEvent(match->getXMatch());
                CGameEngine::getInstance()->getCurrentGame()->getIGameEventStrategy()->process(startMatchEvent);

                int nHomeGoals = getRandomNGoals();
                int nAwayGoals = getRandomNGoals();

                if( nHomeGoals>0 ){
                    std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findActiveTeamPlayersByXFkTeam(match->getXFkTeamHome());
                    while( nHomeGoals>0 ){
                        CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](rand()%teamPlayesList->size());
                        CGoalMatchEvent goalMatchEvent(match->getXMatch(), match->getXFkTeamHome(), teamPlayer->getXTeamPlayer(), rand()%90, false);
                        CGameEngine::getInstance()->getCurrentGame()->getIGameEventStrategy()->process(goalMatchEvent);
                        nHomeGoals--;
                    }
                    teamPlayersDAO->freeVector(teamPlayesList);
                }
                if( nAwayGoals>0 ){
                    std::vector<CPfTeamPlayers*>* teamPlayesList = teamPlayersDAO->findActiveTeamPlayersByXFkTeam(match->getXFkTeamAway());
                    while( nAwayGoals>0 ){
                        CPfTeamPlayers *teamPlayer = teamPlayesList->operator[](rand()%teamPlayesList->size());
                        CGoalMatchEvent goalMatchEvent(match->getXMatch(), match->getXFkTeamAway(), teamPlayer->getXTeamPlayer(), rand()%90, false);
                        CGameEngine::getInstance()->getCurrentGame()->getIGameEventStrategy()->process(goalMatchEvent);
                        nAwayGoals--;
                    }
                    teamPlayersDAO->freeVector(teamPlayesList);
                }

                CEndMatchEvent      endMatchEvent(match->getXMatch());
                CGameEngine::getInstance()->getCurrentGame()->getIGameEventStrategy()->process(endMatchEvent);
            }
        }
        matchesDAO->freeVector(matchesList);
    }
}

int CStateMonitor::getRandomNGoals()
{
    int n = rand()%100;

    if( n>=0  && n<15  ){ return 0; }
    if( n>=15 && n<50  ){ return 1; }
    if( n>=50 && n<90  ){ return 2; }
    if( n>=90 && n<100 ){ return 3; }
}
