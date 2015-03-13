// Menu.h: interface for the Menu class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../Engines/Input/input_engine.h"
#include "../Engines/Graphics/HPTGraphics.h"
#include "igame.h"
#include "SaveGameManager.h"
#include "GameStateManager.h"
#include "AssetList.h"

#include "MainMenuPage.h"
#include "MissionSelectMenuPage.h"
#include "OptionsMenuPage.h"
#include "AboutMenuPage.h"
#include "InstructionsMenuPage.h"

#include<vector>
#include<string>

using namespace std;

//#include "HPT sound.h"
//#include "soundprocessor.h"

//extern SoundProcessor *sound_processor;
//extern Game_Sounds *game_sounds;

#define HPTMENU_GOTOMENU 10000
#define HPTMENU_NEWGAME 10001

typedef int MENU_STATE;

#define menu_main 1
#define menu_mission_select 2
#define menu_options 3
#define menu_instructions 4
#define menu_about 5
#define menu_start_game 6
#define menu_resume_game 7
#define menu_specials 8

class Menu// : public Input_Controller
{
public:
	Menu(SaveGameManager *sarg);
	virtual ~Menu();
	
	// Menu Page Navigation
	void ChangeState(MENU_STATE newState);
	void SetCurrentMenuPage(IMenuPage *menuPage);

	// Sound settings
	int GetSoundVolume();
	void SetSoundVolume(int arg);
	int GetMusicVolume();
	void SetMusicVolume(int arg);
	bool GetSoundMute();
	void SetMuteSound(bool arg);
	bool GetMusicMute();
	void SetMusicMute(bool arg);
	
	// Game operations
	void ReplayIntro();
	void RestartMenu(IGame* arg, bool canResume, SaveGameManager *sarg);
	void Render();
	void Update(float time);
	void SetStartLevel(int level);
	bool CanResume() const {return canResume;}
	void SetCanResume(bool canResume) { this->canResume = canResume; } 
	IGame * GetGame() { return game; }
private:
	// Menu page navigation
	IMenuPage *currentMenuPage;
	MENU_STATE ActiveMState;
	bool stateChanged;
	
	// Game information
	IGame* game;
	bool can_save;
	SaveGameManager *saved_games;
	
	HPTBackground *background;
	int startLevel;
	bool canResume;
	
	// TODO: Sound
	// HPTSoundObject* music;
};
