// EnemyFire.cpp: implementation of the EnemyFire class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyFire.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyFire::EnemyFire(Level *curLevel)
{
	SetCurLife(1);
	SetRenderOffset(3);
	SetWeaponDamage(10);

	SetRenderHealthBar(false);

	level_class = curLevel;
	ipFlags.S_ATTACK = true;
	//SetAnimation(0, 0, true, false, 10, true);

	rectDX = 40;
	rectDY = 64;
	rectXOffset = -20;
	rectYOffset = -32;

}

EnemyFire::~EnemyFire()
{

}

/*HPTRect &EnemyFire::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyFire::GetWeaponWorldLoc()
{
	SetRectangle(rectWeaponWorldLoc, 40, 64, -20, -32);

	return rectWeaponWorldLoc;
}

void EnemyFire::processUpdate()
{
//	SetRectangle(rectWorldLoc, 40, 64, -20, -32);
}

void EnemyFire::StartFlame()
{
	SetAnimation(0, 0, true, false, 10, true);

}
