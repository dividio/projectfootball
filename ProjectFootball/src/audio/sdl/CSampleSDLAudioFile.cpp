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

#include "CSampleSDLAudioFile.h"
#include "../../utils/CLog.h"

CSampleSDLAudioFile::CSampleSDLAudioFile(std::string filepath)
{
    m_filepath  = filepath;
    m_channel   = -1;
    m_chunk     = Mix_LoadWAV(m_filepath.c_str());
    if( m_chunk==NULL ){
        CLog::getInstance()->exception("CSampleSDLAudioFile[filepath: %s]: %s", m_filepath.c_str(), Mix_GetError());
    }
}

CSampleSDLAudioFile::~CSampleSDLAudioFile()
{
    if( m_chunk!=NULL ){
        Mix_FreeChunk(m_chunk);
        m_chunk = NULL;
    }
}

bool CSampleSDLAudioFile::isPaused()
{
    if( m_channel==-1 ){
        return false;
    }else{
        return Mix_Paused(m_channel)==1;
    }

}

bool CSampleSDLAudioFile::isPlaying()
{
    if( m_channel==-1 ){
        return false;
    }else{
        return Mix_Playing(m_channel)==1;
    }

}

void CSampleSDLAudioFile::pause()
{
    if( m_channel==-1 ){
        if( isPlaying() ){
            Mix_Pause(m_channel);
        }else if( isPaused() ){
            Mix_Resume(m_channel);
        }
    }
}

void CSampleSDLAudioFile::play()
{
    if( m_channel==-1 ){
        m_channel = Mix_PlayChannel(-1, m_chunk, 0);
        CLog::getInstance()->info("Playing CSampleSDLAudioFile... [%s]", m_filepath.c_str());
    }else{
        if( isPlaying() ){
            stop();
            play();
        }else if( isPaused() ){
            pause();
        }else{
            Mix_PlayChannel(m_channel, m_chunk, 0);
            CLog::getInstance()->info("Playing CSampleSDLAudioFile... [%s]", m_filepath.c_str());
        }
    }
}

void CSampleSDLAudioFile::stop()
{
    if( m_channel!=-1 ){
        Mix_HaltChannel(m_channel);
    }
}
