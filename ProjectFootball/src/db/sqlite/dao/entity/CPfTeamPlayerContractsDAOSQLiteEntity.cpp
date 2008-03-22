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

#include "CPfTeamPlayerContractsDAOSQLiteEntity.h"
#include "../../../../utils/CLog.h"

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
    std::string sql("DELETE FROM PF_TEAM_PLAYER_CONTRACTS WHERE X_TPCO=");
    sql = sql+"'"+reg->getXTpco_str()+"'";
    return exec(sql);
}

bool CPfTeamPlayerContractsDAOSQLiteEntity::insertReg(CPfTeamPlayerContracts *reg)
{
    std::string sql("INSERT INTO PF_TEAM_PLAYER_CONTRACTS (D_END,D_BEGIN,X_FK_TEAM,X_FK_TEPL) VALUES (");
    sql = sql+" '"+reg->getDEnd_str()+"'";
    sql = sql+",'"+reg->getDBegin_str()+"'";
    sql = sql+",'"+reg->getXFkTeam_str()+"'";
    sql = sql+",'"+reg->getXFkTepl_str()+"'";
    sql = sql+")";
    return exec(sql);
}

bool CPfTeamPlayerContractsDAOSQLiteEntity::updateReg(CPfTeamPlayerContracts *reg)
{
    std::string sql("UPDATE PF_TEAM_PLAYER_CONTRACTS SET ");
    sql = sql+" D_END='"+reg->getDEnd_str()+"'";
    sql = sql+",D_BEGIN='"+reg->getDBegin_str()+"'";
    sql = sql+",X_FK_TEAM='"+reg->getXFkTeam_str()+"'";
    sql = sql+",X_FK_TEPL='"+reg->getXFkTepl_str()+"'";
    sql = sql+",X_TPCO='"+reg->getXTpco_str()+"'";
    sql = sql+" WHERE X_TPCO='"+reg->getXTpco_str()+"'";
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
    if( sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
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
    if( sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
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
    if( sqlite3_exec(m_database, sql.c_str(), NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

int CPfTeamPlayerContractsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if( object!=NULL ){
        CPfTeamPlayerContracts *destiny = (CPfTeamPlayerContracts*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "D_END")==0 ){
                destiny->setDEnd_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "D_BEGIN")==0 ){
                destiny->setDBegin_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM")==0 ){
                destiny->setXFkTeam_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEPL")==0 ){
                destiny->setXFkTepl_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "X_TPCO")==0 ){
                destiny->setXTpco_str(vColumn[i]);
            }
        }
        error = 0; // All OK
    }
    return error;
}

int CPfTeamPlayerContractsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfTeamPlayerContracts*> *container = (std::vector<CPfTeamPlayerContracts*> *)object;
        CPfTeamPlayerContracts *destiny = new CPfTeamPlayerContracts();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "D_END")==0 ){
                destiny->setDEnd_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "D_BEGIN")==0 ){
                destiny->setDBegin_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM")==0 ){
                destiny->setXFkTeam_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEPL")==0 ){
                destiny->setXFkTepl_str(vColumn[i]);
            }else if( strcmp(sColumn[i], "X_TPCO")==0 ){
                destiny->setXTpco_str(vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

