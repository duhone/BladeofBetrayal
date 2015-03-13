// ProjectileJacobShock.cpp: implementation of the ProjectileJacobShock class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileJacobShock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileJacobShock::ProjectileJacobShock(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Jacob_Spike);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(48,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(.25);
	SetDelayTime(.6f);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	proj_flags.S_NON_PROJECTILE = true;

	/* Set Damage Value */
	SetWeaponDamage(10);
}

ProjectileJacobShock::~ProjectileJacobShock()
{
}

HPTRect &ProjectileJacobShock::GetWeaponBounds()
{
	/* Check For Current Animation Frame */
	if(proj_params.timeDelay <= 0)
		switch(projectile_spr->GetFrame())
		{
		case 2:	
			SetRectangle(hptrectBounds, 84, 8, -42, -4);
			break;
		default:
			SetRectangle(hptrectBounds, 0, 0, 0, 0);
		}
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);



	return hptrectBounds;
}

void ProjectileJacobShock::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
		if(proj_params.timeActive <= 0)
				DeActivate();
	}
	else
	{
		proj_params.timeDelay -= time;

		if(proj_params.timeDelay <= 0)
		{
			SetAnimation(0, 0, true, true, 15, true);
			projectile_spr->EnableFrameSkip(false);
		}
	}
}