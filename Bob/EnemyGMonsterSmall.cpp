// EnemyGMonsterSmall.cpp: implementation of the EnemyGMonsterSmall class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyGMonsterSmall.h"

using namespace CR::Sound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyGMonsterSmall::EnemyGMonsterSmall(Level *curLevel)
{
	InitEnemy(base_enemy_type_1, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .4f,
			  0,
			  true);

	SetRenderOffset(enemy_gmonstersmall_render_offset);

	level_class = curLevel;

	rectDX = 25;
	rectDY = 40;
	rectXOffset = -nOffSet;
	rectYOffset = -10;
	m_soundFX = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::growl02::ID);
	m_monsterSound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::monster::ID);
}

EnemyGMonsterSmall::~EnemyGMonsterSmall()
{

}

/*HPTRect &EnemyGMonsterSmall::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyGMonsterSmall::GetWeaponWorldLoc()
{
//	if(player_spr->GetFrame() == 5)	SetRectangle(rectWeaponWorldLoc, 25, 4, 0, -2, ipFlags.S_DIRECTION);

	if(player_spr->GetFrameSet() == ENEMY_G_MONSTER_SMALL_ANIM_JUMP)
	{
		SetRectangle(rectWeaponWorldLoc, 15, 15, 5, -5);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyGMonsterSmall::setJumpVelocity()
{
	ipFlags.S_ON_LADDER = false;
	ipFlags.S_NEXT_TO_LADDER = false;
	ipFlags.S_NO_GRAVITY = false;

	yLoc -= 1;
	velYModifier = 0;
	velYJumpModifier = jumpMaxVelocity;
//	velMovement = 500;
//	velModifier = 200;

//	SetAnimation(0 /* ENEMY_SMALL_MONSTER_JUMP */, 0, true, true, 15, false);
}

void EnemyGMonsterSmall::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{	
		case 0:

			if (ipFlags.S_ACTIVE) m_soundFX->Play();
				
			SetWeaponDamage(base_enemy_dmg_5);
			StopMovement();
			
			if(ipFlags.S_DIRECTION) velModifier = 200;
			else velModifier = -200;
				
			velYModifier = 0;
			velYJumpModifier = jumpMaxVelocity;

			SetAnimation(ENEMY_G_MONSTER_SMALL_ANIM_JUMP, 0, true, true, 15, false);

			ipFlags.S_ATTACK = true;

			break;

		case 1:
			if (ipFlags.S_ACTIVE) m_soundFX->Play();
			/* Up and Down */
			SetWeaponDamage(base_enemy_dmg_5);
			velYModifier = 0;
			velYJumpModifier = jumpMaxVelocity * 2;

			SetAnimation(ENEMY_G_MONSTER_SMALL_ANIM_JUMP, 0, true, true, 15, false);

			ipFlags.S_ATTACK = true;

			break;

		case 2:
			/* Attack Jump */

			if (ipFlags.S_ACTIVE) m_soundFX->Play();
			StopMovement();
			SetWeaponDamage(base_enemy_dmg_5);

			velYModifier = 0;
			velYJumpModifier = jumpMaxVelocity;

			SetAnimation(ENEMY_G_MONSTER_SMALL_ANIM_JUMP, 0, true, true, 15, false);

			ipFlags.S_ATTACK = true;

			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}


void EnemyGMonsterSmall::processDamage()
{
	if (ipFlags.S_ACTIVE) m_soundFX->Play();

	ipFlags.S_ATTACK = false;

	velYModifier = -80;
	StopMovement();
	if(ipFlags.S_DAMAGED_DIRECTION)	velMovement = 200;
	else velMovement = -200;
	
//	ipFlags.S_DIRECTION = !ipFlags.S_DIRECTION;
	/* Set Damage Animation */
//	SetAnimation(0 /*ENEMY_FIRE_MONSTER_DAMAGE */, 0, true, false, 10, false);

}

void EnemyGMonsterSmall::processDeath()
{
	m_monsterSound->Play();
//soundPlayer->PlaySound(monster);

	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_G_MONSTER_SMALL_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyGMonsterSmall::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)	SetAnimation(ENEMY_G_MONSTER_SMALL_ANIM_STAND, 0, false, false, 15, true);
	else SetAnimation(ENEMY_G_MONSTER_SMALL_ANIM_STAND, 0, false, false, 15, false);
}

void EnemyGMonsterSmall::processUpdate()
{
	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();
	else if(ipFlags.S_DAMAGED) StopMovement();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_G_MONSTER_SMALL_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_G_MONSTER_SMALL_ANIM_JUMP) && !player_spr->IsAnimating())
		{
			SetAnimation(ENEMY_G_MONSTER_SMALL_ANIM_STAND, 0, true, false, 10, false);

			ipFlags.S_JUMP = false;
			ipFlags.S_ATTACK = false;
		}

	if(!ipFlags.S_DAMAGED && !ipFlags.S_ATTACK)
		switch(ipFlags.CurMState)
		{
			case move_stop:
				stop();
				break;

			default:
				break;
		}

//	SetRectangle(rectWorldLoc, 25, 40, -nOffSet, -10);
}