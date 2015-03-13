/*
 *  Input_Analog.h
 *  BoB
 *
 *  Created by Robert Shoemate on 1/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "Input_Object.h"

class Input_Analog : public Input_Object
{
public:
	Input_Analog(int _spriteID);
	~Input_Analog();
	
	void SetPosition(float analog_center_x, float analog_center_y);
	void SetRadius(int r, int rMax, int fuzz);
	float GetAnalogX(Touch &touchLocation);
	float GetAnalogY(Touch &touchLocation);
	bool IsInAnalogBounds(Touch &touchLocation);
	bool IsInAnalogFudge(Touch &touchLocation);
	
	void TouchesBeganImpl(Touch &_touches);
	void TouchesMovedImpl(Touch &_touches);
	void TouchesEndedImpl(Touch &_touches);
	
	float AnalogX() const {return analog_x;}
	float AnalogY() const {return analog_y;}
	//float OldAnalogX() const {return old_analog_x;}
	//float OldAnalogY() const {return old_analog_y;}
	
	void Reset();
	void Render();
	virtual void FreeResources();
	virtual void DesignSize(int _width,int _height) {analogSprite->SetDesignSize(_width,_height);}
private:
	float analog_center_x;
	float analog_center_y;
	float analog_center_x_new;
	float analog_center_y_new;
	
	float analog_radius;
	float analog_radius_max; // outer band of radius that allows full analog movement
	float analog_radius_fudge; // if user drags finger out of analog, keeps working
	
	float analog_x;
	float analog_y;
	
	float old_analog_x;
	float old_analog_y;
	
	int touchID;
	HPTSprite1* analogSprite;
	
	bool fudgeAvailable;
};