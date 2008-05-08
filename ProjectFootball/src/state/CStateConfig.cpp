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

#include <Ogre.h>

#include "CStateConfig.h"
#include "../utils/CLog.h"
#include "../engine/option/CSystemOptionManager.h"
#include "../CApplication.h"

CStateConfig::CStateConfig()
    :CState()
{
    CLog::getInstance()->debug("CStateConfig()");
    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"config.layout");

    m_resolutionCombo   = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/ResolutionCombo"));
    m_rendererCombo     = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/RendererCombo"));
    m_fullscreenCheck   = static_cast<CEGUI::Checkbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/FullScreenCheck"));
    m_vSyncCheck        = static_cast<CEGUI::Checkbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/VSyncCheck"));

    m_resolutionCombo->getEditbox()->setEnabled(false);
    m_resolutionCombo->addItem(new CEGUI::ListboxTextItem("1280x1024", 1280));
    m_resolutionCombo->addItem(new CEGUI::ListboxTextItem("1024x768",  1024));
    m_resolutionCombo->addItem(new CEGUI::ListboxTextItem("800x600",   800));

    m_rendererCombo->getEditbox()->setEnabled(false);
    Ogre::RenderSystemList *renderSystemList = CApplication::getInstance()->getRenderSystemList();
    Ogre::RenderSystemList::iterator it;
    for( it=renderSystemList->begin(); it!=renderSystemList->end(); it++ ){
        Ogre::RenderSystem *renderSystem = (*it);
        m_rendererCombo->addItem(new CEGUI::ListboxTextItem(renderSystem->getName()));
    }
}

CStateConfig* CStateConfig::getInstance()
{
    static CStateConfig instance;
    return &instance;
}

CStateConfig::~CStateConfig()
{
    CLog::getInstance()->debug("~CStateConfig()");
}

void CStateConfig::enter()
{
    m_system->setGUISheet(m_sheet);
    Ogre::SceneManager *mgr = m_root->getSceneManager("Default SceneManager");
    mgr->clearScene();

    m_fullscreenCheck->setSelected(CSystemOptionManager::getInstance()->getVideoFullscreen());
    m_vSyncCheck->setSelected(CSystemOptionManager::getInstance()->getVideoVSync());

    bool found  = false;
    int  width  = CSystemOptionManager::getInstance()->getVideoWidth();
    for( int i=0; i<m_resolutionCombo->getItemCount() && !found; i++ ){
        CEGUI::ListboxItem *item = m_resolutionCombo->getListboxItemFromIndex(i);
        if( item->getID()==width ){
            found = true;
            m_resolutionCombo->setItemSelectState(item, true);
            m_resolutionCombo->setText(item->getText());
        }
    }

    found  = false;
    const char *renderer  = CSystemOptionManager::getInstance()->getVideoRenderSystem();
    for( int i=0; i<m_rendererCombo->getItemCount() && !found; i++ ){
        CEGUI::ListboxItem *item = m_rendererCombo->getListboxItemFromIndex(i);
        if( item->getText()==renderer ){
            found = true;
            m_rendererCombo->setItemSelectState(item, true);
            m_rendererCombo->setText(item->getText());
        }
    }
}

void CStateConfig::forcedLeave()
{

}

bool CStateConfig::leave()
{
    return true;
}

void CStateConfig::update()
{
}

void CStateConfig::saveConfig()
{
    CSystemOptionManager::getInstance()->setVideoFullscreen(m_fullscreenCheck->isSelected());
    CSystemOptionManager::getInstance()->setVideoVSync(m_vSyncCheck->isSelected());

    CEGUI::ListboxItem *item = m_resolutionCombo->getSelectedItem();
    if( item!=NULL ){
        switch( item->getID() ){
        case 1280:
            CSystemOptionManager::getInstance()->setVideoWidth( 1280);
            CSystemOptionManager::getInstance()->setVideoHeight(1024);
            break;
        case 1024:
            CSystemOptionManager::getInstance()->setVideoWidth( 1024);
            CSystemOptionManager::getInstance()->setVideoHeight( 768);
            break;
        case 800:
            CSystemOptionManager::getInstance()->setVideoWidth(  800);
            CSystemOptionManager::getInstance()->setVideoHeight( 600);
            break;
        }
    }

    CSystemOptionManager::getInstance()->setVideoRenderSystem(m_rendererCombo->getText().c_str());
    CSystemOptionManager::getInstance()->saveOptions();
}
