/*
 *  Input_Toggle.h
 *  BoB
 *
 *  Created by Robert Shoemate on 2/1/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "../Engines/Input/Input_Object.h"
#include "point.h"
#include "../Engines/Utility/Event.h"

class Input_Toggle : public Input_Object
{
public:
	Input_Toggle(bool _oneSet = false);
	~Input_Toggle();
	
	void TouchesBeganImpl(Touch &_touch);
	void TouchesMovedImpl(Touch &_touch);
	void TouchesEndedImpl(Touch &_touch);
	void Reset();
	void Update(float time);
	void Render();
	void FreeResources();
	
	void SetSprite(int nSprite);
	void SetPosition(int x, int y);
	void SetTouchBounds(int x, int y, int width, int height);
	
	bool IsDown() const {return isDown;}
	bool IsToggleOn() const {return toggleOn;}
	void ToggleOn(bool _value)
	{
		toggleOn = _value;
		
		if (toggleOn)
		{
			if(m_oneSet)
				objectSprite->SetFrame(0);
			else
				objectSprite->SetFrameSet(0);
		}
		else
		{
			if(m_oneSet)
				objectSprite->SetFrame(1);
			else
				objectSprite->SetFrameSet(1);
		}
	}
	
	Event OnToggled;
	void SetSoundOn(bool isOn) { soundOn = isOn; }
	virtual void DesignSize(int _width,int _height) {objectSprite->SetDesignSize(_width,_height);}
private:
	HPTSprite1* objectSprite;
	HPTPoint pos;
	Rect touchBounds;
	bool toggleOn;
	int touchID;
	bool isDown;
	bool m_oneSet;
	bool soundOn;
};