/*******************************************************************************
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

#include "CGNSEditorWindowHandler.h"

#include <libintl.h>
#include "../../engine/CGameEngine.h"
#include "../../engine/wh/CGNSGenericWindowHandler.h"
#include "../../utils/CLog.h"

CGNSEditorWindowHandler::CGNSEditorWindowHandler(CGameEditor &editor) :
	CGNSGenericWindowHandler("DataEditor", "DataEditor"),
	m_editor(editor)
{}

CGNSEditorWindowHandler::~CGNSEditorWindowHandler()
{}

void CGNSEditorWindowHandler::enter()
{
	if (std::string("DataEditor") == CGameEngine::getInstance()->getWindowManager()->getCurrentScreen()) {
		m_noButtonsBackground->setVisible(true);
		m_buttonsBackground->setVisible(false);
		m_homeButton->setVisible(false);
		m_homeButton->setEnabled(false);
		m_nextScreenButton->setVisible(false);
		m_nextScreenButton->setEnabled(false);
		m_previousScreenButton->setVisible(false);
		m_previousScreenButton->setEnabled(false);
	} else {
		m_noButtonsBackground->setVisible(false);
		m_buttonsBackground->setVisible(true);
		m_homeButton->setVisible(true);
		m_homeButton->setEnabled(true);
		m_nextScreenButton->setVisible(true);
		m_nextScreenButton->setEnabled(true);
		m_previousScreenButton->setVisible(true);
		m_previousScreenButton->setEnabled(true);
	}

	CEGUI::RadioButton *button = m_changingRoomRadio->getSelectedButtonInGroup();
	//Forcing the GNS selection change event
	button->setSelected(false);
	button->setSelected(true);
}

bool CGNSEditorWindowHandler::gnsSelectionChanged(const CEGUI::EventArgs &e)
{
	CEGUI::RadioButton *button = m_changingRoomRadio->getSelectedButtonInGroup();
	if( button==m_changingRoomRadio ){
		m_action1Button->setText((CEGUI::utf8*)gettext("Countries"));
		m_action1Button->setUserString("screen", "CountryEditor");
		m_action1Button->setEnabled(true);
		m_action2Button->setText((CEGUI::utf8*)gettext("Stadiums"));
		m_action2Button->setUserString("screen", "StadiumEditor");
		m_action2Button->setEnabled(true);
		m_action3Button->setText((CEGUI::utf8*)gettext("Competitions"));
		m_action3Button->setUserString("screen", "CompetitionEditor");
		m_action3Button->setEnabled(true);
		m_action4Button->setText((CEGUI::utf8*)gettext("Teams"));
		m_action4Button->setUserString("screen", "TeamEditor");
 		m_action4Button->setEnabled(true);
		m_action5Button->setText((CEGUI::utf8*)gettext("Staffs"));
		m_action5Button->setUserString("screen", "StaffEditor");
		m_action5Button->setEnabled(true);

		m_action6Button->setText("");
		m_action6Button->setUserString("screen", "");
		m_action6Button->setEnabled(false);
		m_action7Button->setText("");
		m_action7Button->setUserString("screen", "");
		m_action7Button->setEnabled(false);
		m_action8Button->setText("");
		m_action8Button->setUserString("screen", "");
		m_action8Button->setEnabled(false);

	} else {
		m_action1Button->setText("");
		m_action1Button->setUserString("screen", "");
		m_action1Button->setEnabled(false);
		m_action2Button->setText("");
		m_action2Button->setUserString("screen", "");
		m_action2Button->setEnabled(false);
		m_action3Button->setText("");
		m_action3Button->setUserString("screen", "");
		m_action3Button->setEnabled(false);
		m_action4Button->setText("");
		m_action4Button->setUserString("screen", "");
		m_action4Button->setEnabled(false);
		m_action5Button->setText("");
		m_action5Button->setUserString("screen", "");
		m_action5Button->setEnabled(false);
		m_action6Button->setText("");
		m_action6Button->setUserString("screen", "");
		m_action6Button->setEnabled(false);
		m_action7Button->setText("");
		m_action7Button->setUserString("screen", "");
		m_action7Button->setEnabled(false);
		m_action8Button->setText("");
		m_action8Button->setUserString("screen", "");
		m_action8Button->setEnabled(false);
	}

	return true;
}
