/*
 *  SoundImpl.h
 *  Steph
 *
 *  Created by Eric Duhon on 6/21/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Sound.h"
#include "Buffer.h"
#include <vector>
#include "boost/tr1/tr1/unordered_map"
//#include <map>
//#include <OpenAL/al.h>
//#include <OpenAL/alc.h>
#include "Music.h"
#include <limits>
#include "SoundPrototype.h"

namespace CR
{
	namespace Sound
	{
		class SoundFX;
		class ActiveSoundFX;
		
		class SoundImpl
		{			
		public:		
			SoundImpl();
			virtual ~SoundImpl();
			void SetDatabase(CR::Database::IDatabase* const _database);
			std::tr1::shared_ptr<ISoundFX> CreateSoundFX(const CR::Utility::Guid &_id);
			void MuteSounds(bool _mute);
			bool MuteSounds() {return m_muteSounds;}
			void MuteMusic(bool _mute);
			void PlaySong(const CR::Utility::Guid &_id);
			void Tick();
			unsigned int ReserveSource();
			void SourceFinished(unsigned int _source);
			void QueueSoundFX(ActiveSoundFX *_fx);
			int SoundVolume();
			void SoundVolume(int _volume);
			int MusicVolume();
			void MusicVolume(int _volume);
			void SetProcessingFrequency(int _freq);
			//void DeleteSoundFX(ActiveSoundFX *_fx);
		private:
			CR::Database::IDatabase* m_database;
			typedef std::tr1::unordered_map<CR::Utility::Guid,std::tr1::shared_ptr<Buffer>, CR::Utility::GuidHash > BufferType;
			BufferType m_buffers;
			//ALCcontext* m_context;
			//ALCdevice* m_device;
			std::tr1::shared_ptr<Music> m_music;
			//unsigned int m_sourceIds[32];
			//std::vector<unsigned int> m_availableSources;
			typedef std::tr1::unordered_map<CR::Utility::Guid,std::tr1::shared_ptr<SoundPrototype>,CR::Utility::GuidHash > PrototypeType;
			PrototypeType m_soundPrototypes;
			std::vector<ActiveSoundFX*> m_currentSoundFX;
			bool m_muteSounds;
			CR::Utility::Guid m_currentSongID;
		};
	}
}