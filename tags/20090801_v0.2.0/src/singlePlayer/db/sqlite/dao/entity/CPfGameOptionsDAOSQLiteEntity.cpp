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

#include "CPfGameOptionsDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfGameOptionsDAOSQLiteEntity::CPfGameOptionsDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfGameOptionsDAOSQLiteEntity::~CPfGameOptionsDAOSQLiteEntity()
{
}

void CPfGameOptionsDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfGameOptionsDAOSQLiteEntity::deleteReg(CPfGameOptions *reg)
{
    std::string sql("DELETE FROM PF_GAME_OPTIONS WHERE X_OPTION=");
    sql += "'"+reg->getXOption_str()+"'";
    return exec(sql);
}

bool CPfGameOptionsDAOSQLiteEntity::insertReg(CPfGameOptions *reg)
{
    std::string sql("INSERT INTO PF_GAME_OPTIONS (S_CATEGORY,S_VALUE,S_ATTRIBUTE) VALUES (");
    sql += (reg->getSCategory_str()=="")?"NULL":"'"+reg->getSCategory_str()+"'";
    sql += (reg->getSValue_str()=="")?",NULL":",'"+reg->getSValue_str()+"'";
    sql += (reg->getSAttribute_str()=="")?",NULL":",'"+reg->getSAttribute_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXOption(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfGameOptionsDAOSQLiteEntity::updateReg(CPfGameOptions *reg)
{
    std::string sql("UPDATE PF_GAME_OPTIONS SET ");
    sql += (reg->getSCategory_str()=="")?" S_CATEGORY=NULL":" S_CATEGORY='"+reg->getSCategory_str()+"'";
    sql += (reg->getXOption_str()=="")?",X_OPTION=NULL":",X_OPTION='"+reg->getXOption_str()+"'";
    sql += (reg->getSValue_str()=="")?",S_VALUE=NULL":",S_VALUE='"+reg->getSValue_str()+"'";
    sql += (reg->getSAttribute_str()=="")?",S_ATTRIBUTE=NULL":",S_ATTRIBUTE='"+reg->getSAttribute_str()+"'";
    sql += " WHERE X_OPTION='"+reg->getXOption_str()+"'";
    return exec(sql);
}

void CPfGameOptionsDAOSQLiteEntity::freeVector(std::vector<CPfGameOptions*>* vector )
{
    std::vector<CPfGameOptions*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfGameOptions* CPfGameOptionsDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfGameOptions *destiny = new CPfGameOptions();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfGameOptions*> * CPfGameOptionsDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfGameOptions*> *container = new std::vector<CPfGameOptions*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfGameOptionsDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfGameOptionsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfGameOptions *destiny = (CPfGameOptions*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_CATEGORY")==0 ){
                destiny->setSCategory_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_OPTION")==0 ){
                destiny->setXOption_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_VALUE")==0 ){
                destiny->setSValue_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_ATTRIBUTE")==0 ){
                destiny->setSAttribute_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfGameOptionsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfGameOptions*> *container = (std::vector<CPfGameOptions*> *)object;
        CPfGameOptions *destiny = new CPfGameOptions();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_CATEGORY")==0 ){
                destiny->setSCategory_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_OPTION")==0 ){
                destiny->setXOption_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_VALUE")==0 ){
                destiny->setSValue_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_ATTRIBUTE")==0 ){
                destiny->setSAttribute_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

