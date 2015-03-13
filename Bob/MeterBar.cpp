/*
 *  MeterBar.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 1/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "MeterBar.h"
#include "AssetList.h"
#include <algorithm>
#include "AppConfig.h"

using namespace std;

extern HPTGraphicsEngine *graphics_engine;

MeterBar::MeterBar(MeterBarColor mbColor)
{
	colorMeterSprite = graphics_engine->CreateSprite1();
	if (mbColor == Green)
		colorMeterSprite->SetImage(CR::AssetList::meter_bar_green);
	else if (mbColor == Red)
		colorMeterSprite->SetImage(CR::AssetList::meter_bar_red);
	if(AppConfig::Instance().IsIpad())
		colorMeterSprite->SetDesignSize(1,9);

	leftEdgeSprite = graphics_engine->CreateSprite1();
	leftEdgeSprite->SetImage(CR::AssetList::meter_bar_left_edge);
	if(AppConfig::Instance().IsIpad())
		leftEdgeSprite->SetDesignSize(2,9);
	
	rightEdgeSprite = graphics_engine->CreateSprite1();
	rightEdgeSprite->SetImage(CR::AssetList::meter_bar_right_edge);
	if(AppConfig::Instance().IsIpad())
		rightEdgeSprite->SetDesignSize(2,9);
	
	emptyMeterSprite = graphics_engine->CreateSprite1();
	emptyMeterSprite->SetImage(CR::AssetList::meter_bar_empty);
	if(AppConfig::Instance().IsIpad())
		emptyMeterSprite->SetDesignSize(1,9);
	
	percentFull = 0;
	totalBars = 15;
}

MeterBar::~MeterBar()
{
	colorMeterSprite->Release();
	leftEdgeSprite->Release();
	rightEdgeSprite->Release();
	emptyMeterSprite->Release();
}

void MeterBar::SetPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
	
	leftEdgeSprite->SetPositionAbsalute(pos.x, pos.y);	
}

void MeterBar::SetPercentFull(float p)
{
	percentFull = max(0.0f,p);
}

void MeterBar::SetTotalBars(int totalBars)
{
	this->totalBars = totalBars;
}

void MeterBar::Render()
{
	int pFill = totalBars * percentFull;
	
	leftEdgeSprite->Render();
	
	int xPos = pos.x + colorMeterSprite->DesignWidth();
	int yPos = pos.y;
	/*for (int i = 0; i < totalBars; i++)
	{
		if (i < pFill)
		{
			colorMeterSprite->SetPositionAbsalute(xPos, yPos);
			colorMeterSprite->Render();
			xPos += colorMeterSprite->GetFrameWidth();
		}
		else
		{
			emptyMeterSprite->SetPositionAbsalute(xPos, yPos);
			emptyMeterSprite->Render();
			xPos += emptyMeterSprite->GetFrameWidth();
		}
	}*/
	
	colorMeterSprite->SetPositionAbsalute(xPos, yPos);
	colorMeterSprite->RenderBatch(pFill);
	xPos += colorMeterSprite->DesignWidth()*pFill;
	emptyMeterSprite->SetPositionAbsalute(xPos, yPos);
	emptyMeterSprite->RenderBatch(totalBars-pFill);
	xPos += emptyMeterSprite->DesignWidth()*(totalBars-pFill);
	
	rightEdgeSprite->SetPositionAbsalute(xPos, yPos);
	rightEdgeSprite->Render();
}