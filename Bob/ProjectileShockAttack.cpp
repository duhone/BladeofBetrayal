// ProjectileShockAttack.cpp: implementation of the ProjectileShockAttack class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileShockAttack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileShockAttack::ProjectileShockAttack(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::Electric_Spike);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(48,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(.25f);
	//SetActiveTime(1);
	
//	SetDelayTime(.3f);
	SetDelayTime(.3f);

	/* Set Velocity Direction */
//	SetVelocityVector(20, 0);

	/* Set Velocity Direction */

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Source = PLAYER */
	SetSource(true);
	proj_flags.S_NON_PROJECTILE = true;

	/* Set Damage Value */
	SetWeaponDamage(6);

	weapon_type = 6;
}

ProjectileShockAttack::~ProjectileShockAttack()
{
}

HPTRect &ProjectileShockAttack::GetWeaponBounds()
{
	/* Check For Current Animation Frame */
	if(proj_params.timeDelay <= 0)
		switch(projectile_spr->GetFrame())
		{
		case 2:	
			SetRectangle(hptrectBounds, 64, 8, -36, -3);
			break;
		default:
			SetRectangle(hptrectBounds, 0, 0, 0, 0);
		}
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);



	return hptrectBounds;
}

void ProjectileShockAttack::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
	//	proj_params.xLoc += (proj_params.xVel * time);

		if(proj_params.timeActive <= 0)
			DeActivate();
	}
	else
	{
		proj_params.timeDelay -= time;

		if(proj_params.timeDelay < 0)
		{
			SetAnimation(0, 0, true, true, 22, true);
			projectile_spr->EnableFrameSkip(false);
		}
	}
}