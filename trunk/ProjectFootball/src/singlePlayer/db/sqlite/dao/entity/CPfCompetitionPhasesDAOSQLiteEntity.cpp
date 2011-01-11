/******************************************************************************
* Copyright (C) 2010 - Ikaro Games   www.ikarogames.com                       *
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
*       generated by dia/DAOcodegen.py                                        *
*       Version: 1.23                                                         *
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "CPfCompetitionPhasesDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfCompetitionPhasesDAOSQLiteEntity::CPfCompetitionPhasesDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfCompetitionPhasesDAOSQLiteEntity::~CPfCompetitionPhasesDAOSQLiteEntity()
{
}

void CPfCompetitionPhasesDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfCompetitionPhasesDAOSQLiteEntity::deleteReg(CPfCompetitionPhases *reg)
{
    std::string sql("DELETE FROM PF_COMPETITION_PHASES WHERE X_COMPETITION_PHASE=");
    sql += "'"+reg->getXCompetitionPhase_str()+"'";
    return exec(sql);
}

bool CPfCompetitionPhasesDAOSQLiteEntity::insertReg(CPfCompetitionPhases *reg)
{
    std::string sql("INSERT INTO PF_COMPETITION_PHASES (N_NUMBER_TEAMS,S_COMPETITION_PHASE,X_FK_COMPETITION,N_ORDER,X_FK_PHASE_TYPE) VALUES (");
    sql += (reg->getNNumberTeams_str()=="")?"NULL":"'"+reg->getNNumberTeams_str()+"'";
    sql += (reg->getSCompetitionPhase_str()=="")?",NULL":",'"+reg->getSCompetitionPhase_str()+"'";
    sql += (reg->getXFkCompetition_str()=="")?",NULL":",'"+reg->getXFkCompetition_str()+"'";
    sql += (reg->getNOrder_str()=="")?",NULL":",'"+reg->getNOrder_str()+"'";
    sql += (reg->getXFkPhaseType_str()=="")?",NULL":",'"+reg->getXFkPhaseType_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXCompetitionPhase(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfCompetitionPhasesDAOSQLiteEntity::updateReg(CPfCompetitionPhases *reg)
{
    std::string sql("UPDATE PF_COMPETITION_PHASES SET ");
    sql += (reg->getNNumberTeams_str()=="")?" N_NUMBER_TEAMS=NULL":" N_NUMBER_TEAMS='"+reg->getNNumberTeams_str()+"'";
    sql += (reg->getSCompetitionPhase_str()=="")?",S_COMPETITION_PHASE=NULL":",S_COMPETITION_PHASE='"+reg->getSCompetitionPhase_str()+"'";
    sql += (reg->getXFkCompetition_str()=="")?",X_FK_COMPETITION=NULL":",X_FK_COMPETITION='"+reg->getXFkCompetition_str()+"'";
    sql += (reg->getXCompetitionPhase_str()=="")?",X_COMPETITION_PHASE=NULL":",X_COMPETITION_PHASE='"+reg->getXCompetitionPhase_str()+"'";
    sql += (reg->getNOrder_str()=="")?",N_ORDER=NULL":",N_ORDER='"+reg->getNOrder_str()+"'";
    sql += (reg->getXFkPhaseType_str()=="")?",X_FK_PHASE_TYPE=NULL":",X_FK_PHASE_TYPE='"+reg->getXFkPhaseType_str()+"'";
    sql += " WHERE X_COMPETITION_PHASE='"+reg->getXCompetitionPhase_str()+"'";
    return exec(sql);
}

void CPfCompetitionPhasesDAOSQLiteEntity::freeVector(std::vector<CPfCompetitionPhases*>* vector )
{
    std::vector<CPfCompetitionPhases*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfCompetitionPhases* CPfCompetitionPhasesDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfCompetitionPhases *destiny = new CPfCompetitionPhases();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfCompetitionPhases*> * CPfCompetitionPhasesDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfCompetitionPhases*> *container = new std::vector<CPfCompetitionPhases*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfCompetitionPhasesDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    bool correct = true;
    int result = sqlite3_exec(m_database, sql.c_str(), NULL, NULL, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        correct = false;
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return correct;
}

int CPfCompetitionPhasesDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfCompetitionPhases *destiny = (CPfCompetitionPhases*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_NUMBER_TEAMS")==0 ){
                destiny->setNNumberTeams_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_COMPETITION_PHASE")==0 ){
                destiny->setSCompetitionPhase_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COMPETITION")==0 ){
                destiny->setXFkCompetition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_COMPETITION_PHASE")==0 ){
                destiny->setXCompetitionPhase_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_ORDER")==0 ){
                destiny->setNOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_PHASE_TYPE")==0 ){
                destiny->setXFkPhaseType_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfCompetitionPhasesDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfCompetitionPhases*> *container = (std::vector<CPfCompetitionPhases*> *)object;
        CPfCompetitionPhases *destiny = new CPfCompetitionPhases();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_NUMBER_TEAMS")==0 ){
                destiny->setNNumberTeams_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_COMPETITION_PHASE")==0 ){
                destiny->setSCompetitionPhase_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COMPETITION")==0 ){
                destiny->setXFkCompetition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_COMPETITION_PHASE")==0 ){
                destiny->setXCompetitionPhase_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_ORDER")==0 ){
                destiny->setNOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_PHASE_TYPE")==0 ){
                destiny->setXFkPhaseType_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

