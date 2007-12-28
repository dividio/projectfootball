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

#ifndef CAUDIOFILEOGGOPENAL_H_
#define CAUDIOFILEOGGOPENAL_H_

#include <string>
#include <iostream>

#include <AL/al.h>
#include <vorbis/vorbisfile.h>

#include "../IAudioFile.h"

#define BUFFER_SIZE     (4096 * 8)
#define N_BUFFERS       2

class CAudioFileOGGOpenAL : public IAudioFile
{
public:
	CAudioFileOGGOpenAL( std::string filepath );
	virtual ~CAudioFileOGGOpenAL();

	virtual bool isPaused();
	virtual bool isPlaying();
	virtual void pause();
	virtual void play();
	virtual void stop();
	virtual void update();

private:
	void checkOpenALError();
	bool fillBuffer(ALuint buffer);
    void reset();

	std::string		m_filepath;
	OggVorbis_File 	m_oggStream;
	vorbis_info		*m_vorbisInfo;
	vorbis_comment	*m_vorbisComment;

    ALuint 			m_buffers[N_BUFFERS];
    ALuint 			m_source;
    ALenum			m_format;

};

#endif /*CAUDIOFILEOGGOPENAL_H_*/
