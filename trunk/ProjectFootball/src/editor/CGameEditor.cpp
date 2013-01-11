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
#include "wh/CCompetitionEditorWindowHandler.h"
#include "wh/CStaffEditorWindowHandler.h"
#include "wh/CCountryEditorWindowHandler.h"
#include "wh/CStadiumEditorWindowHandler.h"

#include "../engine/CGameEngine.h"
#include "../exceptions/PFException.h"
#include "../singlePlayer/CSinglePlayerGame.h"
#include "../singlePlayer/option/CSinglePlayerOptionManager.h"
#include "../singlePlayer/CDataBaseGenerator.h"

#include "../utils/CLog.h"
#include "../utils/CResourceManager.h"

CGameEditor::CGameEditor(const std::string &dbStringName):
	m_windowHandlers(),	m_dbStringName(dbStringName)
{
    LOG_DEBUG("CGameEditor::CGameEditor");

    m_windowHandlers.push_back(new CGNSEditorWindowHandler(*this));
    m_windowHandlers.push_back(new CCountryEditorWindowHandler(*this));
	m_windowHandlers.push_back(new CStadiumEditorWindowHandler(*this));
	m_windowHandlers.push_back(new CCompetitionEditorWindowHandler(*this));
	m_windowHandlers.push_back(new CTeamEditorWindowHandler(*this));
	m_windowHandlers.push_back(new CStaffEditorWindowHandler(*this));

	m_daoFactory = new CDAOFactorySQLite(dbStringName);
	CDataBaseGenerator::generateDataBase(m_daoFactory);
	m_editorUtils.setDaoFactory(m_daoFactory);
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
	delete m_daoFactory;
}

CPfGames* CGameEditor::save()
{
	return 0;
}

const char* CGameEditor::getFirstScreenName()
{
	return "Editor";
}

IGame* CGameEditor::load()
{
    LOG_DEBUG("CGameEditor::load");

	CGameEditor *gameEditor = new CGameEditor(CResourceManager::getInstance()->getDbFileName());

	return gameEditor;
}
 
const std::string CGameEditor::getConnString() const
{
	return m_dbStringName;
}

CDAOFactorySQLite *CGameEditor::getDAOFactory()
{
	return m_daoFactory;
}

CEditorUtils &CGameEditor::getEditorUtilsObj()
{
	return m_editorUtils;
}
