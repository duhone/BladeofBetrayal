// EnemyDockWorkerWrench.cpp: implementation of the EnemyDockWorkerWrench class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyDockWorkerWrench.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyDockWorkerWrench::EnemyDockWorkerWrench(Level *curLevel)
{
	InitEnemy(base_enemy_type_2, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .15f,
			  0,
			  true);

	level_class = curLevel;
	SetRenderOffset(10);
	SetMaxWalkVelocity(WALK_FAST);

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = 3;
}

EnemyDockWorkerWrench::~EnemyDockWorkerWrench()
{
}

/*HPTRect &EnemyDockWorkerWrench::GetWorldLoc()
{
	

	return rectWorldLoc;
}*/

HPTRect &EnemyDockWorkerWrench::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_ANIM_ATTACK) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(10);
		SetRectangle(rectWeaponWorldLoc, 25, 10, 0, 10);
	}
	else if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_ANIM_ATTACK) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(10);
		SetRectangle(rectWeaponWorldLoc, 50, 10, 0, 10);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyDockWorkerWrench::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_DOCK_WORKER_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_DOCK_WORKER_ANIM_MOVE, 0, true, false, 22, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyDockWorkerWrench::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_DOCK_WORKER_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_DOCK_WORKER_ANIM_MOVE, 0, true, false, 22, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyDockWorkerWrench::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

	//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(bang00);
		if(!SetAnimation(ENEMY_DOCK_WORKER_ANIM_ATTACK, 0, true, true, 22, false))
		{

			//Stop All Directional Movement
			velMovement = 0;
			velModifier = 0;
		}
	}
}

void EnemyDockWorkerWrench::processDeath()
{
	//soundPlayer->PlaySound(damage00);
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_DOCK_WORKER_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyDockWorkerWrench::processDamage()
{

//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
	ipFlags.S_ATTACK = false;

	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyDockWorkerWrench::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_DOCK_WORKER_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_DOCK_WORKER_ANIM_MOVE, 0, false, false, 22, false);
}

void EnemyDockWorkerWrench::processUpdate()
{
//	BelowFeetLadderCheck();

	if(!ipFlags.S_DEAD)
	{
		if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_ANIM_DEATH)&& !player_spr->IsAnimating())
			Die();

		if(ipFlags.S_ATTACK)
		{
			if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_ANIM_ATTACK) && !player_spr->IsAnimating())
				ipFlags.S_ATTACK = false;
		}

		// Apply Velocity Modifier
		if(!ipFlags.S_DAMAGED)
		{
			if(!ipFlags.S_ATTACK)
				switch(ipFlags.CurMState)
				{
					case move_stop:
						stop();
						break;		
	
					case move_left:
						processLeft();
						break;
	
					case move_right:
						processRight();
						break;

					default:
						break;
				}
		}
	}
}