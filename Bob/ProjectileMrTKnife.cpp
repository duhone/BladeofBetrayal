/*
 *  ProjectileMrTKnife.cpp
 *  BoB
 *
 *  Created by Eric Duhon on 3/1/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ProjectileMrTKnife.h"
#include <cmath>

ProjectileMrTKnife::ProjectileMrTKnife(bool _direction,int xPos, int yPos, bool _circle) :
	m_circle(_circle) , m_direction(_direction)
{
	SetSprite(1, CR::AssetList::MrT_knife);
	SetWeaponBounds(25,25);
	
	SetDirection(_direction);
	/* Set Activate & Delay Timer */
	SetActiveTime(10);
	
	SetDelayTime(0);
	
	proj_flags.S_NON_PROJECTILE = true;
	
	if(!_circle)
	{
		if(_direction) 
			SetVelocityVector(150, 0);
		else
			SetVelocityVector(-150, 0);	
		yPos -= 15;
	}
	else
	{	
		m_angle = 0;
		if(_direction) 
			m_center.x = xPos+c_radius;
		else 
			m_center.x = xPos-c_radius;
		m_center.y = yPos;
	}
		
	/* Set Start Position */
	SetPosition(xPos, yPos);
	
	/* Set Damage Value */
	SetWeaponDamage(3);	
	
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);
}

ProjectileMrTKnife::~ProjectileMrTKnife()
{
}

HPTRect &ProjectileMrTKnife::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);
	
	return hptrectBounds;
}

void ProjectileMrTKnife::Update()
{	
	if(!m_circle)
	{
		proj_params.timeActive -= time;
		
		if(proj_params.timeActive <= 0)
			DeActivate();
		
		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	}
	else
	{
		m_angle += 4.1f*time;
		if(m_angle > 3.14*2)
			DeActivate();

		proj_params.xLoc = cos(m_angle)*c_radius;
		if(m_direction)
			proj_params.xLoc *= -1;
		proj_params.xLoc += m_center.x;
		proj_params.yLoc = -sin(m_angle)*c_radius+m_center.y-5;
	}
}
