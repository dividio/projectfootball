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
*       Version: 1.4                                                          *
******************************************************************************/

#include <stdlib.h>

#include "CPfPaisesDAOSQLiteEntity.h"
#include "../../../../utils/CLog.h"

CPfPaisesDAOSQLiteEntity::CPfPaisesDAOSQLiteEntity(sqlite3 *database)
{
    m_database = database;
}

CPfPaisesDAOSQLiteEntity::~CPfPaisesDAOSQLiteEntity()
{
}

bool CPfPaisesDAOSQLiteEntity::deleteReg(CPfPaises *reg)
{
    std::string sql("DELETE FROM PF_PAISES WHERE X_PAIS=");
    sql = sql+"'"+reg->getXPais()->c_str()+"'";
    return exec(sql);
}

bool CPfPaisesDAOSQLiteEntity::insertReg(CPfPaises *reg)
{
    std::string sql("INSERT INTO PF_PAISES (S_PAIS,X_PAIS,S_RUTA_BANDERA) VALUES (");
    sql = sql+" '"+reg->getSPais()->c_str()+"'";
    sql = sql+",'"+reg->getXPais()->c_str()+"'";
    sql = sql+",'"+reg->getSRutaBandera()->c_str()+"'";
    sql = sql+")";
    return exec(sql);
}

bool CPfPaisesDAOSQLiteEntity::updateReg(CPfPaises *reg)
{
    std::string sql("UPDATE PF_PAISES SET ");
    sql = sql+" S_PAIS='"+reg->getSPais()->c_str()+"'";
    sql = sql+",X_PAIS='"+reg->getXPais()->c_str()+"'";
    sql = sql+",S_RUTA_BANDERA='"+reg->getSRutaBandera()->c_str()+"'";
    sql = sql+" WHERE X_PAIS='"+reg->getXPais()->c_str()+"'";
    return exec(sql);
}

CPfPaises* CPfPaisesDAOSQLiteEntity::loadRegister(std::string sql)
{
    char *msgError = NULL;
    CPfPaises *destiny = new CPfPaises();
    if( sqlite3_exec(m_database, sql.c_str(), callbackRegister, destiny, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return destiny;
}

std::vector<CPfPaises*> * CPfPaisesDAOSQLiteEntity::loadVector(std::string sql)
{
    char *msgError = NULL;
    std::vector<CPfPaises*> *container = new std::vector<CPfPaises*>;
    if( sqlite3_exec(m_database, sql.c_str(), callbackVector, container, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return container;
}

bool CPfPaisesDAOSQLiteEntity::exec(std::string sql)
{
    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, sql.c_str(), NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

int CPfPaisesDAOSQLiteEntity::callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if( object!=NULL ){
        CPfPaises *destiny = (CPfPaises*)object;
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_PAIS")==0 ){
                destiny->setSPais(vColumn[i]);
            }else if( strcmp(sColumn[i], "X_PAIS")==0 ){
                destiny->setXPais(vColumn[i]);
            }else if( strcmp(sColumn[i], "S_RUTA_BANDERA")==0 ){
                destiny->setSRutaBandera(vColumn[i]);
            }
        }
        error = 0; // All OK
    }
    return error;
}

int CPfPaisesDAOSQLiteEntity::callbackVector(void *object, int nColumns, char **vColumn, char **sColumn)
{
    if( object!=NULL ){
        std::vector<CPfPaises*> *container = (std::vector<CPfPaises*> *)object;
        CPfPaises *destiny = new CPfPaises();
        for( int i=0; i<nColumns; i++ ){
            if( strcmp(sColumn[i], "S_PAIS")==0 ){
                destiny->setSPais(vColumn[i]);
            }else if( strcmp(sColumn[i], "X_PAIS")==0 ){
                destiny->setXPais(vColumn[i]);
            }else if( strcmp(sColumn[i], "S_RUTA_BANDERA")==0 ){
                destiny->setSRutaBandera(vColumn[i]);
            }
        }
        container->push_back(destiny);
    }
    return 0; // All OK
}
