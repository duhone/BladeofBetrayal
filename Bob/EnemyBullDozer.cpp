// EnemyBullDozer.cpp: implementation of the EnemyBullDozer class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyBullDozer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyBullDozer::EnemyBullDozer(Level *curLevel)
{
	SetCurLife(enemy_green_ninja_set_cur_life);
	SetNumLifeBars((int)(enemy_green_ninja_set_cur_life * .2f + 1));

	SetDamageTimer(.5);
	level_class = curLevel;

	ipFlags.S_NO_GRAVITY = true;

	SetRenderOffset(0, -8);

	rectDX = 0;
	rectDY = 0;
	rectXOffset = 0;
	rectYOffset = 0;

	ipFlags.S_NO_COLLISION = true;

	SetMaxWalkVelocity(50.0f);
	SetWeaponDamage(20);

	btimer = 1;
	btimer2 = 2.5;
}

EnemyBullDozer::~EnemyBullDozer()
{
}

HPTRect &EnemyBullDozer::GetWeaponWorldLoc()
{
	SetRectangle(rectWeaponWorldLoc, 138, 80, -68, -35);

	return rectWeaponWorldLoc;
}

void EnemyBullDozer::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		//soundPlayer->PlaySound(bulldozerstart);
		ipFlags.S_DIRECTION = true;
		ipFlags.S_ATTACK = true;
		velMovement = maxWalkSpeed;
		
		SetAnimation(0, 0, true, false, 5, true);
	}
}

void EnemyBullDozer::stop()
{
	ipFlags.S_ATTACK = false;

	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	SetAnimation(0, 0, false, false, 22, true);
}

void EnemyBullDozer::processUpdate()
{
	if(ipFlags.S_ATTACK)
	{
		btimer -= time;
		btimer2 -= time;

		if(btimer <= 0)
		{
			//soundPlayer->PlaySound(clamps);
			btimer = 1;
		}

		if(btimer2 <= 0)
		{
			//soundPlayer->PlaySound(bulldozerstart);
			btimer2 = 2.5;
		}
	}

	ipFlags.S_DIRECTION = true;

//	if(!ipFlags.S_ATTACK)
		switch(ipFlags.CurMState)
		{
			case move_stop:
				stop();
				break;		

			default:
				break;
		}


}