%module DAO

%{
#include "../db/CDAOAbstractFactory.h"
#include "../db/bean/CPfTeams.h"
#include "../db/bean/CPfMatches.h"
#include "../db/bean/CPfGoals.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../db/dao/IPfTeamsDAO.h"
#include "../db/dao/IPfMatchesDAO.h"
#include "../db/dao/IPfGoalsDAO.h"
%}

%include "std_string.i"
%include "std_vector.i"

%include ../../../db/CDAOAbstractFactory.h
%include ../../../db/bean/CPfTeams.h
%include ../../../db/bean/CPfMatches.h
%include ../../../db/bean/CPfGoals.h
%include ../../../db/dao/factory/IDAOFactory.h
%include ../../../db/dao/IPfTeamsDAO.h
%include ../../../db/dao/IPfMatchesDAO.h
%include ../../../db/dao/IPfGoalsDAO.h
