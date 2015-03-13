/*
 *  Sound.h
 *  Steph
 *
 *  Created by Eric Duhon on 5/30/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "boost/tr1/tr1/memory"
#include "../Utility/Singleton.h"
#include "../Math/Point.h"
#include "../Math/Vector.h"
#include "../Utility/Guid.h"
#include "../Database/DatabaseFwd.h"

namespace CR
{
	namespace Sound
	{		
		class ISoundFX
		{
		public:
			virtual void Play() = 0;
			virtual bool Playing() const = 0;
			virtual void Location(const CR::Math::PointF &_location) = 0;
			virtual void Velocity(const CR::Math::Vector3F &_velocity) = 0;
		protected:
			ISoundFX() {}
			virtual ~ISoundFX() {}
		};
		
		class SoundImpl;
		
		class ISound : public CR::Utility::Singleton<ISound>
		{			
			friend class CR::Utility::Singleton<ISound>;
		public:		
			void SetDatabase(CR::Database::IDatabase* const _database);
			std::tr1::shared_ptr<ISoundFX> CreateSoundFX(const CR::Utility::Guid &_id);
			void MuteSounds(bool _mute);
			void MuteMusic(bool _mute);
			void PlaySong(const CR::Utility::Guid &_id);
			int SoundVolume();
			void SoundVolume(int _volume);
			int MusicVolume();
			void MusicVolume(int _volume);
			void Tick();
			void SetProcessingFrequency(int _freq);
		protected:
			ISound();
			virtual ~ISound() {}	
		private:
			std::tr1::shared_ptr<SoundImpl> m_soundImpl;
		};
	}
}
