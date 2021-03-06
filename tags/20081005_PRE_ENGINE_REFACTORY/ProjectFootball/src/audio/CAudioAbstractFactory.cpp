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
#include "sdl/CSDLAudioFactory.h"

IAudioFactory* CAudioAbstractFactory::m_instance = NULL;

CAudioAbstractFactory::CAudioAbstractFactory()
{

}


CAudioAbstractFactory::~CAudioAbstractFactory()
{

}


IAudioFactory* CAudioAbstractFactory::getIAudioFactory()
{
    int type = 1;
    if (m_instance==NULL) {
        switch (type) {
            case 1:
                m_instance = CSDLAudioFactory::getInstance();
                break;
            default:
                m_instance = CSDLAudioFactory::getInstance();
        }
    }
    return m_instance;
}
