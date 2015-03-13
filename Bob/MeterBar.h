/*
 *  MeterBar.h
 *  BoB
 *
 *  Created by Robert Shoemate on 1/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "../Engines/Graphics/HPTGraphics.h"
#include "point.h"

enum MeterBarColor
{
	Red,
	Green
};

class MeterBar
{
public:
	MeterBar(MeterBarColor mbColor);
	~MeterBar();
	
	void SetPosition(int x, int y);
	void SetPercentFull(float p); // 0 - 1 
	//void SetLength(int len);
	//void SetFill(int fill);
	void SetTotalBars(int totalBars);
	void Render();
private:
	HPTSprite1 *leftEdgeSprite;
	HPTSprite1 *emptyMeterSprite;
	HPTSprite1 *colorMeterSprite;
	HPTSprite1 *rightEdgeSprite;
	float percentFull;
	HPTPoint pos;
	int totalBars;
};