// EnemyBear1.cpp: implementation of the EnemyBear class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyBear1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
EnemyBear::EnemyBear(Level *curLevel)
{
	SetCurLife(enemy_gmonstersmall_cur_life);
	SetNumLifeBars((int)(enemy_gmonstersmall_cur_life * .2f + 1));
	SetRenderOffset(-8);

	level_class = curLevel;

	SetDamageTimer(.25);
}

EnemyBear::~EnemyBear()
{

}

HPTRect &EnemyBear::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_BEAR_ATTACK) && (player_spr->GetFrame() == 8))
		SetRectangle(rectWeaponWorldLoc, 10, 10, nOffSet, -25);
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

/*HPTRect &EnemyBear::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyBear::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		ipFlags.S_ATTACK = true;

		SetAnimation(ENEMY_BEAR_ATTACK, 0, true, true, 15, true);
		player_spr->EnableFrameSkip(false);
	}
}

void EnemyBear::processDamage()
{
	ipFlags.S_ATTACK = false;
	
//	if(ipFlags.S_DAMAGED_DIRECTION) velMovement = 20;
//	else velMovement = -20;
}

void EnemyBear::processDeath()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_BEAR_DEATH, 0, true, true, 10, true);
}

void EnemyBear::stop()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Frame 0 of Attack Animation */
	if(ipFlags.PrevMState != move_stop) SetAnimation(ENEMY_BEAR_ATTACK, 0, false, false, 15, true);
	else SetAnimation(ENEMY_BEAR_ATTACK, 0, false, false, 15, false);
}

void EnemyBear::processUpdate()
{
//	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_BEAR_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_BEAR_ATTACK) && !player_spr->IsAnimating())
		{
			ipFlags.S_ATTACK = false;
			SetAnimation(ENEMY_BEAR_ATTACK, 0, false, false, 0, true);
		}

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
	SetRectangle(rectWorldLoc, 40, 45, -20, -15);
}