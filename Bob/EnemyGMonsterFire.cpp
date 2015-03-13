// EnemyGMonsterFire.cpp: implementation of the EnemyGMonsterFire class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyGMonsterFire.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyGMonsterFire::EnemyGMonsterFire(Level *curLevel)
{
	InitEnemy(base_enemy_type_2, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .25,
			  0,
			  true);

//	SetCurLife(enemy_gmonstersmall_cur_life);
//	SetNumLifeBars((int)(enemy_gmonstersmall_cur_life * .2f + 1));
	SetRenderOffset(30);

	level_class = curLevel;

//	SetDamageTimer(.25);

	rectDX = 45;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
}

EnemyGMonsterFire::~EnemyGMonsterFire()
{

}

HPTRect &EnemyGMonsterFire::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_FIRE_MONSTER_ATTACK) && (player_spr->GetFrame() == 8))
		SetRectangle(rectWeaponWorldLoc, 60, 45, -10 + nOffSet, -25);
	//	SetRectangle(rectWeaponWorldLoc, 60, 60, 0, 0);
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

/*HPTRect &EnemyGMonsterFire::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyGMonsterFire::processAttack()
{


	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(flame);
		
		ipFlags.S_ATTACK = true;
		SetWeaponDamage(base_enemy_dmg_6);
		SetAnimation(ENEMY_FIRE_MONSTER_ATTACK, 0, true, true, 16, true);
		player_spr->EnableFrameSkip(false);
	}
}

void EnemyGMonsterFire::processDamage()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(growl02);

//	ipFlags.S_ATTACK = false;

//	velYModifier = -100;
	if(ipFlags.S_DAMAGED_DIRECTION) velMovement = 20;
	else velMovement = -20;
	
	/* Set Damage Animation */
//	SetAnimation(0 /*ENEMY_FIRE_MONSTER_DAMAGE */, 0, true, false, 10, false);

}

void EnemyGMonsterFire::processDeath()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(firedeath);

	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_FIRE_MONSTER_DEATH, 0, true, true, 10, true);
}

void EnemyGMonsterFire::stop()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Frame 0 of Attack Animation */
	if(ipFlags.PrevMState != move_stop) SetAnimation(ENEMY_FIRE_MONSTER_ATTACK, 0, false, false, 15, true);
	else SetAnimation(ENEMY_FIRE_MONSTER_ATTACK, 0, false, false, 15, false);
}

void EnemyGMonsterFire::processUpdate()
{
	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_FIRE_MONSTER_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_FIRE_MONSTER_ATTACK) && !player_spr->IsAnimating())
		{
			ipFlags.S_ATTACK = false;
			SetAnimation(ENEMY_FIRE_MONSTER_ATTACK, 0, false, false, 0, true);
		}
//	else
//		SetAnimation(ENEMY_FIRE_MONSTER_ATTACK, 0, false, false, 0, true);
	
	if(!ipFlags.S_DAMAGED && !ipFlags.S_ATTACK)
		switch(ipFlags.CurMState)
		{
			case move_stop:
				stop();
				break;

			default:
				break;
		}

	/* Center (0,0), offset by Render Offset */
//	SetRectangle(rectWorldLoc, 45, 45, -nOffSet, -15);
}