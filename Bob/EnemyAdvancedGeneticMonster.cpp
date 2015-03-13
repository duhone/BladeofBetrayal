// EnemyAdvancedGeneticMonster.cpp: implementation of the EnemyAdvancedGeneticMonster class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyAdvancedGeneticMonster.h"
#include "AssetList.h"
#include "../Engines/Utility/FunctionObjects.h"
#include "ProjectileAgmBone.h"
#include "ProjectileAGMSpit.h"
#include <functional>

using namespace std;
using namespace CR;
using namespace CR::Utility;
using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const float EnemyAdvancedGeneticMonster::c_spikeDropTime = 0.25f;

EnemyAdvancedGeneticMonster::EnemyAdvancedGeneticMonster(Level *curLevel, IPlayer *_player) : 
	m_superJumping(false), m_player(_player)
{
	m_attackWhenDamaged = true;
	SetRenderOffset(0, 0);
	SetCurLife(enemy_mr_thomas_set_cur_life * 2);
	SetNumLifeBars(enemy_mr_thomas_set_cur_life_bars * 2);
	SetPlayerRectangle(15, 55);
	maxWalkSpeed = 130.00;   
	SetDamageTimer(.50);
	level_class = curLevel;
	jumpMaxVelocity = -400;
	deathtimer = 2.5;
	
	for(int i = AssetList::AGM_back_spike;i <= AssetList::AGM_trans_spit;++i)
	{
		m_sprites.push_back(graphics_engine->CreateSprite1(true));
		m_sprites.back()->SetImage(i);
	}
	
	if(player_spr != 0)
		player_spr->Release();
	player_spr = m_sprites[IDLE];
	//SetAnimation(0, 0, true, false, 15, true);
	healthBar = new MeterBar(Red);
	healthBar->SetPosition(200, 10);
	bossIcon = graphics_engine->CreateSprite1();
	bossIcon->SetImage(CR::AssetList::boss_icon);
	bossIcon->SetPositionAbsalute(190, 10);
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::growl00::ID);
}

EnemyAdvancedGeneticMonster::~EnemyAdvancedGeneticMonster()
{
	ForEach(m_sprites,mem_fun(&HPTSprite1::Release));
	m_sprites.clear();
	player_spr = NULL;
	delete healthBar;
	bossIcon->Release();
}

void EnemyAdvancedGeneticMonster::setJumpVelocity()
{
	if(ipFlags.S_DIRECTION) velModifier = 100;
	else velModifier = -100;

	ipFlags.S_ON_GROUND = false;
	ipFlags.S_NO_GRAVITY = false;
	ipFlags.S_JUMP = true;
	
	yLoc -= 1;

	velYModifier = 0;
	velYJumpModifier = jumpMaxVelocity;

	
	player_spr = m_sprites[JUMP];	
	SetAnimation(0, 0, true, true, 8, true);
}

/*HPTRect &EnemyAdvancedGeneticMonster::GetWorldLoc()
{
	if(player_spr->GetFrameSet() == ENEMY_AGM_ANIM_BACK_SPIKE_1)
		SetRectangle(rectWorldLoc, 40, 30, -5, 0);
	else
		SetRectangle(rectWorldLoc, 30, 60, -15, -30);
	
	return rectWorldLoc;
}*/

void EnemyAdvancedGeneticMonster::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;
	
	player_spr = m_sprites[DIE];
	SetAnimation(0, 0, true, true, 4, false);
}

HPTRect &EnemyAdvancedGeneticMonster::GetWeaponWorldLoc()
{
	if(ipFlags.S_VISIBLE)
	{
		if((player_spr == m_sprites[SPLASH]))
		{
			if(player_spr->GetFrame() >= 7)
				SetRectangle(rectWeaponWorldLoc, 40, 4, 0, -15);
		}	
		else if((player_spr == m_sprites[RUN]))
		{
			SetRectangle(rectWeaponWorldLoc, 30, 40, 20, -20);
		}
		else if((player_spr == m_sprites[JUMP]))
		{
			SetRectangle(rectWeaponWorldLoc, 40, 60, -20, -40);
		}
		else if((player_spr == m_sprites[BACK_SPIKE]))
		{
			SetRectangle(rectWeaponWorldLoc, 40, 40, -20, -20);
		}				
		else
			SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyAdvancedGeneticMonster::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	player_spr = m_sprites[RUN];
	if(ipFlags.PrevMState != move_left)	
	{
//		sound_processor->PlaySound(game_sounds->growl00, ipFlags.S_ACTIVE);
//	soundPlayer->PlaySound(growl00);
		m_soundFX->Play();
		SetAnimation(0, 0, true, false, 15, true);
	}
	else SetAnimation(0, 0, true, false, 15, false);

	//Accelerate Left Velocity
	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
	ipFlags.S_ATTACK = true;
	SetWeaponDamage(8);

}

void EnemyAdvancedGeneticMonster::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	player_spr = m_sprites[RUN];
	if(ipFlags.PrevMState != move_right)
	{
//		sound_processor->PlaySound(game_sounds->growl00, ipFlags.S_ACTIVE);
//	soundPlayer->PlaySound(growl00);
		m_soundFX->Play();
		SetAnimation(0, 0, true, false, 15, true);
	}
	else SetAnimation(0, 0, true, false, 15, false);

	//Accelerate Right Velocity
	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
	ipFlags.S_ATTACK = true;
	SetWeaponDamage(8);

}

void EnemyAdvancedGeneticMonster::stop()
{
	if(!ipFlags.S_JUMP)
	{

	//Stop All Movement
	StopMovement();
		
	player_spr = m_sprites[IDLE];
	//Reset Animation
	if(ipFlags.PrevMState != move_stop)	SetAnimation(0, 0, true, false, 15, true);
		else SetAnimation(0, 0, true, false, 15, false);

	}
	
	ipFlags.S_ATTACK = false;
}

void EnemyAdvancedGeneticMonster::processDamage()
{
}

void EnemyAdvancedGeneticMonster::processAttack()
{
	if(player_spr == m_sprites[DIE])
		return;
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;
		
		Projectile *temp;
		switch(ipFlags.nCurrAttack)
		{	
		case 0: /* CLAW ATTACK */
			{
				//soundPlayer->PlaySound(growl01);
				//soundPlayer->PlaySound(swoosh00);
//				sound_processor->PlaySound(game_sounds->growl01);
//				sound_processor->PlaySound(game_sounds->swoosh);
				/*SetWeaponDamage(5);
				player_spr = m_sprites[SPLASH];
				SetAnimation(0, 0, true, true, 25, true);
				StopMovement();*/
				ipFlags.S_ATTACK = true;
				
				StopMovement();
				player_spr = m_sprites[INTRO];
				SetAnimation(0, 0, true, true, 15, true);
								
			}
				break;
			case 1: /* CLAW ATTACK */
			{
				ipFlags.S_ATTACK = true;
				m_soundFX->Play();
//			soundPlayer->PlaySound(growl00);
//			soundPlayer->PlaySound(swoosh00);
				StopMovement();
				player_spr = m_sprites[SPLASH];
				SetAnimation(0, 0, true, true, 15, true);
				
				SetWeaponDamage(5);

				if(ipFlags.S_DIRECTION) 
				{
					temp = new ProjectileAgmBone(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15));
					
				}
				else
				{
					temp = new ProjectileAgmBone(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc - 15));
					
				}
				(*projectile_list).push_back(temp);
				
			}
				break;	
				
		case 2: /* BACK SPIKE 0 */
			{
				//ipFlags.S_INVULNERABLE = true;
				//ipFlags.fInvulnerableTimer = 6;
				
				player_spr = m_sprites[BACK_SPIKE];
//				sound_processor->PlaySound(game_sounds->growl01);
//			soundPlayer->PlaySound(growl00);
//			soundPlayer->PlaySound(swoosh00);
				m_soundFX->Play();
				SetWeaponDamage(3);
				SetAnimation(0, 0, true, true, 10, true);
//				StopMovement();
				ipFlags.S_ATTACK = true;
				m_firedSpikes = false;
			}
			break;
		case 3: /* BACK SPIKE 1 */
			{
				//player_spr = m_sprites[BACK_SPIKE];
//				sound_processor->PlaySound(game_sounds->growl02);
//			soundPlayer->PlaySound(growl02);
//			soundPlayer->PlaySound(swoosh00);
//				sound_processor->PlaySound(game_sounds->swoosh);
				SetWeaponDamage(3);
				//SetAnimation(0, 0, true, true, 20, true);
				//StopMovement();
				ipFlags.S_ATTACK = true;
				m_spikeDropTime=c_spikeDropTime;
				m_droppedSpikes=0;
				m_dropOffset = -50;
			}
			break;
			case 4: /* spit */
			{
				player_spr = m_sprites[TRANS_SPIT];
//			soundPlayer->PlaySound(growl02);
//			soundPlayer->PlaySound(swoosh00);
				//				sound_processor->PlaySound(game_sounds->growl02);
				//				sound_processor->PlaySound(game_sounds->swoosh);
				SetWeaponDamage(3);
				SetAnimation(0, 0, true, true, 15, true);
				//StopMovement();
				ipFlags.S_ATTACK = true;
				m_numSpits = 0;
			}
			break;
		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}

	if(player_spr == m_sprites[BACK_SPIKE])
		SetRectangle(rectWorldLoc, 40, 30, -5, 0);
	else if(player_spr == m_sprites[JUMP])
		SetRectangle(rectWorldLoc, 80, 80, -40, -40);	
	else
		SetRectangle(rectWorldLoc, 50, 60, -25, -30);
}

void EnemyAdvancedGeneticMonster::processUpdate()
{	
	if(player_spr == m_sprites[BACK_SPIKE])
		SetRenderOffset(0, -7);
	if(player_spr == m_sprites[DIE])
		SetRenderOffset(0, -5);	
	if(player_spr == m_sprites[IDLE])
		SetRenderOffset(0, -5);	
	if(player_spr == m_sprites[INTRO])
		SetRenderOffset(-15, -15);	
	if(player_spr == m_sprites[JUMP])
		SetRenderOffset(0, -5);	
	if(player_spr == m_sprites[RUN])
		SetRenderOffset(0, 2);	
	if(player_spr == m_sprites[SPLASH])
		SetRenderOffset(0, -5);	
	if(player_spr == m_sprites[SPIT])
		SetRenderOffset(0, 5);	
	if(player_spr == m_sprites[TRANS_SPIT])
		SetRenderOffset(0, -5);	
		
	if(GetCurLife() < enemy_mr_thomas_set_cur_life*2*0.3)
	{		
		maxWalkSpeed = 130.00*1.3f;   
	}
	if(player_spr == m_sprites[DIE])
	{
		if(!player_spr->IsAnimating())
		{
			deathtimer -= time;
			
			if(deathtimer < 0)
			{
				deathtimer = 2.5;
				Die();
			}
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
			ipFlags.S_ALWAYS_ATTACK = false;
			if(player_spr != m_sprites[DIE])
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
	
	if((player_spr == m_sprites[BACK_SPIKE]) && !player_spr->IsAnimating())
		ipFlags.S_INVULNERABLE = false;

	if(!ipFlags.S_DEAD)
		ipFlags.S_ACTIVE = true;

//	BelowFeetLadderCheck();

	/*if((player_spr == m_sprites[DIE]) && !player_spr->IsAnimating())
	{
		deathtimer -= time;

		if(deathtimer < 0)
		{
			deathtimer = 2.5;
			Die();
		}
	}*/
		
	if(ipFlags.S_ON_GROUND)
	{
		velModifier = 0;
		velYModifier = 0;
		ipFlags.S_JUMP = false;
	}
	else ApplyGravity();

	if(ipFlags.S_ATTACK  )
	{
		if(!player_spr->IsAnimating() && ipFlags.nCurrAttack < 3 )
		{
			ipFlags.nCurrAttack = 0;
			ipFlags.S_ATTACK = false;
		}
		if(ipFlags.nCurrAttack == 2 && !m_firedSpikes && player_spr->GetFrame() >= 8)
		{
			m_firedSpikes=true;
			
			Projectile *temp;
			temp = new ProjectileAgmBone(false, static_cast<int>(xLoc-20 + nOffSet), static_cast<int>(yLoc - 15),true);
			(*projectile_list).push_back(temp);
			temp = new ProjectileAgmBone(false, static_cast<int>(xLoc-10 + nOffSet), static_cast<int>(yLoc - 15),true);
			(*projectile_list).push_back(temp);
			temp = new ProjectileAgmBone(false, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15),true);
			(*projectile_list).push_back(temp);
			temp = new ProjectileAgmBone(false, static_cast<int>(xLoc+10 + nOffSet), static_cast<int>(yLoc - 15),true);
			(*projectile_list).push_back(temp);
			temp = new ProjectileAgmBone(false, static_cast<int>(xLoc+20 + nOffSet), static_cast<int>(yLoc - 15),true);
			(*projectile_list).push_back(temp);
		}
		
		if(ipFlags.nCurrAttack == 3)
		{
			m_spikeDropTime += time;
			
			if(m_spikeDropTime > c_spikeDropTime)
			{
				Projectile *temp;
				temp = new ProjectileAgmBone(true, static_cast<int>(xLoc+m_dropOffset + nOffSet), static_cast<int>(-10-yViewLoc),true);
				//cout << "spawned at" << xLoc-m_dropOffset + nOffSet << endl;
				(*projectile_list).push_back(temp);
				m_dropOffset -= 70;
				m_droppedSpikes++;
				m_spikeDropTime = 0;
				if(m_droppedSpikes >= 10)
				{
					ipFlags.nCurrAttack = 0;
					ipFlags.S_ATTACK = false;
				}					
			}			
		}
		if(ipFlags.nCurrAttack == 4)
		{			
			if(player_spr == m_sprites[TRANS_SPIT] && !player_spr->IsAnimating())
			{				
				player_spr = m_sprites[SPIT];
//			soundPlayer->PlaySound(growl02);
//			soundPlayer->PlaySound(swoosh00);
				//				sound_processor->PlaySound(game_sounds->growl02);
				//				sound_processor->PlaySound(game_sounds->swoosh);
				SetWeaponDamage(10);
				SetAnimation(0, 0, true, true, 15, true);
				Projectile *temp;
				temp = new ProjectileAGMSpit(false, static_cast<int>(xLoc-20 + nOffSet), static_cast<int>(yLoc - 15),*projectile_list,m_player->GetXLoc());
				(*projectile_list).push_back(temp);
				++m_numSpits;
				
			}
			else if(player_spr == m_sprites[SPIT] && !player_spr->IsAnimating())
			{				
				if(GetCurLife() < enemy_mr_thomas_set_cur_life*2*0.3 && m_numSpits < 3)
				{
					SetAnimation(0, 0, true, true, 15, true);
					Projectile *temp;
					temp = new ProjectileAGMSpit(false, static_cast<int>(xLoc-20 + nOffSet), static_cast<int>(yLoc - 15),*projectile_list,m_player->GetXLoc());
					(*projectile_list).push_back(temp);
					++m_numSpits;
				}
				else
				{
					ipFlags.nCurrAttack = 0;
					ipFlags.S_ATTACK = false;
				}
			}
		}
	}

	// Apply Velocity Modifier
	if(/*!ipFlags.S_DAMAGED && */!ipFlags.S_ATTACK || player_spr == m_sprites[RUN])
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

	if(player_spr == m_sprites[BACK_SPIKE])
	{
		rectDX = 50;
		rectDY = 60;
		rectXOffset = -25;
		rectYOffset = -30;
	}
	else if(player_spr == m_sprites[JUMP])
	{
		rectDX = 50;
		rectDY = 150;
		rectXOffset = -25;
		rectYOffset = -25;
	}	
	else
	{
		rectDX = 50;
		rectDY = 60;
		rectXOffset = -25;
		rectYOffset = -30;
	}
}

void EnemyAdvancedGeneticMonster::SuperJump(int _xtile,float _jumpTime,float _exponent,float _height)
{
	m_jumpTarget.x = _xtile;//*16; 
	m_jumpTarget.y = yLoc; 
	m_superJumping = true;
	m_jumpTime = 0;
	m_totalJumpTime = _jumpTime;
	if(GetCurLife() < enemy_mr_thomas_set_cur_life*2*0.3)
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

void EnemyAdvancedGeneticMonster::RenderHealthBar()
{
	healthBar->SetTotalBars((float)GetNumLifeBars() * 3.0f);
	healthBar->SetPercentFull((float)GetCurLife()/((float)GetNumLifeBars() *5.0f));
	healthBar->Render();
	bossIcon->Render();
}