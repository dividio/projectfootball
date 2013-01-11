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

#ifndef CSTAFFEDITORWINDOWHANDLER_H_
#define CSTAFFEDITORWINDOWHANDLER_H_

#include <CEGUI/CEGUI.h>
#include "../singlePlayer/db/sqlite/dao/factory/CDAOFactorySQLite.h"
#include "../../engine/wm/CWindowHandler.h"

//Forward declarations
class CGameEditor;


class CStaffEditorWindowHandler : public CWindowHandler
{
	public:
		CStaffEditorWindowHandler(CGameEditor &editor);
		virtual ~CStaffEditorWindowHandler();

		virtual void enter();
		virtual void init();
		virtual void leave();

		bool searchResultsListboxSelectionChanged(const CEGUI::EventArgs& e);
		bool searchButtonClicked(const CEGUI::EventArgs& e);
		bool searchClearButtonClicked(const CEGUI::EventArgs& e);
		bool entryClearButtonClicked(const CEGUI::EventArgs& e);
		bool entryUpdateButtonClicked(const CEGUI::EventArgs& e);

	private:
		void populateEntryPlayer(std::vector< CPfTeamPlayers * >::iterator it, std::string *label, unsigned int *id);
		void populateEntryCoach(std::vector< CPfCoaches * >::iterator it, std::string *label, unsigned int *id);

		CGameEditor &m_editor;
		CEGUI::PushButton *m_searchButton, *m_clearButton;
		CEGUI::Editbox *m_searchQueryEditbox;
		CEGUI::Listbox *m_searchResultsListbox;
		bool m_initiated;
		CEGUI::PushButton *m_clearEntryButton;
		CEGUI::PushButton *m_updateEntryButton;
		entry_type *m_entryTypes;
};

#endif /*CSTAFFEDITORWINDOWHANDLER_H_*/
