// EnemyZombiePrisoner.cpp: implementation of the EnemyZombiePrisoner class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyZombiePrisoner.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyZombiePrisoner::EnemyZombiePrisoner(Level *curLevel)
{
	SetRenderOffset(enemy_prisoner_zombie_render_offset);
	SetCurLife(enemy_prisoner_zombie_cur_life);
	SetNumLifeBars((int)(enemy_prisoner_zombie_cur_life * .2f + 1));
	SetDamageTimer(.25);
	SetWeaponDamage(3);
	level_class = curLevel;

	ipFlags.S_ATTACK = true;

	SetMaxWalkVelocity(static_cast<float>(rand()%30 + 30));

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::growl01::ID);
}

EnemyZombiePrisoner::~EnemyZombiePrisoner()
{
}

/*HPTRect &EnemyZombiePrisoner::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyZombiePrisoner::GetWeaponWorldLoc()
{
	/* Center (0,0), offset by Render Offset */
	SetRectangle(rectWeaponWorldLoc, 15, 45, -nOffSet, -15);


//	if(ipFlags.S_ATTACK)
//	{
//		SetRectangle(rectWeaponWorldLoc, 60, 60, -30, -30);
//	}
//	else 
//		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyZombiePrisoner::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_PRISONER_ZOMBIE_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_PRISONER_ZOMBIE_ANIM_MOVE, 0, true, false, 15, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyZombiePrisoner::processRight()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_PRISONER_ZOMBIE_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_PRISONER_ZOMBIE_ANIM_MOVE, 0, true, false, 15, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyZombiePrisoner::processAttack()
{
//	if(!ipFlags.S_ATTACK)
//	{
//		ipFlags.S_ATTACK = true;

		/* Scientist Flame Explode */
//		if(!SetAnimation(ENEMY_PRISONER_ZOMBIE_ANIM_ATTACK, 0, true, true, 15, false))
//		{
			//Stop All Directional Movement
//			velMovement = 0;
//			velModifier = 0;
//		}
//	}
}

void EnemyZombiePrisoner::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_PRISONER_ZOMBIE_ANIM_ATTACK, 0, true, true, 15, true);
}

void EnemyZombiePrisoner::processDamage()
{
	if (ipFlags.S_ACTIVE)
		m_soundFX->Play();
	
	ipFlags.S_ATTACK = false;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyZombiePrisoner::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_PRISONER_ZOMBIE_ANIM_MOVE, 0, true, false, 15, true);
	else
		SetAnimation(ENEMY_PRISONER_ZOMBIE_ANIM_MOVE, 0, true, false, 15, false);
}

void EnemyZombiePrisoner::processUpdate()
{
	ipFlags.S_ATTACK = true;


	BelowFeetLadderCheck();

	if(!ipFlags.S_DEAD)
	{
		if((player_spr->GetFrameSet() == ENEMY_PRISONER_ZOMBIE_ANIM_ATTACK) && !player_spr->IsAnimating())
			Die();

		if(ipFlags.S_ATTACK)
		{
			if((player_spr->GetFrameSet() == ENEMY_PRISONER_ZOMBIE_ANIM_ATTACK) && !player_spr->IsAnimating())
				ipFlags.S_ATTACK = false;
		}

		// Apply Velocity Modifier
		if(!ipFlags.S_DAMAGED)
		{
		//	if(!ipFlags.S_ATTACK)
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
	}
}