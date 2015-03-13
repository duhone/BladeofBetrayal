// ProjectileStephPistol.cpp: implementation of the ProjectileStephPistol class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "ProjectileStephPistol.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



ProjectileStephPistol::~ProjectileStephPistol()
{

}


ProjectileStephPistol::ProjectileStephPistol(int angle, int xPos, int yPos,float xveladd,float yveladd,IPlayer *player,int xoffset,int yoffset)
{
	SetSource(true);
	
	this->player = player;
	this->xoffset = xoffset;
	this->yoffset = yoffset;
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::elite_pistol_bullet);
	

	/* Set Sprite Direction */
	//SetDirection(bDirection);
	
	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(.15f);

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
	//if(bDirection) SetVelocityVector(150, 0);
	//else SetVelocityVector(-150, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(2);
}
void ProjectileStephPistol::Update()
{
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);

	/* Process Display Delay Timer */
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
		/* Process Activation Timer */
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
		//soundPlayer->PlaySound(handgun01);
	}
}

/*HPTRect &ProjectileStephPistol::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}*/
/*
void ProjectileStephPistol::Update()
{
	SetAnimation(0, 0, true, false, 15, true);

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

		if(proj_params.timeDelay <= 0) ;
//				sound_processor->PlaySound(game_sounds->handgun01, true);
	}
}*/