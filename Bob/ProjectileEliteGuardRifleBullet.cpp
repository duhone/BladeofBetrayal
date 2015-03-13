// ProjectileEliteGuardRifleBullet.cpp: implementation of the ProjectileEliteGuardRifleBullet class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileEliteGuardRifleBullet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ProjectileEliteGuardRifleBullet::ProjectileEliteGuardRifleBullet()
{

}

ProjectileEliteGuardRifleBullet::ProjectileEliteGuardRifleBullet(bool bDirection, int xPos, int yPos, float delay)
{
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::elite_rifle_bullet);


	
	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(delay);

	/* Set Velocity Direction */
	if(bDirection) SetVelocityVector(120, 0);
	else SetVelocityVector(-120, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(6);

	proj_flags.S_NON_PROJECTILE = true;
}

ProjectileEliteGuardRifleBullet::~ProjectileEliteGuardRifleBullet()
{
}

HPTRect &ProjectileEliteGuardRifleBullet::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileEliteGuardRifleBullet::Update()
{
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 0, true);
	
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

		//soundPlayer->PlaySound(handgun02);
	}
}