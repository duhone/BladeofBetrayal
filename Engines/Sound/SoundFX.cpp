/*
 *  SoundFX.cpp
 *  Steph
 *
 *  Created by Eric Duhon on 6/21/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "SoundFX.h"
#include "SoundImpl.h"
#include "ActiveSoundFX.h"
#include "s3e.h"

using namespace std;
using namespace CR::Sound;

SoundFX::SoundFX(SoundImpl *_soundEngine,SoundPrototype *_prototype) : m_soundEngine(_soundEngine), m_prototype(_prototype)
{

}

SoundFX::~SoundFX()
{
}

void SoundFX::Play()
{	
	if(m_soundEngine->MuteSounds())
		return;
	
	unsigned int _sourceID = m_soundEngine->ReserveSource();
	if(_sourceID != numeric_limits<unsigned int>::max())
	{
		//alSourcei(_sourceID, AL_BUFFER, m_prototype->GetBuffer()->OpenALID());
		//alSourcef(_sourceID, AL_PITCH, 1.0f);
		//alSourcef(_sourceID, AL_GAIN, m_prototype->Gain());
		//alSourcePlay(_sourceID);
		s3eSoundChannelPlay(_sourceID, static_cast<int16*>(m_prototype->GetBuffer()->Data()), m_prototype->GetBuffer()->NumSamples(), 1, 0);
		//m_soundEngine->QueueSoundFX(new ActiveSoundFX(m_soundEngine,_sourceID));
	}
}
