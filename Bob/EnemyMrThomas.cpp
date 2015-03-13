// EnemyMrThomas.cpp: implementation of the EnemyMrThomas class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyMrThomas.h"
#include "../Engines/Utility/FunctionObjects.h"
#include "AssetList.h"
#include "ProjectileMrTKnife.h"
#include <functional>

using namespace CR;
using namespace CR::Utility;
using namespace std;
using namespace CR::Sound;

const float EnemyMrThomas::c_totalWaitTime = 2.0f;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyMrThomas::EnemyMrThomas(Level *curLevel)
{
	m_attackWhenDamaged = true;
	SetRenderOffset(0,2);
	SetCurLife(enemy_mr_thomas_set_cur_life * 1.5);
	SetNumLifeBars(enemy_mr_thomas_set_cur_life_bars * 1.5);
	SetPlayerRectangle(15, 55);
	maxWalkSpeed = 30.00;   
	SetDamageTimer(.25);
	level_class = curLevel;
	deathtimer = 2.5;

	rectDX = 14;
	rectDY = 56;
	rectXOffset = -7;
	rectYOffset = -25;
		
	/*m_sprites.push_back(graphics_engine->CreateSprite1(false));
	m_sprites.back()->SetImage(AssetList::MrT_blade_catch);
	m_sprites.push_back(graphics_engine->CreateSprite1(false));
	m_sprites.back()->SetImage(AssetList::MrT_blade_throw);
	m_sprites.push_back(graphics_engine->CreateSprite1(false));
	m_sprites.back()->SetImage(AssetList::MrT_charge_in);
	m_sprites.push_back(graphics_engine->CreateSprite1(false));
	m_sprites.back()->SetImage(AssetList::MrT_charge_loop);
	m_sprites.push_back(graphics_engine->CreateSprite1(true));
	m_sprites.back()->SetImage(AssetList::MrT_death);
	m_sprites.push_back(graphics_engine->CreateSprite1(false));
	m_sprites.back()->SetImage(AssetList::MrT_idle);
	m_sprites.push_back(graphics_engine->CreateSprite1(false));
	m_sprites.back()->SetImage(AssetList::MrT_intro);
	m_sprites.push_back(graphics_engine->CreateSprite1(false));
	m_sprites.back()->SetImage(AssetList::MrT_walk);*/
	
	/*const int MrT_blade_catch = 258;
	const int MrT_blade_throw = 259;
	const int MrT_charge_in = 260;
	const int MrT_charge_loop = 261;
	const int MrT_death = 262;
	const int MrT_idle = 263;
	const int MrT_intro = 264;
	const int MrT_walk = 265;*/
	
	for(int i = AssetList::MrT_blade_catch;i <= AssetList::MrT_walk;++i)
	{
		m_sprites.push_back(graphics_engine->CreateSprite1(true));
		m_sprites.back()->SetImage(i);
	}
	
	if(player_spr != 0)
		player_spr->Release();
	player_spr = m_sprites[TIDLE];
	
	healthBar = new MeterBar(Red);
	healthBar->SetPosition(211, 10);
	bossIcon = graphics_engine->CreateSprite1();
	bossIcon->SetImage(CR::AssetList::boss_icon);
	bossIcon->SetPositionAbsalute(201, 10);
	
	ipFlags.S_ALWAYS_ATTACK = true;
	
	SetWeaponDamage(1); // was 3
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::knifethrow::ID);
	m_soundFXPhase = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::mrtphase::ID);
}

EnemyMrThomas::~EnemyMrThomas()
{
	ForEach(m_sprites,mem_fun(&HPTSprite1::Release));
	m_sprites.clear();
	player_spr = NULL;
	delete healthBar;
}

/*HPTRect &EnemyMrThomas::GetWorldLoc()
{
	return rectWorldLoc;
}*/

void EnemyMrThomas::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;
	
	player_spr = m_sprites[DEATH];
	SetAnimation(0, 0, true, true, 4, false);
}

HPTRect &EnemyMrThomas::GetWeaponWorldLoc()
{
	/*if(ipFlags.S_VISIBLE)
	{
		if((player_spr->GetFrameSet() == ENEMY_MR_THOMAS_ANIM_SWORD_ATTACK) && (player_spr->GetFrame() == 5))
			SetRectangle(rectWeaponWorldLoc, 40, 4, 0, -2);// ipFlags.S_DIRECTION);
		else
			SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);
	}
	else*/
	SetRectangle(rectWeaponWorldLoc, 25, 60, -10, -30);

	return rectWeaponWorldLoc;
}

void EnemyMrThomas::processLeft()
{
	player_spr = m_sprites[WALK];
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)	SetAnimation(0, 0, true, false, 15, true);
	else SetAnimation(0, 0, true, false, 15, false);

	//Accelerate Left Velocity
	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyMrThomas::processRight()
{
	player_spr = m_sprites[WALK];
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right) SetAnimation(0, 0, true, false, 15, true);
	else SetAnimation(0, 0, true, false, 15, false);

	//Accelerate Right Velocity
	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyMrThomas::stop()
{
	//Stop All Movement
	StopMovement();
	
	player_spr = m_sprites[TIDLE];
	
	//Reset Animation
	if(ipFlags.PrevMState != move_stop)	SetAnimation(0, 0, true, false, 15, true);
	else SetAnimation(0, 0, true, false, 15, false);
}

void EnemyMrThomas::processDamage()
{
	m_soundFXDamage->Play();
//	sound_processor->PlaySound(game_sounds->damage00, true);
//soundPlayer->PlaySound(damage00);
}

void EnemyMrThomas::processAttack()
{
	if((player_spr == m_sprites[DEATH]))
		return;
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{
		case 0: /* Sword Slash Attack */
			{				
				ipFlags.S_ATTACK = true;
				
				StopMovement();
				player_spr = m_sprites[INTRO];
				SetAnimation(0, 0, true, true, 15, true);
				//soundPlayer->PlaySound(swoosh00);
			}
			break;
		case 1: /* Projectile Attack */
			{
//			soundPlayer->PlaySound(phase00);

				/*SetAnimation(ENEMY_MR_THOMAS_ANIM_SPEED_PREP, 0, true, true, 15, true);
			
				Projectile *temp;
				if(ipFlags.S_DIRECTION)	
				{
					temp = new ProjectileMrThomasPhase(static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc), maxWalkSpeed*4, &ipFlags, &xLoc, &yLoc);
					
				}
				else
				{
					temp = new ProjectileMrThomasPhase(static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc), -(maxWalkSpeed*4), &ipFlags, &xLoc, &yLoc);
					
				}
				(*projectile_list).push_back(temp);*/
				
				player_spr = m_sprites[BLADE_THROW];
				SetAnimation(0, 0, true, true, 15, true);
				
				ipFlags.S_ATTACK = true;
				m_threw = false;
				m_soundFX->Play();
			}
			break;
		case 2: /* Breath */
			{
//			soundPlayer->PlaySound(phase00);
				player_spr = m_sprites[BLADE_THROW];
				SetAnimation(0, 0, true, true, 15, true);
				m_soundFX->Play();
				
				ipFlags.S_ATTACK = true;
				m_threw = false;
				m_threw2 = false;
				m_waitTime = 0;
			}
			break;
		case 3:
			{
//			soundPlayer->PlaySound(swoosh00);
				//player_spr = m_sprites[BLADE_THROW];
				//SetAnimation(ENEMY_MR_THOMAS_ANIM_SPEED_PREP, 0, true, true, 15, true);
				
				float phaseSpeedMod = 4;
				if(GetCurLife() < enemy_mr_thomas_set_cur_life*2*0.3)
				{		
					phaseSpeedMod *= 1.25;;   
				}
				
				 Projectile *temp;
				 if(ipFlags.S_DIRECTION)	
				 {
				 temp = new ProjectileMrThomasPhase(static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc), maxWalkSpeed*phaseSpeedMod, &ipFlags, &xLoc, &yLoc,m_leftBound,m_rightBound);
				 
				 }
				 else
				 {
				 temp = new ProjectileMrThomasPhase(static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc), -(maxWalkSpeed*phaseSpeedMod), &ipFlags, &xLoc, &yLoc,m_leftBound,m_rightBound);
				 
				 }
				(*projectile_list).push_back(temp);
				ipFlags.S_ATTACK = true;
				m_soundFXPhase->Play();
//				SetAnimation(ENEMY_MR_THOMAS_ANIM_TAUNT, 0, true, true, 10, true);
			}
			break;
		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

// Mr Thomas Taunt Action
void EnemyMrThomas::processSpecial1()
{
	velMovement = 0;
	//SetAnimation(ENEMY_MR_THOMAS_ANIM_TAUNT, 0, true, true, 10, false);
}



void EnemyMrThomas::processUpdate()
{
	/*if((introtimer > 0) && ipFlags.S_ATTACK)
	{
		introtimer -= time;

		if(introtimer <= 0)
		{
			SetAnimation(ENEMY_MR_THOMAS_ANIM_TAUNT, 0, true, true, 10, true);
		}
	}
	else if((player_spr->GetFrameSet() == ENEMY_MR_THOMAS_ANIM_TAUNT) && !player_spr->IsAnimating())
		ipFlags.S_INVULNERABLE = false;*/

//	BelowFeetLadderCheck();

	if((player_spr == m_sprites[DEATH]) && !player_spr->IsAnimating())
	{
		/*deathtimer -= time;

		if(deathtimer < 0)
		{
			deathtimer = 2.5;*/
			Die();
		//}
	}

	if(ipFlags.S_ON_GROUND)
	{
		velModifier = 0;
		velYModifier = 0;
	}
	else ApplyGravity();

	if(ipFlags.S_ATTACK)
	{
		switch (ipFlags.nCurrAttack)
		{
		case 0:
			if(!player_spr->IsAnimating())
			{
				ipFlags.nCurrAttack = 0;
				ipFlags.S_ATTACK = false;
			}
			break;
		case 1:
			if(!player_spr->IsAnimating())
			{
				if(!m_threw)
				{
					player_spr = m_sprites[BLADE_CATCH];
					SetAnimation(0, 0, true, true, 15, true);
					Projectile *temp;
					if(ipFlags.S_DIRECTION)	
					{
						temp = new ProjectileMrTKnife(ipFlags.S_DIRECTION,static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc), false);
					}
					else
					{
						temp = new ProjectileMrTKnife(ipFlags.S_DIRECTION,static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc), false);						
					}
					(*projectile_list).push_back(temp);
					m_threw = true;
				}
				else
				{
					ipFlags.nCurrAttack = 0;
					ipFlags.S_ATTACK = false;
				}
			}
			break;
		case 2:
			if(!player_spr->IsAnimating())
			{
				if(!m_threw)
				{
					player_spr = m_sprites[BLADE_CATCH];
					SetAnimation(0, 0, true, true, 15, true);
					Projectile *temp;
					if(ipFlags.S_DIRECTION)	
					{
						temp = new ProjectileMrTKnife(ipFlags.S_DIRECTION,static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc), true);
					}
					else
					{
						temp = new ProjectileMrTKnife(ipFlags.S_DIRECTION,static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc), true);						
					}
					(*projectile_list).push_back(temp);
					m_threw = true;
				}
				else if (m_waitTime > c_totalWaitTime*0.5f && !m_threw2)
				{
					m_threw2 = true;
					m_waitTime += time;
					if(GetCurLife() < enemy_mr_thomas_set_cur_life*2*0.3)
					{		
						Projectile *temp;
						if(ipFlags.S_DIRECTION)	
						{
							temp = new ProjectileMrTKnife(ipFlags.S_DIRECTION,static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc), true);
						}
						else
						{
							temp = new ProjectileMrTKnife(ipFlags.S_DIRECTION,static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc), true);						
						}
						(*projectile_list).push_back(temp);
					}
				}
				else if (m_waitTime < c_totalWaitTime)
				{
					m_waitTime += time;
					if(m_waitTime >= c_totalWaitTime)
					{
						player_spr = m_sprites[BLADE_CATCH];
						SetAnimation(0, 0, true, true, 15, true);					}
				}
				else
				{
					ipFlags.nCurrAttack = 0;
					ipFlags.S_ATTACK = false;
				}
			}
			break;
		case 3:
			break;
		};
		/*if(!player_spr->IsAnimating() && (player_spr->GetFrameSet() != ENEMY_MR_THOMAS_ANIM_SPEED_PREP))
		{
			ipFlags.nCurrAttack = 0;
			ipFlags.S_ATTACK = false;
			
		}*/
	}

	// Apply Velocity Modifier
	if(/*!ipFlags.S_DAMAGED &&*/ !ipFlags.S_ATTACK)
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
			//case move_reserved_action_1:
			//	processSpecial1();
			default:
				break;
		}

	//SetRectangle(rectWorldLoc, 14, 56, -7, -25);
}

void EnemyMrThomas::RenderHealthBar()
{
	healthBar->SetTotalBars((float)GetNumLifeBars() * 3.0f);
	healthBar->SetPercentFull((float)GetCurLife()/((float)GetNumLifeBars() *5.0f));
	healthBar->Render();
	bossIcon->Render();
}