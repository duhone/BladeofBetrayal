/*
 *  ProjectileMrTKnife.h
 *  BoB
 *
 *  Created by Eric Duhon on 3/1/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "Projectile.h"
#include "point.h"

class ProjectileMrTKnife : public Projectile
	{
	public:
		ProjectileMrTKnife(bool _direction,int xPos, int yPos, bool _circle);
		virtual ~ProjectileMrTKnife();		
		
		HPTRect &GetWeaponBounds();
		
		virtual void Update();
	private:
		bool m_circle;
		float m_angle;
		static const int c_radius = 42;
		HPTPoint m_center;
		bool m_direction;
	};


