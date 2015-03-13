// EnemyTowerBot.cpp: implementation of the EnemyTowerBot class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyTowerBot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyTowerBot::EnemyTowerBot(Level *curLevel)
{
	SetRenderOffset(5);	
	ipFlags.S_ATTACK = true;

	level_class = curLevel;
}

EnemyTowerBot::~EnemyTowerBot()
{

}

/*HPTRect &EnemyTowerBot::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyTowerBot::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_TOWER_BOT_ANIM_UP) ||
	   (player_spr->GetFrameSet() == ENEMY_TOWER_BOT_ANIM_MOVE_UP))
	{
		rectWeaponWorldLoc.p1.x = static_cast<int>(xLoc - 9 - nOffSet);
		rectWeaponWorldLoc.p2.x = static_cast<int>(xLoc - 5 + nOffSet);
		rectWeaponWorldLoc.p1.y = static_cast<int>(yLoc - 15);
		rectWeaponWorldLoc.p2.y = static_cast<int>(yLoc + 30);
	}
	else if((player_spr->GetFrameSet() == ENEMY_TOWER_BOT_ANIM_DOWN) ||
       	    (player_spr->GetFrameSet() == ENEMY_TOWER_BOT_ANIM_MOVE_DOWN))
	{
		rectWeaponWorldLoc.p1.x = static_cast<int>(xLoc - 9 - nOffSet);
		rectWeaponWorldLoc.p2.x = static_cast<int>(xLoc - 5 + nOffSet);
		rectWeaponWorldLoc.p1.y = static_cast<int>(yLoc + 21);
		rectWeaponWorldLoc.p2.y = static_cast<int>(yLoc + 30);
	}

	return rectWeaponWorldLoc;
}

void EnemyTowerBot::processAttack()
{
	if(player_spr->GetFrameSet() == ENEMY_TOWER_BOT_ANIM_UP)
	{
/*		Projectile *temp;
		temp = new Projectile();
		temp->SetProjectileType(PROJ_TOWER_BOT_BULLET);
		temp->SetPos(static_cast<int>(xLoc - 15), static_cast<int>(yLoc));
//		temp->SetTargetLocation(
		(*projectile_list).push_back(temp);*/
	}
}

void EnemyTowerBot::processDown()
{
	SetAnimation(ENEMY_TOWER_BOT_ANIM_MOVE_DOWN, 0, true, false, 15, false);
}

void EnemyTowerBot::processUp()
{
	SetAnimation(ENEMY_TOWER_BOT_ANIM_MOVE_UP, 0, true, false, 15, false);
}

void EnemyTowerBot::processDeath()
{
	SetAnimation(ENEMY_TOWER_BOT_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyTowerBot::processDamage()
{
	ipFlags.S_ATTACK = false;

	SetAnimation(ENEMY_TOWER_BOT_ANIM_MOVE_DOWN, 0, true, false, 15, false);
}

void EnemyTowerBot::processUpdate()
{
//	BelowFeetLadderCheck();

	if(!ipFlags.S_DEAD)
	{
		if(ipFlags.S_ON_GROUND)
		{
			velModifier = 0;
			velYModifier = 0;
		}
		else
		{
			velYModifier += (gravityConstant * time);
		}

	//Transition Movement State
//	TransitionMovement(ipFlags.CurMState);

	// Apply Velocity Modifier
	if(!ipFlags.S_DAMAGED)
	{
		switch(ipFlags.CurMState)
		{
			case move_up:
				processUp();
				break;
			case move_right:
				processDown();
				break;
			default:
				break;
		}
	}

//	ProcessCalculations();
	}

	rectWorldLoc.p1.x = static_cast<int>(xLoc - 20 + nOffSet); 
	rectWorldLoc.p2.x = static_cast<int>(xLoc - 5 + nOffSet);
	rectWorldLoc.p1.y = static_cast<int>(yLoc - 15);
	rectWorldLoc.p2.y = static_cast<int>(yLoc + 30);
}