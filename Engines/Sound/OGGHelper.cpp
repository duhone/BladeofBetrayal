/*
 *  OGGHelper.cpp
 *  AudioTest
 *
 *  Created by Eric Duhon on 10/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "OGGHelper.h"
#include "Database.h"
#include <algorithm>
#include <cstdio>
#include "Buffer.h"
#include "DecompressorFactory.h"
#include "ivorbisfile.h"

namespace
{
	CR::Sound::IDecompressor* OGGCreater() {return new CR::Sound::OGGHelper;}
	
	const bool g_CreateOGG = CR::Sound::DecompressorFactory::Instance().RegisterCreater(0,OGGCreater);
}

namespace CR
{
	namespace Sound
	{
		class OGGHelperImpl
			{
			public:
				OGGHelperImpl();
				void Init(CR::Database::IRecordData &_reader,long _compressedSize,long _uncompressedSize);
				~OGGHelperImpl();
				size_t Read(void *_ptr,size_t _size, size_t _count);
				long Offset() const {return m_offset;}
				void Seek(long _offset,int _origin);
				unsigned short* DecompressFull();
				void InitStreaming();
				void Decompress(char *_buffer,int _bufferSize);
			private:
				char *m_compressedData;
				long m_compressedSize;
				long m_uncompressedSize;
				long m_offset;
				OggVorbis_File m_vorbisFile;
				ov_callbacks m_callbacks;
				int m_streamingBytesRead;
			};
	}
}

using namespace CR::Sound;
using namespace CR::Database;

size_t ReadOGG(void *_ptr,size_t _size, size_t _count, void *_datasource)
{
	OGGHelperImpl *oggHelper = reinterpret_cast<OGGHelperImpl*>(_datasource);
	return oggHelper->Read(_ptr,_size,_count);
}

long TellOGG(void *_datasource)
{
	OGGHelperImpl *oggHelper = reinterpret_cast<OGGHelperImpl*>(_datasource);
	return oggHelper->Offset();
}

int SeekOGG(void *_datasource, ogg_int64_t _offset, int _whence)
{
	OGGHelperImpl *oggHelper = reinterpret_cast<OGGHelperImpl*>(_datasource);
	oggHelper->Seek(static_cast<long>(_offset),_whence);
	return 0;
}

OGGHelper::OGGHelper() : m_impl(new OGGHelperImpl()) {}
void OGGHelper::Init(CR::Database::IRecordData &_reader,long _compressedSize,long _uncompressedSize) {m_impl->Init(_reader,_compressedSize,_uncompressedSize);}
unsigned short* OGGHelper::DecompressFull() { return m_impl->DecompressFull();}
void OGGHelper::InitStreaming() {m_impl->InitStreaming();}
void OGGHelper::Decompress(char *_buffer,int _bufferSize) {m_impl->Decompress(_buffer,_bufferSize);}

OGGHelperImpl::OGGHelperImpl() : m_compressedSize(0) , m_uncompressedSize(0), m_offset(0), m_compressedData(NULL)
{
	
}

void OGGHelperImpl::Init(IRecordData &_reader,long _compressedSize,long _uncompressedSize)
{
	if(m_compressedData)
		ov_clear(&m_vorbisFile);
	
	m_compressedSize = _compressedSize;
	m_uncompressedSize = _uncompressedSize;
	
	delete[] m_compressedData;
	m_compressedData = new char[m_compressedSize];
	
	_reader.Read(m_compressedData,m_compressedSize);
	m_offset = 0;
}

OGGHelperImpl::~OGGHelperImpl()
{
	delete[] m_compressedData;
}

size_t OGGHelperImpl::Read(void *_ptr,size_t _size, size_t _count)
{
	size_t amountRead = _count*_size;
	amountRead = std::min<size_t>(amountRead,m_compressedSize-m_offset);
	if(amountRead <= 0)
		return 0;
	memcpy(_ptr, m_compressedData+m_offset, amountRead);
	m_offset += amountRead;
	return amountRead;
}

void OGGHelperImpl::Seek(long _offset,int _origin)
{
	if(_origin == SEEK_SET)
	{
		m_offset = _offset;
	}
	else if(_origin == SEEK_CUR)
	{
		m_offset += _offset;
	}
	else if(_origin == SEEK_END)
	{
		m_offset = m_compressedSize + _offset;	
	}
	//else assert(0); //should be impossible	
	m_offset =std::min(m_offset,m_compressedSize);
	m_offset =std::max<long>(m_offset,0);	
}

unsigned short* OGGHelperImpl::DecompressFull()
{
	OggVorbis_File vorbisFile;
	ov_callbacks callbacks;
	callbacks.read_func = ReadOGG;
	callbacks.seek_func = SeekOGG;
	callbacks.tell_func = TellOGG;
	callbacks.close_func = NULL;
	ov_open_callbacks(this, &vorbisFile, NULL, 0, callbacks);
	
	long bytesLeft = m_uncompressedSize;
	unsigned short *result = new unsigned short[m_uncompressedSize>>1];
	char *currentResult = reinterpret_cast<char*>(result);
	int currentSection = 0;
	do
	{
		long bytesRead = ov_read(&vorbisFile,currentResult,bytesLeft,&currentSection);
		
		if (bytesRead == 0 && bytesLeft != 0) 
		{
			//didnt get all of our data. bad stream probably
			//assert(0);
			bytesLeft = 0;
		} 
		else if (bytesRead < 0)
		{
			//bad stream
			//assert(0);
			bytesLeft = 0;
		} 
		else
		{
			bytesLeft -= bytesRead;
			currentResult += bytesRead;
		}
	} while(bytesLeft != 0);
	return result;
}

void OGGHelperImpl::InitStreaming()
{
	m_callbacks.read_func = ReadOGG;
	m_callbacks.seek_func = SeekOGG;
	m_callbacks.tell_func = TellOGG;
	m_callbacks.close_func = NULL;
	ov_open_callbacks(this, &m_vorbisFile, NULL, 0, m_callbacks);	
	m_streamingBytesRead = 0;
}

void OGGHelperImpl::Decompress(char *_buffer,int _bufferSize)
{
	char *currentResult = reinterpret_cast<char*>(_buffer);
	int currentSection = 0;
	do
	{
		int amountToRead = _bufferSize;
		amountToRead = std::min<int>(_bufferSize,m_uncompressedSize-m_streamingBytesRead);
		long bytesRead = ov_read(&m_vorbisFile,currentResult,amountToRead,&currentSection);
		
		if (m_streamingBytesRead >= m_uncompressedSize || (bytesRead == 0 && _bufferSize != 0)) 
		{
			ov_time_seek(&m_vorbisFile,0);	
			m_streamingBytesRead = 0;
		} 
		else if (bytesRead < 0)
		{
			//bad stream
			//assert(0);
			_bufferSize = 0;
		} 
		else
		{
			_bufferSize -= bytesRead;
			currentResult += bytesRead;	
			m_streamingBytesRead += bytesRead;
		}
	} while(_bufferSize != 0);
}
