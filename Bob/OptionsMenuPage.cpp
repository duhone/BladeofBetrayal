/*
 *  OptionsMenuPage.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 2/1/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "OptionsMenuPage.h"
#include "menu.h"
#include "AssetList.h"
#include "MusicManager.h"
#include "Sound.h"
#include "AppConfig.h"

using namespace CR::Sound;

extern HPTGraphicsEngine *graphics_engine;

OptionsMenuPage::OptionsMenuPage(Menu *menu, SaveGameManager *savedGames) : IMenuPage(menu)
{
	this->savedGames = savedGames;
	showSelectionSprite = false;
	
	settingsInfo.soundOn = savedGames->GetSettingsInfo().soundOn;
	settingsInfo.musicOn = savedGames->GetSettingsInfo().musicOn;
	settingsInfo.analogFlip = savedGames->GetSettingsInfo().analogFlip;
	settingsInfo.buttonFlip = savedGames->GetSettingsInfo().buttonFlip;
	settingsInfo.retroMusic = savedGames->GetSettingsInfo().retroMusic;
	settingsInfo.qualityGraphics = savedGames->GetSettingsInfo().qualityGraphics;
	
	selectionSprite = graphics_engine->CreateSprite1();
	selectionSprite->SetImage(CR::AssetList::options_selected);
	if(AppConfig::Instance().IsIpad())
		selectionSprite->SetDesignSize(458,56);
	
	menuButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
	{
		menuButton->SetSpriteAndBounds(12, 15, CR::AssetList::menu_menu_buttons);
		menuButton->DesignSize(69,30);
	}
	else
		menuButton->SetSpriteAndBounds(12, 11, CR::AssetList::menu_menu_buttons);
	menuButton->SetSoundOn(true);
	input_objects.push_back(menuButton);

	
	performanceToggle = new Input_Toggle();
	performanceToggle->SetSprite(CR::AssetList::PerformanceButton);
	if(AppConfig::Instance().IsIpad())
		performanceToggle->SetPosition(345, 77);
	else
		performanceToggle->SetPosition(354, 77);
	performanceToggle->SetTouchBounds(0, 51, 480, 48);
	performanceToggle->OnToggled += Delegate(this, &OptionsMenuPage::OnToggledPerformance);
	performanceToggle->ToggleOn(settingsInfo.qualityGraphics);
	performanceToggle->SetSoundOn(true);
	if(AppConfig::Instance().IsIpad())
		performanceToggle->DesignSize(180,28);
	input_objects.push_back(performanceToggle);

	soundToggle = new Input_Toggle();
	soundToggle->SetSprite(CR::AssetList::options_on_off);
	soundToggle->SetPosition(405, 126);
	soundToggle->SetTouchBounds(0, 100, 480, 48);
	soundToggle->OnToggled += Delegate(this, &OptionsMenuPage::OnToggledSound);
	soundToggle->ToggleOn(settingsInfo.soundOn);
	soundToggle->SetSoundOn(true);
	if(AppConfig::Instance().IsIpad())
		soundToggle->DesignSize(70,16);
	input_objects.push_back(soundToggle);
	
	musicToggle = new Input_Toggle();
	musicToggle->SetSprite(CR::AssetList::options_on_off);
	musicToggle->SetPosition(405, 175);
	if(AppConfig::Instance().IsIAd())
		musicToggle->SetTouchBounds(0, 149, 480, 48);
	else
		musicToggle->SetTouchBounds(360, 149, 90, 48);
	musicToggle->OnToggled += Delegate(this, &OptionsMenuPage::OnToggledMusic);
	musicToggle->ToggleOn(settingsInfo.musicOn);
	musicToggle->SetSoundOn(true);
	if(AppConfig::Instance().IsIpad())
		musicToggle->DesignSize(70,16);
	input_objects.push_back(musicToggle);
	
	if(!AppConfig::Instance().IsIAd())
	{
		retroToggle = new Input_Toggle(true);
		retroToggle->SetSprite(CR::AssetList::SoundTrackToggle);
		retroToggle->SetPosition(285, 175);
		retroToggle->SetTouchBounds(210, 149, 140, 48);
		retroToggle->OnToggled += Delegate(this, &OptionsMenuPage::OnToggledRetro);
		retroToggle->ToggleOn(settingsInfo.retroMusic);
		retroToggle->SetSoundOn(true);
		if(AppConfig::Instance().IsIpad())
			retroToggle->DesignSize(122,16);
		input_objects.push_back(retroToggle);
	}

	analogToggle = new Input_Toggle();
	analogToggle->SetSprite(CR::AssetList::options_on_off);
	analogToggle->SetPosition(405, 224);
	analogToggle->SetTouchBounds(0, 198, 480, 48);
	analogToggle->OnToggled += Delegate(this, &OptionsMenuPage::OnToggledAnalog);
	analogToggle->ToggleOn(settingsInfo.analogFlip);
	analogToggle->SetSoundOn(true);
	if(AppConfig::Instance().IsIpad())
		analogToggle->DesignSize(70,16);
	input_objects.push_back(analogToggle);
	
	buttonToggle = new Input_Toggle();
	buttonToggle->SetSprite(CR::AssetList::options_on_off);
	buttonToggle->SetPosition(405, 272);
	buttonToggle->SetTouchBounds(0, 248, 480, 48);
	buttonToggle->OnToggled += Delegate(this, &OptionsMenuPage::OnToggledButton);
	buttonToggle->ToggleOn(settingsInfo.buttonFlip);
	buttonToggle->SetSoundOn(true);
	if(AppConfig::Instance().IsIpad())
		buttonToggle->DesignSize(70,16);
	input_objects.push_back(buttonToggle);
	
	resetButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
		resetButton->SetSpriteAndBounds(355, 15, CR::AssetList::button_data_reset);
	else
		resetButton->SetSpriteAndBounds(327, 11, CR::AssetList::button_data_reset);
	resetButton->OnClicked += Delegate(this, &OptionsMenuPage::OnResetButtonClicked);
	if(AppConfig::Instance().IsIpad())
		resetButton->DesignSize(111,26);
	input_objects.push_back(resetButton);
	resetButton->SetSoundOn(true);
	resetButton->Disabled(false);
	
	yesButton = new Input_Button();
	yesButton->SetSpriteAndBounds(137, 133, CR::AssetList::button_yes);
	yesButton->OnClicked += Delegate(this, &OptionsMenuPage::OnYesButtonClicked);
	if(AppConfig::Instance().IsIpad())
		yesButton->DesignSize(97,71);
	input_objects.push_back(yesButton);
	yesButton->SetSoundOn(true);
	yesButton->Disabled(true);
	
	noButton = new Input_Button();
	noButton->SetSpriteAndBounds(252, 133, CR::AssetList::button_no);
	noButton->OnClicked += Delegate(this, &OptionsMenuPage::OnNoButtonClicked);
	if(AppConfig::Instance().IsIpad())
		noButton->DesignSize(97,71);
	input_objects.push_back(noButton);
	noButton->SetSoundOn(true);
	noButton->Disabled(true);
	
	resetPopupSprite = graphics_engine->CreateSprite1();
	resetPopupSprite->SetImage(CR::AssetList::reset_popup);
	resetPopupSprite->SetPositionAbsalute(240, 160);
	if(AppConfig::Instance().IsIpad())
		resetPopupSprite->SetDesignSize(263,135);
	showResetDialog = false;
}

OptionsMenuPage::~OptionsMenuPage()
{
	delete menuButton;
	delete soundToggle;
	delete musicToggle;	
	if(!AppConfig::Instance().IsIAd())
		delete retroToggle;
	delete analogToggle;
	delete buttonToggle;
	delete resetButton;
	delete yesButton;
	delete noButton;
	delete performanceToggle;
	selectionSprite->Release();
	resetPopupSprite->Release();
}

int OptionsMenuPage::GetBackgroundImage() const
{
	return CR::AssetList::menu_options_background;
}

void OptionsMenuPage::Update(float time)
{
	//menuButton->Render();
	menuButton->Update(time);
	soundToggle->Update(time);
	musicToggle->Update(time);
	if(!AppConfig::Instance().IsIAd())
		retroToggle->Update(time);
	analogToggle->Update(time);
	buttonToggle->Update(time);
	resetButton->Update(time);
	yesButton->Update(time);
	noButton->Update(time);
	performanceToggle->Update(time);
}

void OptionsMenuPage::Render()
{
	menuButton->Render();
	
	if (showSelectionSprite)
		selectionSprite->Render();
	
	soundToggle->Render();
	musicToggle->Render();
	if(!AppConfig::Instance().IsIAd())
		retroToggle->Render();
	analogToggle->Render();
	buttonToggle->Render();
	resetButton->Render();
	performanceToggle->Render();

	if (showResetDialog)
	{
		resetPopupSprite->Render();
		yesButton->Render();
		noButton->Render();
	}
}

void OptionsMenuPage::InputChanged()
{
	if (menuButton->WasPressed())
	{
		// save settings here
		savedGames->SaveSettings(&settingsInfo);
		savedGames->SaveToDisk(DEFAULT_SAVE_FILE);
		menu->ChangeState(menu_main);
	}
	
	if (performanceToggle->IsDown())
	{
		showSelectionSprite = true;
		if(AppConfig::Instance().IsIpad())
			selectionSprite->SetPositionAbsalute(240, 83);
		else
			selectionSprite->SetPositionAbsalute(276, 88);
	}
	else if (soundToggle->IsDown())
	{
		showSelectionSprite = true;
		if(AppConfig::Instance().IsIpad())
			selectionSprite->SetPositionAbsalute(240, 132);
		else
			selectionSprite->SetPositionAbsalute(276, 136);
	}
	else if (musicToggle->IsDown())
	{
		showSelectionSprite = true;
		if(AppConfig::Instance().IsIpad())
			selectionSprite->SetPositionAbsalute(240, 181);
		else
			selectionSprite->SetPositionAbsalute(276, 185);
	}
	else if (!AppConfig::Instance().IsIAd() && retroToggle->IsDown())
	{
		showSelectionSprite = true;
		if(AppConfig::Instance().IsIpad())
			selectionSprite->SetPositionAbsalute(240, 181);
		else
			selectionSprite->SetPositionAbsalute(276, 185);
	}
	else if (analogToggle->IsDown())
	{
		showSelectionSprite = true;
		if(AppConfig::Instance().IsIpad())
			selectionSprite->SetPositionAbsalute(240, 229);
		else
			selectionSprite->SetPositionAbsalute(276, 234);
	}
	else if (buttonToggle->IsDown())
	{
		showSelectionSprite = true;
		if(AppConfig::Instance().IsIpad())
			selectionSprite->SetPositionAbsalute(240, 278);
		else
			selectionSprite->SetPositionAbsalute(276, 283);
	}
}


void OptionsMenuPage::OnToggledSound()
{
	// TODO: Toggle sound in sound engine
	settingsInfo.soundOn = soundToggle->IsToggleOn();
	ISound::Instance().MuteSounds(!settingsInfo.soundOn);
	
//	soundPlayer->Mute(!settingsInfo.soundOn);
}

void OptionsMenuPage::OnToggledMusic()
{
	// TODO: Toggle music in sound engine
	settingsInfo.musicOn = musicToggle->IsToggleOn();
	
	ISound::Instance().MuteMusic(!settingsInfo.musicOn);
//	musicPlayer->Mute(!settingsInfo.musicOn);
//	if (settingsInfo.musicOn)
//		musicPlayer->Play();
}

void OptionsMenuPage::OnToggledRetro()
{
	// TODO: Toggle music in sound engine
	settingsInfo.retroMusic = retroToggle->IsToggleOn();
	
	savedGames->SaveSettings(&settingsInfo);
	MusicManager::Instance().PlaySong(MusicManager::TitleTheme);
//	musicPlayer->Mute(!settingsInfo.musicOn);
//	if (settingsInfo.musicOn)
//		musicPlayer->Play();
}

void OptionsMenuPage::OnToggledAnalog()
{
	settingsInfo.analogFlip = analogToggle->IsToggleOn();
}

void OptionsMenuPage::OnToggledButton()
{
	settingsInfo.buttonFlip = buttonToggle->IsToggleOn();
}

void OptionsMenuPage::OnToggledPerformance()
{
	settingsInfo.qualityGraphics = performanceToggle->IsToggleOn();
}

void OptionsMenuPage::OnResetButtonClicked()
{
	yesButton->Disabled(false);
	noButton->Disabled(false);
	menuButton->Disabled(true);
	soundToggle->Disabled(true);
	musicToggle->Disabled(true);
	if(!AppConfig::Instance().IsIAd())
		retroToggle->Disabled(true);
	analogToggle->Disabled(true);
	buttonToggle->Disabled(true);
	resetButton->Disabled(true);
	performanceToggle->Disabled(true);
	
	showResetDialog = true;
}

void OptionsMenuPage::OnYesButtonClicked()
{	
	menu->GetGame()->GetSaveGameManager()->Reset();
	menu->GetGame()->GetGameStateManager()->Reset();
	menu->GetGame()->GetLevelStateManager()->Reset();
	menu->SetCanResume(false);
	
	
	yesButton->Disabled(true);
	noButton->Disabled(true);
	menuButton->Disabled(false);
	soundToggle->Disabled(false);
	musicToggle->Disabled(false);
	if(!AppConfig::Instance().IsIAd())
		retroToggle->Disabled(false);
	analogToggle->Disabled(false);
	buttonToggle->Disabled(false);
	resetButton->Disabled(false);
	performanceToggle->Disabled(false);
	
	showResetDialog = false;
}

void OptionsMenuPage::OnNoButtonClicked()
{
	yesButton->Disabled(true);
	noButton->Disabled(true);
	menuButton->Disabled(false);
	soundToggle->Disabled(false);
	musicToggle->Disabled(false);
	if(!AppConfig::Instance().IsIAd())
		retroToggle->Disabled(false);
	analogToggle->Disabled(false);
	buttonToggle->Disabled(false);
	resetButton->Disabled(false);
	performanceToggle->Disabled(false);
	
	showResetDialog = false;
}
