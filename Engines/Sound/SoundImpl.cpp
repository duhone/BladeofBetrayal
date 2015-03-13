/*
 *  SoundImpl.cpp
 *  Steph
 *
 *  Created by Eric Duhon on 6/21/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "SoundImpl.h"
#include "../Database/Database.h"
#include "SoundFX.h"
#include "AudioEngineIDS.h"
//#include "OpenAL/oalStaticBufferExtension.h"
//#include "OpenAL/oalMacOSX_OALExtensions.h"
#include "FunctionObjects.h"
#include "ActiveSoundFX.h"
#include "s3e.h"

using namespace std;
using namespace std::tr1;
using namespace CR::Sound;
using namespace CR::Database;
using namespace CR::Utility;

SoundImpl::SoundImpl() : m_database(NULL) , m_muteSounds(false)
{
	s3eSoundSetInt(S3E_SOUND_DEFAULT_FREQ, 16000);
	//s3eAudioSetInt(S3E_AUDIO_VOLUME , 0);

	/*m_device = alcOpenDevice(NULL); // open default device
	
	if (m_device != NULL)
	{		
		m_context=alcCreateContext(m_device,NULL); // create context		
		if (m_context != NULL)
		{			
			alcMakeContextCurrent(m_context); // set active context			
		}		
	}	
	
	alcMacOSXMixerOutputRateProcPtr alcMacOSXMixerOutputRateProc = (alcMacOSXMixerOutputRateProcPtr)alcGetProcAddress(NULL, (const ALCchar *)"alcMacOSXMixerOutputRate");
	
	alcMacOSXMixerOutputRateProc(16000);*/
		
	/*alGenSources(32, m_sourceIds);
	m_availableSources.reserve(24);
	for(int i = 0;i < 24;++i)
	{
		m_availableSources.push_back(m_sourceIds[i]);
	}*/
	
	m_music.reset(new Music(this));
}

SoundImpl::~SoundImpl()
{
	m_soundPrototypes.clear();
	m_buffers.clear();
	//alDeleteSources(32, m_sourceIds);
	//alcDestroyContext(m_context);
	//alcCloseDevice(m_device);
}

void SoundImpl::SetDatabase(IDatabase* const _database)
{
	m_database = _database;
	const IRecord* const buffersRecord = m_database->GetRecord(CR::AssetList::buffers::ID);
	const std::vector<const IRecord*>& buffers = buffersRecord->GetChildren();
	for(unsigned int i = 0;i < buffers.size();++i)
	{
		m_buffers[buffers[i]->ID()] = shared_ptr<Buffer>(new Buffer(buffers[i]));
	}
	
	const IRecord* const soundsRecord = m_database->GetRecord(CR::AssetList::sounds::ID);
	if(soundsRecord)
	{
		const std::vector<const IRecord*>& sounds = soundsRecord->GetChildren();
		for(unsigned int i = 0;i < sounds.size();++i)
		{
			std::auto_ptr<IRecordData> data = sounds[i]->GetData();
			Guid bufferID;
			float gain;
			bool positional;
			(*data) >> bufferID >> gain >> positional;
			BufferType::const_iterator iterator = m_buffers.find(bufferID);
			if(iterator == m_buffers.end())
				continue;
			Buffer *buffer = iterator->second.get();
		
			m_soundPrototypes[sounds[i]->ID()] = shared_ptr<SoundPrototype>(new SoundPrototype(buffer));
			m_soundPrototypes[sounds[i]->ID()]->Gain(gain);
			m_soundPrototypes[sounds[i]->ID()]->Positional(positional);
		}
	}
}

shared_ptr<ISoundFX> SoundImpl::CreateSoundFX(const CR::Utility::Guid &_id)
{
	PrototypeType::const_iterator iterator = m_soundPrototypes.find(_id);
	if(iterator == m_soundPrototypes.end())
		return shared_ptr<ISoundFX>();
	
	SoundPrototype *prototype = iterator->second.get();
	if(!prototype)
		return shared_ptr<ISoundFX>();
	return shared_ptr<ISoundFX>(new SoundFX(this,prototype));
}

unsigned int SoundImpl::ReserveSource()
{
	int result = s3eSoundGetFreeChannel();
	if(result == -1)
		return numeric_limits<unsigned int>::max();
	return static_cast<unsigned int>(result);

	/*if(m_availableSources.size() == 0)
		return numeric_limits<unsigned int>::max();
	unsigned int result = m_availableSources.back();
	m_availableSources.pop_back();
	return result;*/
}

void SoundImpl::SourceFinished(unsigned int _source)
{
	//m_availableSources.push_back(_source);
}

void SoundImpl::PlaySong(const CR::Utility::Guid &_id)
{	
	if(m_currentSongID == _id)
		return;
	const IRecord* const songRecord = m_database->GetRecord(_id);
	
	std::auto_ptr<IRecordData> data = songRecord->GetData();
	long uncompressedSize,compressedSize;
	(*data.get()) >> uncompressedSize >> compressedSize;
		
	m_music->PlaySong(*data.get(),compressedSize,uncompressedSize);
	
	m_currentSongID = _id;
}

void SoundImpl::Tick()
{
	m_music->Tick();
	ForEach(m_currentSoundFX, mem_fun(&ActiveSoundFX::Tick));
	int numDeleted = 0;
	for(unsigned int i = 0,j = 0; i< m_currentSoundFX.size();++i)
	{
		if(m_currentSoundFX[i]->Done())
		{
			delete m_currentSoundFX[i];
			m_currentSoundFX[i] = NULL;
			++numDeleted;
		}
		m_currentSoundFX[j] = m_currentSoundFX[i];
		if(m_currentSoundFX[j] != NULL)
			++j;
	}
	m_currentSoundFX.resize(m_currentSoundFX.size()-numDeleted);
}

void SoundImpl::MuteMusic(bool _mute)
{
	m_music->Mute(_mute);	
}

void SoundImpl::MuteSounds(bool _mute)
{
	m_muteSounds = _mute;
	if(m_muteSounds)
		ForEach(m_currentSoundFX,mem_fun(&ActiveSoundFX::Stop));
}


void SoundImpl::QueueSoundFX(ActiveSoundFX *_fx)
{
	m_currentSoundFX.push_back(_fx);
}

int SoundImpl::SoundVolume()
{	
	return s3eSoundGetInt(S3E_SOUND_VOLUME);
}

void SoundImpl::SoundVolume(int _volume)
{
	//if(_volume >= 0)
	//	s3eSoundSetInt(S3E_SOUND_VOLUME, _volume);
	//else
	//	s3eSoundSetInt(S3E_SOUND_VOLUME, S3E_SOUND_VOLUME_DEFAULT );
}

int SoundImpl::MusicVolume()
{
	return s3eAudioGetInt(S3E_AUDIO_VOLUME);	
}

void SoundImpl::MusicVolume(int _volume)
{
	//if(_volume >= 0)
	//	s3eAudioSetInt(S3E_AUDIO_VOLUME, _volume);	
	//else
	//	s3eAudioSetInt(S3E_AUDIO_VOLUME, S3E_AUDIO_VOLUME_DEFAULT );
}

void SoundImpl::SetProcessingFrequency(int _freq)
{
	s3eSoundSetInt(S3E_SOUND_DEFAULT_FREQ, _freq);
}

