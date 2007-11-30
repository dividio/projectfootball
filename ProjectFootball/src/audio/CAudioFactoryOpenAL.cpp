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

#include "string.h"

#include "CAudioFactoryOpenAL.h"



CAudioFactoryOpenAL::CAudioFactoryOpenAL()
{
  //Initialization
    m_device = alcOpenDevice(NULL);

    if(m_device) {
      m_context = alcCreateContext(m_device, NULL);
      alcMakeContextCurrent(m_context);
    }

    //Create Buffers
    alGetError();
    alGenBuffers(2, m_gBuffers);
    ALenum error;
    if((error = alGetError()) != AL_NO_ERROR) {
          //printf("alGenBuffers :", error);
          return;
    }



}



CAudioFactoryOpenAL::~CAudioFactoryOpenAL()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);

}


CAudioFactoryOpenAL* CAudioFactoryOpenAL::getInstance()
{
    static CAudioFactoryOpenAL instance;

    return &instance;
}


IAudioFile * CAudioFactoryOpenAL::createAudioFile(char * filepath)
{
  return  0;
}
