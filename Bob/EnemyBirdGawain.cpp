// EnemyBirdGawain.cpp: implementation of the EnemyBirdGawain class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyBirdGawain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyBirdGawain::EnemyBirdGawain(Level *curLevel, IPlayer *player)
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

	ipFlags.S_POINTS = false;

	SetWeaponDamage(3);
}

EnemyBirdGawain::~EnemyBirdGawain()
{

}

/*HPTRect &EnemyBirdGawain::GetWorldLoc()
{
	if(!HIT)
		SetRectangle(rectWorldLoc, 16, 16, -8, -8);
	else
	{
		rectWorldLoc.p1.x = 0;
		rectWorldLoc.p1.y = 0;
		rectWorldLoc.p2.x = 0;
		rectWorldLoc.p2.y = 0;
	}

	return rectWorldLoc;
}*/

HPTRect &EnemyBirdGawain::GetWeaponWorldLoc()
{
	if(!HIT)
		SetRectangle(rectWeaponWorldLoc, 16, 16, -8, -8);
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

/*void EnemyBirdGawain::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		ipFlags.S_ATTACK = true;

		SetAnimation(ENEMY_BIRD_MOVE, 0, true, false, 15, true);
	}
}*/

void EnemyBirdGawain::processDamage()
{
	//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(crow);
	StopMovement();
	velYModifier = 0;
	//Stop All Movement
	if(ipFlags.S_DIRECTION)
		velModifier = -maxWalkSpeed;
	else
		velModifier = maxWalkSpeed;

	ipFlags.S_DIRECTION = !ipFlags.S_DIRECTION;
	HIT = true;
	ipFlags.S_ATTACK = false;
}

void EnemyBirdGawain::processDeath()
{
	/* Stop All Directional Movement */
	//StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_BIRD_DEATH, 0, true, true, 10, true);
}

void EnemyBirdGawain::processUpdate()
{
	if((player_spr->GetFrameSet() == ENEMY_BIRD_DEATH) && !player_spr->IsAnimating())
		Die();

	if(((GetXTilePos() > 24) || (GetXTilePos() < 0)))
		Die();

	
	float x;
	float y;
	GetDisplacementVector(&x, &y);

	if(x == 0)
		Die();

	if(ipFlags.S_ATTACK && !ipFlags.S_DEAD)
	{	
		if(!HIT)
		{
			if(player_spr->GetFrameSet() != ENEMY_BIRD_MOVE)
				SetAnimation(ENEMY_BIRD_MOVE, 0, true, false, 15, false);

			double dx = player->GetXTilePos() - GetXTilePos();
			double dy = (player->GetYTilePos() - 1) - GetYTilePos();
			double Mag = sqrt(pow(dx,2)+pow(dy, 2));

			if(Mag != 0)
			{
				dx = dx / Mag;
				dy = dy / Mag;

				if(dx > 0)
					ipFlags.S_DIRECTION = true;
				else
					ipFlags.S_DIRECTION = false;

				velMovement = maxWalkSpeed * (float)dx;
				velYModifier = maxWalkSpeed * (float)dy;
			}
			else
			{
				Die();
			}
		}
	}

	if(!ipFlags.S_DAMAGED && !ipFlags.S_ATTACK)
		switch(ipFlags.CurMState)
		{
			case move_stop:
				stop();
				break;

			default:
				break;
		}

	if(!HIT)
	{
		rectDX = 16;
		rectDY = 16;
		rectXOffset = -8;
		rectYOffset = -8;

	//	SetRectangle(rectWorldLoc, 16, 16, -8, -8);
	}
	else
	{
		rectDX = 0;
		rectDY = 0;
		rectXOffset = 0;
		rectYOffset = 0;

//		rectWorldLoc.p1.x = 0;
//		rectWorldLoc.p1.y = 0;
//		rectWorldLoc.p2.x = 0;
//		rectWorldLoc.p2.y = 0;
	}
}