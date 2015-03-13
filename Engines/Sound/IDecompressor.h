/*
 *  IDecompressor.h
 *  AudioTest
 *
 *  Created by Eric Duhon on 10/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "DatabaseFwd.h"

namespace CR
{
	namespace Sound
	{
		class IDecompressor
		{
		public:
			virtual void Init(CR::Database::IRecordData &_reader,long _compressedSize,long _uncompressedSize) = 0;
			virtual unsigned short* DecompressFull() = 0;
			virtual ~IDecompressor() {}
		protected:
			IDecompressor() {}
		};
	}
}
