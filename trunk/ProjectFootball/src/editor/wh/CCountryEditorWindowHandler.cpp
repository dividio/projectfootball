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

#include "CCountryEditorWindowHandler.h"

#include <libintl.h>

#include "../CGameEditor.h"

#include "../../engine/CGameEngine.h"
#include "../../utils/CLog.h"

#include <boost/lambda/bind.hpp> 

CCountryEditorWindowHandler::CCountryEditorWindowHandler(CGameEditor &editor) :
	CWindowHandler("countryEditor.layout"),
	m_editor(editor),
	m_initiated(false)
{
    LOG_DEBUG("CCountryEditorWindowHandler()");
}

CCountryEditorWindowHandler::~CCountryEditorWindowHandler()
{
    LOG_DEBUG("~CCountryEditorWindowHandler()");
}

void CCountryEditorWindowHandler::enter()
{

}

void CCountryEditorWindowHandler::init()
{
	CEGUI::WindowManager &windowMngr = CEGUI::WindowManager::getSingleton();

	m_searchButton = static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/SearchGo"));
	m_clearButton = static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/SearchClear"));
    m_searchQueryEditbox = static_cast<CEGUI::Editbox*>(windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/SearchQuery"));
    m_searchResultsListbox = static_cast<CEGUI::Listbox*>(windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/SearchResultsList"));
	m_searchButton = static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/SearchGo"));
	m_clearButton = static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/SearchClear"));
	m_updateEntryButton = static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/UpdateEntry"));
	m_clearEntryButton = static_cast<CEGUI::PushButton*>(windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/ClearEntry"));

	windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/CountryEditorLabel")->setText((CEGUI::utf8*)gettext("Not Implemented Yet."));
	windowMngr.getWindow((CEGUI::utf8*)"CountryEditor/SearchBoxLabel")->setText((CEGUI::utf8*)gettext("Search:"));

	registerEventConnection(m_searchButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CCountryEditorWindowHandler::searchButtonClicked, this)));
	registerEventConnection(m_clearButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CCountryEditorWindowHandler::searchClearButtonClicked, this)));
	registerEventConnection(m_searchResultsListbox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&CCountryEditorWindowHandler::searchResultsListboxSelectionChanged, this)));
	registerEventConnection(m_updateEntryButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CCountryEditorWindowHandler::entryUpdateButtonClicked, this)));
	registerEventConnection(m_clearEntryButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CCountryEditorWindowHandler::entryClearButtonClicked, this)));

	m_searchButton->setEnabled(true);
	m_searchButton->setText("Search");
	m_clearButton->setEnabled(false);
	m_clearButton->setText("Clear");
	m_updateEntryButton->setEnabled(true);
	m_updateEntryButton->setText("Update Entry");
	m_clearEntryButton->setEnabled(false);
	m_clearEntryButton->setText("Clear Entry");

	m_initiated = true;
}

void CCountryEditorWindowHandler::leave()
{

}

bool CCountryEditorWindowHandler::entryClearButtonClicked(const CEGUI::EventArgs &e)
{
	m_clearEntryButton->setEnabled(false);
	return true;
}

bool CCountryEditorWindowHandler::entryUpdateButtonClicked(const CEGUI::EventArgs &e)
{
	return true;
}

void CCountryEditorWindowHandler::populateEntry(std::vector< CPfCountries * >::iterator it, std::string *label, unsigned int *id)
{
	CPfCountries *country = *it;
	label->append(country->getSCountry_str());
	*id = country->getXCountry();
}

bool CCountryEditorWindowHandler::searchButtonClicked(const CEGUI::EventArgs &e)
{
	if (!m_searchQueryEditbox->getText().empty()) {
		std::string query_text = m_searchQueryEditbox->getText().c_str();
		std::vector< CPfCountries* > *query_res = m_editor.getDAOFactory()->getIPfCountriesDAO()->findByName(query_text);

		if (query_res and query_res->size()) {
			struct for_each_if_data data;
			data.list = m_searchResultsListbox;
			data.button = m_clearButton;
			data.clearList = true;
			m_editor.getEditorUtilsObj().for_each< std::vector< CPfCountries* >::iterator >(
				&data, query_res->begin(), query_res->end(),
				boost::lambda::bind(&CCountryEditorWindowHandler::populateEntry,
									this, boost::lambda::_1, boost::lambda::_2,
									boost::lambda::_3));
		}
	}
	return true;
}

bool CCountryEditorWindowHandler::searchClearButtonClicked(const CEGUI::EventArgs &e)
{
	m_clearButton->setEnabled(false);
	m_searchResultsListbox->resetList();
	m_searchQueryEditbox->setText("");
	return true;
}

bool CCountryEditorWindowHandler::searchResultsListboxSelectionChanged(const CEGUI::EventArgs &e)
{
	m_clearEntryButton->setEnabled(true);
	return true;
}