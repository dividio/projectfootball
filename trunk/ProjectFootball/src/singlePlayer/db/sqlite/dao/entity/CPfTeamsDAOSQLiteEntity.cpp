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

#include "CPfTeamsDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfTeamsDAOSQLiteEntity::CPfTeamsDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfTeamsDAOSQLiteEntity::~CPfTeamsDAOSQLiteEntity()
{
}

void CPfTeamsDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfTeamsDAOSQLiteEntity::deleteReg(CPfTeams *reg)
{
    std::string sql("DELETE FROM PF_TEAMS WHERE X_TEAM=");
    sql += "'"+reg->getXTeam_str()+"'";
    return exec(sql);
}

bool CPfTeamsDAOSQLiteEntity::insertReg(CPfTeams *reg)
{
    std::string sql("INSERT INTO PF_TEAMS (S_LOGO,S_TEAM,N_BUDGET,S_SHORT_NAME,X_FK_STADIUM,X_FK_COUNTRY) VALUES (");
    sql += (reg->getSLogo_str()=="")?"NULL":"'"+reg->getSLogo_str()+"'";
    sql += (reg->getSTeam_str()=="")?",NULL":",'"+reg->getSTeam_str()+"'";
    sql += (reg->getNBudget_str()=="")?",NULL":",'"+reg->getNBudget_str()+"'";
    sql += (reg->getSShortName_str()=="")?",NULL":",'"+reg->getSShortName_str()+"'";
    sql += (reg->getXFkStadium_str()=="")?",NULL":",'"+reg->getXFkStadium_str()+"'";
    sql += (reg->getXFkCountry_str()=="")?",NULL":",'"+reg->getXFkCountry_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXTeam(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfTeamsDAOSQLiteEntity::updateReg(CPfTeams *reg)
{
    std::string sql("UPDATE PF_TEAMS SET ");
    sql += (reg->getSLogo_str()=="")?" S_LOGO=NULL":" S_LOGO='"+reg->getSLogo_str()+"'";
    sql += (reg->getXTeam_str()=="")?",X_TEAM=NULL":",X_TEAM='"+reg->getXTeam_str()+"'";
    sql += (reg->getSTeam_str()=="")?",S_TEAM=NULL":",S_TEAM='"+reg->getSTeam_str()+"'";
    sql += (reg->getNBudget_str()=="")?",N_BUDGET=NULL":",N_BUDGET='"+reg->getNBudget_str()+"'";
    sql += (reg->getSShortName_str()=="")?",S_SHORT_NAME=NULL":",S_SHORT_NAME='"+reg->getSShortName_str()+"'";
    sql += (reg->getXFkStadium_str()=="")?",X_FK_STADIUM=NULL":",X_FK_STADIUM='"+reg->getXFkStadium_str()+"'";
    sql += (reg->getXFkCountry_str()=="")?",X_FK_COUNTRY=NULL":",X_FK_COUNTRY='"+reg->getXFkCountry_str()+"'";
    sql += " WHERE X_TEAM='"+reg->getXTeam_str()+"'";
    return exec(sql);
}

void CPfTeamsDAOSQLiteEntity::freeVector(std::vector<CPfTeams*>* vector )
{
    std::vector<CPfTeams*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfTeams* CPfTeamsDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfTeams *destiny = new CPfTeams();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfTeams*> * CPfTeamsDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfTeams*> *container = new std::vector<CPfTeams*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfTeamsDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfTeamsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfTeams *destiny = (CPfTeams*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_LOGO")==0 ){
                destiny->setSLogo_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_TEAM")==0 ){
                destiny->setXTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_TEAM")==0 ){
                destiny->setSTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_BUDGET")==0 ){
                destiny->setNBudget_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_SHORT_NAME")==0 ){
                destiny->setSShortName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_STADIUM")==0 ){
                destiny->setXFkStadium_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COUNTRY")==0 ){
                destiny->setXFkCountry_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfTeamsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfTeams*> *container = (std::vector<CPfTeams*> *)object;
        CPfTeams *destiny = new CPfTeams();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_LOGO")==0 ){
                destiny->setSLogo_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_TEAM")==0 ){
                destiny->setXTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_TEAM")==0 ){
                destiny->setSTeam_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "N_BUDGET")==0 ){
                destiny->setNBudget_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_SHORT_NAME")==0 ){
                destiny->setSShortName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_STADIUM")==0 ){
                destiny->setXFkStadium_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COUNTRY")==0 ){
                destiny->setXFkCountry_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

