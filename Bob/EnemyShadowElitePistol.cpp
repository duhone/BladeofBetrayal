// EnemyShadowElitePistol.cpp: implementation of the EnemyShadowElitePistol class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyShadowElitePistol.h"
#include "Sound.h"
#include "AssetListNew.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyShadowElitePistol::EnemyShadowElitePistol(Level *curLevel)
{
//	SetCurLife(enemy_blue_ninja_set_cur_life);
	SetSprite(1, CR::AssetList::elite_guard);

	level_class = curLevel;

	SetRenderOffset(9);
	
	SetCurLife(8);
	SetNumLifeBars(2);
	
	//SetCurLife(15);
	//SetNumLifeBars(3);

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::revolver38::ID);
}

EnemyShadowElitePistol::~EnemyShadowElitePistol()
{

}
/*
HPTRect &EnemyShadowElitePistol::GetWorldLoc()
{


	return rectWorldLoc;
}
*/
void EnemyShadowElitePistol::processLeft()
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

void EnemyShadowElitePistol::processRight()
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

void EnemyShadowElitePistol::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{
		case 0:

		case 1:

			SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_PISTOL_ATTACK, 0, true, true, 20, true);
		
			Projectile *temp;

			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileEliteGuardPistolBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet + 16), static_cast<int>(yLoc -9 ));
				
				
				temp->SetWeaponDamage(8);
			}
			else
			{
				temp = new ProjectileEliteGuardPistolBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet - 16), static_cast<int>(yLoc -9 ));
				
				temp->SetWeaponDamage(8);
			}
			
			(*projectile_list).push_back(temp);

			ipFlags.S_ATTACK = true;
				
			//Stop All Directional Movement
			velMovement = 0;
			velModifier = 0;

			if (ipFlags.S_ACTIVE) m_soundFX->Play();

			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyShadowElitePistol::processDamage()
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

void EnemyShadowElitePistol::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyShadowElitePistol::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_PISTOL_ELITE_GUARD_ANIM_PISTOL_ATTACK, 0, false, false, 22, false);
}

void EnemyShadowElitePistol::processUpdate()
{
	BelowFeetLadderCheck();

	if((player_spr->GetFrameSet() == ENEMY_BATON_ELITE_GUARD_ANIM_DEATH)&& !player_spr->IsAnimating())
		Die();

	if(ipFlags.S_ATTACK)
	{
		if(!player_spr->IsAnimating())
			ipFlags.S_ATTACK = false;
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
