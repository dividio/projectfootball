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

#include <ctype.h>
#include <Ogre.h>
#include <libintl.h>

#include "CConfigWindowHandler.h"
#include "../CGameEngine.h"
#include "../option/CSystemOptionManager.h"
#include "../../utils/CLog.h"

typedef struct _VideoMode {
	unsigned int width;
	unsigned int height;
} VideoMode;

VideoMode parseVideoMode(const char *str){
	VideoMode videoMode = {0};

	int i=0;
	for( ;str[i]!='\0' && !isdigit(str[i]); i++ );
	for( ;str[i]!='\0' && isdigit(str[i]); videoMode.width=videoMode.width*10+(str[i]-'0'), i++ );
	for( ;str[i]!='\0' && !isdigit(str[i]); i++ );
	for( ;str[i]!='\0' && isdigit(str[i]); videoMode.height=videoMode.height*10+(str[i]-'0'), i++ );

	return videoMode;
}

CConfigWindowHandler::CConfigWindowHandler()
: CWindowHandler("config.layout")
{
    LOG_DEBUG("CConfigWindowHandler()");
}

CConfigWindowHandler::~CConfigWindowHandler()
{
    LOG_DEBUG("~CConfigWindowHandler()");
}

void CConfigWindowHandler::enter()
{
    m_fullscreenCheck->setSelected(CSystemOptionManager::getInstance()->getVideoFullscreen());
    m_vSyncCheck->setSelected(CSystemOptionManager::getInstance()->getVideoVSync());
    m_soundEnabledCheck->setSelected(CSystemOptionManager::getInstance()->getSoundEnabled());

    bool found  = false;
    unsigned int  width  = CSystemOptionManager::getInstance()->getVideoWidth();
    unsigned int  height = CSystemOptionManager::getInstance()->getVideoHeight();
    for( unsigned int i=0; i<m_resolutionCombo->getItemCount() && !found; i++ ){
        CEGUI::ListboxItem *item = m_resolutionCombo->getListboxItemFromIndex(i);
        VideoMode videoMode = parseVideoMode(item->getText().c_str());
        if( videoMode.width==width && videoMode.height==height ){
            found = true;
            m_resolutionCombo->setItemSelectState(item, true);
            m_resolutionCombo->setText(item->getText());
        }
    }

    found  = false;
    const char *renderer  = CSystemOptionManager::getInstance()->getVideoRenderSystem();
    for( unsigned int i=0; i<m_rendererCombo->getItemCount() && !found; i++ ){
        CEGUI::ListboxItem *item = m_rendererCombo->getListboxItemFromIndex(i);
        if( item->getText()==renderer ){
            found = true;
            m_rendererCombo->setItemSelectState(item, true);
            m_rendererCombo->setText(item->getText());
        }
    }
}

void CConfigWindowHandler::init()
{
	CEGUI::WindowManager *windowMngr = CEGUI::WindowManager::getSingletonPtr();

    m_mainWindow        = static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Config/MainWindow"));
    m_acceptButton		= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"Config/AcceptButton"));
    registerEventConnection(m_acceptButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CConfigWindowHandler::saveButtonClicked, this)));

    m_cancelButton		= static_cast<CEGUI::PushButton*>(windowMngr->getWindow((CEGUI::utf8*)"Config/CancelButton"));
    registerEventConnection(m_cancelButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CConfigWindowHandler::backButtonClicked, this)));

    m_resolutionCombo   = static_cast<CEGUI::Combobox*>(windowMngr->getWindow((CEGUI::utf8*)"Config/ResolutionCombo"));
    m_rendererCombo     = static_cast<CEGUI::Combobox*>(windowMngr->getWindow((CEGUI::utf8*)"Config/RendererCombo"));
    m_fullscreenCheck   = static_cast<CEGUI::Checkbox*>(windowMngr->getWindow((CEGUI::utf8*)"Config/FullScreenCheck"));
    m_vSyncCheck        = static_cast<CEGUI::Checkbox*>(windowMngr->getWindow((CEGUI::utf8*)"Config/VSyncCheck"));
    m_soundEnabledCheck = static_cast<CEGUI::Checkbox*>(windowMngr->getWindow((CEGUI::utf8*)"Config/SoundEnabledCheck"));

    // i18n support
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Config/Video"))->setText((CEGUI::utf8*)gettext("Video"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Config/RendererText"))->setText((CEGUI::utf8*)gettext("Renderer:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Config/ResolutionText"))->setText((CEGUI::utf8*)gettext("Resolution:"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Config/FullScreenCheck"))->setText((CEGUI::utf8*)gettext("Fullscreen"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Config/VSyncCheck"))->setText((CEGUI::utf8*)gettext("Vertical Sync"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Config/Sound"))->setText((CEGUI::utf8*)gettext("Sound"));
    static_cast<CEGUI::Window*>(windowMngr->getWindow((CEGUI::utf8*)"Config/SoundEnabledCheck"))->setText((CEGUI::utf8*)gettext("Sound Enabled"));

    m_acceptButton       ->setText((CEGUI::utf8*)gettext("Accept"));
    m_cancelButton       ->setText((CEGUI::utf8*)gettext("Cancel"));

    m_rendererCombo->getEditbox()->setEnabled(false);
    Ogre::RenderSystemList *renderSystemList = Ogre::Root::getSingleton().getAvailableRenderers();
    Ogre::RenderSystemList::iterator it;
    for( it=renderSystemList->begin(); it!=renderSystemList->end(); it++ ){
        Ogre::RenderSystem *renderSystem = (*it);
        m_rendererCombo->addItem(new CEGUI::ListboxTextItem(renderSystem->getName()));
    }

    m_resolutionCombo->getEditbox()->setEnabled(false);
    Ogre::ConfigOptionMap &options = Ogre::Root::getSingleton().getRenderSystem()->getConfigOptions();
    Ogre::ConfigOptionMap::const_iterator itOptions;
    for( itOptions=options.begin(); itOptions!=options.end(); itOptions++ ){
    	Ogre::ConfigOption option = itOptions->second;
    	if( option.name=="Video Mode" ){
			Ogre::StringVector::const_iterator itValues;
			for( itValues=option.possibleValues.begin(); itValues!=option.possibleValues.end(); itValues++ ){
				m_resolutionCombo->addItem(new CEGUI::ListboxTextItem(itValues->c_str()));
			}
    	}
    }
}

bool CConfigWindowHandler::backButtonClicked(const CEGUI::EventArgs& e)
{
	CGameEngine::getInstance()->getWindowManager()->previousScreen();
	return true;
}

bool CConfigWindowHandler::saveButtonClicked(const CEGUI::EventArgs& e)
{
    try {
        CSystemOptionManager::getInstance()->setVideoFullscreen(m_fullscreenCheck->isSelected());
        CSystemOptionManager::getInstance()->setVideoVSync(m_vSyncCheck->isSelected());
        CSystemOptionManager::getInstance()->setSoundEnabled(m_soundEnabledCheck->isSelected());

        CEGUI::ListboxItem *item = m_resolutionCombo->getSelectedItem();
        if( item!=NULL ){
        	VideoMode videoMode = parseVideoMode(item->getText().c_str());
            CSystemOptionManager::getInstance()->setVideoWidth(videoMode.width);
            CSystemOptionManager::getInstance()->setVideoHeight(videoMode.height);
        }

        CSystemOptionManager::getInstance()->setVideoRenderSystem(m_rendererCombo->getText().c_str());
        CSystemOptionManager::getInstance()->saveOptions();
        CGameEngine::getInstance()->getWindowManager()->alert(gettext("Changes will take effect after restart"), CEGUI::Event::Subscriber(&CConfigWindowHandler::acceptConfirmed, this));
    } catch(...) {
        CGameEngine::getInstance()->getWindowManager()->alert(gettext("ATTENTION: Options can not be saved"));
    }

	return true;
}

bool CConfigWindowHandler::acceptConfirmed(const CEGUI::EventArgs &e)
{
	CGameEngine::getInstance()->getWindowManager()->previousScreen();
	return true;
}

