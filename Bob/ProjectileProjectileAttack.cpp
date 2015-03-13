// ProjectileProjectileAttack.cpp: implementation of the ProjectileProjectileAttack class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileProjectileAttack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileProjectileAttack::ProjectileProjectileAttack(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::Spencer_Projectile_Attack);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(60,60);

	/* Set Activate & Delay Timer */
	SetActiveTime(2.25);
	SetDelayTime(.5);

	/* Set Velocity Direction */
	if(bDirection) SetVelocityVector(150, 0);
	else SetVelocityVector(-150, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(9);

	SetSource(true);
	proj_flags.S_NON_PROJECTILE = true;

	weapon_type = 9;
}

ProjectileProjectileAttack::~ProjectileProjectileAttack()
{
}

HPTRect &ProjectileProjectileAttack::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 60, 60, -30, -30);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileProjectileAttack::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		if((projectile_spr->GetFrameSet() == 1) && !projectile_spr->IsAnimating())
			SetAnimation(0, 0, true, false, 15, true);
		
		proj_params.timeActive -= time;
	
		if(proj_params.timeActive <= 0)
			DeActivate();

		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	}
	else
	{
		proj_params.timeDelay -= time;

		if(proj_params.timeDelay <= 0)
			SetAnimation(1, 0, true, true, 10, false);
	}
}