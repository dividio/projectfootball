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

#include "CDAOFactorySQLite.h"
#include "../../../../utils/CLog.h"

CDAOFactorySQLite::CDAOFactorySQLite(std::string file)
{
    CLog::getInstance()->info("Path: %s", file.c_str());
    if( sqlite3_open(file.c_str(), &m_database )!=SQLITE_OK ){
        sqlite3_close(m_database);
        m_database = NULL;
        CLog::getInstance()->exception("Can't open database file: \"%s\" --> \"%s\"", file.c_str(), sqlite3_errmsg(m_database));
    }
    
    m_PfPaisesDAOSQLite = new CPfPaisesDAOSQLite(m_database);
    m_PfEquiposDAOSQLite = new CPfEquiposDAOSQLite(m_database);
    
    CLog::getInstance()->info("SQLite Database open: <-- \"%s\"", file.c_str());
}

CDAOFactorySQLite::~CDAOFactorySQLite()
{
    delete m_PfPaisesDAOSQLite;
    delete m_PfEquiposDAOSQLite;
    
    sqlite3_close(m_database);
    CLog::getInstance()->info("SQLite Database closed");
}

IPfPaisesDAO* CDAOFactorySQLite::getIPfPaisesDAO()
{
    return m_PfPaisesDAOSQLite;
}

IPfEquiposDAO* CDAOFactorySQLite::getIPfEquiposDAO()
{
    return m_PfEquiposDAOSQLite;
}
