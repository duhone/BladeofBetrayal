/*
 *  GoalMarkerBlock.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 3/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "GoalMarkerBlock.h"

GoalMarkerBlock::GoalMarkerBlock()
{
	sprite->SetImage(CR::AssetList::goal_tag);
	sprite->SetAutoAnimate(true);
	sprite->SetFrameSet(0);
	sprite->SetFrame(0);
	draw = true;
}

GoalMarkerBlock::~GoalMarkerBlock()
{
}

bool GoalMarkerBlock::CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype)
{
	return false;
}