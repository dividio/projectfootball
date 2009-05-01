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

#include "CLuaFunctor.h"
#include "CLog.h"

CLuaFunctor::CLuaFunctor()
{
}


CLuaFunctor::CLuaFunctor(lua_State* state, const CEGUI::String& func)
{
  m_luaVM = state;
  m_function = func;
  m_index = LUA_NOREF;
  m_initFlag = true;
}


CLuaFunctor::~CLuaFunctor()
{
}


bool CLuaFunctor::operator()(const CEGUI::EventArgs& args) const
{
    // is this a late binding?
    if (m_initFlag)
    {
        int top = lua_gettop(m_luaVM);
        lua_getglobal(m_luaVM, m_function.c_str());

        // is it a function
        if (!lua_isfunction(m_luaVM,-1))
        {
            lua_settop(m_luaVM,top);
            LOG_ERROR("Unable to call Lua global: '%s' as name not represent a global Lua function", m_function.c_str());
            return true;
        }
        // reference function
        m_index = luaL_ref(m_luaVM, LUA_REGISTRYINDEX);
        m_initFlag = false;
        LOG_DEBUG("Late binding of callback '%s' performed", m_function.c_str());
        m_function.clear();
    }

    // retrieve function
    lua_rawgeti(m_luaVM, LUA_REGISTRYINDEX, m_index);

    int error = lua_pcall(m_luaVM, 0, 0, 0);

    // handle errors
    switch (error) {
        case LUA_ERRRUN:
            LOG_ERROR("Runtime error in %s", m_function.c_str());
            lua_pop(m_luaVM, 1);
            break;
        case LUA_ERRMEM:
            LOG_ERROR("Memory alocation error in %s", m_function.c_str());
            lua_pop(m_luaVM, 1);
            break;
        case LUA_ERRERR:
            LOG_ERROR("Error handler error in %s", m_function.c_str());
            lua_pop(m_luaVM, 1);
            break;
        default:
            break;
    }

    return true;
}
