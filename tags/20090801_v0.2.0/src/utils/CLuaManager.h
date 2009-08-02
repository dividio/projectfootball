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

#ifndef CLUAMANAGER_H_
#define CLUAMANAGER_H_

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

    int luaopen_PF(lua_State* L); // declare the wrapped module
    int luaopen_CEGUI(lua_State* L);
}

#include <CEGUI/CEGUIScriptModule.h>

class CLuaManager: public CEGUI::ScriptModule
{
public:
    static CLuaManager* getInstance();

    virtual ~CLuaManager();

    void executeScriptFile(const CEGUI::String& filename, const CEGUI::String& resourceGroup);
    int executeScriptGlobal(const CEGUI::String& function_name);
    bool executeScriptedEventHandler(const CEGUI::String& handler_name, const CEGUI::EventArgs& e);
    void executeString(const CEGUI::String& str);
    CEGUI::Event::Connection subscribeEvent(CEGUI::EventSet* target,
        const CEGUI::String& name, const CEGUI::String& subscriber_name);
    CEGUI::Event::Connection subscribeEvent(CEGUI::EventSet* target,
        const CEGUI::String& name, CEGUI::Event::Group group, const CEGUI::String& subscriber_name);
    void createBindings(void);
    void destroyBindings(void);
    void runScript(const char* file);

    lua_State* getLuaVM();
protected:
    lua_State* m_luaVM;

    CLuaManager();
};

#endif // CLUAMANAGER_H_
