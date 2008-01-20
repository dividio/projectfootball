%module DAO

%{
#include "../db/CDAOAbstractFactory.h"
#include "../db/bean/CPfEquipos.h"
#include "../db/dao/factory/IDAOFactory.h"
#include "../db/dao/IPfEquiposDAO.h"
%}

%include "std_string.i"
%include "std_vector.i"

%include ../../../db/CDAOAbstractFactory.h
%include ../../../db/bean/CPfEquipos.h
%include ../../../db/dao/factory/IDAOFactory.h
%include ../../../db/dao/IPfEquiposDAO.h
