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
*       Version: 1.18                                                         *
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "CPfGameStatesDAOSQLiteEntity.h"
#include "../../../../utils/CLog.h"

CPfGameStatesDAOSQLiteEntity::CPfGameStatesDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfGameStatesDAOSQLiteEntity::~CPfGameStatesDAOSQLiteEntity()
{
}

void CPfGameStatesDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfGameStatesDAOSQLiteEntity::deleteReg(CPfGameStates *reg)
{
    std::string sql("DELETE FROM PF_GAME_STATES WHERE X_STATE=");
    sql += "'"+reg->getXState_str()+"'";
    return exec(sql);
}

bool CPfGameStatesDAOSQLiteEntity::insertReg(CPfGameStates *reg)
{
    std::string sql("INSERT INTO PF_GAME_STATES (S_STATE,S_VALUE) VALUES (");
    sql += (reg->getSState_str()=="")?"NULL":"'"+reg->getSState_str()+"'";
    sql += (reg->getSValue_str()=="")?",NULL":",'"+reg->getSValue_str()+"'";
    sql += ")";
    return exec(sql);
}

bool CPfGameStatesDAOSQLiteEntity::updateReg(CPfGameStates *reg)
{
    std::string sql("UPDATE PF_GAME_STATES SET ");
    sql += (reg->getSState_str()=="")?" S_STATE=NULL":" S_STATE='"+reg->getSState_str()+"'";
    sql += (reg->getXState_str()=="")?",X_STATE=NULL":",X_STATE='"+reg->getXState_str()+"'";
    sql += (reg->getSValue_str()=="")?",S_VALUE=NULL":",S_VALUE='"+reg->getSValue_str()+"'";
    sql += " WHERE X_STATE='"+reg->getXState_str()+"'";
    return exec(sql);
}

void CPfGameStatesDAOSQLiteEntity::freeVector(std::vector<CPfGameStates*>* vector )
{
    std::vector<CPfGameStates*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfGameStates* CPfGameStatesDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfGameStatesDAOSQLiteEntity::loadRegister] No database connection.");
    }

    char *msgError = NULL;
    CPfGameStates *destiny = new CPfGameStates();
    if( sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfGameStates*> * CPfGameStatesDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfGameStatesDAOSQLiteEntity::loadVector] No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfGameStates*> *container = new std::vector<CPfGameStates*>;
    if( sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfGameStatesDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfGameStatesDAOSQLiteEntity::exec] No database connection.");
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

int CPfGameStatesDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if( object!=NULL ){
        CPfGameStates *destiny = (CPfGameStates*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_STATE")==0 ){
                destiny->setSState_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_STATE")==0 ){
                destiny->setXState_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_VALUE")==0 ){
                destiny->setSValue_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        error = 0; // All OK
    }
    return error;
}

int CPfGameStatesDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfGameStates*> *container = (std::vector<CPfGameStates*> *)object;
        CPfGameStates *destiny = new CPfGameStates();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_STATE")==0 ){
                destiny->setSState_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_STATE")==0 ){
                destiny->setXState_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_VALUE")==0 ){
                destiny->setSValue_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

