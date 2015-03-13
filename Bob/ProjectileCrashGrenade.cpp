// ProjectileCrashGrenade.cpp: implementation of the ProjectileCrashGrenade class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileCrashGrenade.h"
#include "ProjectileCrashFlak.h"

using namespace std;

extern void NEW(void *arg);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileCrashGrenade::ProjectileCrashGrenade(bool bDirection, int xPos, int yPos,list<Projectile*> *projectile_list, bool TYPE)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Crash_grenade_1);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Activate & Delay Timer */
	SetActiveTime(2);
	SetDelayTime(.45f);

	proj_flags.S_DIRECTION = bDirection;

	/* Set Velocity Direction */
	if(!TYPE)
	{
		if(bDirection) SetVelocityVector(70, -80);
		else SetVelocityVector(-70, -80);
	}
	else
	{
		if(bDirection) SetVelocityVector(140, -160);
		else SetVelocityVector(-140, -160);
	}

	/* Set Acceleration Vector */
	SetAccelerationVector(0, 200);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	SetSource(true);

	/* Set Damage Value */
	SetWeaponDamage(10);

	this->projectile_list = projectile_list;

	IS_EXPLODING = false;
	this->TYPE = TYPE;

	SetSource(false);

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 15, true);
}

ProjectileCrashGrenade::~ProjectileCrashGrenade()
{
}

void ProjectileCrashGrenade::DeActivate()
{
	if(!TYPE && !IS_EXPLODING)
	{
		//soundPlayer->PlaySound(explode01);

		/* Set Sprite Number */
		SetSprite(1, CR::AssetList::Item_Chest);

		/* Initialize Sprite */
		SetAnimation(0, 0, true, true, 12, true);

		SetVelocityVector(0, 0);

		/* Set Acceleration Vector */
		SetAccelerationVector(0, 0);
	
		IS_EXPLODING = true;
	}
}

HPTRect &ProjectileCrashGrenade::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		if(!IS_EXPLODING)
			SetRectangle(hptrectBounds, 8, 8, -4, -4);
		else
			SetRectangle(hptrectBounds, 24, 24, -12, -12);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileCrashGrenade::Explode()
{	
	//soundPlayer->PlaySound(explode01);

	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Crash_Explosion);

	/* Initialize Sprite */
	SetAnimation(0, 0, true, true, 12, true);

	SetVelocityVector(0, 0);

	/* Set Acceleration Vector */
	SetAccelerationVector(0, 0);

	Projectile *temp;

	temp = new ProjectileCrashFlak(static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc), -45, 45);
	
	(*projectile_list).push_back(temp);
		
	temp = new ProjectileCrashFlak(static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc), 0, 45);
	
	(*projectile_list).push_back(temp);

	temp = new ProjectileCrashFlak(static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc), 45, 45);
	
	(*projectile_list).push_back(temp);

	IS_EXPLODING = true;
}

void ProjectileCrashGrenade::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		if((proj_params.yVel > 0) && !IS_EXPLODING && TYPE)
			Explode();
		else if(IS_EXPLODING)
			if(!projectile_spr->IsAnimating())
				proj_flags.S_ACTIVE = false;

		proj_params.timeActive -= time;

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