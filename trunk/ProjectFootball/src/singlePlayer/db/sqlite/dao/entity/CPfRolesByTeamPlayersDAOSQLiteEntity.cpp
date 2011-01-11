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

#include "CPfRolesByTeamPlayersDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfRolesByTeamPlayersDAOSQLiteEntity::CPfRolesByTeamPlayersDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfRolesByTeamPlayersDAOSQLiteEntity::~CPfRolesByTeamPlayersDAOSQLiteEntity()
{
}

void CPfRolesByTeamPlayersDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfRolesByTeamPlayersDAOSQLiteEntity::deleteReg(CPfRolesByTeamPlayers *reg)
{
    std::string sql("DELETE FROM PF_ROLES_BY_TEAM_PLAYERS WHERE X_ROLE_BY_TEAM_PLAYER=");
    sql += "'"+reg->getXRoleByTeamPlayer_str()+"'";
    return exec(sql);
}

bool CPfRolesByTeamPlayersDAOSQLiteEntity::insertReg(CPfRolesByTeamPlayers *reg)
{
    std::string sql("INSERT INTO PF_ROLES_BY_TEAM_PLAYERS (X_FK_TEAM_PLAYER,N_SKILL,X_FK_ROLE) VALUES (");
    sql += (reg->getXFkTeamPlayer_str()=="")?"NULL":"'"+reg->getXFkTeamPlayer_str()+"'";
    sql += (reg->getNSkill_str()=="")?",NULL":",'"+reg->getNSkill_str()+"'";
    sql += (reg->getXFkRole_str()=="")?",NULL":",'"+reg->getXFkRole_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXRoleByTeamPlayer(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfRolesByTeamPlayersDAOSQLiteEntity::updateReg(CPfRolesByTeamPlayers *reg)
{
    std::string sql("UPDATE PF_ROLES_BY_TEAM_PLAYERS SET ");
    sql += (reg->getXRoleByTeamPlayer_str()=="")?" X_ROLE_BY_TEAM_PLAYER=NULL":" X_ROLE_BY_TEAM_PLAYER='"+reg->getXRoleByTeamPlayer_str()+"'";
    sql += (reg->getXFkTeamPlayer_str()=="")?",X_FK_TEAM_PLAYER=NULL":",X_FK_TEAM_PLAYER='"+reg->getXFkTeamPlayer_str()+"'";
    sql += (reg->getNSkill_str()=="")?",N_SKILL=NULL":",N_SKILL='"+reg->getNSkill_str()+"'";
    sql += (reg->getXFkRole_str()=="")?",X_FK_ROLE=NULL":",X_FK_ROLE='"+reg->getXFkRole_str()+"'";
    sql += " WHERE X_ROLE_BY_TEAM_PLAYER='"+reg->getXRoleByTeamPlayer_str()+"'";
    return exec(sql);
}

void CPfRolesByTeamPlayersDAOSQLiteEntity::freeVector(std::vector<CPfRolesByTeamPlayers*>* vector )
{
    std::vector<CPfRolesByTeamPlayers*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfRolesByTeamPlayers* CPfRolesByTeamPlayersDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfRolesByTeamPlayers *destiny = new CPfRolesByTeamPlayers();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfRolesByTeamPlayers*> * CPfRolesByTeamPlayersDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfRolesByTeamPlayers*> *container = new std::vector<CPfRolesByTeamPlayers*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfRolesByTeamPlayersDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfRolesByTeamPlayersDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfRolesByTeamPlayers *destiny = (CPfRolesByTeamPlayers*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_ROLE_BY_TEAM_PLAYER")==0 ){
                destiny->setXRoleByTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM_PLAYER")==0 ){
                destiny->setXFkTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_SKILL")==0 ){
                destiny->setNSkill_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_ROLE")==0 ){
                destiny->setXFkRole_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfRolesByTeamPlayersDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfRolesByTeamPlayers*> *container = (std::vector<CPfRolesByTeamPlayers*> *)object;
        CPfRolesByTeamPlayers *destiny = new CPfRolesByTeamPlayers();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_ROLE_BY_TEAM_PLAYER")==0 ){
                destiny->setXRoleByTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM_PLAYER")==0 ){
                destiny->setXFkTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_SKILL")==0 ){
                destiny->setNSkill_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_ROLE")==0 ){
                destiny->setXFkRole_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

