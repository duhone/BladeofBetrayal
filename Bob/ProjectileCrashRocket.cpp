// ProjectileCrashRocket.cpp: implementation of the ProjectileCrashRocket class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileCrashRocket.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileCrashRocket::ProjectileCrashRocket(bool bDirection, int xPos, int yPos, list<Projectile*> *projectile_list)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Crash_basic_rocket);
	
	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Activate & Delay Timer */
	SetActiveTime(4);
	SetDelayTime(.50);

	/* Set Velocity Direction */
	if(bDirection) 
	{
		SetAccelerationVector(300, 0);
		SetVelocityVector(10, 0);
	}
	else
	{
		SetAccelerationVector(-300, 0);
		SetVelocityVector(-10, 0);
	}

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(10);	
	
	this->projectile_list = projectile_list;

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);
	projectile_spr->EnableFrameSkip(false);
}

ProjectileCrashRocket::~ProjectileCrashRocket()
{
}

HPTRect &ProjectileCrashRocket::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 2, -4, -1);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileCrashRocket::DeActivate()
{
	//Projectile *temp;
	//temp = new ProjectileCrashExplosion(static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc), 0);
	//(*projectile_list).push_back(temp);

	proj_flags.S_ACTIVE = false;
}

void ProjectileCrashRocket::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
		/* Process Activation Timer */
		if(proj_params.timeActive <= 0)
		{
			DeActivate();
		}

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