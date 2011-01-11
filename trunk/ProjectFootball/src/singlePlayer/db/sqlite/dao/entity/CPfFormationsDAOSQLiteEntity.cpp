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

#include "CPfFormationsDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfFormationsDAOSQLiteEntity::CPfFormationsDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfFormationsDAOSQLiteEntity::~CPfFormationsDAOSQLiteEntity()
{
}

void CPfFormationsDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfFormationsDAOSQLiteEntity::deleteReg(CPfFormations *reg)
{
    std::string sql("DELETE FROM PF_FORMATIONS WHERE X_FORMATION=");
    sql += "'"+reg->getXFormation_str()+"'";
    return exec(sql);
}

bool CPfFormationsDAOSQLiteEntity::insertReg(CPfFormations *reg)
{
    std::string sql("INSERT INTO PF_FORMATIONS (X_FK_COACH_OWNER,S_NAME) VALUES (");
    sql += (reg->getXFkCoachOwner_str()=="")?"NULL":"'"+reg->getXFkCoachOwner_str()+"'";
    sql += (reg->getSName_str()=="")?",NULL":",'"+reg->getSName_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXFormation(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfFormationsDAOSQLiteEntity::updateReg(CPfFormations *reg)
{
    std::string sql("UPDATE PF_FORMATIONS SET ");
    sql += (reg->getXFkCoachOwner_str()=="")?" X_FK_COACH_OWNER=NULL":" X_FK_COACH_OWNER='"+reg->getXFkCoachOwner_str()+"'";
    sql += (reg->getSName_str()=="")?",S_NAME=NULL":",S_NAME='"+reg->getSName_str()+"'";
    sql += (reg->getXFormation_str()=="")?",X_FORMATION=NULL":",X_FORMATION='"+reg->getXFormation_str()+"'";
    sql += " WHERE X_FORMATION='"+reg->getXFormation_str()+"'";
    return exec(sql);
}

void CPfFormationsDAOSQLiteEntity::freeVector(std::vector<CPfFormations*>* vector )
{
    std::vector<CPfFormations*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfFormations* CPfFormationsDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfFormations *destiny = new CPfFormations();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfFormations*> * CPfFormationsDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfFormations*> *container = new std::vector<CPfFormations*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfFormationsDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfFormationsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfFormations *destiny = (CPfFormations*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_FK_COACH_OWNER")==0 ){
                destiny->setXFkCoachOwner_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_NAME")==0 ){
                destiny->setSName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FORMATION")==0 ){
                destiny->setXFormation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfFormationsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfFormations*> *container = (std::vector<CPfFormations*> *)object;
        CPfFormations *destiny = new CPfFormations();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_FK_COACH_OWNER")==0 ){
                destiny->setXFkCoachOwner_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_NAME")==0 ){
                destiny->setSName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FORMATION")==0 ){
                destiny->setXFormation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

