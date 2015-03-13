// EnemyShadowEliteRifle.cpp: implementation of the EnemyShadowEliteRifle class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyShadowEliteRifle.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyShadowEliteRifle::EnemyShadowEliteRifle(Level *curLevel)
{
	SetRenderOffset(enemy_elite_guard_render_offset);
	//SetCurLife(enemy_blue_ninja_set_cur_life);
	SetSprite(1, CR::AssetList::elite_guard);

	level_class = curLevel;

	SetCurLife(9);
	SetNumLifeBars(2);
	
	//SetCurLife(20);
	//SetNumLifeBars(4);

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::m16burst3::ID);
}

EnemyShadowEliteRifle::~EnemyShadowEliteRifle()
{

}

/*HPTRect &EnemyShadowEliteRifle::GetWorldLoc()
{


	return rectWorldLoc;
}
*/
void EnemyShadowEliteRifle::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Left Velocity
	//velMovement -= walkAcceleration;
//	if(velMovement < -maxWalkSpeed)
		velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyShadowEliteRifle::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Right Velocity
//	velMovement += walkAcceleration;
//	if(velMovement >= maxWalkSpeed)
		velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyShadowEliteRifle::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{
		case 0:
		case 1:

			SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_RIFLE_ATTACK, 0, true, true, 20, true);
		
			Projectile *temp;

			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc- 6),.25f);
				
				temp->SetWeaponDamage(9);
				(*projectile_list).push_back(temp);

				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc- 6),.40f);
				
				temp->SetWeaponDamage(9);
				(*projectile_list).push_back(temp);

				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc- 6),.55f);
				
				temp->SetWeaponDamage(9);
				(*projectile_list).push_back(temp);
			}

			else
			{
				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 6),.25f);
				
				temp->SetWeaponDamage(9);
				(*projectile_list).push_back(temp);
				
				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 6),.40f);
				
				temp->SetWeaponDamage(9);
				(*projectile_list).push_back(temp);

				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 6),.55f);
				
				temp->SetWeaponDamage(9);
				(*projectile_list).push_back(temp);
			}
			
			if (ipFlags.S_ACTIVE) m_soundFX->Play();
//			if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(carbine);
			

			ipFlags.S_ATTACK = true;
				
			//Stop All Directional Movement
			velMovement = 0;
			velModifier = 0;
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyShadowEliteRifle::processDamage()
{
	ipFlags.S_ATTACK = false;
	
	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//	if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);

	SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_DAMAGE, 0, true, false, 10, false);

	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 20;
	else
		velMovement = -20;
}

void EnemyShadowEliteRifle::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyShadowEliteRifle::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_RIFLE_ATTACK, 0, false, false, 22, false);
}

void EnemyShadowEliteRifle::processUpdate()
{
	BelowFeetLadderCheck();

	if((player_spr->GetFrameSet() == ENEMY_RIFLE_ELITE_GUARD_ANIM_DEATH)&& !player_spr->IsAnimating())
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
