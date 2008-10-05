%module DAO

%{
#include "../singlePlayer/db/bean/CPfTeams.h"
#include "../singlePlayer/db/bean/CPfMatches.h"
#include "../singlePlayer/db/bean/CPfGoals.h"
#include "../singlePlayer/db/dao/factory/IDAOFactory.h"
#include "../singlePlayer/db/dao/IPfTeamsDAO.h"
#include "../singlePlayer/db/dao/IPfMatchesDAO.h"
#include "../singlePlayer/db/dao/IPfGoalsDAO.h"
%}

%include "std_string.i"
%include "std_vector.i"

%include ../../../singlePlayer/db/bean/CPfTeams.h
%include ../../../singlePlayer/db/bean/CPfMatches.h
%include ../../../singlePlayer/db/bean/CPfGoals.h
%include ../../../singlePlayer/db/dao/factory/IDAOFactory.h
%include ../../../singlePlayer/db/dao/IPfTeamsDAO.h
%include ../../../singlePlayer/db/dao/IPfMatchesDAO.h
%include ../../../singlePlayer/db/dao/IPfGoalsDAO.h
