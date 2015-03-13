// ProjectileStephRifle.cpp: implementation of the ProjectileStephRifle class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "ProjectileStephRifle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileStephRifle::ProjectileStephRifle(int angle,float delay,float xveladd,float yveladd,IPlayer *player,int xoffset,int yoffset)
{
	SetSource(true);
	
	this->player = player;
	this->xoffset = xoffset;
	this->yoffset = yoffset;

	SetSprite(0, CR::AssetList::elite_rifle_bullet);


	
	/* Set Sprite Direction */
	//SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(delay);

	/* Set Velocity Direction */
	switch(angle)
	{
	case 0:
		SetVelocityVector(250+xveladd,0+yveladd);
		SetDirection(true);
		break;
	case 45:
		SetVelocityVector(177+xveladd,-177+yveladd);
		SetDirection(true);
		break;
	case 90:
		SetVelocityVector(0+xveladd,-250+yveladd);
		SetDirection(true);
		break;
	case 135:
		SetVelocityVector(-177+xveladd,-177+yveladd);
		SetDirection(false);
		break;
	case 180:
		SetVelocityVector(-250+xveladd,0+yveladd);
		SetDirection(false);
		break;
	};
	/* Set Start Position */
//	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(3);

	proj_flags.S_NON_PROJECTILE = true;

}

ProjectileStephRifle::~ProjectileStephRifle()
{

}

HPTRect &ProjectileStephRifle::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileStephRifle::Update()
{
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 0, true);
	
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
		if(proj_params.timeDelay <= 0) 
		{
			SetPosition(player->GetXLoc()+xoffset,player->GetYLoc()+yoffset);
	
		}		
//		if(proj_params.timeDelay <= 0) ;
		//soundPlayer->PlaySound(handgun02);
	}
}