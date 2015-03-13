// EnemyLandMine.cpp: implementation of the EnemyLandMine class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyLandMine.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyLandMine::EnemyLandMine(Level *curLevel)
{
	SetCurLife(1);
	SetRenderOffset(3);
	SetWeaponDamage(6);
	level_class = curLevel;
//	SetRenderOffset(0,0);
	SetRenderHealthBar(false);	

	rectDX = 12;
	rectDY = 6;
	rectXOffset = -nOffSet-3;
	rectYOffset = 25;

	ipFlags.S_POINTS = false;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::explosion::ID);
}

EnemyLandMine::~EnemyLandMine()
{
}

HPTRect &EnemyLandMine::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_LAND_MINE_ANIM_EXPLODE))
		SetRectangle(rectWeaponWorldLoc, 30, 60, -15, -30);
	else 
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyLandMine::processAttack()
{
	ipFlags.S_ATTACK = true;
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(beepbeep);
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(explode01);
	m_soundFX->Play();
	SetAnimation(ENEMY_LAND_MINE_ANIM_EXPLODE, 0, true, true, 10, false);
}

void EnemyLandMine::processDeath()
{
	SetAnimation(ENEMY_LAND_MINE_ANIM_EXPLODE, 0, true, true, 10, false);

	Die();
}

void EnemyLandMine::processDamage()
{
	ipFlags.S_ATTACK = false;

	SetAnimation(ENEMY_LAND_MINE_ANIM_EXPLODE, 0, true, false, 10, false);

	Die();
}

void EnemyLandMine::processUpdate()
{
	if(player_spr->GetFrameSet() == ENEMY_LAND_MINE_ANIM_EXPLODE)
	{
		if(!player_spr->IsAnimating())
		{
			processDeath();
		}
	}
	else SetAnimation(ENEMY_LAND_MINE_ANIM_FLASH, 0, true, false, 2, false);
}

void EnemyLandMine::StartMine()
{
	SetAnimation(ENEMY_LAND_MINE_ANIM_FLASH, 0, true, false, 2, true);
}
