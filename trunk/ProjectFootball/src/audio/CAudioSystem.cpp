/******************************************************************************
* Copyright (C) 2007 - Ikaro Games   www.ikarogames.com                       *
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

#include <boost/filesystem/operations.hpp>

#include "projectfootball_config.h"
#include "CAudioSystem.h"
#include "CAudioAbstractFactory.h"

extern std::string dataPath;

CAudioSystem::CAudioSystem()
{
	m_audioAbstractFactory = new CAudioAbstractFactory();
}

CAudioSystem::~CAudioSystem()
{
	delete m_audioAbstractFactory;
}

CAudioSystem* CAudioSystem::getInstance()
{
    static CAudioSystem instance;
    return &instance;
}

IAudioFile* CAudioSystem::click()
{
	return m_audioAbstractFactory->getIAudioFactory()->createSampleAudioFile(CONCAT_PATH(dataPath,"audio/click.ogg"));
}

IAudioFile* CAudioSystem::mouseOver()
{
	return m_audioAbstractFactory->getIAudioFactory()->createSampleAudioFile(CONCAT_PATH(dataPath,"audio/mouseover.ogg"));
}

IAudioFile* CAudioSystem::lowKick()
{
	return m_audioAbstractFactory->getIAudioFactory()->createSampleAudioFile(CONCAT_PATH(dataPath,"audio/low_kick.ogg"));
}

void CAudioSystem::setAudioSystem(AudioSystemType audioSystemType)
{
	m_audioAbstractFactory->setAudioSystem(audioSystemType);
}
