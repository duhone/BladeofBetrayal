// ProjectileCrashExplosion.cpp: implementation of the ProjectileCrashExplosion class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileCrashExplosion.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileCrashExplosion::ProjectileCrashExplosion(int xPos, int yPos, float tDelay)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Crash_Explosion);

	/* Set Activate & Delay Timer */
	SetDelayTime(tDelay);

	/* Set Velocity Direction */
	SetVelocityVector(0, 0);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(5);	

	proj_flags.S_NON_PROJECTILE = true;

	//soundPlayer->PlaySound(explode01);

}

ProjectileCrashExplosion::~ProjectileCrashExplosion()
{
}

HPTRect &ProjectileCrashExplosion::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 16, 16, -8, -8);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileCrashExplosion::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		if(!projectile_spr->IsAnimating())
			DeActivate();
	}
	else
	{
		proj_params.timeDelay -= time;

		if(proj_params.timeDelay < 0)
			SetAnimation(0, 0, true, true, 8, true);
	}
}