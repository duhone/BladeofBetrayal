// ProjectileNinjaStar.cpp: implementation of the ProjectileNinjaStar class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileNinjaStar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileNinjaStar::ProjectileNinjaStar(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::ninja_star);


	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(.25);

	/* Set Velocity Direction */
	if(bDirection) SetVelocityVector(80, 0);
	else SetVelocityVector(-80, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(2);	
	
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 30, true);
	projectile_spr->EnableFrameSkip(false);
}

ProjectileNinjaStar::~ProjectileNinjaStar()
{
}

HPTRect &ProjectileNinjaStar::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileNinjaStar::Update()
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