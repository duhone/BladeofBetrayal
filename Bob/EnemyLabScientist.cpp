// EnemyLabScientist.cpp: implementation of the EnemyLabScientist class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyLabScientist.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyLabScientist::EnemyLabScientist(Level *curLevel, bool S_ON_FIRE)
{
	InitEnemy(base_enemy_type_1, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .45f,
			  0,
			  true);

	SetRenderOffset(enemy_lab_scientist_render_offset);


	level_class = curLevel;
	this->S_ON_FIRE = S_ON_FIRE;

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::explode02::ID);
	m_firedeathSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::firedeath::ID);
}

EnemyLabScientist::~EnemyLabScientist()
{
}

/*HPTRect &EnemyLabScientist::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyLabScientist::GetWeaponWorldLoc()
{
	if(ipFlags.S_ATTACK)
	{
		SetRectangle(rectWeaponWorldLoc, 60, 60, -30, -30);
	}
	else 
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyLabScientist::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		if(S_ON_FIRE)
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE_FLAME, 0, true, false, 15, true);
		else
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE, 0, true, false, 15, true);
	else
		if(S_ON_FIRE)
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE_FLAME, 0, true, false, 15, false);
		else
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE, 0, true, false, 15, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyLabScientist::processRight()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_right)
		if(S_ON_FIRE)
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE_FLAME, 0, true, false, 15, true);
		else
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE, 0, true, false, 15, true);
	else
		if(S_ON_FIRE)
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE_FLAME, 0, true, false, 15, false);
		else
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE, 0, true, false, 15, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyLabScientist::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		if(S_ON_FIRE)
			SetWeaponDamage(static_cast<int>(base_enemy_dmg_4 * 2));
		else
			SetWeaponDamage(static_cast<int>(base_enemy_dmg_4 * .5));

		if(S_ON_FIRE)
		{
			if (ipFlags.S_ACTIVE) m_soundFX->Play();
		
			/* Scientist Flame Explode */
			if(!SetAnimation(ENEMY_LAB_SCIENTIST_ATTACK, 0, true, true, 15, false))
				StopMovement();

		}
		else
		{
			if(!SetAnimation(ENEMY_LAB_SCIENTIST_DEATH, 0, true, true, 15, false))
				StopMovement();
		}
	}
}

void EnemyLabScientist::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

		if(S_ON_FIRE)
		{
			if (ipFlags.S_ACTIVE) m_soundFX->Play();

			/* Scientist Flame Explode */
			if(!SetAnimation(ENEMY_LAB_SCIENTIST_ATTACK, 0, true, true, 15, false))
				StopMovement();

		}
		else
		{
			if(!SetAnimation(ENEMY_LAB_SCIENTIST_DEATH, 0, true, true, 15, false))
				StopMovement();
		}
}

void EnemyLabScientist::processDamage()
{
	ipFlags.S_ATTACK = false;

	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyLabScientist::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		if(S_ON_FIRE)
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE_FLAME, 0, true, false, 15, true);
		else
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE, 0, true, false, 15, true);
	else
		if(S_ON_FIRE)
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE_FLAME, 0, true, false, 15, false);
		else
			SetAnimation(ENEMY_LAB_SCIENTIST_MOVE, 0, true, false, 15, false);
}

void EnemyLabScientist::processUpdate()
{
	BelowFeetLadderCheck();

	flametimer -= time;

	if(flametimer < 0)
	{
		if (ipFlags.S_ACTIVE) m_firedeathSound->Play();
		flametimer = 5;
	}

	if(!ipFlags.S_DEAD)
	{
		if(((player_spr->GetFrameSet() == ENEMY_LAB_SCIENTIST_DEATH) ||
			(player_spr->GetFrameSet() == ENEMY_LAB_SCIENTIST_ATTACK)) &&
			!player_spr->IsAnimating())
			Die();

//		if(ipFlags.S_ATTACK)
//		{
//			if((player_spr->GetFrameSet() == ENEMY_LAB_SCIENTIST_DEATH) && !player_spr->IsAnimating())
//				ipFlags.S_ATTACK = false;
//		}

		// Apply Velocity Modifier
		if(!ipFlags.S_DAMAGED)
		{
			if(!ipFlags.S_ATTACK)
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