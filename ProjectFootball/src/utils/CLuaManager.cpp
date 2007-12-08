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

#include "CLuaManager.h"
#include "CLog.h"

CLuaManager::CLuaManager()
{
    CLog::getInstance()->debug("CLuaManager()");
    m_luaVM = luaL_newstate();
    if(NULL == m_luaVM) {
        CLog::getInstance()->error("Error initializing lua");
    } else {
        luaL_openlibs(m_luaVM);
        luaopen_PF(m_luaVM);
    }
}


CLuaManager* CLuaManager::getInstance()
{
    static CLuaManager instance;
    return &instance;
}


CLuaManager::~CLuaManager()
{
    CLog::getInstance()->debug("~CLuaManager()");
    lua_close(m_luaVM);
}


void CLuaManager::runScript(char* file)
{
    if (luaL_loadfile(m_luaVM,file)==0) { // load and run the file
        int result = lua_pcall(m_luaVM,0,0,0);
        switch (result) {
            case LUA_ERRRUN:
                CLog::getInstance()->error("Runtime error in %s", file);
                break;
            case LUA_ERRMEM:
                CLog::getInstance()->error("Memory alocation error in %s", file);
                break;
            case LUA_ERRERR:
                CLog::getInstance()->error("Error handler error in %s", file);
                break;
            default:
                break;
        }
    } else {
      CLog::getInstance()->error("Unable to load %s", file);
    }
}
