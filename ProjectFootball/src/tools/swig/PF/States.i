%module States

%{
#include "../engine/CScreenManager.h"
#include "../engine/CScreen.h"
#include "../engine/screen/CScreenMainMenu.h"
#include "../engine/screen/CScreenConfig.h"
#include "../engine/screen/CScreenCredits.h"
#include "../engine/screen/CScreenLoadGame.h"
#include "../singlePlayer/screen/CScreenSimulator.h"
#include "../singlePlayer/screen/CScreenGame.h"
#include "../singlePlayer/screen/CScreenSelectTeam.h"
#include "../singlePlayer/screen/CScreenRanking.h"
#include "../singlePlayer/screen/CScreenTeamPlayers.h"
#include "../singlePlayer/screen/CScreenQuickPlay.h"
#include "../singlePlayer/screen/CScreenResults.h"
#include "../singlePlayer/screen/CScreenMatchResult.h"
%}

%include "std_string.i"
%include "std_vector.i"

%include ../../../engine/CScreenManager.h
%include ../../../engine/CScreen.h
%include ../../../engine/screen/CScreenMainMenu.h
%include ../../../engine/screen/CScreenLoadGame.h
%include ../../../engine/screen/CScreenConfig.h
%include ../../../engine/screen/CScreenCredits.h
%include ../../../singlePlayer/screen/CScreenGame.h
%include ../../../singlePlayer/screen/CScreenSimulator.h
%include ../../../singlePlayer/screen/CScreenSelectTeam.h
%include ../../../singlePlayer/screen/CScreenRanking.h
%include ../../../singlePlayer/screen/CScreenTeamPlayers.h
%include ../../../singlePlayer/screen/CScreenQuickPlay.h
%include ../../../singlePlayer/screen/CScreenResults.h
%include ../../../singlePlayer/screen/CScreenMatchResult.h
