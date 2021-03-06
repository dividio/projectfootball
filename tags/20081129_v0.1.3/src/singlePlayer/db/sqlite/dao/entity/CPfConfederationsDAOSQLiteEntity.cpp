/******************************************************************************
* Copyright (C) 2008 - Ikaro Games   www.ikarogames.com                       *
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
*       Version: 1.20                                                         *
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "CPfConfederationsDAOSQLiteEntity.h"
#include "../../../../../utils/CLog.h"

CPfConfederationsDAOSQLiteEntity::CPfConfederationsDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfConfederationsDAOSQLiteEntity::~CPfConfederationsDAOSQLiteEntity()
{
}

void CPfConfederationsDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfConfederationsDAOSQLiteEntity::deleteReg(CPfConfederations *reg)
{
    std::string sql("DELETE FROM PF_CONFEDERATIONS WHERE X_CONFEDERATION=");
    sql += "'"+reg->getXConfederation_str()+"'";
    return exec(sql);
}

bool CPfConfederationsDAOSQLiteEntity::insertReg(CPfConfederations *reg)
{
    std::string sql("INSERT INTO PF_CONFEDERATIONS (S_CONFEDERATION,S_LOGO) VALUES (");
    sql += (reg->getSConfederation_str()=="")?"NULL":"'"+reg->getSConfederation_str()+"'";
    sql += (reg->getSLogo_str()=="")?",NULL":",'"+reg->getSLogo_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXConfederation(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfConfederationsDAOSQLiteEntity::updateReg(CPfConfederations *reg)
{
    std::string sql("UPDATE PF_CONFEDERATIONS SET ");
    sql += (reg->getXConfederation_str()=="")?" X_CONFEDERATION=NULL":" X_CONFEDERATION='"+reg->getXConfederation_str()+"'";
    sql += (reg->getSConfederation_str()=="")?",S_CONFEDERATION=NULL":",S_CONFEDERATION='"+reg->getSConfederation_str()+"'";
    sql += (reg->getSLogo_str()=="")?",S_LOGO=NULL":",S_LOGO='"+reg->getSLogo_str()+"'";
    sql += " WHERE X_CONFEDERATION='"+reg->getXConfederation_str()+"'";
    return exec(sql);
}

void CPfConfederationsDAOSQLiteEntity::freeVector(std::vector<CPfConfederations*>* vector )
{
    std::vector<CPfConfederations*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfConfederations* CPfConfederationsDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfConfederationsDAOSQLiteEntity::loadRegister] No database connection.");
    }

    char *msgError = NULL;
    CPfConfederations *destiny = new CPfConfederations();
    if( sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfConfederations*> * CPfConfederationsDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfConfederationsDAOSQLiteEntity::loadVector] No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfConfederations*> *container = new std::vector<CPfConfederations*>;
    if( sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfConfederationsDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfConfederationsDAOSQLiteEntity::exec] No database connection.");
    }

    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, sql.c_str(), NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

int CPfConfederationsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if( object!=NULL ){
        CPfConfederations *destiny = (CPfConfederations*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_CONFEDERATION")==0 ){
                destiny->setXConfederation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_CONFEDERATION")==0 ){
                destiny->setSConfederation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_LOGO")==0 ){
                destiny->setSLogo_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        error = 0; // All OK
    }
    return error;
}

int CPfConfederationsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfConfederations*> *container = (std::vector<CPfConfederations*> *)object;
        CPfConfederations *destiny = new CPfConfederations();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_CONFEDERATION")==0 ){
                destiny->setXConfederation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_CONFEDERATION")==0 ){
                destiny->setSConfederation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_LOGO")==0 ){
                destiny->setSLogo_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

