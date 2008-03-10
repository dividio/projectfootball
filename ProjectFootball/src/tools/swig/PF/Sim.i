%module Sim

%{
#include "../sim/CSimulationManager.h"
#include "../sim/CSteeringBehaviors.h"
#include "../sim/message/CMessage.h"
#include "../sim/message/MessageTypes.h"
#include "../sim/message/CMessageDispatcher.h"
#include "../sim/fsm/CStateMachine.h"
#include "../sim/entity/CReferee.h"
#include "../sim/entity/CTeam.h"
#include "../sim/entity/CFootballPlayer.h"
#include "../sim/entity/CBaseGameEntity.h"
#include "../sim/entity/CBaseAgent.h"
#include "../sim/entity/CBall.h"
#include "../sim/entity/CMovingEntity.h"
#include "../sim/entity/CEntityManager.h"
%}

%include "std_string.i"
%include "std_vector.i"
%include "class_p.i"


// Messages
ADD_CLASS_P_CTOR (CMessage);
%include "../../../sim/message/CMessage.h"
%include "../../../sim/message/MessageTypes.h"
%include "../../../sim/message/CMessageDispatcher.h"
//void CMessageDispatcher::dispatchMsg(double delay, int sender, int receiver, int msg, void *info);
//static CMessageDispatcher* CMessageDispatcher::getInstance();

// Simulation Manager
%include "../../../sim/CSimulationManager.h"
%include "../../../sim/CSteeringBehaviors.h"
%include "../../../sim/entity/CBaseGameEntity.h"
%include "../../../sim/entity/CMovingEntity.h"
%include "../../../sim/entity/CBaseAgent.h"
%include "../../../sim/entity/CEntityManager.h"
%include "../../../sim/entity/CBall.h"

ADD_CLASS_P_CTOR (CReferee);
%include "../../../sim/entity/CReferee.h"
ADD_CLASS_P_CTOR (CTeam);
%include "../../../sim/entity/CTeam.h"
ADD_CLASS_P_CTOR (CFootballPlayer);
%include "../../../sim/entity/CFootballPlayer.h"
namespace std {
   %template(PlayerVector) vector<CFootballPlayer*>;
};

// State Machine
%include "../../../sim/fsm/CStateMachine.h"
%template(StateMachineCReferee) CStateMachine<CReferee>;
%template(StateMachineCTeam) CStateMachine<CTeam>;
%template(StateMachineCFootballPlayer) CStateMachine<CFootballPlayer>;


