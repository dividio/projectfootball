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
*       Version: 1.14                                                         *
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>

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

    m_PfRankingDAOSQLite = new CPfRankingDAOSQLite(m_database);
    m_PfGameStatesDAOSQLite = new CPfGameStatesDAOSQLite(m_database);
    m_PfMatchesDAOSQLite = new CPfMatchesDAOSQLite(m_database);
    m_PfGameOptionsDAOSQLite = new CPfGameOptionsDAOSQLite(m_database);
    m_PfTeamPlayerContractsDAOSQLite = new CPfTeamPlayerContractsDAOSQLite(m_database);
    m_PfGoalsDAOSQLite = new CPfGoalsDAOSQLite(m_database);
    m_PfTeamPlayersDAOSQLite = new CPfTeamPlayersDAOSQLite(m_database);
    m_PfTeamsDAOSQLite = new CPfTeamsDAOSQLite(m_database);

    CLog::getInstance()->info("SQLite Database open: <-- \"%s\"", file.c_str());
}

CDAOFactorySQLite::~CDAOFactorySQLite()
{
    delete m_PfRankingDAOSQLite;
    delete m_PfGameStatesDAOSQLite;
    delete m_PfMatchesDAOSQLite;
    delete m_PfGameOptionsDAOSQLite;
    delete m_PfTeamPlayerContractsDAOSQLite;
    delete m_PfGoalsDAOSQLite;
    delete m_PfTeamPlayersDAOSQLite;
    delete m_PfTeamsDAOSQLite;

    sqlite3_close(m_database);
    CLog::getInstance()->info("SQLite Database closed");
}

bool CDAOFactorySQLite::executeScript(const std::string &script)
{
    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, script.c_str(), NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("[CDAOFactorySQLite::executeScript] Error in SQL: \"%s\" --> \"%s\"", script.c_str(), msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

bool CDAOFactorySQLite::executeScriptFile(const char *scriptFile)
{
    char                c;
    std::ostringstream  sql;
    std::ifstream       script(scriptFile);
    if( script.fail() ){
        CLog::getInstance()->error("[CDAOFactorySQLite::executeScriptFile] Error opening the script file: '%s'", scriptFile);
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

bool CDAOFactorySQLite::beginTransaction()
{
    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, "BEGIN TRANSACTION;", NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in 'BEGIN TRANSACTION;': \"%s\"", msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

bool CDAOFactorySQLite::commit()
{
    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, "COMMIT;", NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in 'COMMIT;': \"%s\"", msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

bool CDAOFactorySQLite::rollback()
{
    char *msgError = NULL;
    bool correct = true;
    if( sqlite3_exec(m_database, "ROLLBACK;", NULL, NULL, &msgError)!=SQLITE_OK ){
        CLog::getInstance()->error("Error in 'ROLLBACK;': \"%s\"", msgError);
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}

IPfRankingDAO* CDAOFactorySQLite::getIPfRankingDAO()
{
    return m_PfRankingDAOSQLite;
}

IPfGameStatesDAO* CDAOFactorySQLite::getIPfGameStatesDAO()
{
    return m_PfGameStatesDAOSQLite;
}

IPfMatchesDAO* CDAOFactorySQLite::getIPfMatchesDAO()
{
    return m_PfMatchesDAOSQLite;
}

IPfGameOptionsDAO* CDAOFactorySQLite::getIPfGameOptionsDAO()
{
    return m_PfGameOptionsDAOSQLite;
}

IPfTeamPlayerContractsDAO* CDAOFactorySQLite::getIPfTeamPlayerContractsDAO()
{
    return m_PfTeamPlayerContractsDAOSQLite;
}

IPfGoalsDAO* CDAOFactorySQLite::getIPfGoalsDAO()
{
    return m_PfGoalsDAOSQLite;
}

IPfTeamPlayersDAO* CDAOFactorySQLite::getIPfTeamPlayersDAO()
{
    return m_PfTeamPlayersDAOSQLite;
}

IPfTeamsDAO* CDAOFactorySQLite::getIPfTeamsDAO()
{
    return m_PfTeamsDAOSQLite;
}

