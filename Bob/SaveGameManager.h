// SaveGameManager.h: interface for the SaveGameManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#define BOB_SAVE_VERSION 11
#define DEFAULT_SAVE_FILE "crpds_bob.sav"

const int c_numTutorials = 10;

struct SettingsInfo
{
	bool soundOn;
	bool musicOn;
	bool analogFlip;
	bool buttonFlip;
	bool retroMusic;
	bool qualityGraphics;
	int soundVolume;
	int musicVolume;
	SettingsInfo()
	{
		soundOn = true;
		musicOn = true;
		analogFlip = false;
		buttonFlip = false;
		retroMusic = true;
		qualityGraphics = true;
		soundVolume = -1;
		musicVolume = -1;
	};
};

struct LevelInfo
{
	// TODO: Store retrieved powerups/etc for the current level
	// to prevent the player from getting them again.
	bool bronzeAchievement;
	bool silverAchievement;
	bool goldAchievement;
	LevelInfo()
	{
		bronzeAchievement = false;
		silverAchievement = false;
		goldAchievement = false;
	};
};

struct BonusInfo
{
	bool BonusLevel1;
	bool BonusLevel2;
	bool BonusLevel3;

	BonusInfo()
	{
		BonusLevel1 = true;
		BonusLevel2 = false;
		BonusLevel3 = false;
	};
};

struct SaveGameInfo
{
	int level;
	int health;
	int health_bars;
	int energy;
	int energy_max;
	int score;
	int basic_weapon;
	bool weapons[6];
	int grenades;
	int nlives;
	LevelInfo levelInfo[12];
	SettingsInfo settingsInfo;
	BonusInfo bonusInfo;
	bool tutorials[c_numTutorials];
	bool beatGame;
	bool bonusToggles[7];

	SaveGameInfo()
	{
		level = 1;
		health = 25;
		health_bars = 5;
		energy = 25; //25
		energy_max = 25;//25
		score = 0;
		basic_weapon = 3;
		weapons[0] = true;//true;
		weapons[1] = false;//false;
		weapons[2] = false;//false;
		weapons[3] = false;//false;
		weapons[4] = false;//false;
		weapons[5] = false;//false;
		grenades = 5;
		nlives = 3;
		for(int i = 0;i < c_numTutorials;++i)
		{
			tutorials[i] = false;
		}
		beatGame = false;
		for(int i = 0;i < 7;++i)
		{
			bonusToggles[i] = true;
		}
	};
	int AchievmentCount()
	{
		int count = 0;
		for(int i = 0;i < 12;++i)
		{
			if(levelInfo[i].bronzeAchievement)
				count++;
			if(levelInfo[i].silverAchievement)
				count++;
			if(levelInfo[i].goldAchievement)
				count++;
		}
		return count;
	}
};

class SaveGameManager
{
public:
	enum Unlockables
	{
		Bonus1,
		SpencerBoost,
		Bonus2,
		Bonus3,
		NewHero,
		MachineGunGirl,
		SuperMan,
		Max
	};
	SaveGameManager();
	virtual ~SaveGameManager();
	
	void SaveGame(SaveGameInfo *game);
	void SaveSettings(SettingsInfo *settings);
	void SaveToDisk(char* saveGameFile);
	void SaveToDisk() {SaveToDisk(DEFAULT_SAVE_FILE);}
	void LoadFromDisk(char* saveGameFile);
	void Reset();

	SaveGameInfo GetSaveGameInfo() const {return saveGameInfo;}
	SettingsInfo GetSettingsInfo() const {return saveGameInfo.settingsInfo;}
	bool HasBeatGame() { return saveGameInfo.beatGame;}
	void BeatGame() { saveGameInfo.beatGame = true;}
	//void Temp(int _value) {temp = _value;}
	bool IsBonusUnlocked(Unlockables _unlockable);
	bool IsUnlockEnabled(Unlockables _unlockable);
	void SetUnlockToggle(Unlockables _unlockable,bool _on)
	{
		saveGameInfo.bonusToggles[_unlockable] = _on;
	}
	bool IsQualityMode() { return saveGameInfo.settingsInfo.qualityGraphics;}
private:
	int cur_profile;
	SaveGameInfo saveGameInfo;
};
