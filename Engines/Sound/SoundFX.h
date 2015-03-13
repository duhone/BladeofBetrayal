/*
 *  SoundFX.h
 *  Steph
 *
 *  Created by Eric Duhon on 6/21/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Sound.h"

namespace CR
{
	namespace Sound
	{		
		class SoundImpl;
		class SoundPrototype;
		
		class SoundFX : public ISoundFX
		{
		public:
			SoundFX(SoundImpl *_soundEngine,SoundPrototype *_prototype);
			~SoundFX();

			virtual void Play();
			virtual bool Playing() const {return false;}
			virtual void Location(const CR::Math::PointF &_location)  {}
			virtual void Velocity(const CR::Math::Vector3F &_velocity)  {}
		private:
			SoundImpl *m_soundEngine;
			SoundPrototype *m_prototype;
		};
	}
}