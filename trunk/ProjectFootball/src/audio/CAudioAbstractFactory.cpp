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

#include "CAudioAbstractFactory.h"
#include "IAudioFactory.h"
#include "dummy/CDummyAudioFactory.h"
#include "sdl/CSDLAudioFactory.h"
#include "../utils/CLog.h"


CAudioAbstractFactory::CAudioAbstractFactory()
:m_audioFactory(NULL), type(SDL)
{

}

CAudioAbstractFactory::~CAudioAbstractFactory()
{
	LOG_DEBUG("~CAudioAbstractFactory()");
	if (m_audioFactory!=NULL) {
			delete m_audioFactory;
	}
}

void CAudioAbstractFactory::setAudioSystem(AudioSystemType audioSystemType)
{
	type = audioSystemType;

	if (m_audioFactory!=NULL) {
			delete m_audioFactory;
			m_audioFactory = NULL;
	}
	if (m_audioFactory==NULL) {
		switch (type) {
			case DUMMY:
				m_audioFactory = new CDummyAudioFactory();
				break;
			case SDL:
				m_audioFactory = new CSDLAudioFactory();
				break;
			default:
				m_audioFactory = new CSDLAudioFactory();
		}
	}
}

IAudioFactory* CAudioAbstractFactory::getIAudioFactory()
{
	if (m_audioFactory==NULL) {
		setAudioSystem(type);
	}
    return m_audioFactory;
}
