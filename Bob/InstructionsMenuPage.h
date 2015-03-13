/*
 *  InstructionsMenuPage.h
 *  BoB
 *
 *  Created by Robert Shoemate on 2/1/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "IMenuPage.h"
#include "SaveGameManager.h"

class Menu;

class InstructionsMenuPage : public IMenuPage
	{
	public:
		InstructionsMenuPage(Menu *menu, SaveGameManager *savedGames);
		~InstructionsMenuPage();
		
		int GetBackgroundImage() const;
		void Update(float time);
		void Render();
		void InputChanged();
		void OnMenuButtonClicked();
		void OnNextButtonClicked();
		void OnPrevButtonClicked();
	private:
		SaveGameManager *savedGames;
		Input_Button *menuButton;
		Input_Button *nextButton;
		Input_Button *prevButton;
		HPTSprite1 *instructions01;
		HPTSprite1 *instructions02;
		int currPage;
	};