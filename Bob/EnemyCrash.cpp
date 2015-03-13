// EnemyCrash.cpp: implementation of the EnemyCrash class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyCrash.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyCrash::EnemyCrash(Level *curLevel)
{
	SetRenderOffset(9);
	InitEnemy(enemy_mr_thomas_set_cur_life * 3.5, 
		      base_x_velocity * 1.33,
			  base_y_velocity * 1.33,
			  0,
			  .25f,
			  0,
			  true);

	jumpMaxVelocity = -200;

	S_TIMER = false;

	level_class = curLevel;

	ipFlags.S_DIRECTION = false;
	SetMaxAttacks(10);
}

EnemyCrash::~EnemyCrash()
{
}

//HPTRect &EnemyCrash::GetWorldLoc()
//{
	/* Center (0,0), offset by Render Offset */
//	if(ipFlags.nCurrAttack != 8)
//		SetRectangle(rectWorldLoc, 15, 45, -nOffSet, -15);
//	else if(!S_TIMER)
//	{
//		float x, y;
//		GetVelocityVector(&x, &y);

//		if(y < 0)
//			SetRectangle(rectWorldLoc, 0, 0, -999, -999);
//		else
//			SetRectangle(rectWorldLoc, 15, 45, -nOffSet, -15);
//	}

//	return rectWorldLoc;
//}

HPTRect &EnemyCrash::GetWeaponWorldLoc()
{
	SetWeaponDamage(3);
	SetRectangle(rectWeaponWorldLoc, 15, 45, -nOffSet, -15);

	return rectWeaponWorldLoc;
}

void EnemyCrash::setJumpVelocity()
{
	if(ipFlags.S_DIRECTION) velModifier = 100;
	else velModifier = -100;

	ipFlags.S_ON_GROUND = false;
	ipFlags.S_NO_GRAVITY = false;
	ipFlags.S_JUMP = true;
	
	yLoc -= 1;

	velYModifier = 0;
	velYJumpModifier = jumpMaxVelocity;

	SetAnimation(ENEMY_CRASH_ANIM_JUMP, 0, true, true, 15 , true);
}

void EnemyCrash::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_CRASH_ANIM_WALK, 0, true, false, 22, true);
	else 
		SetAnimation(ENEMY_CRASH_ANIM_WALK, 0, true, false, 22, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyCrash::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_CRASH_ANIM_WALK, 0, true, false, 22, true);
	else 
		SetAnimation(ENEMY_CRASH_ANIM_WALK, 0, true, false, 22, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyCrash::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

	//	ipFlags.nCurrAttack = 6;

		switch(ipFlags.nCurrAttack)
		{
		
		case 0:
			{				
				//soundPlayer->PlaySound(rocket00);
				SetAnimation(ENEMY_CRASH_ANIM_ATTACK_1, 0, true, true, 10, false);
				Projectile *temp;
				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileCrashRocket(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 35), static_cast<int>(yLoc - 2), projectile_list);
				}
				else
				{
					temp = new ProjectileCrashRocket(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 35), static_cast<int>(yLoc - 2), projectile_list);
				}
				(*projectile_list).push_back(temp);
				StopMovement();
			}
			break;
			
		case 1:
			{
				//soundPlayer->PlaySound(rocket00);
				SetAnimation(ENEMY_CRASH_ANIM_ATTACK_2, 0, true, true, 10, false);
				Projectile *temp;
				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileCrashRocket(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 35), static_cast<int>(yLoc+9), projectile_list);
					
				}
				else
				{
					temp = new ProjectileCrashRocket(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 35), static_cast<int>(yLoc+9), projectile_list);
					
				}
				(*projectile_list).push_back(temp);
				StopMovement();
			}
			break;

		case 2:
			{
//				soundPlayer->PlaySound(explode02);
				SetAnimation(ENEMY_CRASH_ANIM_ATTACK_3, 0, true, true, 10, false);
				Projectile *temp;
				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileCrashGrenade(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 27), static_cast<int>(yLoc-21), projectile_list, true);
					
				}
				else 
				{
					temp = new ProjectileCrashGrenade(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 27), static_cast<int>(yLoc-21), projectile_list, true);
					
				}
				(*projectile_list).push_back(temp);
				StopMovement();
			}
			break;
			
		case 3:
			{
//				soundPlayer->PlaySound(explode02);
				SetAnimation(ENEMY_CRASH_ANIM_ATTACK_3, 0, true, true, 10, false);
				Projectile *temp;
				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileCrashGrenade(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 27), static_cast<int>(yLoc-21), projectile_list, false);
					
				}
				else 
				{
					temp = new ProjectileCrashGrenade(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 27), static_cast<int>(yLoc-21), projectile_list, false);
					
				}
				(*projectile_list).push_back(temp);
				StopMovement();
			}
			break;

		case 4:
			{
				//soundPlayer->PlaySound(handgun00);
				SetAnimation(ENEMY_CRASH_ANIM_ATTACK_4, 0, true, true, 22, false);
				Projectile *temp;
				if(ipFlags.S_DIRECTION)	
				{
					temp = new ProjectileCrashBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 30), static_cast<int>(yLoc - 2));
					
				}
				else 
				{
					temp = new ProjectileCrashBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 30), static_cast<int>(yLoc - 2));
					
				}
				(*projectile_list).push_back(temp);
				StopMovement();
			}
			break;

		case 5:
			{
				//soundPlayer->PlaySound(handgun00);
//				soundPlayer->PlaySound(laser00);
				
				SetAnimation(ENEMY_CRASH_ANIM_ATTACK_1, 0, true, true, 10, false);

				if(ipFlags.S_DIRECTION)
				{
					Projectile *temp;
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet + 30), static_cast<int>(yLoc), 45, 45, .5);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet + 30), static_cast<int>(yLoc), 45, 0, .5);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet + 30), static_cast<int>(yLoc), 45, -45, .5);
					
					(*projectile_list).push_back(temp);
				}
				else
				{
					Projectile *temp;
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet - 30), static_cast<int>(yLoc), -45, 45, .5);
					(*projectile_list).push_back(temp);
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet - 30), static_cast<int>(yLoc), -45, 0, .5);
					(*projectile_list).push_back(temp);
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet - 30), static_cast<int>(yLoc), -45, -45, .5);
					(*projectile_list).push_back(temp);
				}
			}
			break;

		case 6:
			{
				//soundPlayer->PlaySound(handgun00);
//				soundPlayer->PlaySound(laser00);
				
				SetAnimation(ENEMY_CRASH_ANIM_ATTACK_2, 0, true, true, 10, false);

				if(ipFlags.S_DIRECTION)
				{
					Projectile *temp;
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet + 30), static_cast<int>(yLoc+8), 45, 45, .5);
					(*projectile_list).push_back(temp);
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet + 30), static_cast<int>(yLoc+8), 45, 0, .5);
					(*projectile_list).push_back(temp);
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet + 30), static_cast<int>(yLoc+8), 45, -45, .5);
					(*projectile_list).push_back(temp);
				}
				else
				{
					Projectile *temp;
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet - 30), static_cast<int>(yLoc+8), -45, 45, .5);
					(*projectile_list).push_back(temp);
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet - 30), static_cast<int>(yLoc+8), -45, 0, .5);
					(*projectile_list).push_back(temp);
					temp = new ProjectileCrashFlak(static_cast<int>(xLoc + nOffSet - 30), static_cast<int>(yLoc+8), -45, -45, .5);
					(*projectile_list).push_back(temp);
				}
			}
			break;

		case 7:
			{
				Projectile *temp;
				
				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileCrashExplosion(static_cast<int>(xLoc + nOffSet - 18), static_cast<int>(yLoc+15), .4f);
					(*projectile_list).push_back(temp);
				}
				else
				{
					temp = new ProjectileCrashExplosion(static_cast<int>(xLoc + nOffSet + 9), static_cast<int>(yLoc+15), .4f);
					(*projectile_list).push_back(temp);
				}

				SetAnimation(ENEMY_CRASH_ANIM_JUMP, 0, true, true, 15 , true);
				jumpTimer = .5;
				S_TIMER = true;
			}
			break;

		case 8:
			{
				Projectile *temp;
				
				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileCrashExplosion(static_cast<int>(xLoc + nOffSet - 18), static_cast<int>(yLoc+15), .4f);
					(*projectile_list).push_back(temp);
				}
				else
				{
					temp = new ProjectileCrashExplosion(static_cast<int>(xLoc + nOffSet + 9), static_cast<int>(yLoc+15), .4f);
					(*projectile_list).push_back(temp);
				}

				SetAnimation(ENEMY_CRASH_ANIM_JUMP, 0, true, true, 15 , true);
				jumpTimer = .5;
				S_TIMER = true;
			}
			break;

		case 9:
			ipFlags.S_INVULNERABLE = true;
			ipFlags.fInvulnerableTimer = 8;
//				SetAnimation(ENEMY_CRASH_ANIM_INTRO, 0, true, true, 10, true);
			break;

		default:

			break;
		}
	}
}

void EnemyCrash::processDamage()
{
//	soundPlayer->PlaySound(damage00);
}

void EnemyCrash::processDeath()
{
	StopMovement();

	SetAnimation(ENEMY_CRASH_ANIM_DEATH, 0, true, true, 5, true);
}

void EnemyCrash::stop()
{
	if(!ipFlags.S_JUMP)
	{
		//Stop All Movement
		velMovement = 0;

		//Reset Animation
		if(ipFlags.PrevMState != move_stop)	SetAnimation(ENEMY_CRASH_ANIM_STAND, 0, false, false, 15, true);
		else SetAnimation(ENEMY_CRASH_ANIM_STAND, 0, false, false, 15, false);
	}
}

void EnemyCrash::processUpdate()
{
	if((introtimer > 0) && ipFlags.S_ATTACK)
	{
		introtimer -= time;

		if(introtimer <= 0)
		{
			SetAnimation(ENEMY_CRASH_ANIM_INTRO, 0, true, true, 10, true);
		}
	}
	else if((player_spr->GetFrameSet() == ENEMY_CRASH_ANIM_INTRO) && !player_spr->IsAnimating())
		ipFlags.S_INVULNERABLE = false;

	if(ipFlags.S_ATTACK && S_TIMER)
	{
		if(ipFlags.nCurrAttack == 7)
		{
			jumpTimer -= time;

			if(jumpTimer < 0)
			{
				if(ipFlags.S_DIRECTION) velModifier = 130;
				else velModifier = -130;

				ipFlags.S_ON_GROUND = false;	
				ipFlags.S_NO_GRAVITY = false;
				ipFlags.S_JUMP = true;
	
				yLoc -= 1;

				velYModifier = 0;
				velYJumpModifier = -250;

			
				S_TIMER = false;
			}
		}
		else if(ipFlags.nCurrAttack == 8)
		{
			jumpTimer -= time;

			if(jumpTimer < 0)
			{
				StopMovement();
				velModifier = 0;

				ipFlags.S_ON_GROUND = false;	
				ipFlags.S_NO_GRAVITY = false;
				ipFlags.S_JUMP = true;
	
				yLoc -= 1;

				velYModifier = 0;
				velYJumpModifier = -500;

				S_TIMER = false;
			}
		}
	}

	if((player_spr->GetFrameSet() == ENEMY_CRASH_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	if(ipFlags.S_ATTACK && !S_TIMER)
	{
		//else
		if(!player_spr->IsAnimating() && !ipFlags.S_JUMP)
		 ipFlags.S_ATTACK = false;
	}

	// Apply Velocity Modifier
//	if(!ipFlags.S_DAMAGED)
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

	/* Center (0,0), offset by Render Offset */
	if(ipFlags.nCurrAttack != 8)
	{
		rectDX = 15;
		rectDY = 45;
		rectXOffset = -nOffSet;
		rectYOffset = -15;

//		SetRectangle(rectWorldLoc, 15, 45, -nOffSet, -15);
	}
	else if(!S_TIMER)
	{
		float x, y;
		GetVelocityVector(&x, &y);

		if(y < 0)
		{
			rectDX = 0;
			rectDY = 0;
			rectXOffset = -999;
			rectYOffset = -999;
		//	SetRectangle(rectWorldLoc, 0, 0, -999, -999);
		}
		else
		{
			rectDX = 15;
			rectDY = 45;
			rectXOffset = -nOffSet;
			rectYOffset = -15;

			//SetRectangle(rectWorldLoc, 15, 45, -nOffSet, -15);
		}
	}
}
