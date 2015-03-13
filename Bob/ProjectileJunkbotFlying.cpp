// ProjectileJunkbotFlying.cpp: implementation of the ProjectileJunkbotFlying class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileJunkbotFlying.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileJunkbotFlying::ProjectileJunkbotFlying(int xPos, int yPos, float xVel, float yVel)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Flying_junkbot_bullet);

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 0, true);

	/* Set Sprite Direction */

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);

	/* Set Velocity Direction */
	SetVelocityVector(xVel, yVel);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(5);

	proj_flags.S_NON_PROJECTILE = true;
}

ProjectileJunkbotFlying::~ProjectileJunkbotFlying()
{
}

HPTRect &ProjectileJunkbotFlying::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileJunkbotFlying::Update()
{
	proj_params.timeActive -= time;
	
	if(proj_params.timeActive <= 0)
		DeActivate();

	proj_params.xLoc += (proj_params.xVel * time);
	proj_params.yLoc += (proj_params.yVel * time);
}