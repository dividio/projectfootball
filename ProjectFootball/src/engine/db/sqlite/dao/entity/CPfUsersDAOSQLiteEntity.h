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
*       Version: 1.6                                                          *
******************************************************************************/

#ifndef CPFUSERSDAOSQLITEENTITY_H_
#define CPFUSERSDAOSQLITEENTITY_H_

#include <string>
#include <vector>
#include <sqlite3.h>

#include "../../../bean/CPfUsers.h"
#include "../../../dao/IPfUsersDAO.h"

class CPfUsersDAOSQLiteEntity : public IPfUsersDAO
{
public:
    CPfUsersDAOSQLiteEntity(sqlite3 *database);
    virtual ~CPfUsersDAOSQLiteEntity();

    virtual bool deleteReg(CPfUsers *reg);
    virtual bool insertReg(CPfUsers *reg);
    virtual bool updateReg(CPfUsers *reg);

    virtual void freeVector(std::vector<CPfUsers*>* vector);

protected:
    CPfUsers* loadRegister(std::string sql);
    std::vector<CPfUsers*>* loadVector(std::string sql);

private:
    bool exec(std::string sql);
    static int callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn );
    static int callbackVector(void *object, int nColumns, char **vColumn, char **sColumn );

    sqlite3 *m_database;

};
#endif /*CPFUSERSDAOSQLITEENTITY_H_*/
