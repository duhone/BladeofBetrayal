// EnemyMohawkPunk.cpp: implementation of the EnemyMohawkPunk class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyMohawkPunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyMohawkPunk::EnemyMohawkPunk(Level *curLevel)
{
	InitEnemy(14, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .25,
			  0,
			  true);

	SetRenderOffset(enemy_prisoner_render_offset);
	level_class = curLevel;
	SetMaxWalkVelocity(WALK_FAST);

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
}

EnemyMohawkPunk::~EnemyMohawkPunk()
{
}


/*HPTRect &EnemyMohawkPunk::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyMohawkPunk::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_MOHAWK_PUNK_PUNCH) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(8);
		SetRectangle(rectWeaponWorldLoc, 15, 4, nOffSet, 2);
	}
	else if((player_spr->GetFrameSet() == ENEMY_MOHAWK_PUNK_PUNCH) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(8);
		SetRectangle(rectWeaponWorldLoc, 15, 4, nOffSet, -2);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyMohawkPunk::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_MOHAWK_PUNK_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_MOHAWK_PUNK_ANIM_MOVE, 0, true, false, 22, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyMohawkPunk::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_MOHAWK_PUNK_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_MOHAWK_PUNK_ANIM_MOVE, 0, true, false, 22, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyMohawkPunk::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swing00);
		if(!SetAnimation(ENEMY_MOHAWK_PUNK_PUNCH, 0, true, true, 30, false))
		{
			velMovement = 0;
			velModifier = 0;
		}
	}
}

void EnemyMohawkPunk::processDeath()
{

//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);

	velMovement = 0;
	velModifier = 0;
	SetAnimation(ENEMY_MOHAWK_PUNK_DEATH, 0, true, true, 10, true);
}

void EnemyMohawkPunk::processDamage()
{
	ipFlags.S_ATTACK = false;

	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyMohawkPunk::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_MOHAWK_PUNK_ANIM_MOVE, 0, false, false, 15, true);
	else
		SetAnimation(ENEMY_MOHAWK_PUNK_ANIM_MOVE, 0, false, false, 15, false);
}

void EnemyMohawkPunk::processUpdate()
{
//	BelowFeetLadderCheck();

	if((player_spr->GetFrameSet() == ENEMY_MOHAWK_PUNK_DEATH)&& !player_spr->IsAnimating())
		Die();

	if(ipFlags.S_ATTACK)
	{
		if((player_spr->GetFrameSet() == ENEMY_MOHAWK_PUNK_PUNCH) && !player_spr->IsAnimating())
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