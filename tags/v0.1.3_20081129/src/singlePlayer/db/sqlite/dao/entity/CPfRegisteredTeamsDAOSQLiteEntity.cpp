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

#include "CPfRegisteredTeamsDAOSQLiteEntity.h"
#include "../../../../../utils/CLog.h"

CPfRegisteredTeamsDAOSQLiteEntity::CPfRegisteredTeamsDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfRegisteredTeamsDAOSQLiteEntity::~CPfRegisteredTeamsDAOSQLiteEntity()
{
}

void CPfRegisteredTeamsDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfRegisteredTeamsDAOSQLiteEntity::deleteReg(CPfRegisteredTeams *reg)
{
    std::string sql("DELETE FROM PF_REGISTERED_TEAMS WHERE X_REGISTERED_TEAM=");
    sql += "'"+reg->getXRegisteredTeam_str()+"'";
    return exec(sql);
}

bool CPfRegisteredTeamsDAOSQLiteEntity::insertReg(CPfRegisteredTeams *reg)
{
    std::string sql("INSERT INTO PF_REGISTERED_TEAMS (X_FK_COMPETITION,X_FK_TEAM) VALUES (");
    sql += (reg->getXFkCompetition_str()=="")?"NULL":"'"+reg->getXFkCompetition_str()+"'";
    sql += (reg->getXFkTeam_str()=="")?",NULL":",'"+reg->getXFkTeam_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXRegisteredTeam(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfRegisteredTeamsDAOSQLiteEntity::updateReg(CPfRegisteredTeams *reg)
{
    std::string sql("UPDATE PF_REGISTERED_TEAMS SET ");
    sql += (reg->getXRegisteredTeam_str()=="")?" X_REGISTERED_TEAM=NULL":" X_REGISTERED_TEAM='"+reg->getXRegisteredTeam_str()+"'";
    sql += (reg->getXFkCompetition_str()=="")?",X_FK_COMPETITION=NULL":",X_FK_COMPETITION='"+reg->getXFkCompetition_str()+"'";
    sql += (reg->getXFkTeam_str()=="")?",X_FK_TEAM=NULL":",X_FK_TEAM='"+reg->getXFkTeam_str()+"'";
    sql += " WHERE X_REGISTERED_TEAM='"+reg->getXRegisteredTeam_str()+"'";
    return exec(sql);
}

void CPfRegisteredTeamsDAOSQLiteEntity::freeVector(std::vector<CPfRegisteredTeams*>* vector )
{
    std::vector<CPfRegisteredTeams*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfRegisteredTeams* CPfRegisteredTeamsDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfRegisteredTeamsDAOSQLiteEntity::loadRegister] No database connection.");
    }

    char *msgError = NULL;
    CPfRegisteredTeams *destiny = new CPfRegisteredTeams();
    if( sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfRegisteredTeams*> * CPfRegisteredTeamsDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfRegisteredTeamsDAOSQLiteEntity::loadVector] No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfRegisteredTeams*> *container = new std::vector<CPfRegisteredTeams*>;
    if( sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfRegisteredTeamsDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfRegisteredTeamsDAOSQLiteEntity::exec] No database connection.");
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

int CPfRegisteredTeamsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if( object!=NULL ){
        CPfRegisteredTeams *destiny = (CPfRegisteredTeams*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_REGISTERED_TEAM")==0 ){
                destiny->setXRegisteredTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COMPETITION")==0 ){
                destiny->setXFkCompetition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM")==0 ){
                destiny->setXFkTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        error = 0; // All OK
    }
    return error;
}

int CPfRegisteredTeamsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfRegisteredTeams*> *container = (std::vector<CPfRegisteredTeams*> *)object;
        CPfRegisteredTeams *destiny = new CPfRegisteredTeams();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_REGISTERED_TEAM")==0 ){
                destiny->setXRegisteredTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COMPETITION")==0 ){
                destiny->setXFkCompetition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM")==0 ){
                destiny->setXFkTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

