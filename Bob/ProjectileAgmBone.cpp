/*
 *  ProjectileAgmBone.cpp
 *  BoB
 *
 *  Created by Eric Duhon on 2/25/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ProjectileAgmBone.h"

ProjectileAgmBone::ProjectileAgmBone(bool bDirection, int xPos, int yPos,bool _vertical)
{
	/* Set Sprite Number */
	if(_vertical)
		SetSprite(1, CR::AssetList::agm_bone_shard_down);
	else
		SetSprite(1, CR::AssetList::AGM_Bone_Shard);
	
	/* Set Sprite Direction */
	SetDirection(bDirection);
	
	/* Set Weapon Bounding Box */
	if(_vertical)
		SetWeaponBounds(16,25);
	else
		SetWeaponBounds(25,16);
	
	/* Set Activate & Delay Timer */
	SetActiveTime(10);
	if(!_vertical)
		SetDelayTime(.25);
	else
		SetDelayTime(0);
	
	/* Set Velocity Direction */
	if(_vertical)
	{
		proj_flags.S_NON_PROJECTILE = true;
		if(bDirection) SetVelocityVector(0, 300);
		else
		{
			SetVelocityVector(0, -300);
			m_vflip = true;
		}
	}
	else
	{
		if(bDirection) SetVelocityVector(300, 0);
		else
			SetVelocityVector(-300, 0);
	}
	
	/* Set Start Position */
	SetPosition(xPos, yPos);
	
	/* Set Damage Value */
	SetWeaponDamage(5);	
	
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);
	projectile_spr->EnableFrameSkip(false);
}

ProjectileAgmBone::~ProjectileAgmBone()
{
}

HPTRect &ProjectileAgmBone::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);
	
	return hptrectBounds;
}

void ProjectileAgmBone::Update()
{
	
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
		
		if(proj_params.timeActive <= 0)
			DeActivate();
		
		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}