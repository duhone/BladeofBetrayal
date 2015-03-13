// EnemyKnifePunk.cpp: implementation of the EnemyKnifePunk class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyKnifePunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyKnifePunk::EnemyKnifePunk(Level *curLevel)
{
	InitEnemy(8, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .5,
			  0,
			  true);

	level_class = curLevel;
	SetRenderOffset(enemy_prisoner_render_offset);

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
}

EnemyKnifePunk::~EnemyKnifePunk()
{
}

/*HPTRect &EnemyKnifePunk::GetWorldLoc()
{


	return rectWorldLoc;
}
*/
void EnemyKnifePunk::processAttack()
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
				temp = new ProjectileKnife(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15), 75, -100,0,200);
				
			}
			else
			{
				temp = new ProjectileKnife(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc - 15), -75, -100,0,200);
				
			}
			(*projectile_list).push_back(temp);
				
			/* Stop All Directional Movement */
			StopMovement();

			/* Set Animation */
			SetAnimation(ENEMY_KNIFE_PUNK_ANIM_ATTACK, 0, true, true, 24, true);

			/* Play Star Throw Sound */
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
			break;

		case 2:
		
			/* Set Attack State */
			ipFlags.S_ATTACK = true;

			/* Create Ninja Star Projectile */
			if(ipFlags.S_DIRECTION) 
			{
				temp = new ProjectileKnife(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15), 130, 0,0,0);
				
			}
			else 
			{
				temp = new ProjectileKnife(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc - 15), -130, 0,0,0);
				
			}
			(*projectile_list).push_back(temp);
				
			/* Stop All Directional Movement */
			StopMovement();

			/* Set Animation */
			SetAnimation(ENEMY_KNIFE_PUNK_ANIM_ATTACK, 0, true, true, 20, true);

			/* Play Star Throw Sound */
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swing00);
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyKnifePunk::processDamage()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);

	ipFlags.S_ATTACK = false;

//	if(ipFlags.S_DAMAGED_DIRECTION) velMovement = 60;
//	else velMovement = -60;
}

void EnemyKnifePunk::processDeath()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_KNIFE_PUNK_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyKnifePunk::stop()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Frame 0 of Attack Animation */
	if(ipFlags.PrevMState != move_stop) SetAnimation(ENEMY_KNIFE_PUNK_ANIM_ATTACK, 0, false, false, 22, true);
	else SetAnimation(ENEMY_KNIFE_PUNK_ANIM_ATTACK, 0, false, false, 22, false);
}

void EnemyKnifePunk::processUpdate()
{
//	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_KNIFE_PUNK_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_KNIFE_PUNK_ANIM_ATTACK) && !player_spr->IsAnimating())
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