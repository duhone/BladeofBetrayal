// ProjectileCrashBullet.cpp: implementation of the ProjectileCrashBullet class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileCrashBullet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileCrashBullet::ProjectileCrashBullet(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Crash_Bullet);
	
	/* Set Sprite Direction */
	SetDirection(bDirection);
	
	/* Set Weapon Bounding Box */
//	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(.50);

	/* Set Velocity Direction */
	if(bDirection) SetVelocityVector(150, 0);
	else SetVelocityVector(-150, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(5);	
	
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);
	projectile_spr->EnableFrameSkip(false);

	proj_flags.S_NON_PROJECTILE = true;
}

ProjectileCrashBullet::~ProjectileCrashBullet()
{
}

HPTRect &ProjectileCrashBullet::GetWeaponBounds()
{
	/* Set Weapon Bounding Rectangle */
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 2, -4, -1);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);
	
	return hptrectBounds;
}

void ProjectileCrashBullet::Update()
{


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
	}
}