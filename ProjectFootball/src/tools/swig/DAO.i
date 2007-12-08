%module DAO

%{
#include "../db/CDAOAbstractFactory.h"
#include "../db/CPfEquipos.h"
#include "../db/IDAOFactory.h"
#include "../db/IPfEquiposDAO.h"
%}

%include "std_string.i"
%include "std_vector.i"

%include ../../db/CDAOAbstractFactory.h
%include ../../db/CPfEquipos.h
%include ../../db/IDAOFactory.h
%include ../../db/IPfEquiposDAO.h