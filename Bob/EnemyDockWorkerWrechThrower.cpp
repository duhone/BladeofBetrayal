// EnemyDockWorkerWrechThrower.cpp: implementation of the EnemyDockWorkerWrechThrower class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyDockWorkerWrechThrower.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyDockWorkerWrechThrower::EnemyDockWorkerWrechThrower(Level *curLevel)
{
	InitEnemy(base_enemy_type_2, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .5,
			  0,
			  true);

	level_class = curLevel;
	SetRenderOffset(5);	

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
}

EnemyDockWorkerWrechThrower::~EnemyDockWorkerWrechThrower()
{
}

/*HPTRect &EnemyDockWorkerWrechThrower::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyDockWorkerWrechThrower::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{	
			Projectile *temp;

		case 0:
			break;

		case 1:

			/* Set Attack State */
			ipFlags.S_ATTACK = true;

			/* Create Ninja Star Projectile */
			if(ipFlags.S_DIRECTION) 
			{
				temp = new ProjectileWrench(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15), 75, -100,0,200);
				
			}
			else
			{
				temp = new ProjectileWrench(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc - 15), -75, -100,0,200);
				
			}
			(*projectile_list).push_back(temp);
				
			/* Stop All Directional Movement */
			StopMovement();

			/* Set Animation */
			SetAnimation(ENEMY_DOCK_WORKER_WRECH_ANIM_ATTACK, 0, true, true, 24, true);

			/* Play Star Throw Sound */
//			if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
			break;

		case 2:
		
			/* Set Attack State */
			ipFlags.S_ATTACK = true;

			/* Create Ninja Star Projectile */
			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileWrench(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15), 130, 0,0,0);
				
			}
			else
			{
				temp = new ProjectileWrench(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc - 15), -130, 0,0,0);
				
			}   
			(*projectile_list).push_back(temp);
				
			/* Stop All Directional Movement */
			StopMovement();

			/* Set Animation */
			SetAnimation(ENEMY_DOCK_WORKER_WRECH_ANIM_ATTACK, 0, true, true, 20, true);

			/* Play Star Throw Sound */
//			if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyDockWorkerWrechThrower::processDamage()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
		ipFlags.S_ATTACK = false;
}

void EnemyDockWorkerWrechThrower::processDeath()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_DOCK_WORKER_WRECH_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyDockWorkerWrechThrower::stop()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Frame 0 of Attack Animation */
	if(ipFlags.PrevMState != move_stop) SetAnimation(ENEMY_DOCK_WORKER_WRECH_ANIM_ATTACK, 0, false, false, 22, true);
	else SetAnimation(ENEMY_DOCK_WORKER_WRECH_ANIM_ATTACK, 0, false, false, 22, false);
}

void EnemyDockWorkerWrechThrower::processUpdate()
{
//	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_WRECH_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_DOCK_WORKER_WRECH_ANIM_ATTACK) && !player_spr->IsAnimating())
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