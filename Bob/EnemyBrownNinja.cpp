// EnemyBrownNinja.cpp: implementation of the EnemyBrownNinja class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyBrownNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyBrownNinja::EnemyBrownNinja(Level *curLevel)
{
	SetCurLife(enemy_brown_ninja_set_cur_life);
	SetSprite(1, enemy_brown_ninja_sprite);
	level_class = curLevel;
}

EnemyBrownNinja::~EnemyBrownNinja()
{
}

/*HPTRect &EnemyBrownNinja::GetWorldLoc()
{
	rectWorldLoc.p1.x = static_cast<int>(xLoc - 20 + nOffSet); 
	rectWorldLoc.p2.x = static_cast<int>(xLoc - 5 + nOffSet);
	rectWorldLoc.p1.y = static_cast<int>(yLoc - 15);
	rectWorldLoc.p2.y = static_cast<int>(yLoc + 30);

	return rectWorldLoc;
}*/

HPTRect &EnemyBrownNinja::GetWeaponWorldLoc()
{
	if(ipFlags.S_DIRECTION)
	{
		rectWeaponWorldLoc.p1.x = static_cast<int>(xLoc + nOffSet);
		rectWeaponWorldLoc.p2.x = static_cast<int>(xLoc + 20 + nOffSet);
		rectWeaponWorldLoc.p1.y = static_cast<int>(yLoc - 2);
		rectWeaponWorldLoc.p2.y = static_cast<int>(yLoc + 2);
	}
	else
	{
		rectWeaponWorldLoc.p1.x = static_cast<int>(xLoc - 20 - nOffSet);
		rectWeaponWorldLoc.p2.x = static_cast<int>(xLoc - nOffSet);
		rectWeaponWorldLoc.p1.y = static_cast<int>(yLoc - 2);
		rectWeaponWorldLoc.p2.y = static_cast<int>(yLoc + 2);
	}

	return rectWeaponWorldLoc;
}

void EnemyBrownNinja::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_BROWN_NINJA_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_BROWN_NINJA_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Left Velocity
//	velMovement -= walkAcceleration;
//	if(velMovement < -maxWalkSpeed)
		velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyBrownNinja::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_BROWN_NINJA_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_BROWN_NINJA_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Right Velocity
//	velMovement += walkAcceleration;
//	if(velMovement >= maxWalkSpeed)
		velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyBrownNinja::processDamage()
{
	SetAnimation(ENEMY_BROWN_NINJA_ANIM_DAMAGE, 0, true, false, 10, false);

	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 40;
	else
		velMovement = -40;
}

void EnemyBrownNinja::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_BROWN_NINJA_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_BROWN_NINJA_ANIM_MOVE, 0, false, false, 22, false);
}

void EnemyBrownNinja::processUpdate()
{

//	BelowFeetLadderCheck();

	if(!ipFlags.S_DEAD)
	{
/*	if(ipFlags.S_ON_GROUND)
	{
		velModifier = 0;
		velYModifier = 0;
	}
	else
	{
		velYModifier += (gravityConstant * time);
	}*/

	//Transition Movement State
//	TransitionMovement(ipFlags.CurMState);

	// Apply Velocity Modifier
	if(!ipFlags.S_DAMAGED)
	{
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

//	ProcessCalculations();
	}

	rectWorldLoc.p1.x = static_cast<int>(xLoc - 20 + nOffSet); 
	rectWorldLoc.p2.x = static_cast<int>(xLoc - 5 + nOffSet);
	rectWorldLoc.p1.y = static_cast<int>(yLoc - 15);
	rectWorldLoc.p2.y = static_cast<int>(yLoc + 30);
}