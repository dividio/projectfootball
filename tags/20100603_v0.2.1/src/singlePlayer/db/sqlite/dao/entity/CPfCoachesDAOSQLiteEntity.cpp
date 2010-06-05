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
*       Version: 1.23                                                         *
******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "CPfCoachesDAOSQLiteEntity.h"
#include "../../../../../exceptions/PFException.h"
#include "../../../../../utils/CLog.h"

CPfCoachesDAOSQLiteEntity::CPfCoachesDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfCoachesDAOSQLiteEntity::~CPfCoachesDAOSQLiteEntity()
{
}

void CPfCoachesDAOSQLiteEntity::setSQLite(sqlite3 *database)
{
    m_database = database;
}

bool CPfCoachesDAOSQLiteEntity::deleteReg(CPfCoaches *reg)
{
    std::string sql("DELETE FROM PF_COACHES WHERE X_COACH=");
    sql += "'"+reg->getXCoach_str()+"'";
    return exec(sql);
}

bool CPfCoachesDAOSQLiteEntity::insertReg(CPfCoaches *reg)
{
    std::string sql("INSERT INTO PF_COACHES (S_SHORT_NAME,S_NAME,S_PHOTO,D_BIRTHDAY,X_FK_COUNTRY,X_FK_FORMATION_SELECTED) VALUES (");
    sql += (reg->getSShortName_str()=="")?"NULL":"'"+reg->getSShortName_str()+"'";
    sql += (reg->getSName_str()=="")?",NULL":",'"+reg->getSName_str()+"'";
    sql += (reg->getSPhoto_str()=="")?",NULL":",'"+reg->getSPhoto_str()+"'";
    sql += (reg->getDBirthday_str()=="")?",NULL":",'"+reg->getDBirthday_str()+"'";
    sql += (reg->getXFkCountry_str()=="")?",NULL":",'"+reg->getXFkCountry_str()+"'";
    sql += (reg->getXFkFormationSelected_str()=="")?",NULL":",'"+reg->getXFkFormationSelected_str()+"'";
    sql += ")";
    if( exec(sql) ){
        reg->setXCoach(sqlite3_last_insert_rowid(m_database));
        return true;
    }else{
        return false;
    }
}

bool CPfCoachesDAOSQLiteEntity::updateReg(CPfCoaches *reg)
{
    std::string sql("UPDATE PF_COACHES SET ");
    sql += (reg->getXCoach_str()=="")?" X_COACH=NULL":" X_COACH='"+reg->getXCoach_str()+"'";
    sql += (reg->getSShortName_str()=="")?",S_SHORT_NAME=NULL":",S_SHORT_NAME='"+reg->getSShortName_str()+"'";
    sql += (reg->getSName_str()=="")?",S_NAME=NULL":",S_NAME='"+reg->getSName_str()+"'";
    sql += (reg->getSPhoto_str()=="")?",S_PHOTO=NULL":",S_PHOTO='"+reg->getSPhoto_str()+"'";
    sql += (reg->getDBirthday_str()=="")?",D_BIRTHDAY=NULL":",D_BIRTHDAY='"+reg->getDBirthday_str()+"'";
    sql += (reg->getXFkCountry_str()=="")?",X_FK_COUNTRY=NULL":",X_FK_COUNTRY='"+reg->getXFkCountry_str()+"'";
    sql += (reg->getXFkFormationSelected_str()=="")?",X_FK_FORMATION_SELECTED=NULL":",X_FK_FORMATION_SELECTED='"+reg->getXFkFormationSelected_str()+"'";
    sql += " WHERE X_COACH='"+reg->getXCoach_str()+"'";
    return exec(sql);
}

void CPfCoachesDAOSQLiteEntity::freeVector(std::vector<CPfCoaches*>* vector )
{
    std::vector<CPfCoaches*>::iterator it;
    for( it=vector->begin(); it!=vector->end(); it++ ){
        delete (*it);
        (*it) = NULL;
    }
    delete vector;
}

CPfCoaches* CPfCoachesDAOSQLiteEntity::loadRegister(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    CPfCoaches *destiny = new CPfCoaches();
    int result = sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError);
    if( result!=SQLITE_OK && result!=SQLITE_ABORT ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfCoaches*> * CPfCoachesDAOSQLiteEntity::loadVector(const std::string &sql)
{
    if( m_database==NULL ){
        throw PFEXCEPTION("No database connection.");
    }

    char *msgError = NULL;
    std::vector<CPfCoaches*> *container = new std::vector<CPfCoaches*>;
    int result = sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError);
    if( result!=SQLITE_OK ){
        LOG_ERROR("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
    }
    if( msgError!=NULL ){ 
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfCoachesDAOSQLiteEntity::exec(const std::string &sql)
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

int CPfCoachesDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        CPfCoaches *destiny = (CPfCoaches*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_COACH")==0 ){
                destiny->setXCoach_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_SHORT_NAME")==0 ){
                destiny->setSShortName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_NAME")==0 ){
                destiny->setSName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_PHOTO")==0 ){
                destiny->setSPhoto_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_BIRTHDAY")==0 ){
                destiny->setDBirthday_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COUNTRY")==0 ){
                destiny->setXFkCountry_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_FORMATION_SELECTED")==0 ){
                destiny->setXFkFormationSelected_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
    }
    return -1; // Abort, don't load more rows
}

int CPfCoachesDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfCoaches*> *container = (std::vector<CPfCoaches*> *)object;
        CPfCoaches *destiny = new CPfCoaches();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "X_COACH")==0 ){
                destiny->setXCoach_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_SHORT_NAME")==0 ){
                destiny->setSShortName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_NAME")==0 ){
                destiny->setSName_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "S_PHOTO")==0 ){
                destiny->setSPhoto_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "D_BIRTHDAY")==0 ){
                destiny->setDBirthday_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_COUNTRY")==0 ){
                destiny->setXFkCountry_str((vColumn[i]==NULL)?"":vColumn[i]);
            }else if( strcmp(sColumn[i], "X_FK_FORMATION_SELECTED")==0 ){
                destiny->setXFkFormationSelected_str((vColumn[i]==NULL)?"":vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}

