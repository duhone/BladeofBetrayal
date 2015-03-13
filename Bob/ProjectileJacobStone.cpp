// ProjectileJacobStone.cpp: implementation of the ProjectileJacobStone class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileJacobStone.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileJacobStone::ProjectileJacobStone(bool sDirection, int xPos, int yPos, float xVel, float yVel, float xAcc, float yAcc, float tDelay)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Jacob_Stone);

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 10, true);

	/* Set Sprite Direction */

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(6);
	SetDelayTime(tDelay);

	/* Set Velocity Direction */
	SetVelocityVector(xVel, yVel);
	SetAccelerationVector(xAcc, yAcc);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(6);

	proj_flags.S_DIRECTION = sDirection;
	proj_flags.S_NON_PROJECTILE = true;
}

ProjectileJacobStone::~ProjectileJacobStone()
{
}

HPTRect &ProjectileJacobStone::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 16, 16, -8, -8);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileJacobStone::Update()
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