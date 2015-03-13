// EnemyPunk.cpp: implementation of the EnemyPunk class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyPunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyPunk::EnemyPunk(Level *curLevel)
{
	InitEnemy(12, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  1,
			  0,
			  true);

	SetRenderOffset(enemy_gmonstersmall_render_offset);
	level_class = curLevel;
	jumpMaxVelocity = -200.0;
	
	rectDX = 25;
	rectDY = 40;
	rectXOffset = -nOffSet;
	rectYOffset = -10;
	SetWeaponDamage(5);
}

EnemyPunk::~EnemyPunk()
{
}

/*HPTRect &EnemyPunk::GetWorldLoc()
{

	return rectWorldLoc;
}*/

HPTRect &EnemyPunk::GetWeaponWorldLoc()
{
	if(player_spr->GetFrameSet() == ENEMY_PUNK_ANIM_JUMP)
	{
		SetRectangle(rectWeaponWorldLoc, 15, 15, 5, -5);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyPunk::setJumpVelocity()
{
	ipFlags.S_ON_LADDER = false;
	ipFlags.S_NEXT_TO_LADDER = false;
	ipFlags.S_NO_GRAVITY = false;

	yLoc -= 1;
	velYModifier = 0;
	velYJumpModifier = jumpMaxVelocity;
}

void EnemyPunk::processAttack()
{
	if(!ipFlags.S_ATTACK && !ipFlags.S_DAMAGED && !ipFlags.S_DEAD)
	{
		ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{	
		case 0:

//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(jump00);

			StopMovement();
			
			if(ipFlags.S_DIRECTION) velModifier = 200;
			else velModifier = -200;
				
			velYModifier = 0;
			velYJumpModifier = jumpMaxVelocity;

			SetAnimation(ENEMY_PUNK_ANIM_JUMP, 0, true, true, 15, false);

			ipFlags.S_ATTACK = true;

			break;

		case 1:

//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(jump00);


			/* Up and Down */
			velYModifier = 0;
			velYJumpModifier = jumpMaxVelocity * 2;

			SetAnimation(ENEMY_PUNK_ANIM_JUMP, 0, true, true, 15, false);

			ipFlags.S_ATTACK = true;

			break;

		case 2:

//		if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(jump00);


			/* Attack Jump */

			StopMovement();

			velYModifier = 0;
			velYJumpModifier = jumpMaxVelocity;

			SetAnimation(ENEMY_PUNK_ANIM_JUMP, 0, true, true, 15, false);

			ipFlags.S_ATTACK = true;

			break;

		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
}


void EnemyPunk::processDamage()
{
	if (ipFlags.S_ACTIVE) 
		m_soundFXDamage->Play();
//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(damage00);


	ipFlags.S_ATTACK = false;
	
	velYModifier = -80;
	StopMovement();
	if(ipFlags.S_DAMAGED_DIRECTION)	velMovement = 200;
	else velMovement = -200;
}

void EnemyPunk::processDeath()
{
	/* Stop All Directional Movement */
	StopMovement();

	/* Set Death Animation */
	SetAnimation(ENEMY_PUNK_ANIM_DEATH, 0, true, true, 10, true);
}

void EnemyPunk::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)	SetAnimation(ENEMY_PUNK_ANIM_STAND, 0, false, false, 15, true);
	else SetAnimation(ENEMY_PUNK_ANIM_STAND, 0, false, false, 15, false);
}

void EnemyPunk::processUpdate()
{
//	BelowFeetLadderCheck();

	/* Stop All Directional Movement */
	if(!ipFlags.S_ON_GROUND) ApplyGravity();
	else if(ipFlags.S_DAMAGED) StopMovement();

	/* Check for End of Death Animation */
	if((player_spr->GetFrameSet() == ENEMY_PUNK_ANIM_DEATH) && !player_spr->IsAnimating())
		Die();

	/* Check for end of an attack state */
	if(ipFlags.S_ATTACK)
		if((player_spr->GetFrameSet() == ENEMY_PUNK_ANIM_JUMP) && !player_spr->IsAnimating())
		{
			SetAnimation(ENEMY_PUNK_ANIM_STAND, 0, true, false, 10, false);

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

	//SetRectangle(rectWorldLoc, 25, 40, -nOffSet, -10);
}