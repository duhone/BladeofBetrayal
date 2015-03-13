// EnemyWolf1.cpp: implementation of the EnemyWolf class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyWolf1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyWolf::EnemyWolf(Level *curLevel, int Type)
{
	if(Type)
	{
		InitEnemy(base_enemy_type_2, 
			      base_x_velocity,
				  base_y_velocity,
				  0,
				  .25,
				  0,
				  true);
		SetWeaponDamage(5);
	}
	else
	{
		InitEnemy(base_enemy_type_2, 
			      base_x_velocity,
				  base_y_velocity,
				  0,
				  .25,
				  0,
				  true);
		SetWeaponDamage(7);
	}

	SetRenderOffset(0, -15);
	this->level_class = curLevel;
	wolfType = Type;
	ipFlags.S_ATTACK = true;

		rectDX = 30;
	rectDY = 20;
	rectXOffset = -nOffSet-10;
	rectYOffset = -5;
}

EnemyWolf::~EnemyWolf()
{
}

/*HPTRect &EnemyWolf::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyWolf::GetWeaponWorldLoc()
{
	/* Center (0,0), offset by Render Offset */
	SetRectangle(rectWeaponWorldLoc, 15, 15, -nOffSet, 0);

	return rectWeaponWorldLoc;
}

void EnemyWolf::processLeft()
{
	if(ipFlags.PrevMState != move_left)
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(growl00);
	
	if(player_spr->GetFrameSet() != ENEMY_WOLF_MOVE)
	{
		SetAnimation(ENEMY_WOLF_MOVE, 0, true, false, 15, true);
	}
	else
		SetAnimation(ENEMY_WOLF_MOVE, 0, true, false, 15, false);

	if(wolfType == 0)
		velMovement = -maxWalkSpeed;
	else
		velMovement = -maxWalkSpeed * 2;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyWolf::processRight()
{
	if(ipFlags.PrevMState != move_right)
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(growl00);

	if(player_spr->GetFrameSet() != ENEMY_WOLF_MOVE)
	{
		
		SetAnimation(ENEMY_WOLF_MOVE, 0, true, false, 15, true);
	}
	else
		SetAnimation(ENEMY_WOLF_MOVE, 0, true, false, 15, false);

	if(wolfType == 0)
		velMovement = maxWalkSpeed;
	else
		velMovement = maxWalkSpeed * 2;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyWolf::processDeath()
{
	StopMovement();

	SetAnimation(ENEMY_WOLF_DEATH, 0, true, true, 10, true);
}

void EnemyWolf::processDamage()
{
	ipFlags.S_ATTACK = false;

	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyWolf::stop()
{
	StopMovement();

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_WOLF_MOVE, 7, false, false, 22, true);
	else
		SetAnimation(ENEMY_WOLF_MOVE, 7, false, false, 22, false);
}

void EnemyWolf::StartWolf()
{
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_WOLF_MOVE, 7, false, false, 22, true);
	else
		SetAnimation(ENEMY_WOLF_MOVE, 7, false, false, 22, false);
}

void EnemyWolf::processUpdate()
{
	if(!ipFlags.S_DEAD)
	{
		if((player_spr->GetFrameSet() == ENEMY_WOLF_DEATH)&& !player_spr->IsAnimating())
			Die();

		// Apply Velocity Modifier
		if(!ipFlags.S_DAMAGED)
		{
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

	/* Center (0,0), offset by Render Offset */
//	SetRectangle(rectWorldLoc, 30, 20, -nOffSet - 10, -5);
}