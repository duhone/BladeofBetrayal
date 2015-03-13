// EnemyElectricField.cpp: implementation of the EnemyElectricField class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyElectricField.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyElectricField::EnemyElectricField(Level *curLevel, float tDelay, bool bOrientation, bool sDirection)
{
	SetRenderHealthBar(false);
	ipFlags.S_NO_GRAVITY = true;
	level_class = curLevel;

	this->tDelay = tDelay;
	this->bOrientation = bOrientation;

	dTimer = tDelay;

	this->sDirection = sDirection;

	SetWeaponDamage(10);
	ipFlags.S_VISIBLE = false;

	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::shock::ID);	
}

EnemyElectricField::~EnemyElectricField()
{

}

HPTRect &EnemyElectricField::GetWeaponWorldLoc()
{
	if(bOrientation)
		SetRectangle(rectWeaponWorldLoc, 16, 96, -8, -48);
	else
		SetRectangle(rectWeaponWorldLoc, 96, 16, -48, -8);

	return rectWeaponWorldLoc;
}
//HPTRect &EnemyElectricField::GetWorldLoc()
//{
	/* Center (0,0), offset by Render Offset */
//	if(bOrientation)
//		SetRectangle(rectWorldLoc, 16, 96, -8, -48);
//	else
//		SetRectangle(rectWorldLoc, 96, 16, -48, -8);

//	return rectWorldLoc;
//}

void EnemyElectricField::processUpdate()
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
		SetAnimation(ENEMY_ELECTRIC_FIELD, 0, true, true, 10, true);
		if (ipFlags.S_ACTIVE) m_soundFX->Play();
	}

	/* Center (0,0), offset by Render Offset */
	if(bOrientation)
	{
		rectDX = 16;
		rectDY = 96;
		rectXOffset = -8;
		rectYOffset = -48;

	//	SetRectangle(rectWorldLoc, 16, 96, -8, -48);
	}
	else
	{
		rectDX = 96;
		rectDY = 12;
		rectXOffset = -48;
		rectYOffset = -6;

	//	SetRectangle(rectWorldLoc, 96, 16, -48, -8);
	}
}
