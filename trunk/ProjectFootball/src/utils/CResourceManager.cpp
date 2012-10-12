/******************************************************************************
* Copyright (C) 2009 - Ikaro Games   www.ikarogames.com                       *
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

#include <stdio.h>
#include <boost/filesystem.hpp>
#include <Ogre.h>

#include "../projectfootball_config.h"
#include "CResourceManager.h"
#include "CLog.h"
#include "../engine/option/CSystemOptionManager.h"
#include "../exceptions/PFException.h"

extern std::string dataPath;


CResourceManager* CResourceManager::getInstance()
{
    static CResourceManager instance;
    return &instance;
}

CResourceManager::CResourceManager()
{
    LOG_DEBUG("CResourceManager()");
}

CResourceManager::~CResourceManager()
{
    LOG_DEBUG("~CResourceManager()");
}

void CResourceManager::defineResources()
{
    defineGeneral();
    defineShields();
    defineConfederations();
    defineFlags();
    defineSkin();
    definePhotos();
}

void CResourceManager::defineGeneral()
{
    Ogre::String archName, typeName, secName;
    archName = CONCAT_PATH(dataPath, "/graphics/simulation/textures");
    typeName = "FileSystem";
    secName  = "General";
    boost::filesystem::path path(archName.c_str());
    if(boost::filesystem::is_directory(path)) {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    } else {
        throw PFEXCEPTION("Can't load \"%s\" directory", archName.c_str());
    }


    archName = CONCAT_PATH(dataPath, "/graphics/simulation/meshes");
    path = archName.c_str();
    if(boost::filesystem::is_directory(path)) {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    } else {
        throw PFEXCEPTION("Can't load \"%s\" directory", archName.c_str());
    }

    archName = CONCAT_PATH(dataPath, "/graphics/simulation/materials");
    path = archName.c_str();
    if(boost::filesystem::is_directory(path)) {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    } else {
        throw PFEXCEPTION("Can't load \"%s\" directory", archName.c_str());
    }
}

void CResourceManager::defineSkin()
{
    Ogre::String skin = CSystemOptionManager::getInstance()->getGUISkin();
    Ogre::String archName, typeName, secName;
    archName = (Ogre::String)CONCAT_PATH(dataPath, "/graphics/skins/") + skin;
    typeName = "FileSystem";
    secName  = skin;
    boost::filesystem::path path(archName.c_str());
    if(boost::filesystem::is_directory(path)) {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName+"/fonts", typeName, secName);
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName+"/imagesets", typeName, secName);
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName+"/layouts", typeName, secName);
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName+"/looknfeel", typeName, secName);
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName+"/lua_scripts", typeName, secName);
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName+"/schemes", typeName, secName);
    } else {
        throw PFEXCEPTION("Can't load \"%s\" directory", archName.c_str());
    }
}

void CResourceManager::defineShields()
{
    Ogre::String shields = CSystemOptionManager::getInstance()->getGUIShields();
    Ogre::String archName, typeName, secName;
    archName = (Ogre::String)CONCAT_PATH(dataPath, "/graphics/shields/") + shields;
    typeName = "FileSystem";
    secName  = shields;
    boost::filesystem::path path(archName.c_str());
    if(boost::filesystem::is_directory(path)) {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    } else {
        throw PFEXCEPTION("Can't load \"%s\" directory", archName.c_str());
    }
}

void CResourceManager::defineFlags()
{
    Ogre::String flags = CSystemOptionManager::getInstance()->getGUIFlags();
    Ogre::String archName, typeName, secName;
    archName = (Ogre::String)CONCAT_PATH(dataPath, "/graphics/countries/") + flags;
    typeName = "FileSystem";
    secName  = flags;
    boost::filesystem::path path(archName.c_str());
    if(boost::filesystem::is_directory(path)) {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    } else {
        throw PFEXCEPTION("Can't load \"%s\" directory", archName.c_str());
    }
}

void CResourceManager::defineConfederations()
{
    Ogre::String conf = CSystemOptionManager::getInstance()->getGUIConfederations();
    Ogre::String archName, typeName, secName;
    archName = (Ogre::String)CONCAT_PATH(dataPath, "/graphics/confederations/") + conf;
    typeName = "FileSystem";
    secName  = conf;
    boost::filesystem::path path(archName.c_str());
    if(boost::filesystem::is_directory(path)) {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    } else {
        throw PFEXCEPTION("Can't load \"%s\" directory", archName.c_str());
    }
}

void CResourceManager::definePhotos()
{
    Ogre::String photos = CSystemOptionManager::getInstance()->getGUIPhotos();
    Ogre::String archName, typeName, secName;
    archName = (Ogre::String)CONCAT_PATH(dataPath, "/graphics/photos/") + photos;
    typeName = "FileSystem";
    secName  = photos;
    boost::filesystem::path path(archName.c_str());
    if(boost::filesystem::is_directory(path)) {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    } else {
        throw PFEXCEPTION("Can't load \"%s\" directory", archName.c_str());
    }
}

