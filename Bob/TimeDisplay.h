/*
 *  TimeDisplay.h
 *  BoB
 *
 *  Created by Robert Shoemate on 1/30/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "../Engines/Graphics/HPTGraphics.h"
#include "point.h"
#include "Sound.h"

#include <string>
#include <stdio.h>

using namespace std;

class TimeDisplay
{
public:
	TimeDisplay();
	~TimeDisplay();
	void SetFont(HPTFont1* displayFont);
	void SetPosition(int x, int y);
	void SetTime(float currTime);
	void Render();
	void SetShowFrontZero(bool showFrontZero) { this->showFrontZero = showFrontZero; }
	
	void BeginCountUpAnimation(float maxTime) { this->maxTime = maxTime; timeCount = 0; delayTimer = .009; doneAnimating = false;}
	void Update(float time);
	bool DoneAnimating() { return doneAnimating; }
	void SetDoneAnimating();
	
	float GetCurrTime() { return currTime; }
private:
	HPTPoint pos;
	float currTime;
	HPTFont1* displayFont;
	char timeString[6];
	bool showFrontZero;
	
	float timeCount;
	float maxTime;
	float delayTimer;
	bool doneAnimating;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFX;
};