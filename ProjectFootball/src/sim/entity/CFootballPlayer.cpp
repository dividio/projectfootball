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


#include "CFootballPlayer.h"
#include "../CSimulationManager.h"
#include "CTeam.h"
#include "CReferee.h"
#include "../../state/CStateMonitor.h"
#include "../db/dao/IPfTeamPlayersDAO.h"
#include "../engine/CGameEngine.h"


char* CFootballPlayer::m_pCtorName = "CFootballPlayer_p_ctor";

CFootballPlayer* CFootballPlayer::getPlayer(CBaseGameEntity *player)
{
    return (CFootballPlayer*) player;
}


CFootballPlayer::CFootballPlayer(int XTeamPlayer, int number, CTeam *team, bool sideLeft)
:CBaseAgent()
{
    Ogre::SceneManager *scnMgr = CStateMonitor::getInstance()->getSimulationSceneManager();
    IPfTeamPlayersDAO *teamPlayersDAO = CGameEngine::getInstance()->getCurrentGame()->getIDAOFactory()->getIPfTeamPlayersDAO();
    m_teamPlayer = teamPlayersDAO->findByXTeamPlayer(XTeamPlayer);
    m_stateMachine = new CStateMachine<CFootballPlayer>(this);
    Ogre::String id;
    char charId[20];
    m_centerOfMassOffset.setOrigin(btVector3(0,-0.9,0));
    m_sideLeft = sideLeft;
    m_team = team;
    m_number = number; //TODO
    m_lastKickBallCycle = -1;

    //m_direction.normalize();
    sprintf(charId,"%s%d", team->getName().c_str(), m_number);
    id = charId;
    m_entity = scnMgr->createEntity("Cylinder"+id, "Cylinder.mesh");
    if(sideLeft) {
        if(m_number == 1) {
            m_entity->setMaterialName("goalie_red");
        } else {
            m_entity->setMaterialName("player_red");
        }
    } else {
        if(m_number == 1) {
            m_entity->setMaterialName("goalie_yellow");
        } else {
            m_entity->setMaterialName("player_yellow");
        }
    }
    btVector3 *initialPos = team->getPlayerStrategicPosition(m_number)->getInitialPosition();
    btVector3 pos(initialPos->x(), initialPos->y(), initialPos->z());
    if(!m_sideLeft) {
        pos.setX(-pos.x());
        pos.setZ(-pos.z());
    }
    m_node = scnMgr->getRootSceneNode()->createChildSceneNode("PlayerNode"+id, Ogre::Vector3(pos.x(), pos.y(), pos.z()));
    m_node->attachObject(m_entity);
    m_shape = new btCylinderShape(btVector3(btScalar(0.5),btScalar(0.9),btScalar(0.5)));
    btScalar mass(70.0);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0,0,0);
    if (isDynamic)
        m_shape->calculateLocalInertia(mass,localInertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,this,m_shape,localInertia);
    m_body = new btRigidBody(rbInfo);
    m_body->setAngularFactor(btScalar(0));
    m_body->setActivationState(DISABLE_DEACTIVATION);

    m_steeringBehavior = new CSteeringBehaviors(this);


    //Draw Circle
    Ogre::ManualObject * circle = scnMgr->createManualObject("circle_name"+id);

    float const radius = 1.5,
                thickness = 0.7, // Of course this must be less than the radius value.
                accuracy = 5,
                height = 0.01;

    Ogre::MaterialPtr matptr;
    Ogre::Pass* pass;

    if(sideLeft) {
        matptr = Ogre::MaterialManager::getSingleton().createOrRetrieve("Red"+id, "General").first;
        matptr->setReceiveShadows(true);
        pass = matptr->getTechnique(0)->getPass(0);
        Ogre::ColourValue colour = Ogre::ColourValue::Red;
        pass->setDiffuse(colour);
        pass->setAmbient(colour);
        pass->setSpecular(colour);
        pass->setSelfIllumination(colour);
        //pass->setEmissive(ColourValue(0,0,0,colour.a));
        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        pass->setDepthWriteEnabled(false);
    } else {
        matptr = Ogre::MaterialManager::getSingleton().createOrRetrieve("Blue"+id, "General").first;
        matptr->setReceiveShadows(true);
        pass = matptr->getTechnique(0)->getPass(0);
        Ogre::ColourValue colour = Ogre::ColourValue::Blue;
        pass->setDiffuse(colour);
        pass->setAmbient(colour);
        pass->setSpecular(colour);
        pass->setSelfIllumination(colour);
        //pass->setEmissive(ColourValue(0,0,0,colour.a));
        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        pass->setDepthWriteEnabled(false);
    }
    circle->begin(matptr->getName(), Ogre::RenderOperation::OT_TRIANGLE_LIST);

    unsigned point_index = 0;
    for(float theta = 0; theta <= 2 * Ogre::Math::PI; theta += Ogre::Math::PI / (radius * accuracy)) {
        circle->position(radius * cos(theta),
                         height,
                         radius * sin(theta));
        circle->position(radius * cos(theta - Ogre::Math::PI / (radius * accuracy)),
                         height,
                         radius * sin(theta - Ogre::Math::PI / (radius * accuracy)));
        circle->position((radius - thickness) * cos(theta - Ogre::Math::PI / (radius * accuracy)),
                         height,
                         (radius - thickness) * sin(theta - Ogre::Math::PI / (radius * accuracy)));
        circle->position((radius - thickness) * cos(theta),
                         height,
                         (radius - thickness) * sin(theta));
        // Join the 4 vertices created above to form a quad.
        circle->quad(point_index, point_index + 1, point_index + 2, point_index + 3);
        point_index += 4;
    }

    circle->end();

    m_ringNode = m_node->createChildSceneNode();
    m_ringNode->attachObject(circle);
}


CFootballPlayer::~CFootballPlayer()
{
    delete m_teamPlayer;
}


bool CFootballPlayer::handleMessage(const CMessage &msg)
{
    return m_stateMachine->handleMessage(msg);
}


void CFootballPlayer::update()
{
    m_canDoActions = true;
    CSimulationManager *simulator = CStateMonitor::getInstance()->getSimulationManager();
    CReferee *referee = simulator->getReferee();
    GameMode mode = referee->getGameMode();
    m_steeringBehavior->setTargetEntity(simulator->getBall());
    m_heading = m_body->getLinearVelocity().normalized();
    m_side = btVector3(-(m_heading.z()), m_heading.y(), m_heading.getX());
    m_stateMachine->update();
}


CStateMachine<CFootballPlayer>* CFootballPlayer::getFSM()
{
    return m_stateMachine;
}


bool CFootballPlayer::canDoActions()
{
    bool aux = m_canDoActions;
    m_canDoActions = false;
    return aux;
}


bool CFootballPlayer::canKickBall(int cycle)
{
    if((cycle - m_lastKickBallCycle) > 3) {
        m_lastKickBallCycle = cycle;
        return true;
    }
    return false;
}


bool CFootballPlayer::atHome()
{
    bool result = false;
    btVector3 actualPos = getPosition();
    if(actualPos.distance(getStrategicPosition()) < 0.5) {
        result = true;
    }
    return result;
}


bool CFootballPlayer::atKickPosition()
{
    bool result = false;
    CSimulationManager *simulator = CStateMonitor::getInstance()->getSimulationManager();
    btVector3 actualPos = getPosition();
    if(actualPos.distance(simulator->getBallPosition()) < 2.5) {
        result = true;
    }
    return result;
}


btVector3 CFootballPlayer::getStrategicPosition() const
{
    CSimulationManager *sim = CStateMonitor::getInstance()->getSimulationManager();
    CStrategicPosition *strPos = m_team->getPlayerStrategicPosition(m_number);
    btVector3 *initialPos = strPos->getCurrentPosition();
    CRectangle *area = strPos->getPlayingArea();
    btVector3 pos(initialPos->x(), initialPos->y(), initialPos->z());
    btVector3 ballPos = sim->getBallPosition();
    double x, z, maxX, maxZ, minX, minZ;

    if(!m_sideLeft) {
        pos.setX(-pos.x());
        pos.setZ(-pos.z());
        maxX = - area->getBottomRight()->x();
        minX = - area->getTopLeft()->x();
        maxZ = - area->getTopLeft()->z();
        minZ = - area->getBottomRight()->z();
    } else {
        maxX = area->getTopLeft()->x();
        minX = area->getBottomRight()->x();
        maxZ = area->getBottomRight()->z();
        minZ = area->getTopLeft()->z();
    }

    if(strPos->getBehindBall() == true && x > ballPos.x()) {
        maxX = ballPos.x();
    }

    x = pos.x() + ballPos.x() * strPos->getAttractionX();
    z = pos.z() + ballPos.z() * strPos->getAttractionZ();

    if(x > maxX) {
        x = maxX;
    }
    if(x < minX) { //minX have preference
        x = minX;
    }
    if(z > maxZ) {
        z = maxZ;
    } else if(z < minZ) {
        z = minZ;
    }
    pos.setX(btScalar(x));
    pos.setZ(btScalar(z));

    return pos;
}


CTeam* CFootballPlayer::getTeam() const
{
    return m_team;
}


int CFootballPlayer::getXTeamPlayer()
{
    return m_teamPlayer->getXTeamPlayer();
}


CSteeringBehaviors* CFootballPlayer::getSteering() const
{
    return m_steeringBehavior;
}


bool CFootballPlayer::isTeamLeft() const
{
    return m_sideLeft;
}


bool CFootballPlayer::isBallKickable() const
{
    CSimulationManager *simulator = CStateMonitor::getInstance()->getSimulationManager();
    return (getPosition().distance(simulator->getBallPosition()) < 2.2);
}


void CFootballPlayer::changeSide()
{
    CSimulationManager *simulator = CStateMonitor::getInstance()->getSimulationManager();
    m_sideLeft = !m_sideLeft;
    btVector3 pos = getStrategicPosition();
    simulator->move(this, (int)pos.x(), (int)pos.z());
}


//synchronizes world transform from physics to user
//Bullet only calls the update of worldtransform for active objects
void CFootballPlayer::setWorldTransform(const btTransform& centerOfMassWorldTrans)
{
    setGraphicTrans(centerOfMassWorldTrans * m_centerOfMassOffset);
}

void CFootballPlayer::setGraphicTrans(btTransform trans)
{
    btVector3 v = trans.getOrigin();
    btScalar y = v.getY();
    m_node->setPosition(v.getX(), y, v.getZ());
    m_ringNode->setPosition(0, -y+0.01, 0);

    btQuaternion q = trans.getRotation();
    m_node->setOrientation(q.w(), q.x(), q.y(), q.z());
}

