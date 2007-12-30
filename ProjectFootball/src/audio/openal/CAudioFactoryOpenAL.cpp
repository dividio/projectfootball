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

#include "CAudioFactoryOpenAL.h"
#include "../../CApplication.h"
#include "../../utils/CLog.h"

using namespace std;

CAudioFactoryOpenAL::CAudioFactoryOpenAL()
	: m_audioFileList(), m_dummyAudioFileList()
{
	//Initialization
    CLog::getInstance()->debug("Initialising OpenAL ...");

    m_device = alcOpenDevice(NULL);
    CLog::getInstance()->info("Setting up default OpenAL device [%s]", alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));


    if(m_device) {
        ALCint attribs[] = {ALC_STEREO_SOURCES, 32, 0};
        m_context = alcCreateContext(m_device, attribs);
        alcMakeContextCurrent(m_context);
    }
    CLog::getInstance()->info("Audio enabled. OpenAL information:");
    CLog::getInstance()->info("  Version:    %s", alGetString(AL_VERSION));
    CLog::getInstance()->info("  Renderer:   %s", alGetString(AL_RENDERER));
    CLog::getInstance()->info("  Vendor:     %s", alGetString(AL_VENDOR));
    CLog::getInstance()->info("  Extensions: %s", alGetString(AL_EXTENSIONS));

    m_frameListener = new CAudioFrameListener(this);
    CApplication::getInstance()->addFrameListener(m_frameListener);
}


CAudioFactoryOpenAL::~CAudioFactoryOpenAL()
{
    CApplication::getInstance()->removeFrameListener(m_frameListener);
    delete m_frameListener;

	for( std::list<CAudioFileOGGOpenAL*>::iterator itAudioFiles = m_audioFileList.begin(); itAudioFiles!=m_audioFileList.end(); itAudioFiles++ ){
		IAudioFile *audioFile = *itAudioFiles;
		delete audioFile;
	}
	m_audioFileList.clear();

	for( std::list<CDummyAudioFile*>::iterator itDummyAudioFiles = m_dummyAudioFileList.begin(); itDummyAudioFiles!=m_dummyAudioFileList.end(); itDummyAudioFiles++ ){
        IAudioFile *dummyAudioFile = *itDummyAudioFiles;
        delete dummyAudioFile;
    }
    m_dummyAudioFileList.clear();

    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}


CAudioFactoryOpenAL* CAudioFactoryOpenAL::getInstance()
{
    static CAudioFactoryOpenAL instance;

    return &instance;
}

void CAudioFactoryOpenAL::updateIAudioFiles()
{
    for( std::list<CAudioFileOGGOpenAL*>::iterator itAudioFiles = m_audioFileList.begin(); itAudioFiles!=m_audioFileList.end(); itAudioFiles++ ){
        CAudioFileOGGOpenAL *audioFile = *itAudioFiles;
        if( audioFile->isPlaying() ){
            audioFile->update();
        }
    }
}

IAudioFile * CAudioFactoryOpenAL::createMusicAudioFile(std::string filepath )
{
    return createAudioFile(filepath);
}

IAudioFile * CAudioFactoryOpenAL::createSampleAudioFile( std::string filepath )
{
    return createAudioFile(filepath);
}


IAudioFile * CAudioFactoryOpenAL::createAudioFile( std::string filepath )
{
	unsigned int pos = filepath.find_last_of(".");
	if( pos<0 || pos>filepath.size() ){
		CLog::getInstance()->error("CAudioFactoryOpenAL::createAudioFile: Extension not found in '%s'. Loading dummy audio file.", filepath.c_str());
		return createDummyAudioFile();
	}

	string extension = filepath.substr(pos);
	if( extension==".ogg" || extension==".OGG"){
		return createOGGAudioFile(filepath);
	}else{
		CLog::getInstance()->error("CAudioFactoryOpenAL::createAudioFile: Extension not supported in '%s'. Loading dummy audio file.", filepath.c_str());
		return createDummyAudioFile();
	}
}

IAudioFile * CAudioFactoryOpenAL::createDummyAudioFile()
{
	CDummyAudioFile *audioFile = new CDummyAudioFile();
	m_dummyAudioFileList.push_back(audioFile);
	return audioFile;
}

IAudioFile* CAudioFactoryOpenAL::createOGGAudioFile( std::string filepath )
{
    CAudioFileOGGOpenAL* audioFile = NULL;
	try{
		audioFile = new CAudioFileOGGOpenAL(filepath);
		m_audioFileList.push_back(audioFile);
		return audioFile;
	}catch(...){
		CLog::getInstance()->error("CAudioFactoryOpenAL::createOGGAudioFile: Error creating the OGG audio file [filepath: '%s']. Loading dummy audio file.", filepath.c_str());
		if(audioFile!=NULL){
			delete audioFile;
		}

		return createDummyAudioFile();
	}
}
