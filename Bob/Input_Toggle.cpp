/*
 *  Input_Toggle.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 2/1/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Input_Toggle.h"
#include "AssetListNew.h"

using namespace CR::Sound;

extern HPTGraphicsEngine *graphics_engine;

Input_Toggle::Input_Toggle(bool _oneSet/* = false*/) : m_oneSet(_oneSet), isDown(false)
{
	objectSprite = 0;
	SetPosition(0, 0);
	SetTouchBounds(0, 0, 0, 0);
	toggleOn = false;
	touchID = -1;

	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::click::ID);
}

Input_Toggle::~Input_Toggle()
{
	FreeResources();
}

void Input_Toggle::TouchesBeganImpl(Touch &_touch)
{
	//CGPoint glLocation;
	//for (UITouch *touch in touches)
	{
		if (this->touchID != -1 && _touch.ID != this->touchID)
			return;
		
		//glLocation = GetGLLocation(view, touch);
		
		if (_touch.X > touchBounds.left && 
			_touch.X < touchBounds.right + touchBounds.left &&
			_touch.Y > touchBounds.top &&
			_touch.Y < touchBounds.bottom + touchBounds.top)
		{
			isDown = true;
			this->touchID = _touch.ID;
		}
		else
		{
			isDown = false;
		}
	}	
}

void Input_Toggle::TouchesMovedImpl(Touch &_touch)
{
	//CGPoint glLocation;
	//for (UITouch *touch in touches)
	{
		if (this->touchID != -1 && _touch.ID != this->touchID)
			return;
		
		//glLocation = GetGLLocation(view, touch);
		
		if (_touch.X > touchBounds.left && 
			_touch.X < touchBounds.right + touchBounds.left &&
			_touch.Y > touchBounds.top &&
			_touch.Y < touchBounds.bottom + touchBounds.top)
		{
			isDown = true;
			this->touchID = _touch.ID;
		}
		else
		{
			isDown = false;
		}
	}	
}

void Input_Toggle::TouchesEndedImpl(Touch &_touch)
{
	//for (UITouch *touch in touches)
	{
		if (_touch.ID == this->touchID)
		{
			if (isDown)
			{
				toggleOn = !toggleOn;
				if(OnToggled.Size() > 0)
					OnToggled();
				
				if (soundOn)
					m_soundFX->Play();
				//	soundPlayer->PlaySound(clickon);
			}
			
			isDown = false;
			this->touchID = -1;
			//break;
		}
	}
}

void Input_Toggle::Reset()
{
}

void Input_Toggle::Update(float time)
{
	if (objectSprite != 0)
	{
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
}

void Input_Toggle::Render()
{
	if (objectSprite != 0)
		objectSprite->Render();
}

void Input_Toggle::FreeResources()
{
	if(	this->objectSprite != 0)
	{
		this->objectSprite->Release();
		this->objectSprite = 0;
	}
}

void Input_Toggle::SetSprite(int nSprite)
{
	if(this->objectSprite == 0)
		this->objectSprite = graphics_engine->CreateSprite1();	
	this->objectSprite->SetImage(nSprite);
	
	this->objectSprite->SetPositionAbsalute(pos.x, pos.y);
	
	if (toggleOn)
		objectSprite->SetFrameSet(0);
	else
		objectSprite->SetFrameSet(1);
}

void Input_Toggle::SetPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
	
	if (this->objectSprite != 0)
		this->objectSprite->SetPositionAbsalute(pos.x, pos.y);
}

void Input_Toggle::SetTouchBounds(int x, int y, int width, int height)
{
	Rect r;
	r.left = x;
	r.top = y;
	r.right = width;
	r.bottom = height;
	this->touchBounds = r;
}
