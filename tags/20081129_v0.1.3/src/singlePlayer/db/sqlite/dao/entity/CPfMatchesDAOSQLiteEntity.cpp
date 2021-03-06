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

#include "CPfMatchesDAOSQLiteEntity.h"
#include "../../../../../utils/CLog.h"

CPfMatchesDAOSQLiteEntity::CPfMatchesDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfMatchesDAOSQLiteEntity::~CPfMatchesDAOSQLiteEntity()
{
}

void CPfMatchesDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfMatchesDAOSQLiteEntity::deleteReg(CPfMatches *reg)
{
    std::string sql("DELETE FROM PF_MATCHES WHERE X_MATCH=");
    sql += "'"+reg->getXMatch_str()+"'";
    return exec(sql);
}

bool CPfMatchesDAOSQLiteEntity::insertReg(CPfMatches *reg)
{
    std::string sql("INSERT INTO PF_MATCHES (X_FK_COMPETITION_PHASE,X_FK_TEAM_AWAY,D_MATCH,L_PLAYED,X_FK_TEAM_HOME) VALUES (");
    sql += (reg->getXFkCompetitionPhase_str()=="")?"NULL":"'"+reg->getXFkCompetitionPhase_str()+"'";
    sql += (reg->getXFkTeamAway_str()=="")?",NULL":",'"+reg->getXFkTeamAway_str()+"'";
    sql += (reg->getDMatch_str()=="")?",NULL":",'"+reg->getDMatch_str()+"'";
    sql += (reg->getLPlayed_str()=="")?",NULL":",'"+reg->getLPlayed_str()+"'";
    sql += (reg->getXFkTeamHome_str()=="")?",NULL":",'"+reg->getXFkTeamHome_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXMatch(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfMatchesDAOSQLiteEntity::updateReg(CPfMatches *reg)
{
    std::string sql("UPDATE PF_MATCHES SET ");
    sql += (reg->getXFkCompetitionPhase_str()=="")?" X_FK_COMPETITION_PHASE=NULL":" X_FK_COMPETITION_PHASE='"+reg->getXFkCompetitionPhase_str()+"'";
    sql += (reg->getXFkTeamAway_str()=="")?",X_FK_TEAM_AWAY=NULL":",X_FK_TEAM_AWAY='"+reg->getXFkTeamAway_str()+"'";
    sql += (reg->getDMatch_str()=="")?",D_MATCH=NULL":",D_MATCH='"+reg->getDMatch_str()+"'";
    sql += (reg->getXMatch_str()=="")?",X_MATCH=NULL":",X_MATCH='"+reg->getXMatch_str()+"'";
    sql += (reg->getLPlayed_str()=="")?",L_PLAYED=NULL":",L_PLAYED='"+reg->getLPlayed_str()+"'";
    sql += (reg->getXFkTeamHome_str()=="")?",X_FK_TEAM_HOME=NULL":",X_FK_TEAM_HOME='"+reg->getXFkTeamHome_str()+"'";
    sql += " WHERE X_MATCH='"+reg->getXMatch_str()+"'";
    return exec(sql);
}

void CPfMatchesDAOSQLiteEntity::freeVector(std::vector<CPfMatches*>* vector )
{
    std::vector<CPfMatches*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfMatches* CPfMatchesDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfMatchesDAOSQLiteEntity::loadRegister] No database connection.");
    }

    char *msgError = NULL;
    CPfMatches *destiny = new CPfMatches();
    if( sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfMatches*> * CPfMatchesDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfMatchesDAOSQLiteEntity::loadVector] No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfMatches*> *container = new std::vector<CPfMatches*>;
    if( sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfMatchesDAOSQLiteEntity::exec(const std::string &sql)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CPfMatchesDAOSQLiteEntity::exec] No database connection.");
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

int CPfMatchesDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if( object!=NULL ){
        CPfMatches *destiny = (CPfMatches*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_FK_COMPETITION_PHASE")==0 ){
                destiny->setXFkCompetitionPhase_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM_AWAY")==0 ){
                destiny->setXFkTeamAway_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_MATCH")==0 ){
                destiny->setDMatch_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_MATCH")==0 ){
                destiny->setXMatch_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "L_PLAYED")==0 ){
                destiny->setLPlayed_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM_HOME")==0 ){
                destiny->setXFkTeamHome_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        error = 0; // All OK
    }
    return error;
}

int CPfMatchesDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfMatches*> *container = (std::vector<CPfMatches*> *)object;
        CPfMatches *destiny = new CPfMatches();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_FK_COMPETITION_PHASE")==0 ){
                destiny->setXFkCompetitionPhase_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM_AWAY")==0 ){
                destiny->setXFkTeamAway_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_MATCH")==0 ){
                destiny->setDMatch_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_MATCH")==0 ){
                destiny->setXMatch_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "L_PLAYED")==0 ){
                destiny->setLPlayed_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_TEAM_HOME")==0 ){
                destiny->setXFkTeamHome_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

