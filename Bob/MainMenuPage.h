/*
 *  MainMenuPage.h
 *  BoB
 *
 *  Created by Robert Shoemate on 1/21/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "IMenuPage.h"
#include "SaveGameManager.h"

class Menu;

class MainMenuPage : public IMenuPage
{
public:
	MainMenuPage(Menu *menu, SaveGameManager *savedGames);
	~MainMenuPage();
	
	int GetBackgroundImage() const;
	void Render();
	void InputChanged();
	
private:
	Input_Button *resumeGameButton;
	Input_Button *missionSelectButton;
	Input_Button *optionsButton;
	Input_Button *instructionsButton;
	Input_Button *aboutButton;
	Input_Button *buyGameButton;
	SaveGameManager *savedGames;
};