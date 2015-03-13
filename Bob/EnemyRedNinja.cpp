// EnemyRedNinja.cpp: implementation of the EnemyRedNinja class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyRedNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyRedNinja::EnemyRedNinja(Level *curLevel)
{
	InitEnemy(base_enemy_type_1, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .5,
			  0,
			  true);

	level_class = curLevel;

	rectDX = 15;
	rectDY = 45;
	rectXOffset = -nOffSet;
	rectYOffset = -15;
	HPTSprite1 *temps;
	temps = graphics_engine->CreateSprite1();
	temps->SetImage(CR::AssetList::ninja_star);

}

EnemyRedNinja::~EnemyRedNinja()
{
}

/*HPTRect &EnemyRedNinja::GetWorldLoc()
{


	return rectWorldLoc;
}*/

void EnemyRedNinja::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{	
			Projectile *temp;

		case 0:
			break;

		case 1:
		case 2:
		
			/* Set Attack State */
			ipFlags.S_ATTACK = true;

			/* Create Ninja Star Projectile */
			if(ipFlags.S_DIRECTION)
			{
				temp = new ProjectileNinjaStar(ipFlags.S_DIRECTION, static_cast<int>(xLoc + nOffSet), static_cast<int>(yLoc - 15));
				
			}
			else
			{
				temp = new ProjectileNinjaStar(ipFlags.S_DIRECTION, static_cast<int>(xLoc - nOffSet), static_cast<int>(yLoc - 15));
				
			}
			(*projectile_list).push_back(temp);
				
			/* Stop All Directional Movement */
			StopMovement();

			/* Set Animation */
			SetAnimation(ENEMY_RED_NINJA_ANIM_ATTACK, 0, true, true, 20, true);

			/* Play Star Throw Sound */
//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(swoosh00);
			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}

void EnemyRedNinja::processDamage()
{
	ipFlags.S_ATTACK = false;

	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);
	if(ipFlags.S_DAMAGED_DIRECTION) velMovement = 20;
	else velMovement = -20;
	
	/* Set Damage Animation */
	SetAnimation(ENEMY_RED_NINJA_ANIM_DAMAGE, 0, true, false, 10, false);

}

void EnemyRedNinja::processDeath()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_RED_NINJA_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyRedNinja::stop()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Frame 0 of Attack Animation */
	if(ipFlags.PrevMState != move_stop) SetAnimation(ENEMY_RED_NINJA_ANIM_ATTACK, 0, false, false, 22, true);
	else SetAnimation(ENEMY_RED_NINJA_ANIM_ATTACK, 0, false, false, 22, false);
}

void EnemyRedNinja::processUpdate()
{
//	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_RED_NINJA_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_RED_NINJA_ANIM_ATTACK) && !player_spr->IsAnimating())
			ipFlags.S_ATTACK = false;
	
	if(!ipFlags.S_DAMAGED && !ipFlags.S_ATTACK)
		switch(ipFlags.CurMState)
		{
			case move_stop:
				stop();
				break;

			default:
				break;
		}
}