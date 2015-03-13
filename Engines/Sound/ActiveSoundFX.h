/*
 *  ActiveSoundFX.h
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include <limits>

namespace CR
{
	namespace Sound
	{
		class SoundImpl;
		
		class ActiveSoundFX
		{
		public:
			ActiveSoundFX(SoundImpl *_soundEngine,unsigned int _sourceID);
			virtual void Stop();
			void Tick();
			bool Done() {return m_sourceID == std::numeric_limits<unsigned int>::max();}
		private:
			unsigned int m_sourceID;
			SoundImpl *m_soundEngine;
		};
	}
}
