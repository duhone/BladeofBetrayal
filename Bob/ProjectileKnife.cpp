// ProjectileKnife.cpp: implementation of the ProjectileKnife class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileKnife.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileKnife::ProjectileKnife(bool sDirection, int xPos, int yPos, float xVel, float yVel, float xAcc, float yAcc)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Knife);

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 22, true);

	/* Set Sprite Direction */

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(2);
	SetDelayTime(.25);

	/* Set Velocity Direction */
	SetVelocityVector(xVel, yVel);
	SetAccelerationVector(xAcc, yAcc);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(10);

	proj_flags.S_DIRECTION = sDirection;
	proj_flags.S_NON_PROJECTILE = true;
}

ProjectileKnife::~ProjectileKnife()
{
}

HPTRect &ProjectileKnife::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileKnife::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
		if(proj_params.timeActive <= 0)
			DeActivate();

		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);

		proj_params.xVel+=proj_params.xAcc*time;
		proj_params.yVel+=proj_params.yAcc*time;
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}