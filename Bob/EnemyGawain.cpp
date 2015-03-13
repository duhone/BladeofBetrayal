// EnemyGawain.cpp: implementation of the EnemyGawain class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyGawain.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyGawain::EnemyGawain(Level *curLevel, vector<Enemy*> *enemys, AIEngine* ai_engine, IPlayer *player)
{
	InitEnemy(enemy_mr_thomas_set_cur_life * 2.5, 
		      base_x_velocity * 1.33,
			  base_y_velocity * 1.33,
			  0,
			  .25,
			  0,
			  true);

	jumpMaxVelocity = -100;

//	SetCurLife(enemy_blue_ninja_set_cur_life);
//	SetNumLifeBars((int)(enemy_blue_ninja_set_cur_life * .2f + 1));

//	SetSprite(1, enemy_blue_ninja_sprite);
	level_class = curLevel;

//	SetDamageTimer(.25);

	SetRenderOffset(3);

	this->enemys = enemys;
	this->ai_engine = ai_engine;

	this->player = player;

	SetMaxAttacks(10);

	MaxPixelDisplacement = 200;

	S_TELEPORT = false;
//	SetPointValue(P_ENEMY_BLUE_NINJA);

	rectDX = 15;
	rectDY = 50;
	rectXOffset = -nOffSet;
	rectYOffset = -14;
	SetWeaponDamage(8);
}

EnemyGawain::~EnemyGawain()
{
}

/*HPTRect &EnemyGawain::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyGawain::GetWeaponWorldLoc()
{
	switch(player_spr->GetFrameSet())
	{
	case ENEMY_GAWAIN_ANIM_ATTACK_1:
		if(player_spr->GetFrame() == 3)
			SetRectangle(rectWeaponWorldLoc, 35, 3, 0, 5);
		break;
	default:
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);
		break;
	}


	return rectWeaponWorldLoc;
}

void EnemyGawain::setJumpVelocity()
{
//	soundPlayer->PlaySound(jump00);

	if(ipFlags.S_DIRECTION) velModifier = -100;
	else velModifier = 100;

	ipFlags.S_ON_GROUND = false;
	ipFlags.S_NO_GRAVITY = false;
	ipFlags.S_JUMP = true;
	
	yLoc -= 1;

	velYModifier = 0;
	velYJumpModifier = jumpMaxVelocity;

	SetAnimation(ENEMY_GAWAIN_ANIM_JUMP_1, 0, true, true, 8, true);
}

void EnemyGawain::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
//	if(!((player_spr->GetFrameSet() == ENEMY_GAWAIN_ANIM_TELEPORT_2) && !player_spr->IsAnimating()))
		if(ipFlags.PrevMState != move_left)
			SetAnimation(ENEMY_GAWAIN_ANIM_WALK, 0, true, false, 22, true);
		else 
			SetAnimation(ENEMY_GAWAIN_ANIM_WALK, 0, true, false, 22, false);

	velMovement = -maxWalkSpeed;

	if(S_TELEPORT)
		velMovement *= 4;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyGawain::processRight()
{
	//If Not Previously Moving Right - Reset Animation
//	if(!((player_spr->GetFrameSet() == ENEMY_GAWAIN_ANIM_TELEPORT_2) && !player_spr->IsAnimating()))

	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_GAWAIN_ANIM_WALK, 0, true, false, 22, true);
	else 
		SetAnimation(ENEMY_GAWAIN_ANIM_WALK, 0, true, false, 22, false);

	velMovement = maxWalkSpeed;

	if(S_TELEPORT)
		velMovement *= 4;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyGawain::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{
		
		case 0:
			ipFlags.S_INVULNERABLE = true;
			ipFlags.fInvulnerableTimer = 8;

	//		if(!SetAnimation(ENEMY_GAWAIN_ANIM_TELEPORT_1, 0, true, true, 10, true))
	//		{
//				ipFlags.S_INVULNERABLE = true;
	//			ipFlags.fInvulnerableTimer = 6;
//				soundPlayer->PlaySound(phase00);

//				StopMovement();
	//		}
			break;
			
		case 1:
			if(!SetAnimation(ENEMY_GAWAIN_ANIM_ATTACK_1, 0, true, true, 15, true))
			{
//				if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swing00);
				StopMovement();
			}
			break;

		case 2:
			if(!SetAnimation(ENEMY_GAWAIN_ANIM_ATTACK_2, 0, true, true, 15, true))
			{
//				if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
				StopMovement();

//				soundPlayer->PlaySound(sparks);
				Projectile *temp;

				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileGroundWave(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 15), static_cast<int>(yLoc + 28));
					
				}
				else 
				{
					temp = new ProjectileGroundWave(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 15), static_cast<int>(yLoc + 28));
					
				}
				
				(*projectile_list).push_back(temp);
			}
			break;

		case 3:
			if(!SetAnimation(ENEMY_GAWAIN_ANIM_ATTACK_3, 0, true, true, 4, true))
			{

				int i = rand()%2;

				if(i == 0)
				{
					if(ipFlags.S_DIRECTION)
					{
						//soundPlayer->PlaySound(crow);

						Enemy *enemy;
						enemy = new EnemyBirdGawain(level_class, player);
						enemy->SetProjectileList(projectile_list);
						enemy->SetWorldLocAbsoluteT(1,GetYTilePos() - 5);
						enemy->setGravityConstant(500.0f);
						enemy->SetSprite(1, CR::AssetList::Green_bird);
						ai_engine->AddAI(enemy,enemy, eGreenNinja);
						enemys->push_back(enemy);
					}
					else
					{
						//soundPlayer->PlaySound(crow);

						Enemy *enemy;
						enemy = new EnemyBirdGawain(level_class, player);
						enemy->SetProjectileList(projectile_list);
						enemy->SetWorldLocAbsoluteT(23,GetYTilePos() - 5);
						enemy->setGravityConstant(500.0f);
						enemy->SetSprite(1, CR::AssetList::Green_bird);
						ai_engine->AddAI(enemy,enemy, eGreenNinja);
						enemys->push_back(enemy);
					}
				}
				else
				{
					if(ipFlags.S_DIRECTION)
					{
//						soundPlayer->PlaySound(growl00);

						Enemy *enemy;
						enemy = new EnemyWolfGawain(level_class, player);
						enemy->SetProjectileList(projectile_list);
						enemy->SetWorldLocAbsoluteT(5,17, 0, -5);
						enemy->setGravityConstant(500.0f);
						enemy->SetSprite(1, CR::AssetList::Grey_wolf);
						ai_engine->AddAI(enemy,enemy, eGreenNinja);
						enemys->push_back(enemy);
					}
					else
					{
//						soundPlayer->PlaySound(growl00);

						Enemy *enemy;
						enemy = new EnemyWolfGawain(level_class, player);
						enemy->SetProjectileList(projectile_list);
						enemy->SetWorldLocAbsoluteT(19,17, 0, -5);
						enemy->setGravityConstant(500.0f);
						enemy->SetSprite(1, CR::AssetList::Grey_wolf);
						ai_engine->AddAI(enemy,enemy, eGreenNinja);
						enemys->push_back(enemy);
					}
				}


				StopMovement();
			}
			break;

		case 4:
//				soundPlayer->PlaySound(phase00);
			ipFlags.S_INVULNERABLE = true;
			ipFlags.fInvulnerableTimer = 9999.0;
			SetAnimation(ENEMY_GAWAIN_ANIM_TELEPORT_2, 0, true, true, 22, true);
			StopMovement();
			break;

		case 5:
			S_TELEPORT = false;
			SetAnimation(ENEMY_GAWAIN_ANIM_TELEPORT_3, 0, true, true, 22, true);
			ipFlags.S_INVULNERABLE = false;
			ipFlags.fInvulnerableTimer = 0.0;
			ipFlags.S_VISIBLE = true;
			StopMovement();
			break;

		case 6:

			SetAnimation(ENEMY_GAWAIN_ANIM_ATTACK_3, 0, true, true, 4, true);

			if(ipFlags.S_DIRECTION)
			{
				//soundPlayer->PlaySound(crow);

				Enemy *enemy;
				enemy = new EnemyBirdGawain(level_class, player);
				enemy->SetProjectileList(projectile_list);
				enemy->SetWorldLocAbsoluteT(1,GetYTilePos() - 5);
				enemy->setGravityConstant(500.0f);
				enemy->SetSprite(1, CR::AssetList::Green_bird);
				ai_engine->AddAI(enemy,enemy, eGreenNinja);
				enemys->push_back(enemy);
			}
			else
			{
				//soundPlayer->PlaySound(crow);

				Enemy *enemy;
				enemy = new EnemyBirdGawain(level_class, player);
				enemy->SetProjectileList(projectile_list);
				enemy->SetWorldLocAbsoluteT(23,GetYTilePos() - 5);
				enemy->setGravityConstant(500.0f);
				enemy->SetSprite(1, CR::AssetList::Green_bird);
				ai_engine->AddAI(enemy,enemy, eGreenNinja);
				enemys->push_back(enemy);
			}
			break;

		default:

			break;
		}
	}
}

void EnemyGawain::processDamage()
{
}

void EnemyGawain::processDeath()
{
	StopMovement();

	SetAnimation(ENEMY_GAWAIN_ANIM_DEATH, 0, true, true, 5, true);
}

void EnemyGawain::stop()
{
	if(!ipFlags.S_JUMP)
	{

	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)	SetAnimation(ENEMY_GAWAIN_ANIM_STAND, 0, false, false, 15, true);
	else SetAnimation(ENEMY_GAWAIN_ANIM_STAND, 0, false, false, 15, false);
	}
}

void EnemyGawain::processUpdate()
{
	if((introtimer > 0) && ipFlags.S_ATTACK)
	{
		introtimer -= time;

		if(introtimer <= 0)
		{
			SetAnimation(ENEMY_GAWAIN_ANIM_TELEPORT_1, 0, true, true, 10, true);
		}
	}
	else if((player_spr->GetFrameSet() == ENEMY_GAWAIN_ANIM_TELEPORT_1) && !player_spr->IsAnimating() && ipFlags.S_ATTACK)
		ipFlags.S_INVULNERABLE = false;

	if((player_spr->GetFrameSet() == ENEMY_GAWAIN_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	if(ipFlags.S_ATTACK)
	{
		if((player_spr->GetFrameSet() == ENEMY_GAWAIN_ANIM_TELEPORT_2) && !player_spr->IsAnimating())
		{
			ipFlags.S_VISIBLE = false;
			S_TELEPORT = true;
		}

//		{
//			if(ipFlags.
//			xLoc += xLoc - 30
//			SetAnimation(ENEMY_GAWAIN_ANIM_TELEPORT_3, 0, true, true, 10, false);
//		}
		//else
		if(!player_spr->IsAnimating())
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
}
