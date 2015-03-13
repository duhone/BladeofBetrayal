/*
 *  Music.h
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include <boost/tr1/tr1/memory>
#include "DatabaseFwd.h"

namespace CR
{
	namespace Sound
	{
		class MusicImpl;
		class SoundImpl;
		
		class Music
		{
		public:
			Music(SoundImpl *_soundEngine);
			void PlaySong(CR::Database::IRecordData &_reader,long _compressedSize,long _uncompressedSize);
			void Tick();
			void Mute(bool _mute);
		private:
			std::tr1::shared_ptr<MusicImpl> m_impl;
		};
	}
}
