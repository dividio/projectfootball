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
*       Version: 1.21                                                         *
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "CPfRankingDAOSQLiteEntity.h"
#include "../../../../../utils/CLog.h"

CPfRankingDAOSQLiteEntity::CPfRankingDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfRankingDAOSQLiteEntity::~CPfRankingDAOSQLiteEntity()
{
}

void CPfRankingDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

void CPfRankingDAOSQLiteEntity::freeVector(std::vector<CPfRanking*>* vector )
{
    std::vector<CPfRanking*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfRanking* CPfRankingDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfRankingDAOSQLiteEntity::loadRegister] No database connection.");
    }

    char *msgError = NULL;
    CPfRanking *destiny = new CPfRanking();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfRanking*> * CPfRankingDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfRankingDAOSQLiteEntity::loadVector] No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfRanking*> *container = new std::vector<CPfRanking*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfRankingDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfRankingDAOSQLiteEntity::exec] No database connection.");
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

int CPfRankingDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfRanking *destiny = (CPfRanking*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_WINS")==0 ){
                destiny->setNWins_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_PLAYED")==0 ){
                destiny->setNPlayed_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_TEAM")==0 ){
                destiny->setSTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_GOALS_AGAINST")==0 ){
                destiny->setNGoalsAgainst_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_POINTS")==0 ){
                destiny->setNPoints_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_GOALS_FOR")==0 ){
                destiny->setNGoalsFor_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_LOSSES")==0 ){
                destiny->setNLosses_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_DRAWS")==0 ){
                destiny->setNDraws_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfRankingDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfRanking*> *container = (std::vector<CPfRanking*> *)object;
        CPfRanking *destiny = new CPfRanking();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "N_WINS")==0 ){
                destiny->setNWins_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_PLAYED")==0 ){
                destiny->setNPlayed_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_TEAM")==0 ){
                destiny->setSTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_GOALS_AGAINST")==0 ){
                destiny->setNGoalsAgainst_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_POINTS")==0 ){
                destiny->setNPoints_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_GOALS_FOR")==0 ){
                destiny->setNGoalsFor_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_LOSSES")==0 ){
                destiny->setNLosses_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_DRAWS")==0 ){
                destiny->setNDraws_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

