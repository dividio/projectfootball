/******************************************************************************
* Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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

#include "CPfVersionDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfVersionDAOSQLiteEntity::CPfVersionDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfVersionDAOSQLiteEntity::~CPfVersionDAOSQLiteEntity()
{
}

void CPfVersionDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfVersionDAOSQLiteEntity::deleteReg(CPfVersion *reg)
{
    std::string sql("DELETE FROM PF_VERSION WHERE X_VERSION=");
    sql += "'"+reg->getXVersion_str()+"'";
    return exec(sql);
}

bool CPfVersionDAOSQLiteEntity::insertReg(CPfVersion *reg)
{
    std::string sql("INSERT INTO PF_VERSION (D_DATE,S_VERSION) VALUES (");
    sql += (reg->getDDate_str()=="")?"NULL":"'"+reg->getDDate_str()+"'";
    sql += (reg->getSVersion_str()=="")?",NULL":",'"+reg->getSVersion_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXVersion(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfVersionDAOSQLiteEntity::updateReg(CPfVersion *reg)
{
    std::string sql("UPDATE PF_VERSION SET ");
    sql += (reg->getDDate_str()=="")?" D_DATE=NULL":" D_DATE='"+reg->getDDate_str()+"'";
    sql += (reg->getSVersion_str()=="")?",S_VERSION=NULL":",S_VERSION='"+reg->getSVersion_str()+"'";
    sql += (reg->getXVersion_str()=="")?",X_VERSION=NULL":",X_VERSION='"+reg->getXVersion_str()+"'";
    sql += " WHERE X_VERSION='"+reg->getXVersion_str()+"'";
    return exec(sql);
}

void CPfVersionDAOSQLiteEntity::freeVector(std::vector<CPfVersion*>* vector )
{
    std::vector<CPfVersion*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfVersion* CPfVersionDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfVersion *destiny = new CPfVersion();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfVersion*> * CPfVersionDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfVersion*> *container = new std::vector<CPfVersion*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfVersionDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfVersionDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfVersion *destiny = (CPfVersion*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "D_DATE")==0 ){
                destiny->setDDate_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_VERSION")==0 ){
                destiny->setSVersion_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_VERSION")==0 ){
                destiny->setXVersion_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfVersionDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfVersion*> *container = (std::vector<CPfVersion*> *)object;
        CPfVersion *destiny = new CPfVersion();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "D_DATE")==0 ){
                destiny->setDDate_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_VERSION")==0 ){
                destiny->setSVersion_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_VERSION")==0 ){
                destiny->setXVersion_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

