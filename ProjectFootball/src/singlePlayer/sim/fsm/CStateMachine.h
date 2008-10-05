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
******************************************************************************/


#ifndef CSTATEMACHINE_H_
#define CSTATEMACHINE_H_

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <string>

#include "../../../utils/CLog.h"
#include "../../../utils/CLuaManager.h"
#include "../message/CMessage.h"


template <class T>
void pushObjectInLua(lua_State *luaVM, T *object)
{
    lua_getglobal(luaVM, "PF"); // push modulename
    lua_pushstring(luaVM, object->m_pCtorName.c_str());
    lua_gettable(luaVM, -2);
    lua_remove(luaVM, -2);     //remove table
    lua_pushlightuserdata(luaVM, (void *) object);
    lua_call(luaVM,1,1); // Ta-Da! swig-wrapped class pointer on the stack
}


template <class T>
void callFunction(const char *state, const char *function, T *entity)
{
    lua_State *luaVM = CLuaManager::getInstance()->getLuaVM();
    lua_settop(luaVM, 0);
    lua_getglobal(luaVM, state);
    if(!lua_istable(luaVM, -1)) {
        CLog::getInstance()->error("Scripted state \"%s\" doesn't exist", state);
    } else {
        lua_pushstring(luaVM, function);
        lua_gettable(luaVM, -2);
        if(!lua_isfunction(luaVM, -1)) {
            CLog::getInstance()->error("Function \"%s\" in state \"%s\" doesn't exist", function, state);
        } else {
            pushObjectInLua(luaVM, entity);
            int error = lua_pcall(luaVM, 1, 0, 0);
            // handle errors
            switch (error) {
                case LUA_ERRRUN:
                    CLog::getInstance()->error("Runtime error in \"%s\" function at state \"%s\" ", function, state);
                    lua_pop(luaVM, 1);
                    break;
                case LUA_ERRMEM:
                    CLog::getInstance()->error("Memory alocation error in \"%s\" function at state \"%s\" ", function, state);
                    lua_pop(luaVM, 1);
                    break;
                case LUA_ERRERR:
                    CLog::getInstance()->error("Error handler error in \"%s\" function at state \"%s\" ", function, state);
                    lua_pop(luaVM, 1);
                    break;
                default:
                    break;
            }
        }
    }
    lua_pop(luaVM, 1);
}


template <class T>
bool messageFunction(const char *state, const CMessage &message, T *entity)
{
    bool result = false;
    CMessage msg = message;
    lua_State *luaVM = CLuaManager::getInstance()->getLuaVM();
    lua_settop(luaVM, 0);
    lua_getglobal(luaVM, state);
    if(!lua_istable(luaVM, -1)) {
        CLog::getInstance()->error("Scripted state \"%s\" doesn't exist", state);
    } else {
        lua_pushstring(luaVM, "OnMessage");
        lua_gettable(luaVM, -2);
        if(!lua_isfunction(luaVM, -1)) {
            CLog::getInstance()->error("Function \"OnMessage\" in state \"%s\" doesn't exist", state);
        } else {
            pushObjectInLua(luaVM, entity);
            pushObjectInLua(luaVM, &msg);
            int error = lua_pcall(luaVM, 2, 1, 0);
            if(lua_isboolean(luaVM, -1)) {
                result = lua_toboolean(luaVM, -1);
            }
            // handle errors
            switch (error) {
                case LUA_ERRRUN:
                    CLog::getInstance()->error("Runtime error in \"OnMessage\" function at state \"%s\" ", state);
                    lua_pop(luaVM, 1);
                    break;
                case LUA_ERRMEM:
                    CLog::getInstance()->error("Memory alocation error in \"OnMessage\" function at state \"%s\" ", state);
                    lua_pop(luaVM, 1);
                    break;
                case LUA_ERRERR:
                    CLog::getInstance()->error("Error handler error in \"OnMessage\" function at state \"%s\" ", state);
                    lua_pop(luaVM, 1);
                    break;
                default:
                    break;
            }
        }
    }
    lua_pop(luaVM, 1);
    return result;
}





template <class entity_type>
class CStateMachine
{
public:
    CStateMachine(entity_type *owner)
    {
        m_owner = owner;
        m_globalState = "";
        m_currentState = "";
        m_previousState = "";
    };

    ~CStateMachine(){};

    void setCurrentState(std::string state) {m_currentState = state;};
    void setGlobalState(std::string state) {m_globalState = state;};
    void setPreviousState(std::string state) {m_previousState = state;};



    void update()
    {
        if(!m_globalState.empty()) {
            callFunction<entity_type>(m_globalState.c_str(), "Execute", m_owner);
        }
        if(!m_currentState.empty()) {
            callFunction<entity_type>(m_currentState.c_str(), "Execute", m_owner);
        }
    };

    void changeState(std::string newState)
    {
        if(!newState.empty()) {
            if(!m_currentState.empty()) {
                m_previousState = m_currentState;
                callFunction<entity_type>(m_currentState.c_str(), "Exit", m_owner);
            }
            m_currentState = newState;
            callFunction<entity_type>(m_currentState.c_str(), "Enter", m_owner);
        } else {
            CLog::getInstance()->error("Can not change to empty state.");
        }
    };

    bool handleMessage(const CMessage &message)
    {
        int result = false;
        if(!m_currentState.empty() &&
            messageFunction<entity_type>(m_currentState.c_str(), message, m_owner)) {
            result = true;
        }

        if(!m_globalState.empty() &&
            messageFunction<entity_type>(m_globalState.c_str(), message, m_owner)) {
            result = true;
        }
        return result;
    };

    void revertToPreviousState() {changeState(m_previousState);};

    std::string currentState() const {return m_currentState;};
    std::string previousState() const {return m_previousState;};
    std::string globalState() const {return m_globalState;};

    bool isInState(const std::string state) const { return (m_currentState == state);};


private:
    entity_type *m_owner;
    std::string m_globalState;
    std::string m_currentState;
    std::string m_previousState;
};

#endif // CSTATEMACHINE_H_
