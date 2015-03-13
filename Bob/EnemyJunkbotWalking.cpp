// EnemyJunkbotWalking.cpp: implementation of the EnemyJunkbotWalking class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyJunkbotWalking.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyJunkbotWalking::EnemyJunkbotWalking(Level *curLevel)
{
	InitEnemy(base_enemy_type_3, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .5,
			  0,
			  true);

	SetRenderOffset(enemy_junkbot_walking_render_offset);

	SetMaxWalkVelocity(35);
	

	level_class = curLevel;

		rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
}

EnemyJunkbotWalking::~EnemyJunkbotWalking()
{
}

/*HPTRect &EnemyJunkbotWalking::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyJunkbotWalking::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_JUNKBOT_WALKING_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_JUNKBOT_WALKING_MOVE, 0, true, false, 15, false);

	//Accelerate Left Velocity
	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyJunkbotWalking::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_JUNKBOT_WALKING_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_JUNKBOT_WALKING_MOVE, 0, true, false, 15, false);

	//Accelerate Right Velocity
	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyJunkbotWalking::processAttack()
{
	Projectile *temp;

	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

//		ipFlags.nCurrAttack = 1;

		

		switch(ipFlags.nCurrAttack)
		{
		case 0:
//			if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser01);
			SetAnimation(ENEMY_JUNKBOT_WALKING_ATTACK, 0, true, true, 20, true);
		
			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileJunkbotWalkingBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc - 10),projectile_list, 90, 0, .4f, 3);
				
				(*projectile_list).push_back(temp);
			}
			else
			{
				temp = new ProjectileJunkbotWalkingBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 10),projectile_list, -90, 0, .4f, 3);
				
				(*projectile_list).push_back(temp);
			}

			//Stop All Directional Movement
			StopMovement();

			break;

		case 1:
			//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser03);

			SetAnimation(ENEMY_JUNKBOT_WALKING_ATTACK, 0, true, true, 20, true);

			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileJunkbotWalkingBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc - 10),projectile_list, 140, 0, .4f,  .20);
				
				(*projectile_list).push_back(temp);
				
				temp = new ProjectileJunkbotWalkingBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc - 10),projectile_list, 130, 80, .45f,  .20);
				
				(*projectile_list).push_back(temp);
				
				temp = new ProjectileJunkbotWalkingBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc - 10),projectile_list, 130, -80, .45f,  .20);
				
				(*projectile_list).push_back(temp);
			}
			else
			{
				temp = new ProjectileJunkbotWalkingBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 10),projectile_list, -140, 0, .4f,  .20);
				
				(*projectile_list).push_back(temp);
				
				temp = new ProjectileJunkbotWalkingBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 10),projectile_list, -130, 80, .45f,  .20);
				
				(*projectile_list).push_back(temp);
				
				temp = new ProjectileJunkbotWalkingBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 10),projectile_list, -130, -80, .45f, .20);
				
				(*projectile_list).push_back(temp);
			}

			//Stop All Directional Movement
			StopMovement();

			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyJunkbotWalking::processDamage()
{
	//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser02);

	ipFlags.S_ATTACK = false;

	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 30;
	else
		velMovement = -30;
}

void EnemyJunkbotWalking::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_JUNKBOT_WALKING_DEATH, 0, true, true, 10, true);
}

void EnemyJunkbotWalking::stop()
{
	//Stop All Movement
	StopMovement();

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_JUNKBOT_WALKING_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_JUNKBOT_WALKING_MOVE, 0, false, false, 22, false);
}

void EnemyJunkbotWalking::processUpdate()
{
	if((player_spr->GetFrameSet() == ENEMY_JUNKBOT_WALKING_DEATH) && !player_spr->IsAnimating())
		Die();

	if(ipFlags.S_ATTACK)
	{
		if(!player_spr->IsAnimating())
		{
			ipFlags.S_ATTACK = false;
		}
	}

	// Apply Velocity Modifier
	if(!ipFlags.S_DAMAGED && !ipFlags.S_ATTACK)
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

	/* Center (0,0), offset by Render Offset */
//	SetRectangle(rectWorldLoc, 15, 45, -nOffSet, -15);
}
