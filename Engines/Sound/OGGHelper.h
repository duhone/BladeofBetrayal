/*
 *  OGGHelper.h
 *  AudioTest
 *
 *  Created by Eric Duhon on 10/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "DatabaseFwd.h"
#include "stdlib.h"
#include "IDecompressor.h"
#include "boost/tr1/tr1/memory"

namespace CR
{
	namespace Sound
	{
		class OGGHelperImpl;
		
		class OGGHelper : public IDecompressor
		{
		public:
			OGGHelper();
			void Init(CR::Database::IRecordData &_reader,long _compressedSize,long _uncompressedSize);
			unsigned short* DecompressFull();
			void InitStreaming();
			void Decompress(char *_buffer,int _bufferSize);
		private:
			std::tr1::shared_ptr<OGGHelperImpl> m_impl;
		};
	}
}
