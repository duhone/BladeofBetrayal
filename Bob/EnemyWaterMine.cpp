// EnemyWaterMine.cpp: implementation of the EnemyWaterMine class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyWaterMine.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyWaterMine::EnemyWaterMine(Level *curLevel)
{
	SetCurLife(1);
	SetRenderOffset(3);
	SetWeaponDamage(6);
	level_class = curLevel;

	SetRenderHealthBar(false);
	ipFlags.S_NO_GRAVITY = true;
	bobtimer = 6;

		rectDX = 32;
	rectDY = 32;
	rectXOffset = -16;
	rectYOffset = -16;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::explosion::ID);
}

EnemyWaterMine::~EnemyWaterMine()
{

}

/*HPTRect &EnemyWaterMine::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyWaterMine::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_WATER_MINE_ANIM_DEATH))
		SetRectangle(rectWeaponWorldLoc, 48, 48, -24, -24);
	else 
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyWaterMine::processAttack()
{
	ipFlags.S_ATTACK = true;

	m_soundFX->Play();
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(beepbeep);
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(explode01);
	
	SetAnimation(ENEMY_WATER_MINE_ANIM_DEATH, 0, true, true, 10, false);
}

void EnemyWaterMine::processDeath()
{
	SetAnimation(ENEMY_WATER_MINE_ANIM_DEATH, 0, true, true, 10, false);

	Die();
}

void EnemyWaterMine::processDamage()
{
	ipFlags.S_ATTACK = false;
	
	SetAnimation(ENEMY_WATER_MINE_ANIM_DEATH, 0, true, false, 10, false);

	Die();
}

void EnemyWaterMine::processUpdate()
{

//	bobtimer -= time;

//	if(bobtimer > 3)
//		velYModifier = rand()%3;
//	else if(bobtimer > 0)
//		velYModifier = -(rand()%3);
//	else
//	{
//		bobtimer = 6;
		velYModifier = 0;
////}

//	BelowFeetLadderCheck();
	/*
	if(player_spr->GetFrameSet() == ENEMY_WATER_MINE_ANIM_DEATH && !ipFlags.S_ATTACK)
		SetAnimation(ENEMY_WATER_MINE_ANIM_FLASH, 0, true, false, static_cast<float>(rand()%5), false);

	if(player_spr->GetFrameSet() == ENEMY_WATER_MINE_ANIM_DEATH)
	{
		if(!player_spr->IsAnimating())
		{
			processDeath();
		}
	}
	

	//Transition Movement State
	TransitionMovement(ipFlags.CurMState);
*/
//	SetRectangle(rectWorldLoc, 32, 32, -16, -16);
	
	
	if(player_spr->GetFrameSet() == ENEMY_WATER_MINE_ANIM_DEATH)
	{
		if(!player_spr->IsAnimating())
		{
			processDeath();
		}
	}
	//else SetAnimation(ENEMY_WATER_MINE_ANIM_FLASH, 0, true, false, 2, false);
}

void EnemyWaterMine::StartMine()
{
	SetAnimation(ENEMY_WATER_MINE_ANIM_FLASH, 0, true, false, 2, true);
}
