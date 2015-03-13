#include "MusicManager.h"
#include "AssetListNew.h"
#include "Sound.h"
#include "Game.h"

using namespace CR::Sound;

extern Game* game_class;

MusicManager::MusicManager()
{
	m_retroSongs.push_back(CR::AssetList::music::Level1ARetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Level1BRetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Level2ARetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Level2BRetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Level3ARetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Level3BRetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::BossBattleRetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Cutscene::ID);
	m_retroSongs.push_back(CR::AssetList::music::FinaleRetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::MenuRetro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Bonus1Retro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Bonus2Retro::ID);
	m_retroSongs.push_back(CR::AssetList::music::Bonus3Retro::ID);
		
	m_remixSongs.push_back(CR::AssetList::music::Level1A::ID);
	m_remixSongs.push_back(CR::AssetList::music::Level1B::ID);
	m_remixSongs.push_back(CR::AssetList::music::Level2A::ID);
	m_remixSongs.push_back(CR::AssetList::music::Level2B::ID);
	m_remixSongs.push_back(CR::AssetList::music::Level3A::ID);
	m_remixSongs.push_back(CR::AssetList::music::Level3B::ID);
	m_remixSongs.push_back(CR::AssetList::music::BossBattle::ID);
	m_remixSongs.push_back(CR::AssetList::music::Cutscene::ID);
	m_remixSongs.push_back(CR::AssetList::music::Finale::ID);
	m_remixSongs.push_back(CR::AssetList::music::Menu::ID);
	m_remixSongs.push_back(CR::AssetList::music::Bonus1::ID);
	m_remixSongs.push_back(CR::AssetList::music::Bonus2::ID);
	m_remixSongs.push_back(CR::AssetList::music::Bonus3::ID);
}

void MusicManager::PlaySong(Songs _song)
{
	//hack. ui is backwords. so just make this backwords too
	if(!game_class->GetSaveGameManager()->GetSettingsInfo().retroMusic)
		ISound::Instance().PlaySong(m_retroSongs[_song]);
	else
		ISound::Instance().PlaySong(m_remixSongs[_song]);
}