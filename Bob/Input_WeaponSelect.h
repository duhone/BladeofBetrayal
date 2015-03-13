/*
 *  Input_WeaponSelect.h
 *  BoB
 *
 *  Created by Robert Shoemate on 1/29/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "../Engines/Input/Input_Object.h"
#include "point.h"
#include "Player.h"

class Input_WeaponSelect : public Input_Object
{
public:
	Input_WeaponSelect(Player *player);
	~Input_WeaponSelect();
	void TouchesBeganImpl(Touch &_touch);
	void TouchesMovedImpl(Touch &_touch);
	void TouchesEndedImpl(Touch &_touch);
	void Reset();
	void Update(float time);
	void Render();
	void FreeResources();
	
	void SetPosition(float x, float y, int boundFuzz);
	
	// Properties
	bool CurrentWeapon() const {return currWeapon;}
	int GetSelectedWeapon(int _x,int _y);
	//void Temp(int _value) {temp = _value;}
	
private:
	int currWeapon;
	HPTSprite1* weaponIconsSprite;
	HPTSprite1* grenadeIconSprite;
	HPTPoint pos;
	Player *player;
	Rect bounds;
	int boundFuzz;
	bool isDown;
	int touchID;
};