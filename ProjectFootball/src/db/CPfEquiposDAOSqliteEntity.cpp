/******************************************************************************
* Copyright (C) 2007 - Ikaro Games   www.ikarogames.com                       *
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
*       Version: 1.1                                                          *
******************************************************************************/


#include <sqlite3.h>

#include "CPfEquiposDAOSqliteEntity.h"
#include "../utils/CLog.h"


CPfEquiposDAOSqliteEntity::CPfEquiposDAOSqliteEntity(sqlite3 *dataBase)
{
    m_dataBase = dataBase;
}


CPfEquiposDAOSqliteEntity::~CPfEquiposDAOSqliteEntity()
{

}


CPfEquipos* CPfEquiposDAOSqliteEntity::loadRegister(string sql)
{
    char *msgError = NULL;
    CPfEquipos *destiny = new CPfEquipos();
    if (sqlite3_exec(m_dataBase, sql.c_str(), callbackRegister, destiny, &msgError)
        != SQLITE_OK) {
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return destiny;
}


vector<CPfEquipos*> * CPfEquiposDAOSqliteEntity::loadVector(string sql)
{
    char *msgError = NULL;
    vector<CPfEquipos *> *container = new vector<CPfEquipos *>;
    if (sqlite3_exec(m_dataBase, sql.c_str(), callbackVector, container, &msgError)
        != SQLITE_OK) {
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return container;
}


bool CPfEquiposDAOSqliteEntity::exec(string sql)
{
    char *msgError = NULL;
    bool correct = true;
    if (sqlite3_exec(m_dataBase, sql.c_str(), NULL, NULL, &msgError)
        != SQLITE_OK) {
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}


bool CPfEquiposDAOSqliteEntity::deleteReg(CPfEquipos * elem)
{
    std::string sql("DELETE FROM PF_EQUIPOS WHERE X_EQUIPO='");
    sql = sql + elem->getXEquipo()->c_str() + "'";
    return exec(sql);
}


bool CPfEquiposDAOSqliteEntity::insert(CPfEquipos * elem)
{
    std::string sql("INSERT INTO PF_EQUIPOS \
                    (X_EQUIPO,X_FK_PAIS,S_EQUIPO,\
                     S_RUTA_ESCUDO) VALUES (");
    sql = sql + " '" + elem->getXEquipo()->c_str() + "'";
    sql = sql + ",'" + elem->getXFkPais()->c_str() + "'";
    sql = sql + ",'" + elem->getSEquipo()->c_str() + "'";
    sql = sql + ",'" + elem->getSRutaEscudo()->c_str() + "'";
    sql = sql + ")";
    return exec(sql);
}


bool CPfEquiposDAOSqliteEntity::update(CPfEquipos * elem)
{
    std::string sql("UPDATE PF_EQUIPOS SET");

    sql = sql + "  X_FK_PAIS='"
               + elem->getXFkPais()->c_str() + "'";
    sql = sql + ",  S_EQUIPO='"
               + elem->getSEquipo()->c_str() + "'";
    sql = sql + ",  S_RUTA_ESCUDO='"
               + elem->getSRutaEscudo()->c_str() + "'";
    sql = sql + "  WHERE X_EQUIPO='"
              + elem->getXEquipo()->c_str() + "'";

    return exec(sql);
}


int CPfEquiposDAOSqliteEntity::callbackRegister
    (void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if (object != NULL) {
        CPfEquipos *destiny = (CPfEquipos*)object;
        for (int i = 0; i < nColumns; i++) {
            if (strcmp(sColumn[i], "X_EQUIPO") == 0) {
                destiny->setXEquipo(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "X_FK_PAIS") == 0) {
                destiny->setXFkPais(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_EQUIPO") == 0) {
                destiny->setSEquipo(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_RUTA_ESCUDO") == 0) {
                destiny->setSRutaEscudo(std::string(vColumn[i]));
            }
        }
        error = 0; // All is ok
    }
    return error;
}


int CPfEquiposDAOSqliteEntity::callbackVector
    (void *object, int nColumns, char **vColumn, char **sColumn)
{
    if (object != NULL) {
        std::vector<CPfEquipos*> *container;
        container = (std::vector<CPfEquipos*> *)object;
        CPfEquipos *destiny = new CPfEquipos();
        for (int i = 0; i < nColumns; i++) {
            if (strcmp(sColumn[i], "X_EQUIPO") == 0) {
                destiny->setXEquipo(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "X_FK_PAIS") == 0) {
                destiny->setXFkPais(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_EQUIPO") == 0) {
                destiny->setSEquipo(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_RUTA_ESCUDO") == 0) {
                destiny->setSRutaEscudo(std::string(vColumn[i]));
            }
        }
        container->push_back(destiny);
    }
    return 0; // All is ok
}


