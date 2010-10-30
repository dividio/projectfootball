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

#ifndef CSDLAUDIOFACTORY_H_
#define CSDLAUDIOFACTORY_H_

#include <list>

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "../dummy/CDummyAudioFile.h"
#include "../IAudioFactory.h"

#define AUDIO_FREQUENCY 44100
#define AUDIO_FORMAT    MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS  2
#define AUDIO_BUFFERS   4096


class CSDLAudioFactory : public IAudioFactory
{
friend class CAudioAbstractFactory;
public:
	virtual ~CSDLAudioFactory();
    virtual IAudioFile* createSampleAudioFile(std::string filepath);
    virtual IAudioFile* createMusicAudioFile(std::string filepath);

private:
    CSDLAudioFactory();
    IAudioFile* createDummyAudioFile();

    bool                    m_sdlInitialized;
    int                     m_frequency;
    Uint16                  m_format;
    int                     m_channels;
    std::list<IAudioFile*>  m_audioFileList;
};

#endif /*CSDLAUDIOFACTORY_H_*/
