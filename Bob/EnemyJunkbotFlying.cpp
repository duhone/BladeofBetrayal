// EnemyJunkbotFlying.cpp: implementation of the EnemyJunkbotFlying class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyJunkbotFlying.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyJunkbotFlying::EnemyJunkbotFlying(Level *curLevel)
{
	InitEnemy(base_enemy_type_2, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .5,
			  0,
			  true);

	SetMaxWalkVelocity(45);
	level_class = curLevel;
	SetRenderOffset(0);
	ipFlags.S_NO_GRAVITY = true;

	rectDX = 35;
	rectDY = 15;
	rectXOffset = -nOffSet-25;
	rectYOffset = -10;
}

EnemyJunkbotFlying::~EnemyJunkbotFlying()
{

}

/*HPTRect &EnemyJunkbotFlying::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyJunkbotFlying::processDeath()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_JUNKBOT_FLYING_DEATH, 0, true, true, 10, true);
}

void EnemyJunkbotFlying::processLeft()
{
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 15, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyJunkbotFlying::processRight()
{
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 15, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyJunkbotFlying::processUp()
{
	if(ipFlags.PrevMState != move_up)
		SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 15, false);

	velYModifier = -maxWalkSpeed;
}

void EnemyJunkbotFlying::processDown()
{
	if(ipFlags.PrevMState != move_down)
		SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 15, false);

	velYModifier = maxWalkSpeed;
}

void EnemyJunkbotFlying::processAttack()
{
	if(ipFlags.nCurrAttack == 0)
	{
		if(ipFlags.S_DIRECTION)
		{
//			if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser00);
			Projectile *temp;
			temp = new ProjectileJunkbotFlying(static_cast<int>(xLoc + 25), static_cast<int>(yLoc + 15), 90, 90);
			;
			(*projectile_list).push_back(temp);
		}
		else
		{
//			if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser00);

			Projectile *temp;
			temp = new ProjectileJunkbotFlying(static_cast<int>(xLoc - 25), static_cast<int>(yLoc + 15), -90, 90);
			;
			(*projectile_list).push_back(temp);
		}
	}
}

void EnemyJunkbotFlying::stop()
{
	StopMovement();
}

void EnemyJunkbotFlying::processDamage()
{
	//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser02);

	ipFlags.S_ATTACK = false;

	SetAnimation(ENEMY_JUNKBOT_FLYING_MOVE, 0, true, false, 10, false);
}

void EnemyJunkbotFlying::processUpdate()
{
	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_JUNKBOT_FLYING_DEATH) && !player_spr->IsAnimating())
		Die();

	if(!ipFlags.S_DEAD)
	{
		// Apply Velocity Modifier
		if(!ipFlags.S_DAMAGED)
		{
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

					case move_up:
						processUp();
						break;

					case move_down:
						processDown();

					default:
						break;
				}
		}
	}

	/* Center (0,0), offset by Render Offset */
//	SetRectangle(rectWorldLoc, 35, 15, -nOffSet - 25, -10);
}


