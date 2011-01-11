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

#include "CPfCompetitionsDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfCompetitionsDAOSQLiteEntity::CPfCompetitionsDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfCompetitionsDAOSQLiteEntity::~CPfCompetitionsDAOSQLiteEntity()
{
}

void CPfCompetitionsDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfCompetitionsDAOSQLiteEntity::deleteReg(CPfCompetitions *reg)
{
    std::string sql("DELETE FROM PF_COMPETITIONS WHERE X_COMPETITION=");
    sql += "'"+reg->getXCompetition_str()+"'";
    return exec(sql);
}

bool CPfCompetitionsDAOSQLiteEntity::insertReg(CPfCompetitions *reg)
{
    std::string sql("INSERT INTO PF_COMPETITIONS (S_COMPETITION,D_FOUNDATION,X_FK_COUNTRY) VALUES (");
    sql += (reg->getSCompetition_str()=="")?"NULL":"'"+reg->getSCompetition_str()+"'";
    sql += (reg->getDFoundation_str()=="")?",NULL":",'"+reg->getDFoundation_str()+"'";
    sql += (reg->getXFkCountry_str()=="")?",NULL":",'"+reg->getXFkCountry_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXCompetition(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfCompetitionsDAOSQLiteEntity::updateReg(CPfCompetitions *reg)
{
    std::string sql("UPDATE PF_COMPETITIONS SET ");
    sql += (reg->getSCompetition_str()=="")?" S_COMPETITION=NULL":" S_COMPETITION='"+reg->getSCompetition_str()+"'";
    sql += (reg->getDFoundation_str()=="")?",D_FOUNDATION=NULL":",D_FOUNDATION='"+reg->getDFoundation_str()+"'";
    sql += (reg->getXCompetition_str()=="")?",X_COMPETITION=NULL":",X_COMPETITION='"+reg->getXCompetition_str()+"'";
    sql += (reg->getXFkCountry_str()=="")?",X_FK_COUNTRY=NULL":",X_FK_COUNTRY='"+reg->getXFkCountry_str()+"'";
    sql += " WHERE X_COMPETITION='"+reg->getXCompetition_str()+"'";
    return exec(sql);
}

void CPfCompetitionsDAOSQLiteEntity::freeVector(std::vector<CPfCompetitions*>* vector )
{
    std::vector<CPfCompetitions*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfCompetitions* CPfCompetitionsDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfCompetitions *destiny = new CPfCompetitions();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfCompetitions*> * CPfCompetitionsDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfCompetitions*> *container = new std::vector<CPfCompetitions*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfCompetitionsDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfCompetitionsDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfCompetitions *destiny = (CPfCompetitions*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_COMPETITION")==0 ){
                destiny->setSCompetition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_FOUNDATION")==0 ){
                destiny->setDFoundation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_COMPETITION")==0 ){
                destiny->setXCompetition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COUNTRY")==0 ){
                destiny->setXFkCountry_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfCompetitionsDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfCompetitions*> *container = (std::vector<CPfCompetitions*> *)object;
        CPfCompetitions *destiny = new CPfCompetitions();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_COMPETITION")==0 ){
                destiny->setSCompetition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_FOUNDATION")==0 ){
                destiny->setDFoundation_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_COMPETITION")==0 ){
                destiny->setXCompetition_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COUNTRY")==0 ){
                destiny->setXFkCountry_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

