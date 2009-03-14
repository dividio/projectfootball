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
*       Version: 1.22                                                         *
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "CPfTeamPlayerAveragesDAOSQLiteEntity.h"
#include "../../../../../utils/CLog.h"

CPfTeamPlayerAveragesDAOSQLiteEntity::CPfTeamPlayerAveragesDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfTeamPlayerAveragesDAOSQLiteEntity::~CPfTeamPlayerAveragesDAOSQLiteEntity()
{
}

void CPfTeamPlayerAveragesDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

void CPfTeamPlayerAveragesDAOSQLiteEntity::freeVector(std::vector<CPfTeamPlayerAverages*>* vector )
{
    std::vector<CPfTeamPlayerAverages*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfTeamPlayerAverages* CPfTeamPlayerAveragesDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayerAveragesDAOSQLiteEntity::loadRegister] No database connection.");
    }

    char *msgError = NULL;
    CPfTeamPlayerAverages *destiny = new CPfTeamPlayerAverages();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfTeamPlayerAverages*> * CPfTeamPlayerAveragesDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayerAveragesDAOSQLiteEntity::loadVector] No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfTeamPlayerAverages*> *container = new std::vector<CPfTeamPlayerAverages*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfTeamPlayerAveragesDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayerAveragesDAOSQLiteEntity::exec] No database connection.");
    }

    char *msgError = NULL;
    bool correct = true;
    int result = sqlite3_exec(m_database, sql.c_str(), NULL, NULL, &msgError);
    if( result!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        correct = false;
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return correct;
}

int CPfTeamPlayerAveragesDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfTeamPlayerAverages *destiny = (CPfTeamPlayerAverages*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_TEAM_PLAYER")==0 ){
                destiny->setXTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_TOTAL")==0 ){
                destiny->setNTotal_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_ATTACK")==0 ){
                destiny->setNAttack_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_DEFENSE")==0 ){
                destiny->setNDefense_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfTeamPlayerAveragesDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfTeamPlayerAverages*> *container = (std::vector<CPfTeamPlayerAverages*> *)object;
        CPfTeamPlayerAverages *destiny = new CPfTeamPlayerAverages();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_TEAM_PLAYER")==0 ){
                destiny->setXTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_TOTAL")==0 ){
                destiny->setNTotal_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_ATTACK")==0 ){
                destiny->setNAttack_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_DEFENSE")==0 ){
                destiny->setNDefense_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

