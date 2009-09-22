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

#include "CConfigGameWindowHandler.h"

#include <libintl.h>

#include "../CSinglePlayerGame.h"
#include "../option/CSinglePlayerOptionManager.h"
#include "../../engine/CGameEngine.h"
#include "../../engine/option/CSystemOptionManager.h"
#include "../../CApplication.h"
#include "../../utils/CLog.h"

CConfigGameWindowHandler::CConfigGameWindowHandler(CSinglePlayerGame &game)
: CWindowHandler("configGame.layout"),
  m_game(game),
  m_initiated(false)
{
    LOG_DEBUG("CConfigGameWindowHandler()");
}

CConfigGameWindowHandler::~CConfigGameWindowHandler()
{
    LOG_DEBUG("~CConfigGameWindowHandler()");
    if( m_initiated ){
        m_simulationTimeCombo->clearAllSelections();
        m_simulationTimeCombo->resetList();
        m_simulationTimeCombo->getEditbox()->setText("");
    }
}

void CConfigGameWindowHandler::enter()
{
    m_resultModeCheck->setSelected(m_game.getOptionManager()->getMatchResultMode());

    bool found  = false;
    unsigned int  cicles  = m_game.getOptionManager()->getMatchDuration();

    m_simulationTimeCombo->clearAllSelections();
    m_simulationTimeCombo->resetList();
    m_simulationTimeCombo->getEditbox()->setText("");
    m_simulationTimeCombo->getEditbox()->setEnabled(false);
    m_simulationTimeCombo->addItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)gettext("1 minute"),  1800));
    m_simulationTimeCombo->addItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)gettext("2 minutes"), 3600));
    m_simulationTimeCombo->addItem(new CEGUI::ListboxTextItem((CEGUI::utf8*)gettext("5 minutes"), 9000));


    for( unsigned int i=0; i<m_simulationTimeCombo->getItemCount() && !found; i++ ){
        CEGUI::ListboxItem *item = m_simulationTimeCombo->getListboxItemFromIndex(i);
        if( item->getID()==cicles ){
            found = true;
            m_simulationTimeCombo->setItemSelectState(item, true);
            m_simulationTimeCombo->setText(item->getText());
        }
    }
}

void CConfigGameWindowHandler::init()
{
	CEGUI::WindowManager *windowMngr = CEGUI::WindowManager::getSingletonPtr();

    m_saveButton		= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"ConfigGame/SaveButton"));
    registerEventConnection(m_saveButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CConfigGameWindowHandler::saveButtonClicked, this)));

    m_simulationTimeCombo = static_cast<CEGUI::Combobox*>(windowMngr->getWindow((CEGUI::utf8*)"ConfigGame/SimulationTimeCombo"));
    m_resultModeCheck     = static_cast<CEGUI::Checkbox*>(windowMngr->getWindow((CEGUI::utf8*)"ConfigGame/ResultModeCheckbox"));

    // i18n support
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"ConfigGame/GameOptionsLabel"))->setText((CEGUI::utf8*)gettext("Game Options"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"ConfigGame/SimulationTimeText"))->setText((CEGUI::utf8*)gettext("Match Duration:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"ConfigGame/ResultModeText"))->setText((CEGUI::utf8*)gettext("Result Mode:"));
    m_saveButton       ->setText((CEGUI::utf8*)gettext("Save"));
}

bool CConfigGameWindowHandler::saveButtonClicked(const CEGUI::EventArgs& e)
{
    try {
        m_game.getOptionManager()->setMatchResultMode(m_resultModeCheck->isSelected());

        CEGUI::ListboxItem *item = m_simulationTimeCombo->getSelectedItem();
        if( item!=NULL ){
            switch( item->getID() ){
            case 1800:
                m_game.getOptionManager()->setMatchDuration(1800);
                break;
            case 3600:
                m_game.getOptionManager()->setMatchDuration(3600);
                break;
            case 9000:
                m_game.getOptionManager()->setMatchDuration(9000);
                break;
            }
        }

        CGameEngine::getInstance()->getWindowManager()->alert(gettext("Game options saved"));
    } catch(...) {
        CGameEngine::getInstance()->getWindowManager()->alert(gettext("ATTENTION: Options can not be saved"));
    }

	return true;
}
