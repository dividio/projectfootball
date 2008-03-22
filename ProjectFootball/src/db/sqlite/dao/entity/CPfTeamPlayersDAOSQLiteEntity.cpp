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
*       Version: 1.15                                                         *
******************************************************************************/

#include <stdlib.h>

#include "CPfTeamPlayersDAOSQLiteEntity.h"
#include "../../../../utils/CLog.h"

CPfTeamPlayersDAOSQLiteEntity::CPfTeamPlayersDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfTeamPlayersDAOSQLiteEntity::~CPfTeamPlayersDAOSQLiteEntity()
{
}

void CPfTeamPlayersDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfTeamPlayersDAOSQLiteEntity::deleteReg(CPfTeamPlayers *reg)
{
    std::string sql("DELETE FROM PF_TEAM_PLAYERS WHERE X_TEPL=");
    sql = sql+"'"+reg->getXTepl_str()+"'";
    return exec(sql);
}

bool CPfTeamPlayersDAOSQLiteEntity::insertReg(CPfTeamPlayers *reg)
{
    std::string sql("INSERT INTO PF_TEAM_PLAYERS (S_NAME) VALUES (");
    sql = sql+" '"+reg->getSName_str()+"'";
    sql = sql+")";
    return exec(sql);
}

bool CPfTeamPlayersDAOSQLiteEntity::updateReg(CPfTeamPlayers *reg)
{
    std::string sql("UPDATE PF_TEAM_PLAYERS SET ");
    sql = sql+" X_TEPL='"+reg->getXTepl_str()+"'";
    sql = sql+",S_NAME='"+reg->getSName_str()+"'";
    sql = sql+" WHERE X_TEPL='"+reg->getXTepl_str()+"'";
    return exec(sql);
}

void CPfTeamPlayersDAOSQLiteEntity::freeVector(std::vector<CPfTeamPlayers*>* vector )
{
    std::vector<CPfTeamPlayers*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfTeamPlayers* CPfTeamPlayersDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayersDAOSQLiteEntity::loadRegister] No database connection.");
    }

    char *msgError = NULL;
    CPfTeamPlayers *destiny = new CPfTeamPlayers();
    if( sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfTeamPlayers*> * CPfTeamPlayersDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayersDAOSQLiteEntity::loadVector] No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfTeamPlayers*> *container = new std::vector<CPfTeamPlayers*>;
    if( sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfTeamPlayersDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayersDAOSQLiteEntity::exec] No database connection.");
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

int CPfTeamPlayersDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if( object!=NULL ){
        CPfTeamPlayers *destiny = (CPfTeamPlayers*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_TEPL")==0 ){
                destiny->setXTepl_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "S_NAME")==0 ){
                destiny->setSName_str(vColumn[i]);
            }
        }
        error = 0; // All OK
    }
    return error;
}

int CPfTeamPlayersDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfTeamPlayers*> *container = (std::vector<CPfTeamPlayers*> *)object;
        CPfTeamPlayers *destiny = new CPfTeamPlayers();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_TEPL")==0 ){
                destiny->setXTepl_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "S_NAME")==0 ){
                destiny->setSName_str(vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

