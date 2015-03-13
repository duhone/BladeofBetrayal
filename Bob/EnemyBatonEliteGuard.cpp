// EnemyBatonEliteGuard.cpp: implementation of the EnemyBatonEliteGuard class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyBatonEliteGuard.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyBatonEliteGuard::EnemyBatonEliteGuard(Level *curLevel)
{
	InitEnemy(enemy_baton_elite_guard_cur_life, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .25,
			  0,
			  true);

	level_class = curLevel;

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::swing::ID);
}

EnemyBatonEliteGuard::~EnemyBatonEliteGuard()
{
}

/*HPTRect &EnemyBatonEliteGuard::GetWorldLoc()
{
	rectWorldLoc.p1.x = static_cast<int>(xLoc - 20 + nOffSet); 
	rectWorldLoc.p2.x = static_cast<int>(xLoc - 5 + nOffSet);
	rectWorldLoc.p1.y = static_cast<int>(yLoc - 15);
	rectWorldLoc.p2.y = static_cast<int>(yLoc + 30);

	return rectWorldLoc;
}*/

HPTRect &EnemyBatonEliteGuard::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(4);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, 2);
	}
	else if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(4);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, -2);
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

void EnemyBatonEliteGuard::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, true, false, 15, false);

	//Accelerate Left Velocity
//	velMovement -= walkAcceleration;
//	if(velMovement < -maxWalkSpeed)
		velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyBatonEliteGuard::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, true, false, 15, false);

	//Accelerate Right Velocity
//	velMovement += walkAcceleration;
//	if(velMovement >= maxWalkSpeed)
		velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyBatonEliteGuard::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		if(!SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK, 0, true, true, 30, false))
		{
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
			//Stop All Directional Movement
			velMovement = 0;
			velModifier = 0;
		}
		if (ipFlags.S_ACTIVE) m_soundFX->Play();
	}
}

void EnemyBatonEliteGuard::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyBatonEliteGuard::processDamage()
{
	ipFlags.S_ATTACK = false;

	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
	SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_DAMAGE, 0, true, false, 10, false);

//	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyBatonEliteGuard::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, false, false, 22, false);
}

void EnemyBatonEliteGuard::processUpdate()
{
	BelowFeetLadderCheck();
	
	if(!ipFlags.S_DEAD)
	{
		if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_DEATH)&& !player_spr->IsAnimating())
			Die();

/*		if(ipFlags.S_ON_GROUND)
		{
			velModifier = 0;
			velYModifier = 0;
		}
		else
		{
			velYModifier += (gravityConstant * time);
		}*/

		if(ipFlags.S_ATTACK)
		{
			if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK) && !player_spr->IsAnimating())
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