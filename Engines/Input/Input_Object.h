/*
 *  Input_Object.h
 *  Input
 *
 *  Created by Robert Shoemate on 1/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "../graphics/HPTGraphics.h"
#include <vector>
//#include "CRSoundPlayer.h"
#include "Sound.h"

//extern CRSoundPlayer *soundPlayer;

struct Rect
{
	int top,bottom,left,right;
};

struct Touch
{
	Touch() : X(0),Y(0),Active(false),ID(-1) {}
	Touch(int _id) : X(0),Y(0),Active(false),ID(_id) {}
    int X; // position x
    int Y; // position y
    bool Active; // is touch active (currently down)
    int ID; // touch's unique identifier
};

class Input_Object
	{
	public:	
		Input_Object() : m_disabled(false)
		{
			
		}
		
		virtual ~Input_Object()
		{
		}
		
		void TouchesBegan(Touch &_touches)
		{
			if(!m_disabled)
				TouchesBeganImpl(_touches);
		}
		void TouchesMoved(Touch &_touches)
		{
			if(!m_disabled)
				TouchesMovedImpl(_touches);			
		}
		void TouchesEnded(Touch &_touches)
		{
			if(!m_disabled)
				TouchesEndedImpl(_touches);			
		}
		bool Disabled() const {return m_disabled;}
		void Disabled(bool _disabled) 
		{
			if(!_disabled && m_disabled)
				Reset();
			m_disabled = _disabled;
		}
		
		virtual void TouchesBeganImpl(Touch &_touches) = 0;
		virtual void TouchesMovedImpl(Touch &_touches) = 0;
		virtual void TouchesEndedImpl(Touch &_touches) = 0;
		virtual void Reset() = 0;
		
		//CGPoint GetGLLocation(Touch &touch);

		//void SetSprite(int nSprite);
		virtual void Update(float time){}
		virtual void Render() = 0;
		virtual void FreeResources() = 0;
	protected:
		bool m_disabled;
		std::tr1::shared_ptr<CR::Sound::ISoundFX> m_soundFX;
	};