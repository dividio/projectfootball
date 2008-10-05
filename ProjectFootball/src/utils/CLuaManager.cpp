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

#include "CEGUI.h"

#include "CLuaManager.h"
#include "CLog.h"
#include "CLuaFunctor.h"

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
    // set ID string
    d_identifierString = "CLuaManager - Project Football scripting module for Lua and CEGUI";
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


void CLuaManager::executeScriptFile(const CEGUI::String& filename, const CEGUI::String& resourceGroup)
{
    // load file
    CEGUI::RawDataContainer raw;
    CEGUI::System::getSingleton().getResourceProvider()->loadRawDataContainer(filename,
          raw, resourceGroup.empty() ? d_defaultResourceGroup : resourceGroup);

    // load code into lua
    int loaderr = luaL_loadbuffer(m_luaVM, (char*)raw.getDataPtr(), raw.getSize(), filename.c_str());
    CEGUI::System::getSingleton().getResourceProvider()->unloadRawDataContainer(raw);

    // call it
    if (loaderr==0) { // run the file
        int result = lua_pcall(m_luaVM,0,0,0);
        switch (result) {
            case LUA_ERRRUN:
                CLog::getInstance()->error("Runtime error in %s", filename.c_str());
                break;
            case LUA_ERRMEM:
                CLog::getInstance()->error("Memory alocation error in %s", filename.c_str());
                break;
            case LUA_ERRERR:
                CLog::getInstance()->error("Error handler error in %s", filename.c_str());
                break;
            default:
                break;
        }
    } else {
        CLog::getInstance()->error("Unable to load %s", filename.c_str());
    }
}


int CLuaManager::executeScriptGlobal(const CEGUI::String& function_name)
{
    int top = lua_gettop(m_luaVM);

    // get the function from lua
    lua_getglobal(m_luaVM, function_name.c_str());

    // is it a function
    if (!lua_isfunction(m_luaVM,-1))
    {
        lua_settop(m_luaVM,top);
        CLog::getInstance()->error("Unable to get Lua global: '%s' as name not represent a global Lua function", function_name.c_str());
        return -1;
    }

    // call it
    int error = lua_pcall(m_luaVM,0,1,0);

    // handle errors
    switch (error) {
        case LUA_ERRRUN:
            lua_settop(m_luaVM,top);
            CLog::getInstance()->error("Runtime error in %s global function", function_name.c_str());
            return -1;
        case LUA_ERRMEM:
            lua_settop(m_luaVM,top);
            CLog::getInstance()->error("Memory alocation error in %s global function", function_name.c_str());
            return -1;
        case LUA_ERRERR:
            lua_settop(m_luaVM,top);
            CLog::getInstance()->error("Error handler error in %s global function", function_name.c_str());
            return -1;
        default:
            break;
    }

    // get return value
    if (!lua_isnumber(m_luaVM,-1))
    {
        // log that return value is invalid. return -1 and move on.
        lua_settop(m_luaVM,top);
        CLog::getInstance()->error("Unable to get Lua global : '%s' return value as it's not a number", function_name.c_str());
        return -1;
    }

    int ret = (int)lua_tonumber(m_luaVM,-1);
    lua_pop(m_luaVM,1);

    // return it
    return ret;
}


bool CLuaManager::executeScriptedEventHandler(const CEGUI::String& handler_name, const CEGUI::EventArgs& e)
{

    // TODO search dots in handler name
    int top = lua_gettop(m_luaVM);
    lua_getglobal(m_luaVM, handler_name.c_str());

    // is it a function
    if (!lua_isfunction(m_luaVM,-1))
    {
        lua_settop(m_luaVM,top);
        CLog::getInstance()->error("Unable to get Lua event handler: '%s' as name not represent a global Lua function", handler_name.c_str());
        return true;
    }

    // TODO push CEGUI::EventArgs as the first parameter
    //tolua_pushusertype(d_state,(void*)&e,"const CEGUI::EventArgs");
    //lua_pushnil(m_luaVM);

    // call it
    //int error = lua_pcall(m_luaVM,1,0,0);
    int error = lua_pcall(m_luaVM,0,0,0);

    // handle errors
    switch (error) {
        case LUA_ERRRUN:
            CLog::getInstance()->error("Runtime error in %s event handler", handler_name.c_str());
            break;
        case LUA_ERRMEM:
            CLog::getInstance()->error("Memory alocation error in %s event handler", handler_name.c_str());
            break;
        case LUA_ERRERR:
            CLog::getInstance()->error("Error handler error in %s event handler", handler_name.c_str());
            break;
        default:
            break;
    }

    return true;
}


void CLuaManager::executeString(const CEGUI::String& str)
{
    int top = lua_gettop(m_luaVM);

    // load code into lua
    int loaderror =	luaL_loadbuffer(m_luaVM, str.c_str(), str.length(), str.c_str());
    if(loaderror == 0) {
        int error = lua_pcall(m_luaVM,0,0,0);

        // handle errors
        switch (error) {
            case LUA_ERRRUN:
                CLog::getInstance()->error("Runtime error in string: %s", str.c_str());
                lua_settop(m_luaVM,top);
                break;
            case LUA_ERRMEM:
                CLog::getInstance()->error("Memory alocation error in string: %s", str.c_str());
                lua_settop(m_luaVM,top);
                break;
            case LUA_ERRERR:
                CLog::getInstance()->error("Error handler error in string: %s", str.c_str());
                lua_settop(m_luaVM,top);
                break;
            default:
                break;
        }
    } else {
        CLog::getInstance()->error("Unable to load string: %s", str.c_str());
        lua_settop(m_luaVM,top);
    }

}


CEGUI::Event::Connection CLuaManager::subscribeEvent(CEGUI::EventSet* target,
    const CEGUI::String& event_name, const CEGUI::String& subscriber_name)
{
    CLuaFunctor functor(m_luaVM,subscriber_name);
    CEGUI::Event::Connection con = target->subscribeEvent(event_name, CEGUI::Event::Subscriber(functor));

    return con;
}


CEGUI::Event::Connection CLuaManager::subscribeEvent(CEGUI::EventSet* target,
    const CEGUI::String& event_name, CEGUI::Event::Group group, const CEGUI::String& subscriber_name)
{
    CLuaFunctor functor(m_luaVM,subscriber_name);
    CEGUI::Event::Connection con = target->subscribeEvent(event_name, group, CEGUI::Event::Subscriber(functor));

    return con;
}


void CLuaManager::createBindings(void)
{

}


void CLuaManager::destroyBindings(void)
{

}


void CLuaManager::runScript(const char* file)
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


lua_State* CLuaManager::getLuaVM()
{
    return m_luaVM;
}
