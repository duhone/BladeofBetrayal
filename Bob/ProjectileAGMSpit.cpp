/*
 *  ProjectileAGMSpit.cpp
 *  BoB
 *
 *  Created by Eric Duhon on 2/28/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ProjectileAGMSpit.h"

const float ProjectileAGMSpit::c_xTime = 1.0f;

ProjectileAGMSpit::ProjectileAGMSpit(bool bDirection, int xPos, int yPos, std::list<Projectile*> &_projectile_list,int _playerX,bool _isSmall) :
	m_projectileList(_projectile_list), m_isSmall(_isSmall)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::agm_spit);
	
	/* Set Sprite Direction */
	SetDirection(bDirection);
	
	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);
	
	/* Set Activate & Delay Timer */
	SetActiveTime(8);
	SetDelayTime(0);
	
	m_xVel = (_playerX - xPos)/c_xTime;
	//-vt = 1/2 at^2
	//-v = (0.5at^2)/t
	//v = -0.5at;
	m_yVel = -0.5f*c_gravityConstant*c_xTime;
	
	/* Set Velocity Direction */
	SetVelocityVector(m_xVel, m_yVel);
	
	/* Set Start Position */
	SetPosition(xPos, yPos);
	
	/* Set Damage Value */
	SetWeaponDamage(10);	
	
	/* Initialize Sprite */
	SetAnimation(_isSmall?3:0, 0, true, false, 15, true);
	projectile_spr->EnableFrameSkip(false);
}

ProjectileAGMSpit::~ProjectileAGMSpit()
{
}

HPTRect &ProjectileAGMSpit::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);
	
	return hptrectBounds;
}

void ProjectileAGMSpit::Update()
{
	
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
		
		if(proj_params.timeActive <= 0)
			DeActivate();
		
		m_yVel += c_gravityConstant*time;
		SetVelocityVector(m_xVel, m_yVel);
		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}

void ProjectileAGMSpit::DeActivate()
{	
	if(!m_isSmall)
	{
		Projectile *temp;
		temp = new ProjectileAGMSpit(false, proj_params.xLoc, proj_params.yLoc-5,m_projectileList,proj_params.xLoc-30,true);
		temp->SetWeaponDamage(this->nAmtDmg);
		m_projectileList.push_back(temp);
		temp = new ProjectileAGMSpit(false, proj_params.xLoc, proj_params.yLoc-5,m_projectileList,proj_params.xLoc+30,true);
		temp->SetWeaponDamage(this->nAmtDmg);
		m_projectileList.push_back(temp);
	}
	Projectile::DeActivate();
}