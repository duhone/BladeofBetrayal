// ProjectileEliteGuardPistolBullet.cpp: implementation of the ProjectileEliteGuardPistolBullet class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileEliteGuardPistolBullet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileEliteGuardPistolBullet::ProjectileEliteGuardPistolBullet()
{

}

ProjectileEliteGuardPistolBullet::ProjectileEliteGuardPistolBullet(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::elite_pistol_bullet);
	

	/* Set Sprite Direction */
	SetDirection(bDirection);
	
	/* Set Weapon Bounding Box */
	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(.15f);

	/* Set Velocity Direction */
	if(bDirection) SetVelocityVector(150, 0);
	else SetVelocityVector(-150, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(5);
}

ProjectileEliteGuardPistolBullet::~ProjectileEliteGuardPistolBullet()
{
}

HPTRect &ProjectileEliteGuardPistolBullet::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileEliteGuardPistolBullet::Update()
{
	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);

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

		if(proj_params.timeDelay <= 0) ;

		//soundPlayer->PlaySound(handgun01);
	}
}