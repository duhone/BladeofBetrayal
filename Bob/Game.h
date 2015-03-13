// Game.h: interface for the Game class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Level.h"
#include "../Engines/Input/input_engine.h"
#include "player.h"
#include "./aiengine/aiengine.h"
#include "enemy.h"
#include "theater.h"
#include "IGame.h"
#include "menu.h"
#include "projectile.h"
#include "BroadcastMessage.h"
#include "ProgressMeter.h"
#include "ProjectilePoints.h"
#include "TransitionScreen.h"
#include "GEnemies.h"
#include "SaveGameManager.h"
#include "LevelStateManager.h"
#include "MeterBar.h"
#include "TimeDisplay.h"
#include "TallyDisplay.h"
//#include "CRMusicPlayer.h"
//#include "CRSoundPlayer.h"
#include "../Engines/Utility/FSM.h"
#include <vector>
#include <list>
#include <string>
#include "Input_WeaponSelect.h"
#include "Database.h"
#include "Timer.h"
#include "Sound.h"

char *hptstrcat(char *x,char *y);

struct Rain2
{
	std::vector<HPTSprite1*> m_sprites;
	int m_currentSprite;
	float m_delay;
	float m_x;
	float m_y;
};

/*enum GAME_STATE 
{
//	game_special = 1,
	game_end = 2,
	game_start = 3,
	game_movie = 4,
	game_credits = 5,
	game_paused = 6,
	game_menu = 7,
	game_ingame = 8,
//	game_test = 9,
	game_death = 10,
//	game_demo = 11,
	game_scores = 12,
	game_new_score = 13,
	FORCE_DWORD = 0x7fffffff
};*/

typedef int GAME_STATE;

#define	game_end 0
#define	game_start 1
#define	game_movie 2
#define	game_credits 3
#define	game_paused 4
#define	game_menu 5
#define	game_ingame 6
#define	game_death 7
#define game_level_load 8
#define game_level_end 9
#define game_tutorial 10
#define game_noiad 11

class Game: public Input_Controller, public IGame
{
public:
	Game();
	virtual ~Game();
	
	//IGame
	virtual void StartGame(int nLevel, bool skipMovie);
	virtual void SetVideoQuality(int arg);
	virtual int GetVideoQuality();
	virtual bool GetEnableStatus();
	virtual void SetEnableStatus(bool arg);
	virtual void Resume();
	virtual void ReplayIntro();
	virtual SaveGameManager *GetSaveGameManager() { return &saved_games; }
	virtual GameStateManager *GetGameStateManager() { return &gameStateManager; }
	virtual LevelStateManager *GetLevelStateManager() { return &levelStateManager; }
	
	//Game
	void SetSpawnPoints();
	void UpdateHUD();
	void RenderHUD();
	void Render();
	void ProcessDemo();
	void EndLevelScreen();
	void ProcessDeath();
	void PlayerDeathState1();
	void PlayerDeathState2();
	void PlayerDeathState3();
	void PlayerDeathState4();
	void Initialize();
	void PlayerDeath();
	void EndLevel();
	void LoadLevel1();
	void LoadLevel2();
	void LoadLevel3();
	void LoadLevel4();
	void LoadLevel5();
	void LoadLevel6();
	void LoadLevel7();
	void LoadLevel8();
	void LoadLevel9();
	void LoadLevel10();
	void LoadLevel11();
	void LoadLevel12();
	void LevelTransition(bool arg = true);
	void LoadLevel(int arg);
	void InputChanged();
	void ProcessMovie();
	void ProcessMenu();
	void ProcessGame();
	void ProcessPause();
	void ProcessCredits();
	void ProcessTest();
	void ProcessStart();
	void ProcessEnd();
	void ProcessLevelLoad();
	void ProcessEndLevel();
	void ProcessTutorial();
	void ProcessNoIAD();
	void ChangeState(GAME_STATE newState);
	void ApplicationTerminated();
	void ExecuteGame();

	int GetCompletionPercent();
	int GetAchievementsCount();
	
	void AddBeacon() {tallyNumBeacons++;}
	bool IsInTransition() {return transition->sActive;}
	GAME_STATE ActiveGState;
	GAME_STATE RequestGState;
	GAME_STATE PauseGState;
	int video_quality;
	Level *level_class;
	HPTBackground *static_background;
	Player *player;
	AIEngine* ai_engine;
	AIObject aiobject;
	std::vector<Enemy*> enemys;
	std::vector<Enemy*> activeEnemys;
//	HPTFont1* blue12;
	HPTFont1* gothic12;
	HPTFont1* gothic10r;
	HPTFont1* bankGothic;
		void CaptureSpawnPointInfo();
	
	int GetCurrentLevel() const {return current_level;}
private:
	//Event handlers
	void OnClickedLevelLoadScreen();
	void OnClickedPauseButton();
	void OnClickedResumeGameButton();
	void OnClickedQuitGameButton();
	void LoadLevelPhase1();
	void LoadLevelPhase2();
	void LoadLevelPhase3();
	void LoadLevelPhase4();
	void LoadLevelPhase5();
	
	SpawnPointInfo m_SpawnPointInfo;

	
	void SaveLevelState();
	void SaveGameState(bool canResume);
	void SaveGame();
	
	int new_score_entry;
	bool enable_score;
	bool enable_status;
	int enemy_hits;
	int player_hits;
	bool disable_input;
	int screen_size;
	int level_end_efficiency;
	int level_end_score;
	int basic_bonus_points;
	int treasure_bonus_points;
	int special_bonus_points;
	int combat_bonus;
	int bonus_points;
	unsigned int avail_mem;
	bool new_level;
	bool key_pressed;
	int current_level;
	Theater *cut_scenes;
	unsigned int starttime;
	unsigned int currenttime;
	float timerfreq;
	int nframes;
	CR::Utility::Timer m_gameTimer;
	CR::Utility::Timer m_renderTimer;

	unsigned int m_gameTime;
	unsigned int m_renderTime;
	float time;
	
	Menu *menu;
	HPTBackground* level_load;
	HPTBackground* level_end;
	std::list<Projectile*> projectile_list;
	SaveGameManager saved_games;
	GameStateManager gameStateManager;
	LevelStateManager levelStateManager;
	ProgressMeter *m_ProgressMeter;
	
	// Performance Variables
	float frame_rate_count;
	float frame_rate;
	
	// Input Engine
	Input_Analog *analogStick;
	Input_Button *jumpButton;
	Input_Button *attackButton;
	Input_Button *specialAttackButton;
	Input_Button *grenadeButton;
	Input_Button *pauseButton;
	Input_WeaponSelect *weaponSelect;
	Input_Button *resumeGameButton;
	Input_Button *quitGameButton;
	Input_Button* loadScreenButton;
	Input_Button* endScreenButton;
	Input_Button* deathScreenButton;
	
	// HUD Sprites
	MeterBar *healthMeterBar;
	MeterBar *energyMeterBar;
	TimeDisplay *timeDisplay;
	
	// Other Sprites
	HPTSprite1 *pauseBackground;
	TransitionScreen *transition;
	HPTSprite1 *loadingButton;
	HPTSprite1 *awardInfo;
	HPTSprite1 *loadingLevelTags;
	HPTSprite1 *loadingObjectiveTags;
	//HPTSprite1 *tallyFont;
	HPTSprite1 *endTally;
	HPTSprite1 *medalsSprite;
	TimeDisplay *endTimeDisplay;
	bool bronzeAwardReceived;
	bool silverAwardReceived;
	bool goldAwardReceived;
	
	TallyDisplay *itemsTallyDisplay;
	TallyDisplay *enemiesTallyDisplay;
	int tallyNumEnemies;
	int tallyNumDeadEnemies;
	int tallyNumObjects;
	int tallyNumGotObjects;
	int tallyNumBeacons;

	std::string m_levelLoadingText;
	int m_levelLoadImage;
	int m_levelStaticBackground;
	int m_levelLoadState;
	float m_playTime;
	
	CR::Utility::SimpleFSM<5> m_levelEndFSM;
	CR::Utility::SimpleFSM<4> m_playerDeathFSM;
	
	HPTSprite1 *m_overlay;
	float m_TimeTillOverlayFlip;
	bool m_overlayOn;
	float m_overlayoffTime;
	float m_overlayonTime;
	
	float m_healthTick;

	std::vector<Rain2> m_rain;
	
	void LevelEndState1();
	void LevelEndState2();
	void LevelEndState3();
	void LevelEndState4();
	void LevelEndState5();

	void OnEndScreenClick()
	{
		if (endTimeDisplay && endTimeDisplay->DoneAnimating() && enemiesTallyDisplay->DoneAnimating() && 
			(!itemsTallyDisplay || itemsTallyDisplay->DoneAnimating()))
		{
			m_levelEndFSM++;
		}
		else
		{
			endTimeDisplay->SetDoneAnimating();
			enemiesTallyDisplay->SetDoneAnimating();
			if(itemsTallyDisplay)
				itemsTallyDisplay->SetDoneAnimating();
		}
		
		
		//transition->Begin(false, 0);
	}
	
	void OnClickedDeathScreen()
	{
		m_playerDeathFSM++;
	}
	
	bool resumeGame;
	void InitializeLevelState();
	
	std::vector<float> levelAchievementTimes;
	
	bool GotGoldAchievement();
	bool GotSilverAchievement();
	bool GotBronzeAchievement();

	CR::Database::IDatabase *m_database;

	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundBang;

	float m_bannerTime;
	int m_bannerShow;

	float m_attackButtonAdjust;
	float m_specialAttackButtonAdjust;
	float m_analogAdjust;
};
