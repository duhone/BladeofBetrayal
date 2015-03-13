/*
 *  ProjectileAgmBone.h
 *  BoB
 *
 *  Created by Eric Duhon on 2/25/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "Projectile.h"

class ProjectileAgmBone : public Projectile  
	{
	public:
		ProjectileAgmBone(bool bDirection, int xPos, int yPos,bool _vertical = false);
		virtual ~ProjectileAgmBone();
		
		HPTRect &GetWeaponBounds();
		
		virtual void Update();
	};
