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

#ifndef CMUSICSDLAUDIOFILE_H_
#define CMUSICSDLAUDIOFILE_H_

#include <string>

#include "SDL/SDL_mixer.h"
#include "../IAudioFile.h"

class CMusicSDLAudioFile : public IAudioFile
{
public:
	CMusicSDLAudioFile(std::string filepath);
	virtual ~CMusicSDLAudioFile();

    virtual bool isPaused();
    virtual bool isPlaying();
    virtual void pause();
    virtual void play();
    virtual void stop();

private:
    Mix_Music   *m_music;
    std::string m_filepath;
};

#endif /*CMUSICSDLAUDIOFILE_H_*/
