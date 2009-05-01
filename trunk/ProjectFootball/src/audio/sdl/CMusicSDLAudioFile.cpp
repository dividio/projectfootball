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

#include "CMusicSDLAudioFile.h"
#include "../../exceptions/PFException.h"
#include "../../utils/CLog.h"

CMusicSDLAudioFile::CMusicSDLAudioFile( std::string filepath )
{
    m_filepath  = filepath;
    m_music     = Mix_LoadMUS(m_filepath.c_str());
    if( m_music==NULL ){
        throw PFEXCEPTION("CMusicSDLAudioFile[filepath: %s]: %s", m_filepath.c_str(), Mix_GetError());
    }
}

CMusicSDLAudioFile::~CMusicSDLAudioFile()
{
    if( m_music!=NULL ){
        Mix_FreeMusic(m_music);
        m_music = NULL;
    }
}

bool CMusicSDLAudioFile::isPaused()
{
    // Since SQL only allows play a music file at once,
    // we can only see the general state of music
    return Mix_PausedMusic()==1;
}

bool CMusicSDLAudioFile::isPlaying()
{
    // Since SQL only allows play a music file at once,
    // we can only see the general state of music
    return Mix_PlayingMusic()==1;
}

void CMusicSDLAudioFile::pause()
{
    // Since SQL only allows play a music file at once,
    // we can only set the general state of music
    if( isPlaying() ){
        Mix_PauseMusic();
    }else if( isPaused() ){
        Mix_ResumeMusic();
    }
}

void CMusicSDLAudioFile::play()
{
    // Since SQL only allows play a music file at once,
    // we can only set the general state of music
    if( isPlaying() || isPaused() ){
        Mix_HaltMusic();
        Mix_PlayMusic(m_music, 0);
        LOG_INFO("Playing CMusicSDLAudioFile... [%s]", m_filepath.c_str());
    }else{
        Mix_PlayMusic(m_music, 0);
        LOG_INFO("Playing CMusicSDLAudioFile... [%s]", m_filepath.c_str());
    }
}

void CMusicSDLAudioFile::stop()
{
    // Since SQL only allows play a music file at once,
    // we can only set the general state of music
    if( isPlaying() || isPaused() ){
        Mix_HaltMusic();
    }
}
