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

#ifndef CLUAFUNCTOR_H_
#define CLUAFUNCTOR_H_

#include "CEGUI.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class CLuaFunctor
{
public:
  CLuaFunctor();
  CLuaFunctor(lua_State* state, const CEGUI::String& func);
  ~CLuaFunctor();

  bool operator()(const CEGUI::EventArgs& args) const;

private:
  mutable CEGUI::String m_function;
  mutable int m_index;
  lua_State* m_luaVM;
  mutable bool m_initFlag;
};

#endif // CLUAFUNCTOR_H_
