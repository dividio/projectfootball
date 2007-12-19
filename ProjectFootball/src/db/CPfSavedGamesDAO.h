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


#ifndef __CPfSavedGamesDAO_H__
#define __CPfSavedGamesDAO_H__

#include <sqlite3.h>
#include <string>
#include <vector>

#include "CPfSavedGames.h"


class CPfSavedGamesDAO
{

public:
    ~CPfSavedGamesDAO();
    static CPfSavedGamesDAO* getInstance();

    bool deleteReg(CPfSavedGames * elem);
    bool insert(CPfSavedGames * elem);
    bool update(CPfSavedGames * elem);

    CPfSavedGames* findByXSavedGame(std::string XSavedGame);

private:
    sqlite3 *m_dataBase;

    CPfSavedGamesDAO();
    bool exec(std::string sql);
    static int callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn );
    static int callbackVector(void *object, int nColumns, char **vColumn, char **sColumn );
    CPfSavedGames* loadRegister(std::string sql);
    vector<CPfSavedGames*> * loadVector(std::string sql);
};
#endif // __CPfSavedGamesDAO_H__
