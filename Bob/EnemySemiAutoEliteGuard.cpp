// EnemySemiAutoEliteGuard.cpp: implementation of the EnemySemiAutoEliteGuard class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemySemiAutoEliteGuard.h"
#include "AssetListNew.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemySemiAutoEliteGuard::EnemySemiAutoEliteGuard(Level *curLevel)
{
	SetRenderOffset(enemy_elite_guard_render_offset);
	SetCurLife(enemy_rifle_elite_guard_cur_life);
	SetSprite(1, CR::AssetList::elite_guard);

	level_class = curLevel;


	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	HPTSprite1 *temps;
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::elite_rifle_bullet);

	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::m16burst3::ID);
}

EnemySemiAutoEliteGuard::~EnemySemiAutoEliteGuard()
{

}

/*HPTRect &EnemySemiAutoEliteGuard::GetWorldLoc()
{


	return rectWorldLoc;
}
*/
void EnemySemiAutoEliteGuard::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE, 0, true, false, 22, false);

	//Accelerate Left Velocity
//	velMovement -= walkAcceleration;
//	if(velMovement < -maxWalkSpeed)
		velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemySemiAutoEliteGuard::processRight()
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

void EnemySemiAutoEliteGuard::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{
		case 0:
		case 1:

			SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_RIFLE_ATTACK, 0, true, true, 20, false);
		
			Projectile *temp;

			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc- 6),.25f);
				
				(*projectile_list).push_back(temp);

				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc- 6),.40f);
			
				(*projectile_list).push_back(temp);

				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet+20), static_cast<int>(yLoc- 6),.55f);
				
				(*projectile_list).push_back(temp);
			}

			else
			{
				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 6),.25f);
				
				(*projectile_list).push_back(temp);
				
				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 6),.40f);
				
				(*projectile_list).push_back(temp);

				temp = new ProjectileEliteGuardRifleBullet(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet-20), static_cast<int>(yLoc - 6),.55f);
				
				(*projectile_list).push_back(temp);
			}

			if (ipFlags.S_ACTIVE) m_soundFX->Play();


			ipFlags.S_ATTACK = true;
				
			//Stop All Directional Movement
			StopMovement();
//			velMovement = 0;
//			velModifier = 0;
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemySemiAutoEliteGuard::processDamage()
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

void EnemySemiAutoEliteGuard::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemySemiAutoEliteGuard::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_RIFLE_ELITE_GUARD_ANIM_RIFLE_ATTACK, 0, false, false, 22, false);
}

void EnemySemiAutoEliteGuard::processUpdate()
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
