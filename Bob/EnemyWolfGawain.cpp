// EnemyWolfGawain.cpp: implementation of the EnemyWolfGawain class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyWolfGawain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyWolfGawain::EnemyWolfGawain(Level *curLevel, IPlayer *player)
{
	maxWalkSpeed = 100.00;   
	ipFlags.S_NO_GRAVITY = true;

	SetCurLife(6);
	SetNumLifeBars(1);
	level_class = curLevel;
	SetDamageTimer(1);

	this->player = player;

	ipFlags.S_ATTACK = true;
	HIT = false;
	COLLISION = false;
	START = false;
	SetWeaponDamage(5);

	ipFlags.S_POINTS = false;
//	SetMaxWalkVelocity(60);
}

EnemyWolfGawain::~EnemyWolfGawain()
{

}

/*HPTRect &EnemyWolfGawain::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyWolfGawain::GetWeaponWorldLoc()
{
	if(!HIT)
		SetRectangle(rectWeaponWorldLoc, 15, 15, -nOffSet, 15);
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyWolfGawain::processDamage()
{
	ipFlags.S_ATTACK = false;
	
	HIT = true;
	/* Stop All Directional Movement */
	StopMovement();

	SetAnimation(ENEMY_WOLF_DEATH, 0, true, true, 10, true);
}

void EnemyWolfGawain::processDeath()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_WOLF_DEATH, 0, true, true, 10, true);
}

void EnemyWolfGawain::processUpdate()
{
	if((player_spr->GetFrameSet() == ENEMY_WOLF_DEATH) && !player_spr->IsAnimating())
		Die();

//	if(((GetXTilePos() > 22) || (GetXTilePos() < 2)))
//		Die();

	if(((GetXTilePos() > 18) || (GetXTilePos() < 4)))
		Die();
	else
		COLLISION = true;

	if(ipFlags.S_ATTACK && !ipFlags.S_DEAD)
	{	
		if(!HIT)
		{
			if(!START)
			{
				int dx = player->GetXTilePos() - GetXTilePos();

				if(dx > 0)
				{
					ipFlags.S_DIRECTION = true;
					velMovement = maxWalkSpeed;
				}
				else
				{
					ipFlags.S_DIRECTION = false;
					velMovement = -maxWalkSpeed;
				}			

				SetAnimation(ENEMY_WOLF_MOVE, 0, true, false, 15, true);
				START = true;
			}
			else if(START)
			{
				if(ipFlags.S_DIRECTION)
					velMovement = maxWalkSpeed;
				else
					velMovement = -maxWalkSpeed;
			}

		}
	}

	if(COLLISION)
	{
		rectDX = 15;
		rectDY = 15;
		rectXOffset = -nOffSet;
		rectYOffset = 15;

//		SetRectangle(rectWorldLoc, 15, 15, -nOffSet, 15);
	}
	else
	{
		rectDX = 0;
		rectDY = 0;
		rectXOffset = 0;
		rectYOffset = 0;

//		SetRectangle(rectWorldLoc, 0, 0, 0, 0);
	}
}