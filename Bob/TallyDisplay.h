/*
 *  TallyDisplay.h
 *  BoB
 *
 *  Created by Robert Shoemate on 2/18/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "../Engines/Graphics/HPTGraphics.h"
#include "point.h"
#include "Sound.h"

#include <string>
#include <stdio.h>

using namespace std;

class TallyDisplay
	{
	public:
		TallyDisplay();
		~TallyDisplay();
		void SetFont(HPTFont1* displayFont);
		void SetPosition(int x, int y);
		void SetTally(int total, int maxTotal);
		void Render();
		
		void BeginCountUpAnimation() { currTotal = 0; delayTimer = .03;}
		void Update(float time);
		bool DoneAnimating() { return currTotal == total; }
		void SetDoneAnimating();
		int CurrentTally() const { return currTotal; }
	private:
		HPTPoint pos;
		float delayTimer;
		HPTFont1* displayFont;
		//char timeString[6];
		//bool showFrontZero;
		int total;
		int maxTotal;
		int currTotal;
		std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFX;
	};