#pragma once
#include "IMenuPage.h"
#include "SaveGameManager.h"
#include "../Engines/Utility/Event.h"
#include "Input_Toggle.h"
//#include "CRSoundPlayer.h"
//#include "CRMusicPlayer.h"

class Menu;

//extern CRMusicPlayer *musicPlayer;
//extern CRSoundPlayer *soundPlayer;

class SpecialsMenuPage : public IMenuPage
{
public:
	SpecialsMenuPage(Menu *menu, SaveGameManager *savedGames);
	~SpecialsMenuPage();

	int GetBackgroundImage() const;
	void Update(float time);
	void Render();
	void InputChanged();
	
private:
	SaveGameManager *savedGames;
	SettingsInfo settingsInfo;
	Input_Button *backButton;

	// selection sprite
	HPTSprite1 *selectionSprite;
	bool showSelectionSprite;
	
	// Input Toggle
	Input_Toggle *speedBoostToggle;
	void OnToggledSpeedBoost();

	// Unlocked Sprite
	HPTSprite1 *survivalRunUnlockedSprite;
	bool showSurvivalRunUnlockedSprite;

	//Input_Toggle *gamerGirlToggle;
	//void OnToggledGamerGirl();
	
	//Input_Toggle *machineGunToggle;
	//void OnToggledMachineGun();
	
	//Input_Toggle *infinityBladeToggle;
	//void OnToggledInfinityBlade();

	HPTSprite1 *medalFontSprite;
};