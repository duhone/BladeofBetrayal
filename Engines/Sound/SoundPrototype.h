/*
 *  SoundPrototype.h
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "Guid.h"

namespace CR
{
	namespace Sound
	{
		class Buffer;
		
		class SoundPrototype
		{
		public:
			SoundPrototype(Buffer *_buffer);
			Buffer *GetBuffer() { return m_buffer;}
			float Gain() const { return m_gain; }
			void Gain(float _gain) {m_gain = _gain;}
			bool Positional() const { return m_positional; }
			void Positional(bool _positional) {m_positional = _positional;}
		private:
			Buffer *m_buffer;
			float m_gain;
			bool m_positional;
		};
	}
}
