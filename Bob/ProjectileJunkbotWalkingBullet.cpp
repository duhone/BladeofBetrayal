// ProjectileJunkbotWalkingBullet.cpp: implementation of the ProjectileJunkbotWalkingBullet class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileJunkbotWalkingBullet.h"
#include <math.h>
#include <stdlib.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileJunkbotWalkingBullet::ProjectileJunkbotWalkingBullet(bool bDirection, int xPos, int yPos, list<Projectile*> *projectile_list, int xVel, int yVel, float delay, float activetime)
{
	/* Set Sprite Number */
	SetSprite(1, CR::AssetList::Walking_junkbot_bullet);

	/* Set Sprite Direction */
	SetDirection(bDirection);

	/* Set Weapon Bounding Box */
	SetWeaponBounds(9,9);
	this->projectile_list = projectile_list;

	/* Set Activate & Delay Timer */
	SetActiveTime(activetime);
	SetDelayTime((float)delay);

	/* Set Velocity Direction */
	SetVelocityVector((float)xVel,(float) yVel);
	
	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(2);

	proj_flags.S_NON_PROJECTILE = true;

	/* Initialize Sprite */
	SetAnimation(0, 0, true, false, 5, true);
}

ProjectileJunkbotWalkingBullet::~ProjectileJunkbotWalkingBullet()
{
}

HPTRect &ProjectileJunkbotWalkingBullet::GetWeaponBounds()
{
	if(proj_params.timeDelay <= 0)
		SetRectangle(hptrectBounds, 8, 8, -4, -4);
	else
		SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileJunkbotWalkingBullet::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		proj_params.timeActive -= time;
	
		if(proj_params.timeActive <= 0)
		{
			DeActivate();
		}

		proj_params.xLoc += (proj_params.xVel * time);
		proj_params.yLoc += (proj_params.yVel * time);
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}