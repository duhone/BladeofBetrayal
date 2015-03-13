/*
 *  MissionSelectMenuPage.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 1/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "MissionSelectMenuPage.h"
#include "Menu.h"
#include "AppConfig.h"

//extern Input_Engine *input_engine;

MissionSelectMenuPage::MissionSelectMenuPage(Menu *menu, SaveGameManager *savedGames) : IMenuPage(menu)
{
	this->savedGames = savedGames;
	
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
	
	if(!AppConfig::Instance().IsIAd())
	{
		specialsButton = new Input_Button();
		if(AppConfig::Instance().IsIpad())
		{
			specialsButton->SetSpriteAndBounds(82, 15, CR::AssetList::specials_specialButton);
			specialsButton->DesignSize(83,30);
		}
		else
			specialsButton->SetSpriteAndBounds(92, 11, CR::AssetList::specials_specialButton);
		specialsButton->SetSoundOn(true);
		input_objects.push_back(specialsButton);
	}

	missionSelect = new Input_MissionSelect(savedGames);
	missionSelect->SetPosition(95, 185);
	input_objects.push_back(missionSelect);
}

MissionSelectMenuPage::~MissionSelectMenuPage()
{
	delete menuButton;
	if(!AppConfig::Instance().IsIAd())
		delete specialsButton;
	delete missionSelect;
}

int MissionSelectMenuPage::GetBackgroundImage() const
{
	return CR::AssetList::menu_background_01;
}

void MissionSelectMenuPage::Update(float time)
{
	missionSelect->Update(time);
	
	if (missionSelect->StartLevel())
	{
		menu->SetStartLevel(missionSelect->LevelToStart());
		menu->ChangeState(menu_start_game);
	}
}

void MissionSelectMenuPage::Render()
{
	menuButton->Render();
	if(!AppConfig::Instance().IsIAd())
		specialsButton->Render();
	missionSelect->Render();
}

void MissionSelectMenuPage::InputChanged()
{
	if (menuButton->WasPressed())
		menu->ChangeState(menu_main);
	else if(!AppConfig::Instance().IsIAd() && specialsButton->WasPressed())
		menu->ChangeState(menu_specials);
}