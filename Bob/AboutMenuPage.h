/*
 *  AboutMenuPage.h
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

class AboutMenuPage : public IMenuPage
	{
	public:
		AboutMenuPage(Menu *menu, SaveGameManager *savedGames);
		~AboutMenuPage();
		
		int GetBackgroundImage() const;
		void Update(float time);
		void Render();
		void InputChanged();
		
	private:
		SaveGameManager *savedGames;
		Input_Button *menuButton;
		HPTSprite1 *aboutSprite;
	};