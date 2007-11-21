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


#ifndef __CPfEquiposDAOSqlite_H__
#define __CPfEquiposDAOSqlite_H__

#include <sqlite3.h>

#include "CPfEquiposDAOSqliteEntity.h"

class CPfEquiposDAOSqlite : public CPfEquiposDAOSqliteEntity
{

public:
    CPfEquiposDAOSqlite(sqlite3 *dataBase);
    virtual ~CPfEquiposDAOSqlite();

    //CPfEquipos* findByXFkPais(string XFkPais);
    std::vector<CPfEquipos*>* findVectorByXFkPais(std::string sql);
    CPfEquipos* findByXEquipo(string XEquipo);

};
#endif // __CPfEquiposDAOSqlite_H__
