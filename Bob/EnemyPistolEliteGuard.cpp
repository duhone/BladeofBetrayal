// EnemyPistolEliteGuard.cpp: implementation of the EnemyPistolEliteGuard class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyPistolEliteGuard.h"
#include "Sound.h"
#include "AssetListNew.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyPistolEliteGuard::EnemyPistolEliteGuard(Level *curLevel)
{
	SetCurLife(enemy_pistol_elite_guard_cur_life);
	SetSprite(0, CR::AssetList::elite_guard);

	level_class = curLevel;


	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	HPTSprite1 *temps;
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::elite_pistol_bullet);

	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::revolver38::ID);

}

EnemyPistolEliteGuard::~EnemyPistolEliteGuard()
{

}

/*HPTRect &EnemyPistolEliteGuard::GetWorldLoc()
{


	return rectWorldLoc;
}*/

/*HPTRect &EnemyPistolEliteGuard::GetWeaponWorldLoc()
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
}*/

void EnemyPistolEliteGuard::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Left Velocity
//	velMovement -= walkAcceleration;
//	if(velMovement < -maxWalkSpeed)
		velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyPistolEliteGuard::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Right Velocity
//	velMovement += walkAcceleration;
//	if(velMovement >= maxWalkSpeed)
		velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyPistolEliteGuard::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{
		case 0:

		/*	if(!SetAnimation(ENEMY_BLUE_NINJA_ANIM_SWORD_ATTACK, 0, true, true, 22, false))
			{
				//Stop All Directional Movement
				velMovement = 0;
				velModifier = 0;
			}
			break;*/

		case 1:

			SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_PISTOL_ATTACK, 0, true, true, 20, false);
		
			Projectile *temp;

			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileEliteGuardPistolBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 16), static_cast<int>(yLoc -9 ));
				
			}
			else
			{
				temp = new ProjectileEliteGuardPistolBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 16), static_cast<int>(yLoc -9 ));
				
			}
			
			(*projectile_list).push_back(temp);

			ipFlags.S_ATTACK = true;
				
			//Stop All Directional Movement
			StopMovement();
//			velMovement = 0;
//			velModifier = 0;

			if (ipFlags.S_ACTIVE) m_soundFX->Play();
			
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyPistolEliteGuard::processDamage()
{
	ipFlags.S_ATTACK = false;
	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);

	SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_DAMAGE, 0, true, false, 10, false);

	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 20;
	else
		velMovement = -20;
}

void EnemyPistolEliteGuard::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyPistolEliteGuard::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_PISTOL_ATTACK, 0, false, false, 22, false);
}

void EnemyPistolEliteGuard::processUpdate()
{
	BelowFeetLadderCheck();

	if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_DEATH)&& !player_spr->IsAnimating())
		Die();

/*	if(ipFlags.S_ON_GROUND)
	{
		velModifier = 0;
		velYModifier = 0;
	}
	else
	{
		velYModifier += (gravityConstant * time);
	}*/

	if(ipFlags.S_ATTACK)
	{
		if(!player_spr->IsAnimating())
			ipFlags.S_ATTACK = false;
	}

	//Transition Movement State
//	TransitionMovement(ipFlags.CurMState);

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
