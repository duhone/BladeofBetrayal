/*
 *  ActiveSoundFX.cpp
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ActiveSoundFX.h"
//#include <OpenAL/al.h>
//#include <OpenAL/alc.h>
#include "SoundImpl.h"
#include "s3e.h"

using namespace std;
using namespace CR::Sound;

ActiveSoundFX::ActiveSoundFX(SoundImpl *_soundEngine,unsigned int _sourceID) : m_soundEngine(_soundEngine), m_sourceID(_sourceID)
{
	
}

void ActiveSoundFX::Stop()
{
	s3eSoundChannelStop(m_sourceID);
	//alSourceStop(m_sourceID);
}

void ActiveSoundFX::Tick()
{
	/*int stat = s3eSoundChannelGetInt (m_sourceID, S3E_CHANNEL_STATUS );
	if(state != AL_PLAYING)
	{
		m_soundEngine->SourceFinished(m_sourceID);	
		m_sourceID = numeric_limits<unsigned int>::max();		
	}*/

	/*ALint state;
	alGetSourcei(m_sourceID, AL_SOURCE_STATE, &state);
	if(state != AL_PLAYING)
	{
		m_soundEngine->SourceFinished(m_sourceID);	
		m_sourceID = numeric_limits<unsigned int>::max();		
	}*/
}