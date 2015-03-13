// ProjectilePrisonerRock.cpp: implementation of the ProjectilePrisonerRock class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectilePrisonerRock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectilePrisonerRock::ProjectilePrisonerRock(bool bDirection, int xPos, int yPos)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::prisoner_rock);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(12,12);

	/* Set Activate & Delay Timer */
	SetActiveTime(3);
	SetDelayTime(.25);

	/* Set Velocity Direction */	
	if(bDirection) SetVelocityVector((float)(rand()%50+75), 0);
	else SetVelocityVector((float)(-(rand()%50+75)), 0);

	/* Set Acceleration Vector */
	SetAccelerationVector(0, (float)(rand()%75 + 65));
	
	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(5);

	proj_flags.S_NON_PROJECTILE = true;

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 10, true);
}

ProjectilePrisonerRock::~ProjectilePrisonerRock()
{
}

HPTRect &ProjectilePrisonerRock::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 12, 12, -6, -6);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);


	
	return hptrectBounds;
}

void ProjectilePrisonerRock::Update()
{	
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
		if(proj_params.timeActive <= 0)
			DeActivate();

		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	
		if(proj_params.xVel < proj_params.MaxXVel) proj_params.xVel+=proj_params.xAcc*time;
		if(proj_params.yVel < proj_params.MaxYVel) proj_params.yVel+=proj_params.yAcc*time;
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}