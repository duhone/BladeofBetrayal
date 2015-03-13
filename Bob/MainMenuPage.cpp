/*
 *  MainMenuPage.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 1/21/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainMenuPage.h"
#include "Menu.h"
#include "AppConfig.h"
#include "s3eExt_OSExec.h"
//#import <UIKit/UIApplication.h>

//extern Input_Engine *input_engine;

MainMenuPage::MainMenuPage(Menu *menu, SaveGameManager *savedGames) : IMenuPage(menu), buyGameButton(NULL)
{
	this->savedGames = savedGames;
	
	// Create input objects
//#ifdef BOB_LITE
	if(AppConfig::Instance().IsIAd())
	{
		buyGameButton = new Input_Button();
		buyGameButton->SetSpriteAndBounds(27, 161, CR::AssetList::BuyButton);
		buyGameButton->SetSoundOn(true);
		input_objects.push_back(buyGameButton);
	}
//#endif
	
	resumeGameButton = new Input_Button();
//#ifdef BOB_LITE
//	resumeGameButton->SetSpriteAndBounds(243, 161, CR::AssetList::menu_resume_game_buttons);
//#else
	if(AppConfig::Instance().IsIpad())
	{
		resumeGameButton->SetSpriteAndBounds(11, 259, CR::AssetList::menu_resume_game_buttons);
		resumeGameButton->DesignSize(113,23);
	}
	else if(AppConfig::Instance().IsIAd())
	{
		resumeGameButton->SetSpriteAndBounds(243, 161, CR::AssetList::menu_resume_game_buttons);
		resumeGameButton->DesignSize(211,50);
	}
	else
		resumeGameButton->SetSpriteAndBounds(132, 161, CR::AssetList::menu_resume_game_buttons);	
//#endif
	resumeGameButton->SetSoundOn(true);
	input_objects.push_back(resumeGameButton);
	
	missionSelectButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
	{
		missionSelectButton->SetSpriteAndBounds(11, 284, CR::AssetList::menu_mission_select_buttons);
		missionSelectButton->DesignSize(113,23);
	}
	else
		missionSelectButton->SetSpriteAndBounds(27, 210, CR::AssetList::menu_mission_select_buttons);
	missionSelectButton->SetSoundOn(true);
	input_objects.push_back(missionSelectButton);
	
	optionsButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
	{
		optionsButton->SetSpriteAndBounds(241, 284, CR::AssetList::menu_options_buttons);
		optionsButton->DesignSize(113,23);
	}
	else
		optionsButton->SetSpriteAndBounds(243, 210, CR::AssetList::menu_options_buttons);
	optionsButton->SetSoundOn(true);
	input_objects.push_back(optionsButton);
	
	instructionsButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
	{
		instructionsButton->SetSpriteAndBounds(126, 284, CR::AssetList::menu_instructions_buttons);
		instructionsButton->DesignSize(113,23);
	}
	else
		instructionsButton->SetSpriteAndBounds(27, 258, CR::AssetList::menu_instructions_buttons);
	instructionsButton->SetSoundOn(true);
	input_objects.push_back(instructionsButton);
	
	aboutButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
	{
		aboutButton->SetSpriteAndBounds(356, 284, CR::AssetList::menu_about_buttons);
		aboutButton->DesignSize(113,23);
	}
	else
		aboutButton->SetSpriteAndBounds(243, 258, CR::AssetList::menu_about_buttons);
	aboutButton->SetSoundOn(true);
	input_objects.push_back(aboutButton);
}

MainMenuPage::~MainMenuPage()
{
	delete resumeGameButton;
	delete missionSelectButton;
	delete optionsButton;
	delete instructionsButton;
	delete aboutButton;
	delete buyGameButton;
}

int MainMenuPage::GetBackgroundImage() const
{
	if(savedGames->HasBeatGame())
		return CR::AssetList::MenuBackgroundWon;
	else
		return CR::AssetList::menu_background_02;
}

void MainMenuPage::Render()
{
	if (menu->CanResume())
	{
		resumeGameButton->Disabled(false);
		resumeGameButton->Render();
	}
	else
	{
		resumeGameButton->Disabled(true);
		//resumeGameButton->Render();
	}
	
	missionSelectButton->Render();
	optionsButton->Render();
	instructionsButton->Render();
	aboutButton->Render();
	
//#ifdef BOB_LITE
	if(AppConfig::Instance().IsIAd())
		buyGameButton->Render();
//#endif
}

void MainMenuPage::InputChanged()
{
	if (resumeGameButton->WasPressed())
	{
		menu->ChangeState(menu_resume_game);
	}
	else if (missionSelectButton->WasPressed())
	{
#ifdef BOB_LITE
		menu->SetStartLevel(1);
		menu->ChangeState(menu_start_game);
#else
		menu->ChangeState(menu_mission_select);
#endif
	}
	else if (optionsButton->WasPressed())
	{
		menu->ChangeState(menu_options);
	}
	else if (instructionsButton->WasPressed())
	{
		menu->ChangeState(menu_instructions);
	}
	else if (aboutButton->WasPressed())
	{
		menu->ChangeState(menu_about);
	}
//#ifdef BOB_LITE
	else if (buyGameButton && buyGameButton->WasPressed())
	{
		//[[UIApplication sharedApplication] openURL:[[NSURL alloc]  initWithString: [NSString stringWithCString:"itms://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=308315671&mt=8"]]];
		s3eOSExecExecute("itms://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=308315671&mt=8",false);
	}
//#endif
}