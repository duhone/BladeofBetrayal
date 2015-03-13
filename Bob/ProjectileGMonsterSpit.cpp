// ProjectileGMonsterSpit.cpp: implementation of the ProjectileGMonsterSpit class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileGMonsterSpit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileGMonsterSpit::ProjectileGMonsterSpit(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Green_Crate);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(.25);

	/* Set Velocity Direction */
	if(bDirection) SetVelocityVector(100, 0);
	else SetVelocityVector(-100, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(20);	
	
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);
	projectile_spr->EnableFrameSkip(false);
}

ProjectileGMonsterSpit::~ProjectileGMonsterSpit()
{
}

HPTRect &ProjectileGMonsterSpit::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileGMonsterSpit::Update()
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