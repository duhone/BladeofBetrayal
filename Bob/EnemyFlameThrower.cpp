// EnemyFlameThrower.cpp: implementation of the EnemyFlameThrower class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyFlameThrower.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyFlameThrower::EnemyFlameThrower(Level *curLevel, float tDelay, bool bOrientation, bool sDirection)
{
	SetRenderHealthBar(false);
	ipFlags.S_NO_GRAVITY = true;
	level_class = curLevel;

	this->tDelay = tDelay;
	this->bOrientation = bOrientation;

	dTimer = tDelay;

	this->sDirection = sDirection;


	SetWeaponDamage(15);
	ipFlags.S_VISIBLE = false;

	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::flame::ID);	
}

EnemyFlameThrower::~EnemyFlameThrower()
{

}

HPTRect &EnemyFlameThrower::GetWeaponWorldLoc()
{
	if(bOrientation)
	{
		switch(player_spr->GetFrame())
		{
		case 0:
			SetRectangle(rectWeaponWorldLoc, 16, 20, -8, -10);
			break;
		case 1:
			SetRectangle(rectWeaponWorldLoc, 16, 40, -8, -20);
			break;
		case 2:
			SetRectangle(rectWeaponWorldLoc, 16, 70, -8, -35);
			break;
		case 3:
			SetRectangle(rectWeaponWorldLoc, 16, 96, -8, -48);
			break;
		}
	}
	else
	{
		switch(player_spr->GetFrame())
		{
		case 0:
			SetRectangle(rectWeaponWorldLoc, 20, 20, -10, -10);
			break;
		case 1:
			SetRectangle(rectWeaponWorldLoc, 30, 20, -15, -10);
			break;
		case 2:
			SetRectangle(rectWeaponWorldLoc, 50, 20, -25, -10);
			break;
		case 3:
			SetRectangle(rectWeaponWorldLoc, 60, 20, -30, -10);
			break;
		case 4:
			SetRectangle(rectWeaponWorldLoc, 80, 20, -40, -10);
			break;
		}
	}

		

	return rectWeaponWorldLoc;
}
/*HPTRect &EnemyFlameThrower::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyFlameThrower::processUpdate()
{
	ipFlags.S_DIRECTION = sDirection;

	if(!player_spr->IsAnimating())
	{
		ipFlags.S_VISIBLE = false;
		ipFlags.S_ATTACK = false;
	}

	dTimer -= time;

	if(dTimer < 0)
	{
		ipFlags.S_ATTACK = true;
		dTimer = tDelay;
		ipFlags.S_VISIBLE = true;
		SetAnimation(ENEMY_FLAME_THROW, 0, true, true, 10, true);
		if (ipFlags.S_ACTIVE) m_soundFX->Play();
	}

	/* Center (0,0), offset by Render Offset */
	if(bOrientation)
	{
		rectDX = 16;
		rectDY = 96;
		rectXOffset = -8;
		rectYOffset = -48;

//		SetRectangle(rectWorldLoc, 16, 96, -8, -48);
	}
	else
	{
		rectDX = 80;
		rectDY = 20;
		rectXOffset = -40;
		rectYOffset = -10;

//		SetRectangle(rectWorldLoc, 80, 32, -40, -16);
	}
}
