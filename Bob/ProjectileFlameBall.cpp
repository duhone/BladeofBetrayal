// ProjectileFlameBall.cpp: implementation of the ProjectileFlameBall class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileFlameBall.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileFlameBall::ProjectileFlameBall(bool bDirection, int xPos, int yPos, int xVel, int yVel, int frameset, float sDelay)
{
	/* Set Sprite Number */
	SetSprite(0, CR::AssetList::Flame_Attack);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(24,24);

	/* Set Activate & Delay Timer */
//	SetActiveTime(2);
	SetDelayTime(sDelay);

	/* Set Velocity Direction */
	SetVelocityVector(static_cast<float>(xVel), static_cast<float>(yVel));

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(6);
	
	SetSource(true);
	proj_flags.S_NON_PROJECTILE = true;

	/* Initialize Sprite */
	this->frameset = frameset;
//	projectile_spr->EnableFrameSkip(false);

	weapon_type = 7;
}

ProjectileFlameBall::~ProjectileFlameBall()
{
}

HPTRect &ProjectileFlameBall::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 12, 12, -6, -6);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);


	
	return hptrectBounds;
}

void ProjectileFlameBall::Update()
{
	if(proj_params.timeDelay <= 0)
	{


		if(!projectile_spr->IsAnimating())
			DeActivate();

		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	}
	else
	{
		proj_params.timeDelay -= time;
		
		if(proj_params.timeDelay <= 0)
			SetAnimation(frameset, 0, true, true, 10, true);
	}
}