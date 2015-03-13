// ProjectileJacobFlame.cpp: implementation of the ProjectileJacobFlame class.
//
//////////////////////////////////////////////////////////////////////


#include "ProjectileJacobFlame.h"

using namespace std;

extern void NEW(void *arg);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ProjectileJacobFlame::ProjectileJacobFlame(bool bDirection, int xPos, int yPos, list<Projectile*> *projectile_list)
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
	SetWeaponDamage(12);

	this->projectile_list = projectile_list;

	/* Initialize Sprite */
//	SetAnimation(0, 0, true, true, 5, true);
//	SetAnimation(0, 0, true, true, .2, true);
//	projectile_spr->EnableFrameSkip(false);
}

ProjectileJacobFlame::~ProjectileJacobFlame()
{

}

HPTRect &ProjectileJacobFlame::GetWeaponBounds()
{
	/* Check For Current Animation Frame */
/*	switch(projectile_spr->GetFrame())
	{
	case 0:
//		if(proj_flags.S_DIRECTION)
			SetRectangle(hptrectBounds, 40, 14, -30, -5);
//		else
//			SetRectangle(hptrectBounds, 40, 16, -18, -8);
		break;
	case 1:
//		if(proj_flags.S_DIRECTION)
			SetRectangle(hptrectBounds, 60, 22, -40, -9);
//		else
//			SetRectangle(hptrectBounds, 60, 22, -9, -15);
		break;
	case 2:	
//		if(proj_flags.S_DIRECTION)
			SetRectangle(hptrectBounds, 70, 25, -45, -20);
//		else
//			SetRectangle(hptrectBounds, 80, 30, -15, -20);
		break;
	case 3:	
//		if(proj_flags.S_DIRECTION)
			SetRectangle(hptrectBounds, 70, 20, -45, -20);
//		else
//			SetRectangle(hptrectBounds, 75, 25, -15, -20);
		break;
	case 4:	
//		if(proj_flags.S_DIRECTION)
			SetRectangle(hptrectBounds, 70, 20, -45, -20);
//		else
//			SetRectangle(hptrectBounds, 70, 25, -15, -20);
		break;
	}*/

	SetRectangle(hptrectBounds, 0, 0, 0, 0);

	return hptrectBounds;
}

void ProjectileJacobFlame::Update()
{
	if(proj_params.timeDelay <= 0)
	{
		//Spawn Flame Projectiles;
		Projectile *temp;
		
		if(proj_flags.S_DIRECTION)
		{
			temp = new ProjectileJacobFlameBall(true, static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc - 50), 0, -75, 0, .55f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileJacobFlameBall(false, static_cast<int>(proj_params.xLoc + 15), static_cast<int>(proj_params.yLoc - 53), 25, -50, 4, .50f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileJacobFlameBall(false, static_cast<int>(proj_params.xLoc + 30), static_cast<int>(proj_params.yLoc - 35), 50, -50, 1, .4f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileJacobFlameBall(false, static_cast<int>(proj_params.xLoc + 45), static_cast<int>(proj_params.yLoc - 10), 50, -25, 3, .3f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileJacobFlameBall(false, static_cast<int>(proj_params.xLoc + 40), static_cast<int>(proj_params.yLoc + 15), 50, 0, 2, .1f);
			
			(*projectile_list).push_back(temp);
		}
		else
		{
			temp = new ProjectileJacobFlameBall(false, static_cast<int>(proj_params.xLoc), static_cast<int>(proj_params.yLoc - 50), 0, -75, 0, .55f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileJacobFlameBall(true, static_cast<int>(proj_params.xLoc - 15), static_cast<int>(proj_params.yLoc - 53), -25, -50, 4, .50f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileJacobFlameBall(true, static_cast<int>(proj_params.xLoc - 30), static_cast<int>(proj_params.yLoc - 35), -50, -50, 1, .4f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileJacobFlameBall(true, static_cast<int>(proj_params.xLoc - 45), static_cast<int>(proj_params.yLoc - 10), -50, -25, 3, .3f);
			
			(*projectile_list).push_back(temp);
			temp = new ProjectileJacobFlameBall(true, static_cast<int>(proj_params.xLoc - 40), static_cast<int>(proj_params.yLoc + 15), -50, 0, 2, .1f);
			
			(*projectile_list).push_back(temp);
		}

		DeActivate();
	}
	else
	{
		proj_params.timeDelay -= time;
	}
}

