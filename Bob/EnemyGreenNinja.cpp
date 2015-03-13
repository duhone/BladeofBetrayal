// EnemyGreenNinja.cpp: implementation of the EnemyGreenNinja class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyGreenNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyGreenNinja::EnemyGreenNinja(Level *curLevel)
{
	InitEnemy(base_enemy_type_2, 
		      (int)(base_x_velocity*0.7f),
			  (int)(base_y_velocity*0.7f),
			  0,
			  .5,
			  0,
			  true);

	level_class = curLevel;

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
}

EnemyGreenNinja::~EnemyGreenNinja()
{
}

/*HPTRect &EnemyGreenNinja::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyGreenNinja::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_GREEN_NINJA_ANIM_ATTACK) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(2);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, 2);
	}
	else if((player_spr->GetFrameSet() == ENEMY_GREEN_NINJA_ANIM_ATTACK) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(2);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, -2);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyGreenNinja::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_GREEN_NINJA_ANIM_MOVE, 0, true, false, 14, true);
	else
		SetAnimation(ENEMY_GREEN_NINJA_ANIM_MOVE, 0, true, false, 14, false);

	//Accelerate Left Velocity
//	velMovement -= walkAcceleration;
//	if(velMovement < -maxWalkSpeed)
	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyGreenNinja::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_GREEN_NINJA_ANIM_MOVE, 0, true, false, 14, true);
	else
		SetAnimation(ENEMY_GREEN_NINJA_ANIM_MOVE, 0, true, false, 14, false);

	//Accelerate Right Velocity
//	velMovement += walkAcceleration;
//	if(velMovement >= maxWalkSpeed)
	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyGreenNinja::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		if(!SetAnimation(ENEMY_GREEN_NINJA_ANIM_ATTACK, 0, true, true, 30, false))
		{
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
			
			//Stop All Directional Movement
			velMovement = 0;
			velModifier = 0;
		}
	}
}

void EnemyGreenNinja::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_GREEN_NINJA_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyGreenNinja::processDamage()
{
	ipFlags.S_ATTACK = false;

	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
	
	SetAnimation(ENEMY_GREEN_NINJA_ANIM_DAMAGE, 0, true, false, 10, false);

	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyGreenNinja::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_GREEN_NINJA_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_GREEN_NINJA_ANIM_MOVE, 0, false, false, 22, false);
}

void EnemyGreenNinja::Reset()
{
	SetAnimation(ENEMY_GREEN_NINJA_ANIM_MOVE, 0, false, false, 22, false);

	SetCurLife(enemy_green_ninja_set_cur_life);
	SetNumLifeBars((int)(enemy_green_ninja_set_cur_life * .2f + 1));

	ipFlags.S_DEAD = false;
	ipFlags.S_ACTIVE = true;
}

void EnemyGreenNinja::processUpdate()
{
//	BelowFeetLadderCheck();

	if(!ipFlags.S_DEAD)
	{
		if((player_spr->GetFrameSet() == ENEMY_GREEN_NINJA_ANIM_DEATH)&& !player_spr->IsAnimating())
			Die();

		if(ipFlags.S_ATTACK)
		{
			if((player_spr->GetFrameSet() == ENEMY_GREEN_NINJA_ANIM_ATTACK) && !player_spr->IsAnimating())
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