// EnemyPrisoner.cpp: implementation of the EnemyPrisoner class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyPrisoner.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/* Prisoner Values
Hits to Kill - 2 Standard Attacks
*/

EnemyPrisoner::EnemyPrisoner(Level *curLevel)
{
	SetRenderOffset(enemy_prisoner_render_offset);
	SetMaxWalkVelocity(static_cast<float>(enemy_prisoner_max_walk_velocity));
	SetWalkAcceleration(static_cast<float>(enemy_prisoner_walk_acceleration));
	SetPlayerRectangle(enemy_prisoner_width, enemy_prisoner_height);

	level_class = curLevel;

	SetCurLife(enemy_prisoner_cur_life);
	SetNumLifeBars((int)(enemy_prisoner_cur_life * .2f + 1));

	SetDamageTimer(.25);


	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
}

EnemyPrisoner::~EnemyPrisoner()
{
}


/*HPTRect &EnemyPrisoner::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyPrisoner::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_PRISONER_ANIM_PUNCH) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(4);
		SetRectangle(rectWeaponWorldLoc, 15, 4, nOffSet, 2);//, ipFlags.S_DIRECTION);
	}
	else if((player_spr->GetFrameSet() == ENEMY_PRISONER_ANIM_PUNCH) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(4);
		SetRectangle(rectWeaponWorldLoc, 15, 4, nOffSet, -2);//, ipFlags.S_DIRECTION);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);



/*	if(player_spr->GetFrame() == 5)
	if(ipFlags.S_DIRECTION)
	{
		rectWeaponWorldLoc.p1.x = static_cast<int>(xLoc + nOffSet);
		rectWeaponWorldLoc.p2.x = static_cast<int>(xLoc + 20 + nOffSet);
		rectWeaponWorldLoc.p1.y = static_cast<int>(yLoc - 2);
		rectWeaponWorldLoc.p2.y = static_cast<int>(yLoc + 2);
	}
	else
	{
		rectWeaponWorldLoc.p1.x = static_cast<int>(xLoc - 20 - nOffSet);
		rectWeaponWorldLoc.p2.x = static_cast<int>(xLoc - nOffSet);
		rectWeaponWorldLoc.p1.y = static_cast<int>(yLoc - 2);
		rectWeaponWorldLoc.p2.y = static_cast<int>(yLoc + 2);
	}*/

	return rectWeaponWorldLoc;
}

void EnemyPrisoner::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_PRISONER_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_PRISONER_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Left Velocity
//	velMovement -= walkAcceleration;
//	if(velMovement < -maxWalkSpeed)
		velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyPrisoner::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_PRISONER_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_PRISONER_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Right Velocity
//	velMovement += walkAcceleration;
//	if(velMovement >= maxWalkSpeed)
		velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyPrisoner::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		if(!SetAnimation(ENEMY_PRISONER_ANIM_PUNCH, 0, true, true, 30, false))
		{
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swing00);

			velMovement = 0;
			velModifier = 0;
		}
	}
}

void EnemyPrisoner::processDeath()
{
	velMovement = 0;
	velModifier = 0;
	SetAnimation(ENEMY_PRISONER_ANIM_DEATH, 0, true, true, 8, true);
}

void EnemyPrisoner::processDamage()
{
	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);


	ipFlags.S_ATTACK = false;

	SetAnimation(ENEMY_PRISONER_ANIM_DAMAGE, 0, true, false, 10, true);

//	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyPrisoner::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_PRISONER_ANIM_MOVE, 0, false, false, 15, true);
	else
		SetAnimation(ENEMY_PRISONER_ANIM_MOVE, 0, false, false, 15, false);
}

void EnemyPrisoner::processUpdate()
{
	BelowFeetLadderCheck();

	if(!ipFlags.S_DEAD)
	{
		if((player_spr->GetFrameSet() == ENEMY_PRISONER_ANIM_DEATH)&& !player_spr->IsAnimating())
			Die();

		if(ipFlags.S_ATTACK)
		{
			if((player_spr->GetFrameSet() == ENEMY_PRISONER_ANIM_PUNCH) && !player_spr->IsAnimating())
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