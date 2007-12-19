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
******************************************************************************/


#include <sqlite3.h>

#include "CPfSavedGamesDAO.h"
#include "../utils/CLog.h"
#include "../utils/COptionManager.h"


CPfSavedGamesDAO::CPfSavedGamesDAO()
{
    const char *fileDB = COptionManager::getInstance()->getStringOption
            ("DataBase", "FilePath", "data/database/savedgames.sql3");
    if (sqlite3_open(fileDB, &m_dataBase) != SQLITE_OK) {
        sqlite3_close(m_dataBase);
        m_dataBase = NULL;
        CLog::getInstance()->exception("Can't open data base file: \"%s\" --> \"%s\"", fileDB, sqlite3_errmsg(m_dataBase));
    }
    CLog::getInstance()->info("Saved Games DAO initialized: <-- \"%s\"", fileDB);
}


CPfSavedGamesDAO::~CPfSavedGamesDAO()
{
    if(m_dataBase != NULL) {
        sqlite3_close(m_dataBase);
    }
}


CPfSavedGamesDAO* CPfSavedGamesDAO::getInstance()
{
    static CPfSavedGamesDAO instance;

    return &instance;
}


bool CPfSavedGamesDAO::deleteReg(CPfSavedGames * elem)
{
    std::string sql("DELETE FROM PF_SAVED_GAMES WHERE X_SAVED_GAME='");
    sql = sql + elem->getXSavedGame()->c_str() + "'";
    return exec(sql);
}


bool CPfSavedGamesDAO::insert(CPfSavedGames * elem)
{
    std::string sql("INSERT INTO PF_SAVED_GAMES \
                    (X_SAVED_GAME,S_USER,S_CONNECTION_STRING,\
                     S_SAVED_GAME,S_DRIVER) VALUES (");
    sql = sql + " '" + elem->getXSavedGame()->c_str() + "'";
    sql = sql + ",'" + elem->getSUser()->c_str() + "'";
    sql = sql + ",'" + elem->getSConnectionString()->c_str() + "'";
    sql = sql + ",'" + elem->getSSavedGame()->c_str() + "'";
    sql = sql + ",'" + elem->getSDriver()->c_str() + "'";
    sql = sql + ")";
    return exec(sql);
}


bool CPfSavedGamesDAO::update(CPfSavedGames * elem)
{
    std::string sql("UPDATE PF_SAVED_GAMES SET");

    sql = sql + "  S_USER='"
               + elem->getSUser()->c_str() + "'";
    sql = sql + ",  S_CONNECTION_STRING='"
               + elem->getSConnectionString()->c_str() + "'";
    sql = sql + ",  S_SAVED_GAME='"
               + elem->getSSavedGame()->c_str() + "'";
    sql = sql + ",  S_DRIVER='"
               + elem->getSDriver()->c_str() + "'";
    sql = sql + "  WHERE X_SAVED_GAME='"
              + elem->getXSavedGame()->c_str() + "'";

    return exec(sql);
}


CPfSavedGames* CPfSavedGamesDAO::findByXSavedGame(std::string val)
{
    CPfSavedGames *destiny = NULL;
    std::string sql = "SELECT * FROM PF_SAVED_GAMES";
    const char *aux = val.c_str();
    if (strcmp(aux,"") != 0) {
        sql = sql + " WHERE X_SAVED_GAME='" + aux + "'";
    }
    destiny = loadRegister(sql);
    return destiny;
}


bool CPfSavedGamesDAO::exec(string sql)
{
    char *msgError = NULL;
    bool correct = true;
    if (sqlite3_exec(m_dataBase, sql.c_str(), NULL, NULL, &msgError)
        != SQLITE_OK) {
        CLog::getInstance()->error( "Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError );
        sqlite3_free(msgError);
        correct = false;
    }
    return correct;
}


int CPfSavedGamesDAO::callbackRegister
    (void *object, int nColumns, char **vColumn, char **sColumn)
{
    int error = 1;
    if (object != NULL) {
        CPfSavedGames *destiny = (CPfSavedGames*)object;
        for (int i = 0; i < nColumns; i++) {
            if (strcmp(sColumn[i], "X_SAVED_GAME") == 0) {
                destiny->setXSavedGame(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_USER") == 0) {
                destiny->setSUser(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_CONNECTION_STRING") == 0) {
                destiny->setSConnectionString(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_SAVED_GAME") == 0) {
                destiny->setSSavedGame(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_DRIVER") == 0) {
                destiny->setSDriver(std::string(vColumn[i]));
            }
        }
        error = 0; // All is ok
    }
    return error;
}


int CPfSavedGamesDAO::callbackVector
    (void *object, int nColumns, char **vColumn, char **sColumn)
{
    if (object != NULL) {
        std::vector<CPfSavedGames*> *container;
        container = (std::vector<CPfSavedGames*> *)object;
        CPfSavedGames *destiny = new CPfSavedGames();
        for (int i = 0; i < nColumns; i++) {
            if (strcmp(sColumn[i], "X_SAVED_GAME") == 0) {
                destiny->setXSavedGame(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_USER") == 0) {
                destiny->setSUser(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_CONNECTION_STRING") == 0) {
                destiny->setSConnectionString(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_SAVED_GAME") == 0) {
                destiny->setSSavedGame(std::string(vColumn[i]));
            } else if (strcmp(sColumn[i], "S_DRIVER") == 0) {
                destiny->setSDriver(std::string(vColumn[i]));
            }
        }
        container->push_back(destiny);
    }
    return 0; // All is ok
}


CPfSavedGames* CPfSavedGamesDAO::loadRegister(string sql)
{
    char *msgError = NULL;
    CPfSavedGames *destiny = new CPfSavedGames();
    if (sqlite3_exec(m_dataBase, sql.c_str(), callbackRegister, destiny, &msgError)
        != SQLITE_OK) {
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return destiny;
}


vector<CPfSavedGames*> * CPfSavedGamesDAO::loadVector(string sql)
{
    char *msgError = NULL;
    vector<CPfSavedGames *> *container = new vector<CPfSavedGames *>;
    if (sqlite3_exec(m_dataBase, sql.c_str(), callbackVector, container, &msgError)
        != SQLITE_OK) {
        CLog::getInstance()->error("Error in SQL: \"%s\" --> \"%s\"", sql.c_str(), msgError);
        sqlite3_free(msgError);
    }
    return container;
}
