/*
 *  Input_Analog.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 1/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Input_Analog.h"
//#include "AssetList.h"
#include "math.h"

extern HPTGraphicsEngine *graphics_engine;

Input_Analog::Input_Analog(int _spriteID)
{
	touchID = -1;
	analog_center_x = 0;
	analog_center_y = 0;
	analog_center_x_new = 0;
	analog_center_y_new = 0;
	analog_radius = 0;
	analog_x = 0;
	analog_y = 0;
	old_analog_x = 0;
	old_analog_y = 0;
	analog_radius_max = 0;
	analog_radius_fudge = 0;
	fudgeAvailable = false;
	
	this->analogSprite = graphics_engine->CreateSprite1();	
	this->analogSprite->SetImage(_spriteID);
}

Input_Analog::~Input_Analog()
{
	FreeResources();
}

void Input_Analog::SetPosition(float analog_center_x, float analog_center_y)
{
	this->analog_center_x = analog_center_x;
	this->analog_center_y = analog_center_y;
	analog_center_x_new = analog_center_x;
	analog_center_y_new = analog_center_y;

	analogSprite->SetPositionAbsalute(analog_center_x_new, analog_center_y_new);
}

void Input_Analog::SetRadius(int r, int rMax, int fudge)
{
	this->analog_radius = r; // from the sprite
	this->analog_radius_max = rMax; // the last 10 pixels of the radius will return 1 for the analog
	this->analog_radius_fudge = fudge;
}

float Input_Analog::GetAnalogX(Touch &touchLocation)
{
	if (IsInAnalogBounds(touchLocation) || IsInAnalogFudge(touchLocation))
	{
		if (touchLocation.X > analog_center_x_new + analog_radius - analog_radius_max)
			return 1;
		else if (touchLocation.X < analog_center_x_new - analog_radius + analog_radius_max)
			return -1;
		else
		{
			float pX = (touchLocation.X - analog_center_x_new)/(analog_radius - analog_radius_max);
			if(fabs(pX) < 0.05)
				pX = 0;
			return pX;
		}
	}
	else
		return 0;
}

float Input_Analog::GetAnalogY(Touch &touchLocation)
{
	if (IsInAnalogBounds(touchLocation) || IsInAnalogFudge(touchLocation))
	{
		if (touchLocation.Y > analog_center_y_new + analog_radius - analog_radius_max)
			return 1;
		else if (touchLocation.Y < analog_center_y_new - analog_radius + analog_radius_max)
			return -1;
		else
		{
			float pY = (touchLocation.Y - analog_center_y_new)/(analog_radius - analog_radius_max);
			if(fabs(pY) < 0.05)
				pY = 0;
			return pY;
		}
	}
	else
		return 0;
}

bool Input_Analog::IsInAnalogBounds(Touch &touchLocation)
{	
	float dX = touchLocation.X - analog_center_x_new;
	float dY = touchLocation.Y - analog_center_y_new;
	
	float dR = sqrt((float)(dX*dX+dY*dY));
	
	if (dR <= analog_radius)
	{
		fudgeAvailable = true;
		return true;
	}
	else
		return false;
}

bool Input_Analog::IsInAnalogFudge(Touch &touchLocation)
{
	if (!fudgeAvailable)
		return false;
	
	float dX = touchLocation.X - analog_center_x_new;
	float dY = touchLocation.Y - analog_center_y_new;
	
	float dR = sqrt((float)(dX*dX+dY*dY));
	
	if (dR <= analog_radius + analog_radius_fudge)
		return true;
	else
		return false;
}

void Input_Analog::TouchesBeganImpl(Touch &_touches)
{
	bool analogSet = true;
	float tmp;
	
	//CGPoint pos;
	//for (int i = 0;i < _touches.size();++i)
	{
		if (touchID != -1 && touchID != _touches.ID)
			return;
		
		// Get the GL position
		//pos = [touch locationInView: view];
		//tmp = pos.x;
		//pos.x = pos.y;
		//pos.y = 320-tmp;
		analogSet = false;
		if (IsInAnalogBounds(_touches))
		{
			this->touchID = _touches.ID;
			fudgeAvailable = true;
			
			analog_center_x_new = _touches.X;
			analog_center_y_new = _touches.Y;
			float dx = analog_center_x - analog_center_x_new;
			float dy = analog_center_y - analog_center_y_new;

			float radius = sqrt(dx*dx+dy*dy);
			dx /= radius;
			dy /= radius;
			radius = std::min(radius,analog_radius*.12f);
			analog_center_x_new = analog_center_x - dx*radius;
			analog_center_y_new = analog_center_y - dy*radius;

			// Analog X
			old_analog_x = analog_x;
			analog_x = GetAnalogX(_touches);

			// Analog Y
			old_analog_y = analog_y;
			analog_y = GetAnalogY(_touches);
			
			analogSet = true;
		}
		
		//if (analogSet)
		//	break;
	}
	
	if (!analogSet)
	{
		analog_x = 0;
		analog_y = 0;
	}
	
}

void Input_Analog::TouchesMovedImpl(Touch &_touches)
{
	bool analogSet = true;
	float tmp;
	
	//CGPoint pos;
	//for (int i = 0;i < _touches.size();++i)
	{
		if (touchID != -1 && touchID != _touches.ID)
			return;
		
		// Get the GL position
		//pos = [touch locationInView: view];
		//tmp = pos.x;
		//pos.x = pos.y;
		//pos.y = 320-tmp;
		analogSet = false;
		if (IsInAnalogBounds(_touches) || IsInAnalogFudge(_touches))
		{
			//this->touch = touch;
			
			// Analog X
			old_analog_x = analog_x;
			analog_x = GetAnalogX(_touches);
			
			// Analog Y
			old_analog_y = analog_y;
			analog_y = GetAnalogY(_touches);
			
			analogSet = true;
		}
		
		//if (analogSet)
		//	break;
	}
	
	if (!analogSet)
	{
		analog_x = 0;
		analog_y = 0;
	}
}

void Input_Analog::TouchesEndedImpl(Touch &_touches)
{
	//for (int i = 0;i < _touches.size();++i)
	{
		if (touchID == _touches.ID)
		{
			analog_center_x_new = analog_center_x;
			analog_center_y_new = analog_center_y;
			analog_x = 0;
			analog_y = 0;
			fudgeAvailable = false;
			this->touchID = -1;
			//break;
		}
	}
}

void Input_Analog::Reset()
{
	this->touchID = -1;
	analog_x = 0;
	analog_y = 0;
	old_analog_x = 0;
	old_analog_y = 0;
	analog_center_x_new = analog_center_x;
	analog_center_y_new = analog_center_y;
}

void Input_Analog::Render()
{
	analogSprite->SetPositionAbsalute(analog_center_x_new, analog_center_y_new);
	analogSprite->Render();
}

void Input_Analog::FreeResources()
{
	this->analogSprite->Release();
}