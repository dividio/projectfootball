%module States

%{
#include "../state/CStateManager.h"
#include "../state/CState.h"
#include "../state/CStateMainMenu.h"
#include "../state/CStateMonitor.h"
#include "../state/CStateCredits.h"
#include "../state/CStateGame.h"
#include "../state/CStateLoadGame.h"
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
