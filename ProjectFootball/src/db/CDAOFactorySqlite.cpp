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
*       Version: 1.0                                                          *
******************************************************************************/


#include <sqlite3.h>

#include "CDAOFactorySqlite.h"
#include "CPfEquiposDAOSqlite.h"


sqlite3 * CDAOFactorySqlite::m_dataBase = NULL;

CDAOFactorySqlite::CDAOFactorySqlite()
{
//    Se lee el nombre del fichero que contiene la bbdd
//    const char *fileDB = CGestorOpciones::opcionCadena( "BaseDeDatos",
//                              "fichero", "data/bbdd/PFBaseDatos.sql3" );
    const char *fileDB = "data/bbdd/dbtest.sql3";
    if (sqlite3_open(fileDB, &m_dataBase) != SQLITE_OK) {
        sqlite3_close(m_dataBase);
        m_dataBase = NULL;
        //CGestorLog::excepcion( "No se pudo abrir el fichero de la bbdd: \"%s\" --> \"%s\"", ficheroBD, sqlite3_errmsg(m_baseDeDatos) );
    }
    //CGestorLog::info( "Gestor de Base de Datos inicializado: <-- \"%s\"", ficheroBD );
}

CDAOFactorySqlite::~CDAOFactorySqlite()
{

}

CDAOFactorySqlite* CDAOFactorySqlite::getInstance()
{
    static CDAOFactorySqlite instance;

    return &instance;
}

IPfEquiposDAO* CDAOFactorySqlite::getIPfEquiposDAO()
{
    static CPfEquiposDAOSqlite dao(m_dataBase);
    return &dao;
}
