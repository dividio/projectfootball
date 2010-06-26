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
*       Version: 1.23                                                         *
******************************************************************************/

#ifndef CPFSEASONSDAOSQLITEENTITY_H_
#define CPFSEASONSDAOSQLITEENTITY_H_

#include <string>
#include <vector>
#include <sqlite3.h>

#include "../../../bean/CPfSeasons.h"
#include "../../../dao/IPfSeasonsDAO.h"

class CPfSeasonsDAOSQLiteEntity : public IPfSeasonsDAO
{
public:
    CPfSeasonsDAOSQLiteEntity(sqlite3 *database);
    virtual ~CPfSeasonsDAOSQLiteEntity();

    void setSQLite(sqlite3 *database);

    virtual bool deleteReg(CPfSeasons *reg);
    virtual bool insertReg(CPfSeasons *reg);
    virtual bool updateReg(CPfSeasons *reg);

    virtual void freeVector(std::vector<CPfSeasons*>* vector);

protected:
    CPfSeasons* loadRegister(const std::string &sql);
    std::vector<CPfSeasons*>* loadVector(const std::string &sql);

private:
    bool exec(const std::string &sql);
    static int callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn );
    static int callbackVector(void *object, int nColumns, char **vColumn, char **sColumn );

    sqlite3 *m_database;

};
#endif /*CPFSEASONSDAOSQLITEENTITY_H_*/