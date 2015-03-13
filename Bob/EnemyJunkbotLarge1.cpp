// EnemyJunkbotLarge1.cpp: implementation of the EnemyJunkbotLarge class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyJunkbotLarge1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyJunkbotLarge::EnemyJunkbotLarge(Level *curLevel, bool sDirection)
{
	InitEnemy(base_enemy_type_3, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .25,
			  0,
			  true);

	level_class = curLevel;
	SetRenderOffset(15, -45);
	ipFlags.S_DIRECTION = sDirection;
	ipFlags.S_RENDER_FLASH = false;
}

EnemyJunkbotLarge::~EnemyJunkbotLarge()
{
}

/*HPTRect &EnemyJunkbotLarge::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyJunkbotLarge::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		SetAnimation(ENEMY_JUNKBOT_LARGE_ATTACK, 0, true, true, 10, true);
		
		//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(machinery);
		Projectile *temp;

		if(ipFlags.S_DIRECTION)
		{
			temp = new ProjectileJunkbotLarge(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 3), static_cast<int>(yLoc - 13));
			
		}
		else
		{
			temp = new ProjectileJunkbotLarge(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 3), static_cast<int>(yLoc - 13));
			
		}
			
		(*projectile_list).push_back(temp);

		ipFlags.S_ATTACK = true;
				
		//Stop All Directional Movement
		velMovement = 0;
		velModifier = 0;
	}
}

void EnemyJunkbotLarge::processDamage()
{
	ipFlags.S_ATTACK = false;

}

void EnemyJunkbotLarge::processDeath()
{
	if(player_spr->GetFrameSet() != ENEMY_JUNKBOT_LARGE_DEATH)
	{
		timer = 5;
		//Stop All Directional Movement
		velMovement = 0;
		velModifier = 0;
		SetAnimation(ENEMY_JUNKBOT_LARGE_DEATH, 0, true, true, 10, true);
	}
}

void EnemyJunkbotLarge::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_JUNKBOT_LARGE_STAND, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_JUNKBOT_LARGE_STAND, 0, false, false, 22, false);
}

void EnemyJunkbotLarge::processUpdate()
{
//	BelowFeetLadderCheck();

	if(ipFlags.S_ON_GROUND)
	{
		velModifier = 0;
		velYModifier = 0;
	}
	else
	{
		velYModifier += (gravityConstant * time);
	}

	if((player_spr->GetFrameSet() == ENEMY_JUNKBOT_LARGE_DEATH)&& !player_spr->IsAnimating())
	{
		timer -= time;

		if(timer <= 0)
		{
			SetCurLife(5);
			ipFlags.S_PROCESS_DEATH = false;
			ipFlags.S_DEAD = false;
			ipFlags.S_ACTIVE = true;
			SetAnimation(ENEMY_JUNKBOT_LARGE_STAND, 0, false, false, 22, true);
		}
	}

	if(ipFlags.S_ATTACK)
	{
		if((player_spr->GetFrameSet() == ENEMY_JUNKBOT_LARGE_ATTACK) && !player_spr->IsAnimating())
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

	SetRectangle(rectWorldLoc, 40, 80, -nOffSet, -50);//-55);
}