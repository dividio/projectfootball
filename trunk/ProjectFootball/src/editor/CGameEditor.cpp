/******************************************************************************
* Copyright (C) 2012 - Ikaro Games   www.ikarogames.com                       *
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

#include "CGameEditor.h"

#include "wh/CGNSEditorWindowHandler.h"
#include "wh/CTeamEditorWindowHandler.h"

#include "../engine/CGameEngine.h"
#include "../exceptions/PFException.h"
#include "../singlePlayer/CSinglePlayerGame.h"
#include "../singlePlayer/db/dao/factory/IDAOFactory.h"
#include "../singlePlayer/option/CSinglePlayerOptionManager.h"
#include "../utils/CLog.h"


CGameEditor::CGameEditor() :
	m_windowHandlers()
{
    LOG_DEBUG("CGameEditor::CGameEditor");

    m_windowHandlers.push_back(new CGNSEditorWindowHandler());
    m_windowHandlers.push_back(new CTeamEditorWindowHandler(*this));
}

CGameEditor::~CGameEditor()
{
    LOG_DEBUG("CGameEditor::~CGameEditor");

    if( !m_windowHandlers.empty() ){
		std::vector<IWindowHandler*>::iterator itWindowHandlers;
		for( itWindowHandlers=m_windowHandlers.begin(); itWindowHandlers!=m_windowHandlers.end(); itWindowHandlers++ ){
			delete (*itWindowHandlers);
		}
		m_windowHandlers.clear();
	}
}

CPfGames* CGameEditor::save()
{
//	CPfGames *game = m_game->save();
//	game->setSGameType(S_GAME_TYPE_FRIENDLYMATCH);
//	return game;
	return 0;
}

const char* CGameEditor::getFirstScreenName()
{
	return "Editor";
}

IGame* CGameEditor::load()
{
    LOG_DEBUG("CGameEditor::load");

    CGameEditor *gameEditor = new CGameEditor();

	return gameEditor;
}
