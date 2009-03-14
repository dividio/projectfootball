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

#include "CPfTeamPlayerContractsDAOSQLiteEntity.h"
#include "../../../../../utils/CLog.h"

CPfTeamPlayerContractsDAOSQLiteEntity::CPfTeamPlayerContractsDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfTeamPlayerContractsDAOSQLiteEntity::~CPfTeamPlayerContractsDAOSQLiteEntity()
{
}

void CPfTeamPlayerContractsDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfTeamPlayerContractsDAOSQLiteEntity::deleteReg(CPfTeamPlayerContracts *reg)
{
    std::string sql("DELETE FROM PF_TEAM_PLAYER_CONTRACTS WHERE X_TEAM_PLAYER_CONTRACT=");
    sql += "'"+reg->getXTeamPlayerContract_str()+"'";
    return exec(sql);
}

bool CPfTeamPlayerContractsDAOSQLiteEntity::insertReg(CPfTeamPlayerContracts *reg)
{
    std::string sql("INSERT INTO PF_TEAM_PLAYER_CONTRACTS (D_BEGIN,D_END,X_FK_TEAM_PLAYER,N_LINEUP_ORDER,X_FK_TEAM) VALUES (");
    sql += (reg->getDBegin_str()=="")?"NULL":"'"+reg->getDBegin_str()+"'";
    sql += (reg->getDEnd_str()=="")?",NULL":",'"+reg->getDEnd_str()+"'";
    sql += (reg->getXFkTeamPlayer_str()=="")?",NULL":",'"+reg->getXFkTeamPlayer_str()+"'";
    sql += (reg->getNLineupOrder_str()=="")?",NULL":",'"+reg->getNLineupOrder_str()+"'";
    sql += (reg->getXFkTeam_str()=="")?",NULL":",'"+reg->getXFkTeam_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXTeamPlayerContract(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfTeamPlayerContractsDAOSQLiteEntity::updateReg(CPfTeamPlayerContracts *reg)
{
    std::string sql("UPDATE PF_TEAM_PLAYER_CONTRACTS SET ");
    sql += (reg->getDBegin_str()=="")?" D_BEGIN=NULL":" D_BEGIN='"+reg->getDBegin_str()+"'";
    sql += (reg->getXTeamPlayerContract_str()=="")?",X_TEAM_PLAYER_CONTRACT=NULL":",X_TEAM_PLAYER_CONTRACT='"+reg->getXTeamPlayerContract_str()+"'";
    sql += (reg->getDEnd_str()=="")?",D_END=NULL":",D_END='"+reg->getDEnd_str()+"'";
    sql += (reg->getXFkTeamPlayer_str()=="")?",X_FK_TEAM_PLAYER=NULL":",X_FK_TEAM_PLAYER='"+reg->getXFkTeamPlayer_str()+"'";
    sql += (reg->getNLineupOrder_str()=="")?",N_LINEUP_ORDER=NULL":",N_LINEUP_ORDER='"+reg->getNLineupOrder_str()+"'";
    sql += (reg->getXFkTeam_str()=="")?",X_FK_TEAM=NULL":",X_FK_TEAM='"+reg->getXFkTeam_str()+"'";
    sql += " WHERE X_TEAM_PLAYER_CONTRACT='"+reg->getXTeamPlayerContract_str()+"'";
    return exec(sql);
}

void CPfTeamPlayerContractsDAOSQLiteEntity::freeVector(std::vector<CPfTeamPlayerContracts*>* vector )
{
    std::vector<CPfTeamPlayerContracts*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfTeamPlayerContracts* CPfTeamPlayerContractsDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayerContractsDAOSQLiteEntity::loadRegister] No database connection.");
    }

    char *msgError = NULL;
    CPfTeamPlayerContracts *destiny = new CPfTeamPlayerContracts();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfTeamPlayerContracts*> * CPfTeamPlayerContractsDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayerContractsDAOSQLiteEntity::loadVector] No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfTeamPlayerContracts*> *container = new std::vector<CPfTeamPlayerContracts*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfTeamPlayerContractsDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfTeamPlayerContractsDAOSQLiteEntity::exec] No database connection.");
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

int CPfTeamPlayerContractsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfTeamPlayerContracts *destiny = (CPfTeamPlayerContracts*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "D_BEGIN")==0 ){
                destiny->setDBegin_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_TEAM_PLAYER_CONTRACT")==0 ){
                destiny->setXTeamPlayerContract_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_END")==0 ){
                destiny->setDEnd_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM_PLAYER")==0 ){
                destiny->setXFkTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_LINEUP_ORDER")==0 ){
                destiny->setNLineupOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM")==0 ){
                destiny->setXFkTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfTeamPlayerContractsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfTeamPlayerContracts*> *container = (std::vector<CPfTeamPlayerContracts*> *)object;
        CPfTeamPlayerContracts *destiny = new CPfTeamPlayerContracts();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "D_BEGIN")==0 ){
                destiny->setDBegin_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_TEAM_PLAYER_CONTRACT")==0 ){
                destiny->setXTeamPlayerContract_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_END")==0 ){
                destiny->setDEnd_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM_PLAYER")==0 ){
                destiny->setXFkTeamPlayer_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_LINEUP_ORDER")==0 ){
                destiny->setNLineupOrder_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM")==0 ){
                destiny->setXFkTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

