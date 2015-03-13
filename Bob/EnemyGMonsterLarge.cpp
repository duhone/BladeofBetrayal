// EnemyGMonsterLarge.cpp: implementation of the EnemyGMonsterLarge class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyGMonsterLarge.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyGMonsterLarge::EnemyGMonsterLarge(Level *curLevel)
{
	InitEnemy(base_enemy_type_3, 
		      base_x_velocity * 1.33,
			  base_y_velocity,
			  0,
			  .25,
			  0,
			  true);

//	SetRenderOffset(0, -15);

//	SetMaxWalkVelocity(static_cast<float>(enemy_ninja_max_walk_velocity*1.33));

//	SetCurLife(1);
//	SetNumLifeBars(1);

	this->level_class = curLevel;
	SetWeaponDamage(base_enemy_dmg_7);
	
	rectDX = 30;
	rectDY = 30;
	rectXOffset = -15;
	rectYOffset = -0;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::growl01::ID);
	m_firedeathSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::firedeath::ID);
}

EnemyGMonsterLarge::~EnemyGMonsterLarge()
{
}

/*HPTRect &EnemyGMonsterLarge::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyGMonsterLarge::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_LARGE_MONSTER_ROLL) ||(player_spr->GetFrameSet() == ENEMY_LARGE_MONSTER_ROLL_PREP)  )
		SetRectangle(rectWeaponWorldLoc, 30, 30, -15, 0);
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyGMonsterLarge::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
	{
		if (ipFlags.S_ACTIVE) m_soundFX->Play();

		SetAnimation(ENEMY_LARGE_MONSTER_MOVE, 0, true, false, 20, true);
	}
	else
		SetAnimation(ENEMY_LARGE_MONSTER_MOVE, 0, true, false, 20, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyGMonsterLarge::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
	{
		if (ipFlags.S_ACTIVE) m_soundFX->Play();
		SetAnimation(ENEMY_LARGE_MONSTER_MOVE, 0, true, false, 20, true);
	}
	else
		SetAnimation(ENEMY_LARGE_MONSTER_MOVE, 0, true, false, 20, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyGMonsterLarge::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		switch(ipFlags.nCurrAttack)
		{
		case 0:
			{
				ipFlags.S_ATTACK = true;
				if(!SetAnimation(ENEMY_LARGE_MONSTER_ROLL_PREP, 0, true, true, 15, false))
				{
//				if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(growl02);
					StopMovement();

					if(ipFlags.S_DIRECTION)
						velMovement = maxWalkSpeed * 2;
					else
						velMovement = -maxWalkSpeed * 2;

					if (ipFlags.S_ACTIVE) m_firedeathSound->Play();

				}
			};
			break;
		case 1:
			{
				ipFlags.S_ATTACK = false;
				SetAnimation(ENEMY_LARGE_MONSTER_STAND, 0, true, false, 10, true);
			}
			break;
		default:
			break;
		}
	}
}

void EnemyGMonsterLarge::processDeath()
{
	

	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_LARGE_MONSTER_DEATH, 0, true, true, 10, true);
}

void EnemyGMonsterLarge::processDamage()
{
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(growl02);

	
	ipFlags.S_ATTACK = false;

	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 60;
	else
		velMovement = -60;
}

void EnemyGMonsterLarge::stop()
{
	//Stop All Movement
	StopMovement();

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_LARGE_MONSTER_STAND, 0, true, false, 10, true);
	else
		SetAnimation(ENEMY_LARGE_MONSTER_STAND, 0, true, false, 10, false);
}

void EnemyGMonsterLarge::processUpdate()
{
	BelowFeetLadderCheck();
	
	if(!ipFlags.S_DEAD)
	{
	//	ipFlags.S_ACTIVE = true;

		//ApplyGravity();

		if((player_spr->GetFrameSet() == ENEMY_LARGE_MONSTER_DEATH) && !player_spr->IsAnimating())
			Die();

		if(ipFlags.S_ATTACK)
		{
			if(!player_spr->IsAnimating() && player_spr->GetFrameSet() == ENEMY_LARGE_MONSTER_ROLL_PREP)
			{
				SetAnimation(ENEMY_LARGE_MONSTER_ROLL, 0, true, false,10, false);
			}
			else if(player_spr->GetFrameSet() == ENEMY_LARGE_MONSTER_ROLL)
			{
				float x, y;

				GetVelocityVector(&x, &y);

				if((x <= 1) && (x >= -1))
				{
					ipFlags.S_ATTACK = false;
					SetAnimation(ENEMY_LARGE_MONSTER_STAND, 0, true, false, 10, true);
				}

				else if(ipFlags.S_DIRECTION)
				{
					if((level_class->GetLevelData(GetXTilePos()+4, GetYTilePos()) == 0) ||
						(level_class->GetLevelData(GetXTilePos()+4, GetYTilePos()) == CLIMBLADDER))
					{
						StopMovement();
						ipFlags.S_ATTACK = false;
						SetAnimation(ENEMY_LARGE_MONSTER_STAND, 0, true, false, 10, true);
					}
				}
				else if(!ipFlags.S_DIRECTION)
				{
					if((level_class->GetLevelData(GetXTilePos()-4, GetYTilePos()) == 0) ||
						(level_class->GetLevelData(GetXTilePos()-4, GetYTilePos()) == CLIMBLADDER))
					{
						StopMovement();
						ipFlags.S_ATTACK = false;
						SetAnimation(ENEMY_LARGE_MONSTER_STAND, 0, true, false, 10, true);
					}
				}

			}
		}

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

//	SetRectangle(rectWorldLoc, 30, 30, -15, 0);
}