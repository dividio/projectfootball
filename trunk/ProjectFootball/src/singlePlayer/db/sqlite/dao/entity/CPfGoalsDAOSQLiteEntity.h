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
*       Version: 1.22                                                         *
******************************************************************************/

#ifndef CPFGOALSDAOSQLITEENTITY_H_
#define CPFGOALSDAOSQLITEENTITY_H_

#include <string>
#include <vector>
#include <sqlite3.h>

#include "../../../bean/CPfGoals.h"
#include "../../../dao/IPfGoalsDAO.h"

class CPfGoalsDAOSQLiteEntity : public IPfGoalsDAO
{
public:
    CPfGoalsDAOSQLiteEntity(sqlite3 *database);
    virtual ~CPfGoalsDAOSQLiteEntity();

    void setSQLite(sqlite3 *database);

    virtual bool deleteReg(CPfGoals *reg);
    virtual bool insertReg(CPfGoals *reg);
    virtual bool updateReg(CPfGoals *reg);

    virtual void freeVector(std::vector<CPfGoals*>* vector);

protected:
    CPfGoals* loadRegister(const std::string &sql);
    std::vector<CPfGoals*>* loadVector(const std::string &sql);

private:
    bool exec(const std::string &sql);
    static int callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn );
    static int callbackVector(void *object, int nColumns, char **vColumn, char **sColumn );

    sqlite3 *m_database;

};
#endif /*CPFGOALSDAOSQLITEENTITY_H_*/
