// ProjectileSentryBullet.cpp: implementation of the ProjectileSentryBullet class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileSentryBullet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileSentryBullet::ProjectileSentryBullet(int xPos, int yPos, float xVel, float yVel)
{
	/* Set Sprite Number */
	SetSprite(0,CR::AssetList::sentry_bullet);

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 0, true);

	/* Set Sprite Direction */

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(6);

	/* Set Velocity Direction */
	SetVelocityVector(xVel, yVel);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(3);

	proj_flags.S_NON_PROJECTILE = false;
}

ProjectileSentryBullet::~ProjectileSentryBullet()
{
}

HPTRect &ProjectileSentryBullet::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileSentryBullet::Update()
{
	proj_params.timeActive -= time;
	
	if(proj_params.timeActive <= 0)
		DeActivate();

	proj_params.xLoc += (proj_params.xVel * time);
	proj_params.yLoc += (proj_params.yVel * time);
}