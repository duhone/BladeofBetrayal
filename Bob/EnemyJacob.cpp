// EnemyJacob.cpp: implementation of the EnemyJacob class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyJacob.h"
#include "AssetList.h"
#include "ProjectileGroundWave.h"
#include <algorithm>
#include <functional>
#include "../Engines/Utility/FunctionObjects.h"
using namespace CR::Sound;

using namespace CR;
using namespace std;
using namespace CR::Utility;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyJacob::EnemyJacob(Level *curLevel, Player *player) : m_superJumping(false)
{
	m_attackWhenDamaged = true;
	/*InitEnemy(enemy_mr_thomas_set_cur_life * 4.75, 
		      base_x_velocity * .90,
			  base_y_velocity * 1.33,
			  0,
			  .25,
			  0,
			  true);*/
	
	SetCurLife(enemy_mr_thomas_set_cur_life*3);
	SetNumLifeBars(enemy_mr_thomas_set_cur_life_bars*3);
	
	//jumpMaxVelocity = -200;
	level_class = curLevel;
	SetMaxAttacks(10);
	SetRenderOffset(0, 10);
	this->player = player;
	//resetDelay = 0;	
	
	maxWalkSpeed = 60.00;   
	
	rectDX = 30;
	rectDY = 60;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	ipFlags.S_DIRECTION = false;
	//S_START = false;
	
	
	/*const int jacob_idle = 273;
	const int jacob_intro = 274;
	const int jacob_flame = 275;
	const int jacob_grab = 276;
	const int jacob_ground = 277;
	const int jacob_ground_idle = 278;
	const int jacob_jump = 279;
	const int jacob_walk = 280;
	const int jacob_quake = 281;
	const int jacob_standard = 282;
	const int jacob_stomp = 283;*/
	
	for(int i = AssetList::jacob_idle;i <= AssetList::jacob_stomp;++i)
	{
		m_sprites.push_back(graphics_engine->CreateSprite1(true));
		m_sprites.back()->SetImage(i);
	}
	
	if(player_spr != 0)
		player_spr->Release();
	player_spr = m_sprites[INTRO];
	
	healthBar = new MeterBar(Red);
	healthBar->SetPosition(166, 10);
	bossIcon = graphics_engine->CreateSprite1();
	bossIcon->SetImage(CR::AssetList::boss_icon);
	bossIcon->SetPositionAbsalute(156, 10);
		
	ipFlags.S_ALWAYS_ATTACK = true;
		
	for(int i = 0;i < 20;++i)
	{
		Rain temp;
		temp.m_sprites.push_back(graphics_engine->CreateSprite1(true));
		temp.m_sprites.back()->SetImage(AssetList::rain);
		temp.m_sprites.back()->SetFrameRate(15);
		temp.m_sprites.push_back(graphics_engine->CreateSprite1(true));
		temp.m_sprites.back()->SetImage(AssetList::rain2);
		temp.m_sprites.back()->SetFrameRate(15);		
		temp.m_sprites.push_back(graphics_engine->CreateSprite1(true));
		temp.m_sprites.back()->SetImage(AssetList::rain3);
		temp.m_sprites.back()->SetFrameRate(15);
		
		temp.m_delay = (rand()&100)/100.0f;
		temp.m_currentSprite = -1;
		
		if(i < 5)
		{
			temp.m_y = 264;
		}
		else if(i >= 15)
		{
			temp.m_y = 216;
		}
		else
		{
			temp.m_y = 408;
		}
		m_rain.push_back(temp);
	}
	
	m_thunder = graphics_engine->CreateSprite1();
	m_thunder->SetImage(AssetList::thunder);
	m_thunder->SetPositionAbsalute(240, 160);
	m_thunderDelay = (rand()%100)*0.01f+4;
	m_thundering = false;
	
	m_swingSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::swing::ID);
	m_shockSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::shock::ID);
	m_flameSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::flame::ID);
	m_waveSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::wave::ID);
	m_quakeSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::quake::ID);
	m_explodeSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::explode00::ID);
	m_jumpSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::jump::ID);
	m_thunderSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::thunder::ID);
}

EnemyJacob::~EnemyJacob()
{	
	for(int i = 0;i < m_rain.size();++i)
	{
		m_rain[i].m_sprites[0]->Release();
		m_rain[i].m_sprites[1]->Release();
		m_rain[i].m_sprites[2]->Release();
	}
	m_thunder->Release();
	delete healthBar;
	bossIcon->Release();
}

void EnemyJacob::Render()
{
	Enemy::Render();
	
	float viewx,viewy;
	player->getViewTransform(&viewx, &viewy);
	
	for(int i = 0;i < m_rain.size();++i)
	{
		if(m_rain[i].m_currentSprite == -1)
		{
			m_rain[i].m_delay -= time;
			if(m_rain[i].m_delay <= 0)
			{
				m_rain[i].m_x = (i*3*16+(rand()%(3*16)));
				m_rain[i].m_currentSprite = rand()%3;
				m_rain[i].m_sprites[m_rain[i].m_currentSprite]->SetFrame(0);
				m_rain[i].m_sprites[m_rain[i].m_currentSprite]->SetAutoAnimate(true);
				m_rain[i].m_sprites[m_rain[i].m_currentSprite]->AutoStopAnimate();
				m_rain[i].m_sprites[m_rain[i].m_currentSprite]->SetPositionAbsalute(m_rain[i].m_x+viewx,m_rain[i].m_y+viewy);
				m_rain[i].m_sprites[m_rain[i].m_currentSprite]->Render();

			}
		}
		else
		{
			m_rain[i].m_sprites[m_rain[i].m_currentSprite]->SetPositionAbsalute(m_rain[i].m_x+viewx,m_rain[i].m_y+viewy);
			m_rain[i].m_sprites[m_rain[i].m_currentSprite]->Render();

			if(!m_rain[i].m_sprites[m_rain[i].m_currentSprite]->IsAnimating())
			{
				m_rain[i].m_currentSprite = -1;
				if(i < 5 || i >= 15)
					m_rain[i].m_delay = (rand()&100)/100.0f;
				else
					m_rain[i].m_delay = (rand()&100)*0.001f;
			}
		}
		
	}
	
	m_thunderDelay -= time;
	if(m_thundering)
	{
		if(rand()%5 == 0)
			m_thunder->Render();
		if(m_thunderDelay <= 0)
		{
			m_thundering = false;
			m_thunderDelay = (rand()%100)*0.10f+7;
		}
	}
	else
	{
		if(m_thunderDelay <= 0)
		{
			m_thundering = true;
			m_thunderDelay = (rand()%100)*0.005f+0.5f;
			m_thunderSound->Play();
//			soundPlayer->PlaySound(thunder);
		}		
	}
	//ForEach(m_rain, mem_fun(&HPTSprite1::Render));
}

/*HPTRect &EnemyJacob::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyJacob::GetWeaponWorldLoc()
{
	/*if((player_spr->GetFrameSet() == ENEMY_JACOB_ANIM_ATTACK_0) && (player_spr->GetFrame() == 2))	
	{
		SetWeaponDamage(10);
		SetRectangle(rectWeaponWorldLoc, 25, 4, 0, 0);
	}
	else if((player_spr->GetFrameSet() == ENEMY_JACOB_ANIM_ATTACK_0) && (player_spr->GetFrame() == 3))	
	{
		SetWeaponDamage(10);
		SetRectangle(rectWeaponWorldLoc, 50, 4, 0, 0);
	}
	else*/
	if(player_spr == m_sprites[FLAME])
		SetRectangle(rectWeaponWorldLoc, 50, 50, -25, 0);
	else if(player_spr == m_sprites[STANDARD])
		SetRectangle(rectWeaponWorldLoc, 50, 10, 0, 0);
	else if(player_spr == m_sprites[STOMP])
		SetRectangle(rectWeaponWorldLoc, 40, 40, -25, 0);
	else if(player_spr == m_sprites[GRAB])
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);
	else
		SetRectangle(rectWeaponWorldLoc, 20, 40, -10, 0);


	return rectWeaponWorldLoc;
}

void EnemyJacob::processLeft()
{
	if(ipFlags.S_DEAD || player_spr == m_sprites[GRAB])
		return;
	player_spr = m_sprites[WALK];
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)	SetAnimation(0, 0, true, false, 13, true);
	else SetAnimation(0, 0, true, false, 13, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyJacob::processRight()
{
	if(ipFlags.S_DEAD || player_spr == m_sprites[GRAB])
		return;
	player_spr = m_sprites[WALK];
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right) SetAnimation(0, 0, true, false, 13, true);
	else SetAnimation(0, 0, true, false, 13, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyJacob::processAttack()
{
	if(ipFlags.S_DEAD || player_spr == m_sprites[GRAB])
		return;
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;
		m_drop = false;
		//ipFlags.nCurrAttack = 9;
		switch(ipFlags.nCurrAttack)
		{
			Projectile *temp;
		
		case 0:
			{				
				ipFlags.S_ATTACK = true;
				
				StopMovement();
				player_spr = m_sprites[INTRO];
				SetAnimation(0, 0, true, true, 12, true);
				//				SetAnimation(ENEMY_JACOB_ANIM_INTRO, 0, true, true, 8, true);
	//			StopMovement();
			}
			break;

		case 1:
			{
				ipFlags.S_ATTACK = true;
				m_swingSound->Play();
//				soundPlayer->PlaySound(swing00);
				
				StopMovement();
				player_spr = m_sprites[STANDARD];
				SetAnimation(0, 0, true, true, 15, true);
				
				SetWeaponDamage(6);
			}
			break;

		case 2:
			{
//				sound_processor->PlaySound(game_sounds->explode00);
//				sound_processor->PlaySound(game_sounds->explode02);
				
				ipFlags.S_ATTACK = true;
				m_swingSound->Play();
//				soundPlayer->PlaySound(swoosh00);
				
				StopMovement();
				player_spr = m_sprites[STOMP];
				SetAnimation(0, 0, true, true, 10, true);
				
				SetWeaponDamage(2);
				m_groundWaves = 0;
			}
			break;

		case 3:
			{
//				sound_processor->PlaySound(game_sounds->sparks);
				
				ipFlags.S_ATTACK = true;
				m_swingSound->Play();
				//soundPlayer->PlaySound(swoosh00);
				
				StopMovement();
				player_spr = m_sprites[QUAKE];
				SetAnimation(0, 0, true, true, 15, true);
				
				SetWeaponDamage(2);	
				m_quakeTime = 0;
				m_quakeStart = false;
				m_stoneDropTime = 0;
				m_stoneLeft = (rand()%2) == 0;
				
			}
			break;

		case 4:
			{
				ipFlags.S_ATTACK = true;
				m_jumpSound->Play();
//				soundPlayer->PlaySound(jump00);
				
				StopMovement();
				player_spr = m_sprites[JUMP];
				SetAnimation(0, 0, true, true, 8, true);
				
				SetWeaponDamage(2);
				ipFlags.S_ON_GROUND = false;
				ipFlags.S_NO_GRAVITY = true;				
				m_jumpStart.Set(xLoc,yLoc);
				m_totalJumpTime = 0.75f;
				m_jumpTime = 0;
				m_drop = false;
			}
			break;

		case 5:
			{
//				sound_processor->PlaySound(game_sounds->quake);	
//				sound_processor->PlaySound(game_sounds->explode01);
//				sound_processor->PlaySound(game_sounds->explode02);
//				sound_processor->PlaySound(game_sounds->explode00);

				ipFlags.S_ATTACK = true;
				m_flameSound->Play();
//				soundPlayer->PlaySound(flame);
				
				StopMovement();
				player_spr = m_sprites[FLAME];
				SetAnimation(0, 0, true, true, 15, true);
				
				SetWeaponDamage(8);
				
				Projectile *temp;
				
				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileJacobFlameBall(true, static_cast<int>(xLoc), static_cast<int>(yLoc - 50), 0, -75, 0, .9f);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileJacobFlameBall(false, static_cast<int>(xLoc + 15), static_cast<int>(yLoc - 53), 25, -50, 4, .8f);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileJacobFlameBall(false, static_cast<int>(xLoc + 30), static_cast<int>(yLoc - 35), 50, -50, 1, .7f);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileJacobFlameBall(false, static_cast<int>(xLoc + 45), static_cast<int>(yLoc - 10), 50, -25, 3, .6f);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileJacobFlameBall(false, static_cast<int>(xLoc + 40), static_cast<int>(yLoc + 15), 50, 0, 2, .5f);
					
					(*projectile_list).push_back(temp);
				}
				else
				{
					temp = new ProjectileJacobFlameBall(false, static_cast<int>(xLoc), static_cast<int>(yLoc - 50), 0, -75, 0, .9f);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileJacobFlameBall(true, static_cast<int>(xLoc - 15), static_cast<int>(yLoc - 53), -25, -50, 4, .8f);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileJacobFlameBall(true, static_cast<int>(xLoc - 30), static_cast<int>(yLoc - 35), -50, -50, 1, .7f);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileJacobFlameBall(true, static_cast<int>(xLoc - 45), static_cast<int>(yLoc - 10), -50, -25, 3, .6f);
					
					(*projectile_list).push_back(temp);
					temp = new ProjectileJacobFlameBall(true, static_cast<int>(xLoc - 40), static_cast<int>(yLoc + 15), -50, 0, 2, .5f);
					
					(*projectile_list).push_back(temp);
				}
				
			}
			break;

		/* forward jump */
		case 6:
			{

//				sound_processor->PlaySound(game_sounds->jump00);

				
				ipFlags.S_PROCESS_DEATH = true;
				StopMovement();
				 player->ipFlags.S_FINAL_ANIM = true;
				 player->S_JACOB_INVIS = true;
				
				 player_spr = m_sprites[GRAB];
				 //				sound_processor->PlaySound(game_sounds->quake);	
				 SetAnimation(0, 0, true, true, 2, true);
			}
			break;

			/* rear jump */
		case 7:
			{
//				sound_processor->PlaySound(game_sounds->jump00);

				if(ipFlags.S_DIRECTION) velModifier = -130;
				else velModifier = 130;

				ipFlags.S_ON_GROUND = false;
				ipFlags.S_ON_LADDER = false;
				ipFlags.S_NEXT_TO_LADDER = false;
				ipFlags.S_NO_GRAVITY = false;
				ipFlags.S_JUMP = true;
		
				yLoc -= 1;

				ipFlags.S_CROUCH = false;
				ipFlags.S_CRAWL = false;
				ipFlags.S_CROUCH_TOGGLE = false;

				velYModifier = 0;
				velYJumpModifier = jumpMaxVelocity;
	
				SetAnimation(0, 0, true, true, 12, true);
			}
			break;

		case 8:
			{
				//player->ipFlags.S_FINAL_ANIM = true;
//				sound_processor->PlaySound(game_sounds->quake);	
				m_quakeSound->Play();
				SetAnimation(0, 0, true, true, 8, true);
				
				temp = new ProjectileJacobRockQuake(&player->xQuakeAttackModifier, &player->yQuakeAttackModifier,static_cast<int>(player->xLoc), static_cast<int>(player->yLoc),player->projectile_list, &player->xLoc, &player->yLoc,&player->ipFlags);
				
				(*projectile_list).push_back(temp);


				if(ipFlags.S_DIRECTION)
				{
					temp = new ProjectileJacobStone(ipFlags.S_DIRECTION, static_cast<int>(xLoc + 25), static_cast<int>(yLoc + 30), 120, -180, 0, 100, .25);
					
				}
				else
				{
					temp = new ProjectileJacobStone(ipFlags.S_DIRECTION, static_cast<int>(xLoc - 25), static_cast<int>(yLoc + 30), -120, -180, 0, 100, .25);
					
				}
				
				(*projectile_list).push_back(temp);

				StopMovement();
			}
			break;

		case 9:
			{
				StopMovement();
				player->ipFlags.S_FINAL_ANIM = true;
//				sound_processor->PlaySound(game_sounds->quake);	
				SetAnimation(0, 0, true, true, 2, true);
			}
			break;
		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyJacob::processDamage()
{
//	ipFlags.S_ATTACK = false;

}

void EnemyJacob::processDown()
{
	if(!ipFlags.S_CROUCH)
		SetAnimation(0, 0, true, true, 10, true);

	ipFlags.S_CROUCH = true;
}

void EnemyJacob::processUp()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)	SetAnimation(0, 0, false, false, 15, true);
	else SetAnimation(0, 0, false, false, 15, false);

	ipFlags.S_CROUCH = false;
}

void EnemyJacob::processDeath()
{
	ipFlags.S_DAMAGED = false;
	ipFlags.S_ATTACK = false;
	ipFlags.S_DEAD = false;
	ipFlags.S_FINAL_ANIM = true;
	ipFlags.S_PROCESS_DEATH = false;
	
	player->ipFlags.CurMState = move_stop;
	player->ipFlags.S_FREEZE_INPUT = true;
	//player->setGravityConstant(0);
	this->nCurLife = 1;
	
	moveStop();
	/*StopMovement();
	player->ipFlags.S_FINAL_ANIM = true;
	
	player_spr = m_sprites[GRAB];
	//				sound_processor->PlaySound(game_sounds->quake);	
	SetAnimation(0, 0, true, true, 2, true);*/
}

void EnemyJacob::stop()
{
	if(ipFlags.S_DEAD || player_spr == m_sprites[GRAB])
		return;
	StopMovement();
	
	if(player_spr != m_sprites[INTRO])
	{
		if(!m_drop)
		{
			player_spr = m_sprites[IDLE];
			//Reset Animation
			if(ipFlags.PrevMState != move_stop)	SetAnimation(0, 0, true, false, 15, true);
			else SetAnimation(0, 0, true, false, 15, false);
		}
		else
		{
			player_spr = m_sprites[GROUND_IDLE];
			//Reset Animation
			if(ipFlags.PrevMState != move_stop)	SetAnimation(0, 0, true, false, 3, true);
			else SetAnimation(0, 0, true, false, 3, false);
		}
		
	}
	
	//Reset Animation
//	//if(ipFlags.PrevMState != move_stop)	SetAnimation(ENEMY_JACOB_ANIM_WALK, 0, false, false, 15, true);
//	else SetAnimation(ENEMY_JACOB_ANIM_WALK, 0, false, false, 15, false);
}

void EnemyJacob::processUpdate()
{
	if(ipFlags.S_DEAD)
		return;
	/*if((introtimer > 0) && ipFlags.S_ATTACK)
	{
		introtimer -= time;

		if(introtimer <= 0)
		{
			S_START = true;
			SetAnimation(0, 0, true, true, 10, true);
		}
	}
	else if((player_spr->GetFrameSet() == 0) && !player_spr->IsAnimating() && ipFlags.S_ATTACK && S_START)
		ipFlags.S_INVULNERABLE = false;*/

	
	//		if(player_spr->GetFrameSet() == ENEMY_JACOB_ANIM_QUAKE_ATTACK)
//	{
	//	if(S_SHAKE)
	//	{
	//		int temp = rand()%100;
	//		shake += .05;
	//		if(shake > 15)
	//			S_SHAKE = false;
	//	}
	//	else
	//	{
//			int temp = rand()%100;
//			shake -= .05;
	//		if(shake <= 1)
	//		{
	//		//	ipFlags->S_ATTACK = false;
	//			DeActivate();
	//			return;
	//		}
	//	}
//		player->xQuakeAttackModifier= rand()%(static_cast<int>(shake))-(shake*.5);
//		player->yQuakeAttackModifier= rand()%(static_cast<int>(shake))-(shake*.5);
//	}
//	else
//	{
//		shake = 10;
//	}
		
	if(player_spr == m_sprites[IDLE])
		SetRenderOffset(0, 14);
	if(player_spr == m_sprites[INTRO])
		SetRenderOffset(0, 10);
	if(player_spr == m_sprites[FLAME])
		SetRenderOffset(0, 0);
	if(player_spr == m_sprites[GRAB])
		SetRenderOffset(0, 14);
	if(player_spr == m_sprites[GROUND])
		SetRenderOffset(0, 22);
	if(player_spr == m_sprites[GROUND_IDLE])
		SetRenderOffset(0, 22);
	if(player_spr == m_sprites[JUMP])
		SetRenderOffset(0, 14);
	if(player_spr == m_sprites[WALK])
		SetRenderOffset(0, 14);
	if(player_spr == m_sprites[QUAKE])
		SetRenderOffset(0, 2);
	if(player_spr == m_sprites[STANDARD])
		SetRenderOffset(15, 14);
	if(player_spr == m_sprites[STOMP])
		SetRenderOffset(0, 14);
	
	bool lowHealth = false;
	if(GetCurLife() < enemy_mr_thomas_set_cur_life*4.75*0.3)
	{
		lowHealth = true;
		
		maxWalkSpeed = 60.0f*1.25f; 
	}
	if(ipFlags.S_FINAL_ANIM)
	{
		player->ipFlags.CurMState = move_stop;
		player->stop();
	}
	if((player_spr == m_sprites[GRAB]))
	{
		if(!player_spr->IsAnimating())
		{
			//player->S_JACOB_INVIS = false;
			//player->ipFlags.S_FINAL_ANIM = false;
			Die();
		}
		return;
	}
	
	if(m_superJumping)
	{
		m_jumpTime += time;
		if(m_jumpTime > m_totalJumpTime)
		{
			xLoc = m_jumpTarget.x;
			yLoc = m_jumpTarget.y;
			ipFlags.S_ON_GROUND = true;
			ipFlags.S_NO_GRAVITY = false;
			m_superJumping = false;
			ipFlags.S_ALWAYS_ATTACK = true;
			if(player_spr != m_sprites[GRAB])
			{
				player_spr = m_sprites[IDLE];
				SetAnimation(0, 0, true, false, 15, true);
			}
		}
		else
		{
			float percent = m_jumpTime/m_totalJumpTime;
			xLoc = (m_jumpStart.x + (m_jumpTarget.x-m_jumpStart.x)*percent);
			yLoc = m_jumpStart.y-pow(sin(percent*3.1459),m_jumpXP)*m_jumpHeight;
		}
		return;
	}


	/*if((player_spr->GetFrameSet() == ENEMY_JACOB_ANIM_CROUCH_TRANSITION) && !player_spr->IsAnimating())
	{
		SetAnimation(0, 0, true, false, 5, false);
	}*/

	/*if(ipFlags.S_ATTACK && player_spr->GetFrameSet() == ENEMY_JACOB_ANIM_QUAKE_2)
	{
		if(!player_spr->IsAnimating() )
			if(resetDelay < 0)
			{

				ipFlags.S_INVULNERABLE = false;
				ipFlags.S_ATTACK = false;
				SetAnimation(0, 0, false, false, 15, false);
			}
			else
			{
				
				resetDelay -= time;
			}
	}
	else if(ipFlags.S_ATTACK && player_spr->GetFrameSet() != ENEMY_JACOB_ANIM_INTRO)
	{
		if(!player_spr->IsAnimating())
			ipFlags.S_ATTACK = false;
	}
	else if(player_spr->GetFrameSet() == ENEMY_JACOB_ANIM_INTRO)
		if(!player_spr->IsAnimating())
			if(player_spr->GetFrame() == 10)
				ipFlags.S_ATTACK = false;
*/

	if(ipFlags.S_ATTACK)
	{
		switch (ipFlags.nCurrAttack)
		{
			case 0:
			case 1:
			case 5:
				if(!player_spr->IsAnimating())
				{
					ipFlags.nCurrAttack = 0;
					ipFlags.S_ATTACK = false;
				}
				break;
			case 2:				
				if(!player_spr->IsAnimating())
				{
					StopMovement();
					
//					soundPlayer->PlaySound(explode01);
//					soundPlayer->PlaySound(sparks);
					Projectile *temp;
					
					if(ipFlags.S_DIRECTION)
					{
						temp = new ProjectileGroundWave(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 15), static_cast<int>(yLoc + 36));
						
					}
					else 
					{
						temp = new ProjectileGroundWave(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 15), static_cast<int>(yLoc + 36));
						
					}
					
					(*projectile_list).push_back(temp);
					m_groundWaves++;
					if(!lowHealth || m_groundWaves>=3)
					{
						ipFlags.nCurrAttack = 0;
						ipFlags.S_ATTACK = false;
					}
					else
					{						
						player_spr = m_sprites[STOMP];
						SetAnimation(0, 0, true, true, 10, true);
					}						
				}
				break;				
			case 3:				
				if(!player_spr->IsAnimating())
				{
					if(!m_quakeStart)
					{
						m_quakeSound->Play();
//						soundPlayer->PlaySound(earthquake);
						Projectile *temp;

						temp = new ProjectileJacobRockQuake(&player->xQuakeAttackModifier, &player->yQuakeAttackModifier,static_cast<int>(player->xLoc), static_cast<int>(player->yLoc),player->projectile_list, &player->xLoc, &player->yLoc,&player->ipFlags);
						(*projectile_list).push_back(temp);
						m_quakeStart = true;
					}
					
					m_stoneDropTime += time;
					if(m_stoneDropTime > 0.165f)
					{
						int drop = rand() % 30;
						drop = drop*16+8;
						
						int dropChance = rand() % 101;
						
						if (dropChance > 30)
						{
							Projectile *temp = new ProjectileJacobStone(ipFlags.S_DIRECTION, static_cast<int>(player->GetXLoc()-240+drop), static_cast<int>(player->GetYLoc()-170), 0, 150, 0, 150, 0);
							(*projectile_list).push_back(temp);
						}
						
						m_stoneDropTime = 0;
					}
					
					m_quakeTime += time;
					float totalQuakeTime = 6;
					if(lowHealth)
						totalQuakeTime*=1.5f;
					if(m_quakeTime > totalQuakeTime)
					{
						ipFlags.nCurrAttack = 0;
						ipFlags.S_ATTACK = false;						
					}
				}
				break;
			case 4:
			{
				if(!m_drop)
				{
					m_jumpTime += time;
					float percent = m_jumpTime/m_totalJumpTime;
					xLoc = (m_jumpStart.x + (player->GetXLoc()-m_jumpStart.x)*percent*percent);
					yLoc = (m_jumpStart.y - sqrt(percent)*100);
					
					if(m_jumpTime > m_totalJumpTime)
					{
						m_drop = true;
						ipFlags.S_NO_GRAVITY = false;
						this->setGravityConstant(2000.0f);
						
						player_spr = m_sprites[GROUND];
						SetAnimation(0, 0, true, true, 12, true);
					}
				}
				else
				{
					if(ipFlags.S_ON_GROUND)
					{
						//m_quakeSound->Play();
//						soundPlayer->PlaySound(explode00);
						m_explodeSound->Play();

						player_spr = m_sprites[GROUND_IDLE];
						SetAnimation(0, 0, true, false, 10, true);
						this->setGravityConstant(500.0f);
						ipFlags.S_ATTACK = false;
						
						Projectile *temp;
						
						temp = new ProjectileJacobStone(ipFlags.S_DIRECTION, static_cast<int>(xLoc + 25), static_cast<int>(yLoc + 30), 120, -180, 0, 100, .1);
						(*projectile_list).push_back(temp);
						temp = new ProjectileJacobStone(ipFlags.S_DIRECTION, static_cast<int>(xLoc - 25), static_cast<int>(yLoc + 30), -120, -180, 0, 100, .1);
						(*projectile_list).push_back(temp);
					}
				}
			}
			break;
		};
	}

	// Apply Velocity Modifier
	//if(!ipFlags.S_DAMAGED)
	//{
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

				case move_down:
					processDown();
					break;

				case move_up:
					processUp();
					break;

				default:
					break;
			}
	//}
		
	/* Center (0,0), offset by Render Offset */
//	SetRectangle(rectWorldLoc, 30, 60, -nOffSet, -15);
}

void EnemyJacob::doDamage(int nDamageAmount, bool sDirection,int damage_type)
{
	if(ipFlags.S_FINAL_ANIM) return;
	IPlayer::doDamage(nDamageAmount,sDirection,damage_type);
}

void EnemyJacob::StartJacob()
{
	S_START = false;
	SetAnimation(0, 0, false, false, 8, true);
}
/*
void EnemyJacob::setTime(float time)
{
	IPlayer::time = time;

	if(ipFlags.S_DAMAGED)
	{
		ipFlags.fDmgTimer-=time;

		if(ipFlags.fDmgTimer < 0)
		{
			//bool temp;

			//if(ipFlags.S_CROUCH)
			//	temp = true;
			ipFlags.S_DAMAGED = false;
			if(nCurLife <= 0) ipFlags.S_ATTACK = false;
			//ResetStates();

			//ipFlags.S_CROUCH = temp;

			ipFlags.S_INVULNERABLE = true;
			ipFlags.fInvulnerableTimer = .5;
		}
	}
	else if(ipFlags.S_INVULNERABLE)
	{
		ipFlags.fInvulnerableTimer -= time;

		if(ipFlags.fInvulnerableTimer < 0)
			ipFlags.S_INVULNERABLE = false;
	}
}*/


/*
bool EnemyJacob::TransitionMovement(M_STATE state)
{
	if(ipFlags.ReqIState != input_0 && !ipFlags.S_PROCESS_DEATH)
	{
		ipFlags.PrevMState = ipFlags.CurMState; //Store Previous Movement State
		


		//Transition Movement State
		switch(ipFlags.ReqIState)
		{
		case input_stop:
			if(ipFlags.CurMState == move_left || ipFlags.CurMState == move_right || ipFlags.CurMState == move_up || ipFlags.CurMState == move_down)
			{
				moveStop();
				ipFlags.CurMState = move_stop;
			}
			break;

		case input_left:
			if((ipFlags.CurMState == move_stop || ipFlags.CurMState == move_right))// && !ipFlags.S_ON_LADDER)
			{
				ipFlags.CurMState = move_left;
			}
			break;

		case input_right:
			if((ipFlags.CurMState == move_stop || ipFlags.CurMState == move_left))// && !ipFlags.S_ON_LADDER)
			{
				ipFlags.CurMState = move_right;
			}
			break;

		case input_up:
			if((ipFlags.CurMState == move_stop ||  ipFlags.CurMState == move_down))// && !ipFlags.S_JUMP)
			{
				ipFlags.CurMState = move_up; //Transition State To Move Up
			}
			break;

		case input_down:
			if((ipFlags.CurMState == move_stop ||  ipFlags.CurMState == move_up))// && !ipFlags.S_JUMP)
			{
				ipFlags.CurMState = move_down; //Transition State To Move Down
			}
			break;

		case input_button1: //Special 1 - Reserved Custom Action
			{
				ipFlags.CurMState = move_reserved_action_1;
			}
			break;

		case input_button2: //Special 2 - Reserved Custom Action
			{
				ipFlags.CurMState = move_reserved_action_2;
			}
			break;

		case input_button3:
			if((ipFlags.S_ON_GROUND || ipFlags.S_NEXT_TO_LADDER) && !ipFlags.S_ON_LADDER && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD && !ipFlags.S_JUMP)
			{
				setJumpVelocity();
		//		ipFlags.S_JUMP = true;
		//		ipFlags.S_ON_GROUND = false;
		//		ipFlags.S_CROUCH = false;
			}
			else if((ipFlags.S_ON_GROUND || ipFlags.S_NEXT_TO_LADDER) && ipFlags.S_ON_LADDER && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD && !ipFlags.S_JUMP)
			{
			//	if(ipFlags.S_ON_LADDER && (ipFlags.CurMState == move_left || ipFlags.CurMState == move_right))

				if(!(ipFlags.CurMState == move_up || ipFlags.CurMState == move_down))
					setJumpVelocity();
				
		//		ipFlags.S_JUMP = true;
		//		ipFlags.S_ON_GROUND = false;

			}
			break;

		case input_button4:
			{
				if(!ipFlags.S_ATTACK && !ipFlags.S_ON_LADDER) //Disable Attack During Damaged State
					processAttack();
			}
			break;

		default:
			StopMovement();
			break;
		};
	};

	ipFlags.ReqIState = input_0;

	return true;
 }*/

void EnemyJacob::SuperJump(int _xtile,float _jumpTime,float _exponent,float _height)
{
	if(ipFlags.S_DEAD || player_spr == m_sprites[GRAB])
		return;
	m_jumpSound->Play();
//	soundPlayer->PlaySound(jump00);
	m_jumpTarget.x = _xtile*16; 
	m_jumpTarget.y = yLoc; 
	m_superJumping = true;
	m_jumpTime = 0;
	m_totalJumpTime = _jumpTime;
	if(GetCurLife() < enemy_mr_thomas_set_cur_life*4.75*0.3)
		m_totalJumpTime *= 0.8f;
	m_jumpXP = _exponent;
	m_jumpHeight = _height;
	m_jumpStart.Set(xLoc,yLoc);
	ipFlags.S_ON_GROUND = false;
	ipFlags.S_NO_GRAVITY = true;
	player_spr = m_sprites[JUMP];	
	SetAnimation(0, 0, true, true, 8, true);
	ipFlags.S_ALWAYS_ATTACK = true;
}

void EnemyJacob::RenderHealthBar()
{
	healthBar->SetTotalBars((float)GetNumLifeBars() * 3.0f);
	healthBar->SetPercentFull((float)GetCurLife()/((float)GetNumLifeBars() *5.0f));
	healthBar->Render();
	bossIcon->Render();
}
