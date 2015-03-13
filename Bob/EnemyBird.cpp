// EnemyBird.cpp: implementation of the EnemyBird class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyBird.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
EnemyBird::EnemyBird(Level *curLevel)
{
	ipFlags.S_NO_GRAVITY = true;

	SetCurLife(1);
	SetNumLifeBars(1);
	level_class = curLevel;
	SetDamageTimer(1);
	SetPointValue(0);

	points[0].x = tx1;
	points[0].y = ty1;
	points[1].x = tx2;
	points[1].y = ty2;
	points[2].x = tx3;
	points[2].y = ty3;
}

EnemyBird::~EnemyBird()
{
}

void EnemyBird::CalculateAttack()
{
		double dx = points[ipFlags.nCurrAttack].x - GetXTilePos();
		double dy = points[ipFlags.nCurrAttack].y - GetYTilePos();
		double Mag = sqrt(pow(dx,2)+pow(dy, 2));
		dx = dx / Mag;
		dy = dy / Mag;

		if(dx > 0)
			ipFlags.S_DIRECTION = true;
		else
			ipFlags.S_DIRECTION = false;

		velMovement = maxWalkSpeed * (float)dx;
		velYModifier = maxWalkSpeed * (float)dy;
}

HPTRect &EnemyBird::GetWorldLoc()
{
	SetRectangle(rectWorldLoc, 24, 16, -8, -12);

	return rectWorldLoc;
}

HPTRect &EnemyBird::GetWeaponWorldLoc()
{
	SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyBird::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		ipFlags.S_ATTACK = true;

		ipFlags.nCurrAttack = rand()%3;

		CalculateAttack();

		SetAnimation(ENEMY_BIRD_MOVE, 0, true, false, 15, true);
	}
}

void EnemyBird::processDeath()
{

	StopMovement();

	SetAnimation(ENEMY_BIRD_DEATH, 0, true, true, 10, true);
}

void EnemyBird::stop()
{
	//Stop All Movement
//	StopMovement();

	//Reset Animation
//	if(ipFlags.PrevMState != move_stop)	SetAnimation(ENEMY_BIRD_MOVE, 0, false, false, 15, true);
//	else SetAnimation(ENEMY_BIRD_MOVE, 0, false, false, 15, false);
}

void EnemyBird::processUpdate()
{

	if((player_spr->GetFrameSet() == ENEMY_BIRD_DEATH) && !player_spr->IsAnimating())
		Die();

	if(ipFlags.S_ATTACK)
	{	

		if((points[ipFlags.nCurrAttack].x == GetXTilePos()) && (points[ipFlags.nCurrAttack].y == GetYTilePos()))
		{
			//Stop All Movement
			velYModifier = 0;
			StopMovement();
			SetAnimation(ENEMY_BIRD_STAND, 0, false, false, 15, true);
			ipFlags.S_ATTACK = false;
			ipFlags.nCurrAttack = -1;
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
}*/


EnemyBird::EnemyBird(Level *curLevel, IPlayer *player)
{
	maxWalkSpeed = 100.00;   
	ipFlags.S_NO_GRAVITY = true;

	SetCurLife(6);
	SetNumLifeBars(1);
	level_class = curLevel;
	SetDamageTimer(1);

	this->player = player;

//	ipFlags.S_ATTACK = true;
	HIT = false;

	SetWeaponDamage(5);
}

EnemyBird::~EnemyBird()
{

}

/**HPTRect &EnemyBird::GetWorldLoc()
{
	if(!HIT)
		SetRectangle(rectWorldLoc, 24, 16, -8, -12);
	else
	{
		rectWorldLoc.p1.x = 0;
		rectWorldLoc.p1.y = 0;
		rectWorldLoc.p2.x = 0;
		rectWorldLoc.p2.y = 0;
	}

	return rectWorldLoc;
}*/

HPTRect &EnemyBird::GetWeaponWorldLoc()
{
	if(!HIT)
		SetRectangle(rectWeaponWorldLoc, 24, 16, -8, -12);
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyBird::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(crow);
		ipFlags.S_ATTACK = true;

		SetAnimation(ENEMY_BIRD_MOVE, 0, true, false, 15, true);
	}
}

void EnemyBird::processDamage()
{
	ipFlags.S_ATTACK = false;

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

void EnemyBird::processDeath()
{
	//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(crow);
	/* Stop All Directional Movement */
	//StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_BIRD_DEATH, 0, true, true, 10, true);
}

void EnemyBird::processUpdate()
{
	if((player_spr->GetFrameSet() == ENEMY_BIRD_DEATH) && !player_spr->IsAnimating())
		Die();

	if(((GetXTilePos() > 24) || (GetXTilePos() < 0)))
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
					StopMovement();
			
					velYModifier = 0;

					//Stop All Movement
					if(ipFlags.S_DIRECTION)
						velModifier = maxWalkSpeed;
					else
						velModifier = -maxWalkSpeed;

					HIT = true;
			
					ipFlags.S_ATTACK = false;
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
		rectDX = 24;
		rectDY = 16;
		rectXOffset = -8;
		rectYOffset = -12;

		//SetRectangle(rectWorldLoc, 24, 16, -8, -12);
	}
	else
	{
		rectDX = 0;
		rectDY = 0;
		rectXOffset = 0;
		rectYOffset = 0;

	/*	rectWorldLoc.p1.x = 0;
		rectWorldLoc.p1.y = 0;
		rectWorldLoc.p2.x = 0;
		rectWorldLoc.p2.y = 0;*/
	}
}