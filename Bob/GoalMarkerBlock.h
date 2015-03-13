/*
 *  GoalMarkerBlock.h
 *  BoB
 *
 *  Created by Robert Shoemate on 3/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once

#include "Object.h"

class GoalMarkerBlock : public Object  
	{
	public:
		GoalMarkerBlock();
		virtual ~GoalMarkerBlock();
		virtual bool CollideCheck(IPlayer* arg,int& x,int& y,bool& m,bool& ladder,bool& my,HPTRect& temprect,int& ltype);
		bool IsObject() const { return false; }
	private:
	};