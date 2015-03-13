// EnemyShadowElite.cpp: implementation of the EnemyShadowElite class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyShadowElite.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyShadowElite::EnemyShadowElite(Level *curLevel)
{
//	SetCurLife(enemy_baton_elite_guard_cur_life);
	SetSprite(1, CR::AssetList::elite_guard);
	this->level_class = curLevel;

	SetCurLife(6);
	SetNumLifeBars(2);
	
	//SetCurLife(25);
	//SetNumLifeBars(5);

	SetRenderOffset(9);
	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::swing::ID);
}

EnemyShadowElite::~EnemyShadowElite()
{
}

/*HPTRect &EnemyShadowElite::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyShadowElite::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK) && (player_spr->GetFrame() == 4))	
	{
		SetWeaponDamage(7);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, 2);
	}
	else if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK) && (player_spr->GetFrame() == 5))	
	{
		SetWeaponDamage(7);
		SetRectangle(rectWeaponWorldLoc, 25, 4, nOffSet, -2);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyShadowElite::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, true, false, 15, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyShadowElite::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, true, false, 15, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyShadowElite::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		if(!SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK, 0, true, true, 30, false))
		{
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(ninjaswing);
			//Stop All Directional Movement
			velMovement = 0;
			velModifier = 0;
		}
		if (ipFlags.S_ACTIVE) m_soundFX->Play();
	}
}

void EnemyShadowElite::processDeath()
{
	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);

	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyShadowElite::processDamage()
{
	ipFlags.S_ATTACK = false;
	
	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);

	SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_DAMAGE, 0, true, false, 10, false);
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyShadowElite::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_BATON_ELITE_GUARD_ANIM_MOVE, 0, false, false, 22, false);
}

void EnemyShadowElite::processUpdate()
{
	if(!ipFlags.S_DEAD)
	{
		if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_DEATH)&& !player_spr->IsAnimating())
			Die();

		if(ipFlags.S_ATTACK)
		{
			if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK) && !player_spr->IsAnimating())
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
	}
}