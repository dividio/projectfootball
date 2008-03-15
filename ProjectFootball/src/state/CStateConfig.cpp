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
{
    CLog::getInstance()->debug("CStateConfig()");
    m_sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"config.layout");

    CEGUI::Combobox* resolutionCombo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/ResolutionCombo"));
    resolutionCombo->getEditbox()->setEnabled(false);
    resolutionCombo->addItem(new CEGUI::ListboxTextItem("1280x1024", 1280));
    resolutionCombo->addItem(new CEGUI::ListboxTextItem("1024x768",  1024));
    resolutionCombo->addItem(new CEGUI::ListboxTextItem("800x600",   800));

    CEGUI::Combobox* rendererCombo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/RendererCombo"));
    rendererCombo->getEditbox()->setEnabled(false);
    Ogre::RenderSystemList *renderSystemList = CApplication::getInstance()->getRenderSystemList();
    Ogre::RenderSystemList::iterator it;
    for( it=renderSystemList->begin(); it!=renderSystemList->end(); it++ ){
        Ogre::RenderSystem *renderSystem = (*it);
        rendererCombo->addItem(new CEGUI::ListboxTextItem(renderSystem->getName()));
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

    CEGUI::Checkbox* fullscreenCheck = static_cast<CEGUI::Checkbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/FullScreenCheck"));
    fullscreenCheck->setSelected(CSystemOptionManager::getInstance()->getBooleanOption("Video", "Fullscreen"));

    CEGUI::Checkbox* vSyncCheck = static_cast<CEGUI::Checkbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/VSyncCheck"));
    vSyncCheck->setSelected(CSystemOptionManager::getInstance()->getBooleanOption("Video", "VSync"));

    bool found  = false;
    int  width  = CSystemOptionManager::getInstance()->getIntOption("Video", "Width");
    CEGUI::Combobox* resolutionCombo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/ResolutionCombo"));
    for( int i=0; i<resolutionCombo->getItemCount() && !found; i++ ){
        CEGUI::ListboxItem *item = resolutionCombo->getListboxItemFromIndex(i);
        if( item->getID()==width ){
            found = true;
            resolutionCombo->setItemSelectState(item, true);
            resolutionCombo->setText(item->getText());
        }
    }

    found  = false;
    const char *renderer  = CSystemOptionManager::getInstance()->getStringOption("Video", "RenderSystem");
    CEGUI::Combobox* rendererCombo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/RendererCombo"));
    for( int i=0; i<rendererCombo->getItemCount() && !found; i++ ){
        CEGUI::ListboxItem *item = rendererCombo->getListboxItemFromIndex(i);
        if( item->getText()==renderer ){
            found = true;
            rendererCombo->setItemSelectState(item, true);
            rendererCombo->setText(item->getText());
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
    CEGUI::Checkbox* fullscreenCheck = static_cast<CEGUI::Checkbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/FullScreenCheck"));
    CSystemOptionManager::getInstance()->setBooleanOption("Video", "Fullscreen", fullscreenCheck->isSelected());

    CEGUI::Checkbox* vSyncCheck = static_cast<CEGUI::Checkbox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/VSyncCheck"));
    CSystemOptionManager::getInstance()->setBooleanOption("Video", "VSync", vSyncCheck->isSelected());

    CEGUI::Combobox* resolutionCombo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/ResolutionCombo"));
    CEGUI::ListboxItem *item = resolutionCombo->getSelectedItem();
    if( item!=NULL ){
        switch( item->getID() ){
        case 1280:
            CSystemOptionManager::getInstance()->setIntOption("Video", "Width", 1280);
            CSystemOptionManager::getInstance()->setIntOption("Video", "Height", 1024);
            break;
        case 1024:
            CSystemOptionManager::getInstance()->setIntOption("Video", "Width", 1024);
            CSystemOptionManager::getInstance()->setIntOption("Video", "Height", 768);
            break;
        case 800:
            CSystemOptionManager::getInstance()->setIntOption("Video", "Width", 800);
            CSystemOptionManager::getInstance()->setIntOption("Video", "Height", 600);
            break;
        }
    }

    CEGUI::Combobox* rendererCombo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Config/RendererCombo"));
    CSystemOptionManager::getInstance()->setStringOption("Video", "RenderSystem", rendererCombo->getText().c_str());
}
