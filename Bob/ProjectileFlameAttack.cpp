// ProjectileFlameAttack.cpp: implementation of the ProjectileFlameAttack class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileFlameAttack.h"

using namespace std;

extern void NEW(void *arg);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectileFlameAttack::ProjectileFlameAttack(bool bDirection, int xPos, int yPos, list<Projectile*> *projectile_list)
{
	/* Set Sprite Number */
//	SetSprite(0, CR::AssetList::Flame_Attack);
	
	/* Set Sprite Direction */
	SetDirection(bDirection);
	
	/* Set Weapon Bounding Box */
//	SetWeaponBounds(125,50);
	
	/* Set Activate & Delay Timer */
	SetActiveTime(.3f);
	SetDelayTime(.4f);

	/* Set Velocity Direction */

	/* Set Start Position */
	SetPosition(xPos, yPos);

	SetSource(true);
	proj_flags.S_NON_PROJECTILE = true;

	/* Set Damage Value */
	SetWeaponDamage(6);

	this->projectile_list = projectile_list;

	weapon_type = 7;
	/* Initialize Sprite */
//	SetAnimation(0, 0, true, true, 5, true);
//	SetAnimation(0, 0, true, true, .2, true);
//	projectile_spr->EnableFrameSkip(false);
}

ProjectileFlameAttack::~ProjectileFlameAttack()
{

}

HPTRect &ProjectileFlameAttack::GetWeaponBounds()
{
	SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileFlameAttack::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		//Spawn Flame Projectiles;
		Projectile *temp;
		
		if(proj_flags.S_DIRECTION)
		{
			temp = new ProjectileFlameBall(false, static_cast<int>(proj_params.xLoc + 30), static_cast<int>(proj_params.yLoc + 8), 50, 0, 2, .05f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileFlameBall(false, static_cast<int>(proj_params.xLoc + 30), static_cast<int>(proj_params.yLoc - 20), 50, -50, 1, .075);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileFlameBall(false, static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc - 35), 0, -50, 0, .1f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileFlameBall(true, static_cast<int>(proj_params.xLoc - 30), static_cast<int>(proj_params.yLoc - 20), -50, -50, 1, .125f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileFlameBall(true, static_cast<int>(proj_params.xLoc - 30), static_cast<int>(proj_params.yLoc + 8), -50, 0, 2, .15f);
			
			(*projectile_list).push_back(temp);
		}
		else
		{
			temp = new ProjectileFlameBall(false, static_cast<int>(proj_params.xLoc + 30), static_cast<int>(proj_params.yLoc + 8), 50, 0, 2, .15f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileFlameBall(false, static_cast<int>(proj_params.xLoc + 30), static_cast<int>(proj_params.yLoc - 20), 50, -50, 1, .125f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileFlameBall(false, static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc - 35), 0, -50, 0, .1f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileFlameBall(true, static_cast<int>(proj_params.xLoc - 30), static_cast<int>(proj_params.yLoc - 20), -50, -50, 1, .075f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileFlameBall(true, static_cast<int>(proj_params.xLoc - 30), static_cast<int>(proj_params.yLoc + 8), -50, 0, 2, .05f);
			
			(*projectile_list).push_back(temp);
		}

		DeActivate();
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}

