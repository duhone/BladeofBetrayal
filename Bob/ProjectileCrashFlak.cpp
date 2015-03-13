// ProjectileCrashFlak.cpp: implementation of the ProjectileCrashFlak class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileCrashFlak.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileCrashFlak::ProjectileCrashFlak(int xPos, int yPos, float xVel, float yVel, float tDelay)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::sentry_bullet);

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 0, true);

	/* Set Sprite Direction */

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(6);
	SetDelayTime(tDelay);

	/* Set Velocity Direction */
	SetVelocityVector(xVel, yVel);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(5);

	proj_flags.S_NON_PROJECTILE = true;
}

ProjectileCrashFlak::~ProjectileCrashFlak()
{
}

HPTRect &ProjectileCrashFlak::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileCrashFlak::Update()
{
//	proj_params.timeActive -= time;
	
//	if(proj_params.timeActive <= 0)
//		DeActivate();

//	proj_params.xLoc += (proj_params.xVel * time);
//	proj_params.yLoc += (proj_params.yVel * time);

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