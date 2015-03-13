#pragma once
#include "Singleton.h"
#include "Guid.h"
#include<vector>

class MusicManager : public CR::Utility::Singleton<MusicManager>
{
	friend class CR::Utility::Singleton<MusicManager>;
public:
	enum Songs
	{
		Level1A,
		Level1B,
		Level2A,
		Level2B,
		Level3A,
		Level3B,
		BossBattle,
		Cutscene,
		Finale,
		TitleTheme,
		Bonus1,
		Bonus2,
		Bonus3,
		Max
	};
	void PlaySong(Songs _song);
private:
	MusicManager();
	~MusicManager() {}
	MusicManager(const MusicManager &_musicManager) {}

	std::vector<CR::Utility::Guid> m_retroSongs;
	std::vector<CR::Utility::Guid> m_remixSongs;
};
