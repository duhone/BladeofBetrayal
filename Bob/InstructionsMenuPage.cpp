/*
 *  InstructionsMenuPage.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 2/1/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "InstructionsMenuPage.h"
#include "menu.h"
#include "AssetList.h"
#include "AppConfig.h"

extern HPTGraphicsEngine *graphics_engine;

InstructionsMenuPage::InstructionsMenuPage(Menu *menu, SaveGameManager *savedGames) : IMenuPage(menu)
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
	menuButton->OnClicked += Delegate(this, &InstructionsMenuPage::OnMenuButtonClicked);
	input_objects.push_back(menuButton);
	
	nextButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
	{
		nextButton->SetSpriteAndBounds(394, 268, CR::AssetList::button_next);
		nextButton->DesignSize(78,47);
	}
	else
		nextButton->SetSpriteAndBounds(420, 277, CR::AssetList::button_next);
	nextButton->SetSoundOn(true);
	nextButton->OnClicked += Delegate(this, &InstructionsMenuPage::OnNextButtonClicked);
	input_objects.push_back(nextButton);
	
	prevButton = new Input_Button();
	if(AppConfig::Instance().IsIpad())
	{
		prevButton->SetSpriteAndBounds(394, 268, CR::AssetList::button_previous);
		prevButton->DesignSize(78,47);
	}
	else
		prevButton->SetSpriteAndBounds(420, 277, CR::AssetList::button_previous);
	prevButton->SetSoundOn(true);
	prevButton->OnClicked += Delegate(this, &InstructionsMenuPage::OnPrevButtonClicked);
	prevButton->Disabled(true);
	input_objects.push_back(prevButton);
	
	instructions01 = graphics_engine->CreateSprite1();
	instructions01->SetImage(CR::AssetList::menu_instructions_01);
	instructions01->SetPositionAbsalute(240, 160);
	if(AppConfig::Instance().IsIpad())
		instructions01->SetDesignSize(480,320);
	
	instructions02 = graphics_engine->CreateSprite1();
	instructions02->SetImage(CR::AssetList::menu_instructions_02);
	instructions02->SetPositionAbsalute(240, 160);
	if(AppConfig::Instance().IsIpad())
		instructions02->SetDesignSize(480,320);
	
	currPage = 1;
}

InstructionsMenuPage::~InstructionsMenuPage()
{
	delete menuButton;
	delete nextButton;
	delete prevButton;
	
	instructions01->Release();
	instructions02->Release();
}

int InstructionsMenuPage::GetBackgroundImage() const
{
	return CR::AssetList::menu_instructions_background;
}

void InstructionsMenuPage::Update(float time)
{
	//menuButton->Render();
}

void InstructionsMenuPage::Render()
{
	menuButton->Render();
	
	if (currPage == 1)
	{
		instructions01->Render();
		nextButton->Render();
	}
	else if (currPage == 2)
	{
		instructions02->Render();
		prevButton->Render();
	}
}

void InstructionsMenuPage::InputChanged()
{
}

void InstructionsMenuPage::OnMenuButtonClicked()
{
	menu->ChangeState(menu_main);
}

void InstructionsMenuPage::OnNextButtonClicked()
{
	this->currPage = 2;
	nextButton->Disabled(true);
	prevButton->Disabled(false);
}

void InstructionsMenuPage::OnPrevButtonClicked()
{
	this->currPage = 1;
	nextButton->Disabled(false);
	prevButton->Disabled(true);
}
