/*
 *  OptionsMenuPage.h
 *  BoB
 *
 *  Created by Robert Shoemate on 2/1/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
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

class OptionsMenuPage : public IMenuPage
{
public:
	OptionsMenuPage(Menu *menu, SaveGameManager *savedGames);
	~OptionsMenuPage();

	int GetBackgroundImage() const;
	void Update(float time);
	void Render();
	void InputChanged();
	
private:
	SaveGameManager *savedGames;
	SettingsInfo settingsInfo;
	Input_Button *menuButton;
	Input_Toggle *soundToggle;
	Input_Toggle *musicToggle;
	Input_Toggle *retroToggle;
	Input_Toggle *analogToggle;
	Input_Toggle *buttonToggle;
	Input_Toggle *performanceToggle;
	HPTSprite1 *selectionSprite;
	bool showSelectionSprite;
	
	// Reset Game
	HPTSprite1 *resetPopupSprite;
	Input_Button *resetButton;
	Input_Button *yesButton;
	Input_Button *noButton;
	
	void OnToggledSound();
	void OnToggledMusic();
	void OnToggledRetro();
	void OnToggledAnalog();
	void OnToggledButton();
	void OnToggledPerformance();
	
	void OnResetButtonClicked();
	void OnYesButtonClicked();
	void OnNoButtonClicked();
	
	bool showResetDialog;
};