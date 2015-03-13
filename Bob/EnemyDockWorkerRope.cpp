// EnemyDockWorkerRope.cpp: implementation of the EnemyDockWorkerRope class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyDockWorkerRope.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyDockWorkerRope::EnemyDockWorkerRope(Level *curLevel)
{
	InitEnemy(base_enemy_type_2, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .5,
			  0,
			  true);

	level_class = curLevel;
	SetRenderOffset(38);

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -5;
	rectYOffset = -15;
}

EnemyDockWorkerRope::~EnemyDockWorkerRope()
{
}

HPTRect &EnemyDockWorkerRope::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_ROPE_ANIM_ATTACK) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(15);
		SetRectangle(rectWeaponWorldLoc, 50, 10, 0, 0);
	}
	else if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_ROPE_ANIM_ATTACK) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(15);
		SetRectangle(rectWeaponWorldLoc, 80, 10, 0, 0);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

/*HPTRect &EnemyDockWorkerRope::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyDockWorkerRope::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{	
		case 2:
		
			/* Set Attack State */
			ipFlags.S_ATTACK = true;
				
			/* Stop All Directional Movement */
			StopMovement();

			/* Set Animation */
			SetAnimation(ENEMY_DOCK_WORKER_ROPE_ANIM_ATTACK, 0, true, true, 10, true);

			/* Play Star Throw Sound */
				//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(whip00);
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyDockWorkerRope::processDamage()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
	ipFlags.S_ATTACK = false;
}

void EnemyDockWorkerRope::processDeath()
{

//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_DOCK_WORKER_ROPE_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyDockWorkerRope::stop()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Frame 0 of Attack Animation */
	if(ipFlags.PrevMState != move_stop) SetAnimation(ENEMY_DOCK_WORKER_ROPE_ANIM_MOVE, 0, true, false, 12, true);
	else SetAnimation(ENEMY_DOCK_WORKER_ROPE_ANIM_MOVE, 0, true, false, 12, false);
}

void EnemyDockWorkerRope::processUpdate()
{
//	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_ROPE_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_ROPE_ANIM_ATTACK) && !player_spr->IsAnimating())
			ipFlags.S_ATTACK = false;
	
	if(!ipFlags.S_DAMAGED && !ipFlags.S_ATTACK)
		switch(ipFlags.CurMState)
		{
			case move_stop:
				stop();
				break;

			default:
				break;
		}
}

void EnemyDockWorkerRope::StartDockWorkerRope()
{
	SetAnimation(ENEMY_DOCK_WORKER_ROPE_ANIM_MOVE, 0, true, false, 12, true);
}