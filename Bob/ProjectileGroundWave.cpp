// ProjectileGroundWave.cpp: implementation of the ProjectileGroundWave class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileGroundWave.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileGroundWave::ProjectileGroundWave(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Gawain_wave_attack);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(32,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	//SetDelayTime(.55f);

	/* Set Velocity Direction */
	if(bDirection) SetVelocityVector(200, 0);
	else SetVelocityVector(-200, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(8);	
	
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 10, true);
	projectile_spr->EnableFrameSkip(false);
}

ProjectileGroundWave::~ProjectileGroundWave()
{
}

HPTRect &ProjectileGroundWave::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 16, 8, -8, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);


	
	return hptrectBounds;
}

void ProjectileGroundWave::Update()
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