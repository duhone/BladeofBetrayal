/*
 *  Input_Button.cpp
 *  BoB
 *
 *  Created by Robert Shoemate on 1/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Input_Button.h"
#include "AssetListNew.h"

using namespace CR::Sound;

extern HPTGraphicsEngine *graphics_engine;

Input_Button::Input_Button(bool _oneSet/* = false*/) : m_oneSet(_oneSet)
{
	isDown = false;
	wasPressed = false;
	touchID = -1;
	bounds.top = 0;
	bounds.left = 0;
	bounds.bottom = 0;
	bounds.right = 0;
	objectSprite = 0;
	isActing = false;
	soundOn = false;
	position = bounds;
	
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::click::ID);
}

Input_Button::~Input_Button()
{
	FreeResources();
}

void Input_Button::FreeResources()
{
	if(	this->objectSprite != 0)
	{
		this->objectSprite->Release();
		this->objectSprite = 0;
	}
}

void Input_Button::SetButtonBounds(float left, float top, float width, float height)
{
	Rect r;
	r.top = top;
	r.left = left;
	r.bottom = height;
	r.right = width;
	bounds = r;
}

void Input_Button::SetSpriteAndBounds(float left, float top, int nSprite)
{
	this->SetSprite(nSprite);
	
	Rect r;
	r.top = top;
	r.left = left;
	r.bottom = objectSprite->DesignHeight();
	r.right = objectSprite->DesignWidth();
	bounds = r;
	position = r;
}


 void Input_Button::SetSprite(int nSprite)
 {
	 if(this->objectSprite == 0)
		 this->objectSprite = graphics_engine->CreateSprite1();	
	 this->objectSprite->SetImage(nSprite);
 }

void Input_Button::TouchesBeganImpl(Touch &_touches)
{
	//CGPoint glLocation;
	//for (int i = 0;i < _touches.size();++i)
	{
		if (touchID != -1 && touchID != _touches.ID)
			return;
		
		//glLocation = GetGLLocation(view, touch);
		
		if (_touches.X > bounds.left && 
			_touches.X < bounds.right + bounds.left &&
			_touches.Y > bounds.top &&
			_touches.Y < bounds.bottom + bounds.top)
		{
			isDown = true;
			isActing = true;
			this->touchID = _touches.ID;
		}
		else
		{
			isDown = false;
			isActing = false;
		}
	}
}

void Input_Button::TouchesMovedImpl(Touch &_touches)
{
	//CGPoint glLocation;
	//for (int i = 0;i < _touches.size();++i)
	{
		if (touchID != -1 && touchID != _touches.ID)
			return;
		
		//glLocation = GetGLLocation(view, touch);
		
		if (_touches.X > bounds.left && 
			_touches.X < bounds.right + bounds.left &&
			_touches.Y > bounds.top &&
			_touches.Y < bounds.bottom + bounds.top)
		{
			isDown = true;
			isActing = true;
			//this->touch = touch;
		}
		else
		{
			isDown = false;
			isActing = false;
		}
	}
}

void Input_Button::TouchesEndedImpl(Touch &_touches)
{
	//for (int i = 0;i < _touches.size();++i)
	{
		if (touchID ==  _touches.ID)
		{
			if (isDown)
			{
				if (soundOn)
					m_soundFX->Play();
				//	soundPlayer->PlaySound(clickon);
				
				if(OnClicked.Size() > 0)
					OnClicked();
				else
					wasPressed = true;
			}
			
			isDown = false;
			isActing = false;
			this->touchID = -1;
			//break;
		}
	}
}

void Input_Button::Reset()
{
	touchID = -1;
	isDown = false;
	isActing = false;
	wasPressed = false;
}

void Input_Button::Render()
{
	if(objectSprite != 0)
	{
		//player_spr->SetPositionAbsalute(static_cast<int>(240 + nOffSet + xWorldOffset + xTransformOffset + xQuakeAttackModifier), static_cast<int>(159 + yWorldOffset + yTransformOffset + yQuakeAttackModifier));
		objectSprite->SetPositionAbsalute(position.left + (objectSprite->DesignWidth()/2), position.top + (objectSprite->DesignHeight()/2));
		if (!isDown)
		{
			if(m_oneSet)
				objectSprite->SetFrame(0);
			else
				objectSprite->SetFrameSet(0);
			objectSprite->Render();
		}
		else
		{
			if(m_oneSet)
				objectSprite->SetFrame(1);
			else
				objectSprite->SetFrameSet(1);
			objectSprite->Render();
		}
	}
}

void Input_Button::SetPosition(int x, int y)
{
	position.left = x;
	position.top = y;
	bounds.left = x;
	bounds.top = y;
}