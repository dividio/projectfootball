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

#include <iostream>
#include <fstream>
#include <sstream>

#include "CMasterDAOFactorySQLite.h"
#include "../../../../../utils/CLog.h"

CMasterDAOFactorySQLite::CMasterDAOFactorySQLite(const std::string &filepath)
{
    m_filepath      = filepath;
    m_filepath_tmp  = filepath;
    m_filepath_tmp += ".tmp";

    copyFile(m_filepath, m_filepath_tmp);
    if( sqlite3_open(m_filepath_tmp.c_str(), &m_database )!=SQLITE_OK ){
        sqlite3_close(m_database);
        m_database = NULL;
        CLog::getInstance()->exception("[CMasterDAOFactorySQLite::CMasterDAOFactorySQLite] Can't open database file: '%s' --> '%s'", m_filepath_tmp.c_str(), sqlite3_errmsg(m_database));
    }

    m_PfGamesDAOSQLite = new CPfGamesDAOSQLite(m_database);
    m_PfUsersDAOSQLite = new CPfUsersDAOSQLite(m_database);

    CLog::getInstance()->debug("[CMasterDAOFactorySQLite::CMasterDAOFactorySQLite] SQLite Database open: '%s'", m_filepath_tmp.c_str());
}

CMasterDAOFactorySQLite::~CMasterDAOFactorySQLite()
{
    delete m_PfGamesDAOSQLite;
    delete m_PfUsersDAOSQLite;

    sqlite3_close(m_database);
    remove(m_filepath_tmp.c_str());
    CLog::getInstance()->debug("[CMasterDAOFactorySQLite::~CMasterDAOFactorySQLite] SQLite Database closed: '%s'", m_filepath_tmp.c_str());
}

bool CMasterDAOFactorySQLite::executeScript(const std::string &script)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CMasterDAOFactorySQLite::executeScript] No database connection.");
    }

    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, script.c_str(), NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("[CMasterDAOFactorySQLite::executeScript] Error in SQL: \"%s\" --> \"%s\"", script.c_str(), msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

bool CMasterDAOFactorySQLite::executeScriptFile(const char *scriptFile)
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CMasterDAOFactorySQLite::executeScriptFile] No database connection.");
    }

    char                c;
    std::ostringstream  sql;
    std::ifstream       script(scriptFile);
    if( script.fail() ){
        CLog::getInstance()->error("[CMasterDAOFactorySQLite::executeScriptFile] Error opening the script file: '%s'", scriptFile);
        return false;
    }

    while( script.good() ){
        c = (char) script.get();
        if( c!='\r' && c!='\n' && script.good() ){
            sql << c;
        }else{
            sql << ' ';
        }
    }
    script.close();

    return executeScript(sql.str());
}

bool CMasterDAOFactorySQLite::beginTransaction()
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CMasterDAOFactorySQLite::beginTransaction] No database connection.");
    }

    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, "BEGIN TRANSACTION;", NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in 'BEGIN TRANSACTION;': \"%s\"", msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

bool CMasterDAOFactorySQLite::commit()
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CMasterDAOFactorySQLite::commit] No database connection.");
    }

    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, "COMMIT;", NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in 'COMMIT;': \"%s\"", msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

bool CMasterDAOFactorySQLite::rollback()
{
    if( m_database==NULL ){
        CLog::getInstance()->exception("[CMasterDAOFactorySQLite::rollback] No database connection.");
    }

    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, "ROLLBACK;", NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in 'ROLLBACK;': \"%s\"", msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

void CMasterDAOFactorySQLite::save()
{
    // Closing temp database
    m_PfGamesDAOSQLite->setSQLite(NULL);
    m_PfUsersDAOSQLite->setSQLite(NULL);

    sqlite3_close(m_database);
    m_database = NULL;

    // Copying data to original database
    copyFile(m_filepath_tmp, m_filepath);
    CLog::getInstance()->debug("[CMasterDAOFactorySQLite::save] SQLite Database saved: '%s'", m_filepath.c_str());

    // Reopening temp database
    if( sqlite3_open(m_filepath_tmp.c_str(), &m_database )!=SQLITE_OK ){
        sqlite3_close(m_database);
        m_database = NULL;
        CLog::getInstance()->exception("[CMasterDAOFactorySQLite::save] Can't open database file: '%s' --> '%s'", m_filepath_tmp.c_str(), sqlite3_errmsg(m_database));
    }

    m_PfGamesDAOSQLite->setSQLite(m_database);
    m_PfUsersDAOSQLite->setSQLite(m_database);
}

IPfGamesDAO* CMasterDAOFactorySQLite::getIPfGamesDAO()
{
    return m_PfGamesDAOSQLite;
}

IPfUsersDAO* CMasterDAOFactorySQLite::getIPfUsersDAO()
{
    return m_PfUsersDAOSQLite;
}

void CMasterDAOFactorySQLite::copyFile(const std::string &origin, const std::string &destination)
{
    std::ifstream  is(origin.c_str(),       std::ifstream::in|std::ifstream::binary);
    std::ofstream  os(destination.c_str(),  std::ofstream::out|std::ofstream::binary|std::ofstream::trunc);
    if( is.is_open() && os.is_open() ){
        CLog::getInstance()->debug("[CMasterDAOFactorySQLite::copyFile] Copying files: is:'%s' os:'%s'", origin.c_str(), destination.c_str());

        char buffer[4096]; // 4KBytes
        int  nBytes;
        while( !is.eof() ){
            is.read(buffer, sizeof(buffer));
            nBytes = is.gcount();
            os.write(buffer, nBytes);
        }
    }

    is.close();
    os.close();
}
