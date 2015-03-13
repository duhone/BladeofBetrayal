// EnemyBaseballPunk.cpp: implementation of the EnemyBaseballPunk class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyBaseballPunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyBaseballPunk::EnemyBaseballPunk(Level *curLevel)
{
	InitEnemy(10, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .15f,
			  0,
			  true);

	level_class = curLevel;
	SetRenderOffset(enemy_prisoner_render_offset);
	SetMaxWalkVelocity(WALK_FAST);	
			
	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
}

EnemyBaseballPunk::~EnemyBaseballPunk()
{
}

/*HPTRect &EnemyBaseballPunk::GetWorldLoc()
{
	return rectWorldLoc;
}*/

HPTRect &EnemyBaseballPunk::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_BASEBALL_PUNK_ANIM_BATON_ATTACK) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(6);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, 2);
	}
	else if((player_spr->GetFrameSet() == ENEMY_BASEBALL_PUNK_ANIM_BATON_ATTACK) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(6);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, -2);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyBaseballPunk::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_BASEBALL_PUNK_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_BASEBALL_PUNK_ANIM_MOVE, 0, true, false, 15, false);

	//Accelerate Left Velocity
	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyBaseballPunk::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_BASEBALL_PUNK_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_BASEBALL_PUNK_ANIM_MOVE, 0, true, false, 15, false);

	//Accelerate Right Velocity
	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyBaseballPunk::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		if(!SetAnimation(ENEMY_BASEBALL_PUNK_ANIM_BATON_ATTACK, 0, true, true, 30, false))
		{
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swing00);
			//Stop All Directional Movement
			velMovement = 0;
			velModifier = 0;
		}
	}
}

void EnemyBaseballPunk::processDeath()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_BASEBALL_PUNK_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyBaseballPunk::processDamage()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
	ipFlags.S_ATTACK = false;

	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyBaseballPunk::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_BASEBALL_PUNK_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_BASEBALL_PUNK_ANIM_MOVE, 0, false, false, 22, false);
}

void EnemyBaseballPunk::processUpdate()
{
//	BelowFeetLadderCheck();

	if((player_spr->GetFrameSet() == ENEMY_BASEBALL_PUNK_ANIM_DEATH) && (!player_spr->IsAnimating()))
		Die();

	if(ipFlags.S_ATTACK)
	{
		if((player_spr->GetFrameSet() == ENEMY_BASEBALL_PUNK_ANIM_BATON_ATTACK) && !player_spr->IsAnimating())
			ipFlags.S_ATTACK = false;
	}

	//Apply Velocity Modifier
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