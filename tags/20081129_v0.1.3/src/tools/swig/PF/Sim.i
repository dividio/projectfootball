%module Sim

%{
#include "../singlePlayer/sim/CSimulationManager.h"
#include "../singlePlayer/sim/CSteeringBehaviors.h"
#include "../singlePlayer/sim/message/CMessage.h"
#include "../singlePlayer/sim/message/MessageTypes.h"
#include "../singlePlayer/sim/message/CMessageDispatcher.h"
#include "../singlePlayer/sim/fsm/CStateMachine.h"
#include "../singlePlayer/sim/entity/CReferee.h"
#include "../singlePlayer/sim/entity/CTeam.h"
#include "../singlePlayer/sim/entity/CFootballPlayer.h"
#include "../singlePlayer/sim/entity/CBaseGameEntity.h"
#include "../singlePlayer/sim/entity/CBall.h"
#include "../singlePlayer/sim/entity/CMovingEntity.h"
#include "../singlePlayer/sim/entity/CEntityManager.h"
#include "../singlePlayer/sim/tactic/CFormation.h"
#include "../singlePlayer/sim/tactic/CStrategicPosition.h"
#include "../utils/geometry/CRectangle.h"
#include "../utils/geometry/CLine2D.h"
%}

%include "std_string.i"
%include "std_vector.i"
%include "class_p.i"


// Messages
ADD_CLASS_P_CTOR (CMessage);
%include "../../../singlePlayer/sim/message/CMessage.h"
%include "../../../singlePlayer/sim/message/MessageTypes.h"
%include "../../../singlePlayer/sim/message/CMessageDispatcher.h"
//void CMessageDispatcher::dispatchMsg(double delay, int sender, int receiver, int msg, void *info);
//static CMessageDispatcher* CMessageDispatcher::getInstance();

// Simulation Manager
%include "../../../singlePlayer/sim/CSimulationManager.h"
%include "../../../singlePlayer/sim/CSteeringBehaviors.h"
%include "../../../singlePlayer/sim/entity/CBaseGameEntity.h"
%include "../../../singlePlayer/sim/entity/CMovingEntity.h"
%include "../../../singlePlayer/sim/entity/CEntityManager.h"
%include "../../../singlePlayer/sim/entity/CBall.h"

ADD_CLASS_P_CTOR (CReferee);
%include "../../../singlePlayer/sim/entity/CReferee.h"
ADD_CLASS_P_CTOR (CTeam);
%include "../../../singlePlayer/sim/entity/CTeam.h"
ADD_CLASS_P_CTOR (CFootballPlayer);
%include "../../../singlePlayer/sim/entity/CFootballPlayer.h"
namespace std {
   %template(PlayerVector) vector<CFootballPlayer*>;
};

// State Machine
%include "../../../singlePlayer/sim/fsm/CStateMachine.h"
%template(StateMachineCReferee) CStateMachine<CReferee>;
%template(StateMachineCTeam) CStateMachine<CTeam>;
%template(StateMachineCFootballPlayer) CStateMachine<CFootballPlayer>;

// Tactic
%include "../../../singlePlayer/sim/tactic/CFormation.h"
namespace std {
   %template(FormationVector) vector<CFormation*>;
};
%include "../../../singlePlayer/sim/tactic/CStrategicPosition.h"
%include "../../../utils/geometry/CRectangle.h"
%include "../../../utils/geometry/CLine2D.h"
