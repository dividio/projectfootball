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

#include "CSDLAudioFactory.h"
#include "CMusicSDLAudioFile.h"
#include "CSampleSDLAudioFile.h"
#include "../CDummyAudioFile.h"
#include "../../utils/CLog.h"

CSDLAudioFactory::CSDLAudioFactory()
    : m_audioFileList()
{
    if( SDL_Init(SDL_INIT_AUDIO)!=0 ){
        CLog::getInstance()->error(" Error during the initiation of SDL: %s", SDL_GetError());
        m_sdlInitialized = false;
        return;
    }

    if( Mix_OpenAudio( AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS )!=0 ){
        CLog::getInstance()->error(" Error during the initiation of SDL_mixer: %s", Mix_GetError());
        m_sdlInitialized = false;
        return;
    }

    if( Mix_QuerySpec(&m_frequency, &m_format, &m_channels)==0 ){
        CLog::getInstance()->error(" Error during the querySpec of SDL_mixer: %s", Mix_GetError());
        m_sdlInitialized = true;
    }else{
        const char * format_str = "";

        switch(m_format){
        case AUDIO_U8:      format_str = "U8";      break;
        case AUDIO_S8:      format_str = "S8";      break;
        case AUDIO_U16LSB:  format_str = "U16LSB";  break;
        case AUDIO_S16LSB:  format_str = "S16LSB";  break;
        case AUDIO_U16MSB:  format_str = "U16MSB";  break;
        case AUDIO_S16MSB:  format_str = "S16MSB";  break;
        }

        CLog::getInstance()->info("Audio enabled. SDL information:");
        CLog::getInstance()->info("  Frequency:  %d", m_frequency);
        CLog::getInstance()->info("  Format:     %s", format_str);
        CLog::getInstance()->info("  Channels:   %d", m_channels);
        m_sdlInitialized = true;
    }
}

CSDLAudioFactory::~CSDLAudioFactory()
{
    Mix_HaltChannel(-1);
    Mix_HaltMusic();

    Mix_CloseAudio();
    SDL_Quit();

    for( std::list<IAudioFile*>::iterator itAudioFiles = m_audioFileList.begin(); itAudioFiles!=m_audioFileList.end(); itAudioFiles++ ){
        IAudioFile *audioFile = *itAudioFiles;
        delete audioFile;
    }
    m_audioFileList.clear();
}

CSDLAudioFactory* CSDLAudioFactory::getInstance()
{
    static CSDLAudioFactory instance;
    return &instance;
}


IAudioFile * CSDLAudioFactory::createMusicAudioFile(std::string filepath )
{
    if( !m_sdlInitialized ){
        return createDummyAudioFile();
    }

    CMusicSDLAudioFile* audioFile = NULL;
    try{
        audioFile = new CMusicSDLAudioFile(filepath);
        m_audioFileList.push_back(audioFile);
        return audioFile;
    }catch(...){
        CLog::getInstance()->error("CSDLAudioFactory::createMusicAudioFile: Error creating the music audio file [filepath: '%s']. Loading dummy audio file.", filepath.c_str());
        if(audioFile!=NULL){
            delete audioFile;
        }

        return createDummyAudioFile();
    }
}

IAudioFile * CSDLAudioFactory::createSampleAudioFile( std::string filepath )
{
    if( !m_sdlInitialized ){
        return createDummyAudioFile();
    }

    CSampleSDLAudioFile* audioFile = NULL;
    try{
        audioFile = new CSampleSDLAudioFile(filepath);
        m_audioFileList.push_back(audioFile);
        return audioFile;
    }catch(...){
        CLog::getInstance()->error("CSDLAudioFactory::createSampleAudioFile: Error creating the sample audio file [filepath: '%s']. Loading dummy audio file.", filepath.c_str());
        if(audioFile!=NULL){
            delete audioFile;
        }

        return createDummyAudioFile();
    }
}

IAudioFile * CSDLAudioFactory::createDummyAudioFile()
{
    CDummyAudioFile *audioFile = new CDummyAudioFile();
    m_audioFileList.push_back(audioFile);
    return audioFile;
}
