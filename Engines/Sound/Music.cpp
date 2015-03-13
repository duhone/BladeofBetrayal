/*
 *  Music.cpp
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Music.h"
#include "OGGHelper.h"
#include "Database.h"
#include "IDecompressor.h"
#include "DecompressorFactory.h"
#//include <OpenAL/al.h>
//#include <OpenAL/alc.h>
//#include "OpenAL/oalStaticBufferExtension.h"
//#include "OpenAL/oalMacOSX_OALExtensions.h"
#include "SoundImpl.h"
#include "s3e.h"

namespace CR
{
	namespace Sound
	{
		class MusicImpl
		{
		public:
			MusicImpl(SoundImpl *_soundEngine);
			~MusicImpl();
			void PlaySong(CR::Database::IRecordData &_reader,long _compressedSize,long _uncompressedSize);
			void Tick();
			void Mute(bool _mute);
		private:
			SoundImpl *m_soundEngine;
			std::tr1::shared_ptr<IDecompressor> m_decompressor;
			bool m_mutted;
			//unsigned int m_buffer1ID,m_buffer2ID;
			//char m_buffer1[8192]; // 1/4 of a second
			//char m_buffer2[8192]; // 1/4 of a second
			//unsigned int m_source;
			OGGHelper m_oggHelper;
			char *m_buffer;
		};
	}
}

using namespace std;
using namespace std::tr1;
using namespace CR::Sound;
using namespace CR::Database;

Music::Music(SoundImpl *_soundEngine) : m_impl(new MusicImpl(_soundEngine))
{
	
}

MusicImpl::MusicImpl(SoundImpl *_soundEngine) : m_buffer(NULL), m_mutted(false), m_decompressor(DecompressorFactory::Instance().Create(0)), m_soundEngine(_soundEngine)
{
	/*alGenBuffers(1, &m_buffer1ID);
	alGenBuffers(1, &m_buffer2ID);
	
	alBufferDataStaticProcPtr alBufferDataStaticProc = (alBufferDataStaticProcPtr)alcGetProcAddress(NULL, (const ALCchar *)"alBufferDataStatic");	
	alBufferDataStaticProc(m_buffer1ID,AL_FORMAT_MONO16,m_buffer1,8192,16000);	
	alBufferDataStaticProc(m_buffer2ID,AL_FORMAT_MONO16,m_buffer2,8192,16000);
	
	
	m_source = m_soundEngine->ReserveSource();
	if(m_source != numeric_limits<unsigned int>::max())
	{
		alSourcef(m_source, AL_PITCH, 1.0f);
		alSourcef(m_source, AL_GAIN, 0.35f);
	}*/
}

MusicImpl::~MusicImpl()
{
	if(m_buffer)
	{
		s3eAudioStop();
		delete[] m_buffer;
	}
	/*alSourceStop(m_source);
	
	int numProcessed;
	alGetSourcei(m_source,AL_BUFFERS_PROCESSED,&numProcessed);
	
	for(int i = 0;i < numProcessed;++i)
	{
		unsigned int removedBuffer;
		alSourceUnqueueBuffers(m_source, 1, &removedBuffer);
	}
	
	m_soundEngine->SourceFinished(m_source);
	alDeleteBuffers(1, &m_buffer1ID);
	alDeleteBuffers(1, &m_buffer2ID);*/
}

void MusicImpl::PlaySong(CR::Database::IRecordData &_reader,long _compressedSize,long _uncompressedSize)
{	
	if(m_buffer)
	{
		s3eAudioStop();
		delete[] m_buffer;
	}

	m_buffer = new char[_compressedSize];
	_reader.Read(m_buffer,_compressedSize);
	s3eAudioPlayFromBuffer(m_buffer,_compressedSize,0);
	if(m_mutted)
		s3eAudioPause();
	/*alSourceStop(m_source);
	
	int numProcessed;
	alGetSourcei(m_source,AL_BUFFERS_PROCESSED,&numProcessed);
	
	for(int i = 0;i < numProcessed;++i)
	{
		unsigned int removedBuffer;
		alSourceUnqueueBuffers(m_source, 1, &removedBuffer);
	}
	
	m_oggHelper.Init(_reader, _compressedSize, _uncompressedSize);
	m_oggHelper.InitStreaming();
	m_oggHelper.Decompress(m_buffer1,8192);
	m_oggHelper.Decompress(m_buffer2,8192);
	
	alSourceQueueBuffers(m_source, 1, &m_buffer1ID);
	alSourceQueueBuffers(m_source, 1, &m_buffer2ID);
	if(!m_mutted)
		alSourcePlay(m_source);*/
}

void MusicImpl::Tick()
{
	/*if(!m_mutted)
	{
		unsigned int bufferID;
		char *buffer;
		
		int numProcessed;
		alGetSourcei(m_source,AL_BUFFERS_PROCESSED,&numProcessed);
		if(numProcessed > 0)
		{
			alSourceUnqueueBuffers(m_source, 1, &bufferID);
			if(bufferID == m_buffer1ID)
				buffer = m_buffer1;
			else
				buffer = m_buffer2;
			
			m_oggHelper.Decompress(buffer,8192);			
			
			alSourceQueueBuffers(m_source, 1, &bufferID);
		}
		int state;
		alGetSourcei(m_source,AL_SOURCE_STATE,&state);
		if(state != AL_PLAYING)
			alSourcePlay(m_source);
	}*/
}

void MusicImpl::Mute(bool _mute)
{
	m_mutted = _mute;
	if(m_mutted)
		s3eAudioPause();
	else
		s3eAudioResume();
}

void Music::PlaySong(CR::Database::IRecordData &_reader,long _compressedSize,long _uncompressedSize)
{
	m_impl->PlaySong(_reader,_compressedSize,_uncompressedSize);
}

void Music::Tick()
{
	m_impl->Tick();
}

void Music::Mute(bool _mute)
{
	m_impl->Mute(_mute);
}
