%module States

%{
#include "../state/CStateManager.h"
#include "../state/CState.h"
#include "../state/CStateMainMenu.h"
#include "../state/CStateMonitor.h"
#include "../state/CStateCredits.h"
#include "../state/CStateGame.h"
#include "../state/CStateLoadGame.h"
#include "../state/CStateConfig.h"
#include "../state/CStateSelectTeam.h"
#include "../state/CStateRanking.h"
#include "../state/CStateTeamPlayers.h"
#include "../state/CStateQuickPlay.h"
#include "../state/CStateResults.h"
%}

%include "std_string.i"
%include "std_vector.i"

%include ../../../state/CStateManager.h
%include ../../../state/CState.h
%include ../../../state/CStateMainMenu.h
%include ../../../state/CStateMonitor.h
%include ../../../state/CStateCredits.h
%include ../../../state/CStateGame.h
%include ../../../state/CStateLoadGame.h
%include ../../../state/CStateConfig.h
%include ../../../state/CStateSelectTeam.h
%include ../../../state/CStateRanking.h
%include ../../../state/CStateTeamPlayers.h
%include ../../../state/CStateQuickPlay.h
%include ../../../state/CStateResults.h
