// ProjectileQuakeAttackRock.cpp: implementation of the ProjectileQuakeAttackRock class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileQuakeAttackRock.h"
#include <math.h>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileQuakeAttackRock::ProjectileQuakeAttackRock(int xPos, int yPos, float xVel, float yVel, float xAcc, float yAcc)
{
	/* Set Sprite Number */
	//SetSprite(0, CR::AssetList::Rock);
	SetSprite(0, CR::AssetList::Jacob_Stone);


	/* Set Sprite Direction */

	/* Set Weapon Bounding Box */
//	SetWeaponBounds(16,16);

	/* Set Activate & Delay Timer */
	SetActiveTime(rand()%200 * .01f + 2);
//	SetDelayTime(1);

	/* Set Velocity Direction */
	SetVelocityVector(xVel, yVel);
	SetAccelerationVector(xAcc, yAcc);

	/* Set Start Position */
	SetPosition(xPos, yPos);

	/* Set Damage Value */
	SetWeaponDamage(8);

	SetSource(true);
	proj_flags.S_NON_PROJECTILE = true;

	SetAnimation(0, 0, true, false, (float)(rand()%10 + 5), true);

	weapon_type = 10;
}

ProjectileQuakeAttackRock::~ProjectileQuakeAttackRock()
{

}


HPTRect &ProjectileQuakeAttackRock::GetWeaponBounds()
{
	//SetRectangle(hptrectBounds, 8, 8, -4, -4);
	SetRectangle(hptrectBounds, 16, 16, -8, -8);
	return hptrectBounds;
}

void ProjectileQuakeAttackRock::Update()
{
	/* Initialize Sprite */
//	projectile_spr->SetFrame(0);


	proj_params.timeActive -= time;
	
	if(proj_params.timeActive <= 0)
		DeActivate();

	proj_params.xLoc += (proj_params.xVel * time);
	proj_params.yLoc += (proj_params.yVel * time);

	proj_params.xVel+=proj_params.xAcc*time;
	proj_params.yVel+=proj_params.yAcc*time;
}