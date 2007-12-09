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

#include "../../utils/CLog.h"
#include "CAudioFileOGGOpenAL.h"

CAudioFileOGGOpenAL::CAudioFileOGGOpenAL( std::string filepath )
{
	m_filepath = filepath;

	char *path = new char[filepath.size()];
	strcpy(path, filepath.c_str());
	int result = ov_fopen( path, &m_oggStream );
	delete []path;
    if( result<0)
    {
    	switch(result){
    	case OV_EREAD:
            CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: Could not open file.", m_filepath.c_str());
    		break;
    	case OV_ENOTVORBIS:
            CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: Bitstream does not contain any Vorbis data.", m_filepath.c_str());
    		break;
    	case OV_EVERSION:
            CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: Vorbis version mismatch.", m_filepath.c_str());
    		break;
    	case OV_EBADHEADER:
            CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: Invalid Vorbis bitstream header.", m_filepath.c_str());
    		break;
    	case OV_EFAULT:
            CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: Internal OGG/Vorbis logic fault.", m_filepath.c_str());
    		break;
    	default:
            CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: Unknown OGG/Vorbis error.", m_filepath.c_str());
    	}
    }

    m_vorbisInfo	= ov_info(&m_oggStream, -1);
    m_vorbisComment = ov_comment(&m_oggStream, -1);

    if(m_vorbisInfo->channels == 1){
        m_format = AL_FORMAT_MONO16;
    }else{
        m_format = AL_FORMAT_STEREO16;
    }

    checkOpenALError();
    alGenBuffers(2, m_buffers);
    checkOpenALError();
    alGenSources(1, &m_source);
    checkOpenALError();

    alSource3f(m_source, AL_POSITION,        0.0, 0.0, 0.0);
    alSource3f(m_source, AL_VELOCITY,        0.0, 0.0, 0.0);
    alSource3f(m_source, AL_DIRECTION,       0.0, 0.0, 0.0);
    alSourcef (m_source, AL_ROLLOFF_FACTOR,  0.0          );
    alSourcei (m_source, AL_SOURCE_RELATIVE, AL_TRUE      );
}

CAudioFileOGGOpenAL::~CAudioFileOGGOpenAL()
{
	stop();


    alDeleteSources(1, &m_source);
    checkOpenALError();
    alDeleteBuffers(2, m_buffers);
    checkOpenALError();

    ov_clear(&m_oggStream);
}

void CAudioFileOGGOpenAL::checkOpenALError()
{
	int error = alGetError();
	if( error!=AL_NO_ERROR ){
		CLog::getInstance()->error("OpenAL error [errorCode: %d]", error);
	}
}

bool CAudioFileOGGOpenAL::isPaused()
{
    ALenum state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);

    return (state == AL_PAUSED);
}

bool CAudioFileOGGOpenAL::isPlaying()
{
    ALenum state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);

    return (state == AL_PLAYING);
}

void CAudioFileOGGOpenAL::pause()
{
	if( isPlaying() ){
		alSourcePause(m_source);
	}else if( isPaused() ){
		alSourcePlay(m_source);
	}
}

void CAudioFileOGGOpenAL::play()
{
    if( isPlaying() ){
    	stop();
    	play();
    }else if( isPaused() ){
    	pause();
    }else{
    	fillDataBuffer(m_buffers[0]);
    	fillDataBuffer(m_buffers[1]);
        alSourceQueueBuffers(m_source, 2, m_buffers);
        alSourcePlay(m_source);
    }
}

void CAudioFileOGGOpenAL::stop()
{
	if( isPlaying() || isPaused() ){
		alSourceStop(m_source);
		ov_time_seek(&m_oggStream, 0.0);

	    // unqueue remaining buffers in source
	    int queued = 0;
	    alGetSourcei(m_source, AL_BUFFERS_QUEUED, &queued);
	    while(queued>0)
	    {
	        ALuint buffer;
	        alSourceUnqueueBuffers(m_source, 1, &buffer);
	        checkOpenALError();
	        queued--;
	    }
	}
}

void CAudioFileOGGOpenAL::update()
{
	if( isPlaying() ){

	    int processed;
	    alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &processed);

	    while(processed--)
	    {
	        ALuint buffer;

	        checkOpenALError();
	        alSourceUnqueueBuffers(m_source, 1, &buffer);
	        checkOpenALError();

	        fillDataBuffer(buffer);

	        checkOpenALError();
	        alSourceQueueBuffers(m_source, 1, &buffer);
	        checkOpenALError();
	    }
	}
}

void CAudioFileOGGOpenAL::fillDataBuffer( ALuint buffer )
{
    char data[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;

    bool eof = false;
    while( size<BUFFER_SIZE && !eof ){

        result = ov_read(&m_oggStream, data + size, BUFFER_SIZE - size, 0, 2, 1, &section);
        if( result==0 ){
        	eof = true;
        }else if( result<0 ){
        	switch(result){
        	case OV_HOLE:
                CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: There was an interruption in the data.", m_filepath.c_str());
        		break;
        	case OV_EBADLINK:
                CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: Invalid stream section was supplied to libvorbisfile, or the requested link is corrupt.", m_filepath.c_str());
        		break;
        	default:
                CLog::getInstance()->exception("CAudioFileOGGOpenAL[filepath: %s]: Unknown OGG/Vorbis error.", m_filepath.c_str());
        	}
        }else{
        	size += result;
        }
    }

    if(size>0){
    	checkOpenALError();
    	alBufferData(buffer, m_format, data, size, m_vorbisInfo->rate);
    	checkOpenALError();
    }
}
