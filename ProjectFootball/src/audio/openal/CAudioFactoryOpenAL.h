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

#ifndef __CAudioFactoryOpenAL_H__
#define __CAudioFactoryOpenAL_H__

#include <list>
#include <string>

#include <AL/al.h>
#include <AL/alc.h>

#include "CAudioFileOGGOpenAL.h"
#include "../CAudioFrameListener.h"
#include "../CDummyAudioFile.h"
#include "../IUpdatableAudioFactory.h"

class CAudioFactoryOpenAL : public IUpdatableAudioFactory
{
friend class CAudioAbstractFactory;
public:
	virtual ~CAudioFactoryOpenAL();
    virtual IAudioFile* createSampleAudioFile(std::string filepath);
    virtual IAudioFile* createMusicAudioFile(std::string filepath);
	virtual void updateIAudioFiles();

private:
    CAudioFactoryOpenAL();
    virtual IAudioFile * createAudioFile(std::string filepath);
    IAudioFile* createDummyAudioFile();
    IAudioFile* createOGGAudioFile( std::string filepath );

    static CAudioFactoryOpenAL* getInstance();

    ALCdevice                       *m_device;
    ALCcontext                      *m_context;
    CAudioFrameListener             *m_frameListener;
    std::list<CAudioFileOGGOpenAL*> m_audioFileList;
    std::list<CDummyAudioFile*>     m_dummyAudioFileList;
};
#endif // __CAudioFactoryOpenAL_H__
