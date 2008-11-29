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

#ifndef CPFGAMESDAOSQLITEENTITY_H_
#define CPFGAMESDAOSQLITEENTITY_H_

#include <string>
#include <vector>
#include <sqlite3.h>

#include "../../../bean/CPfGames.h"
#include "../../../dao/IPfGamesDAO.h"

class CPfGamesDAOSQLiteEntity : public IPfGamesDAO
{
public:
    CPfGamesDAOSQLiteEntity(sqlite3 *database);
    virtual ~CPfGamesDAOSQLiteEntity();

    void setSQLite(sqlite3 *database);

    virtual bool deleteReg(CPfGames *reg);
    virtual bool insertReg(CPfGames *reg);
    virtual bool updateReg(CPfGames *reg);

    virtual void freeVector(std::vector<CPfGames*>* vector);

protected:
    CPfGames* loadRegister(const std::string &sql);
    std::vector<CPfGames*>* loadVector(const std::string &sql);

private:
    bool exec(const std::string &sql);
    static int callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn );
    static int callbackVector(void *object, int nColumns, char **vColumn, char **sColumn );

    sqlite3 *m_database;

};
#endif /*CPFGAMESDAOSQLITEENTITY_H_*/
