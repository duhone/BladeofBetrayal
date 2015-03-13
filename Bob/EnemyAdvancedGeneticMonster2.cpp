// EnemyAdvancedGeneticMonster2.cpp: implementation of the EnemyAdvancedGeneticMonster2 class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyAdvancedGeneticMonster2.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EnemyAdvancedGeneticMonster2::EnemyAdvancedGeneticMonster2(Level *curLevel)
{
	SetRenderOffset(13, -20);
	SetCurLife(enemy_mr_thomas_set_cur_life * 1.7);
	SetNumLifeBars(enemy_mr_thomas_set_cur_life_bars * 1.7);
	SetPlayerRectangle(15, 55);
	maxWalkSpeed = 130.00;   
	SetDamageTimer(.50);
	level_class = curLevel;
	jumpMaxVelocity = -400;
	deathtimer = 2.5;
}

EnemyAdvancedGeneticMonster2::~EnemyAdvancedGeneticMonster2()
{

}

void EnemyAdvancedGeneticMonster2::setJumpVelocity()
{
	if(ipFlags.S_DIRECTION) velModifier = 100;
	else velModifier = -100;

	ipFlags.S_ON_GROUND = false;
	ipFlags.S_NO_GRAVITY = false;
	ipFlags.S_JUMP = true;
	
	yLoc -= 1;

	velYModifier = 0;
	velYJumpModifier = jumpMaxVelocity;

	SetAnimation(ENEMY_AGM_ANIM_JUMP2, 0, true, true, 8, true);
}

/*HPTRect &EnemyAdvancedGeneticMonster::GetWorldLoc()
{
	if(player_spr->GetFrameSet() == ENEMY_AGM_ANIM_BACK_SPIKE_1)
		SetRectangle(rectWorldLoc, 40, 30, -5, 0);
	else
		SetRectangle(rectWorldLoc, 30, 60, -15, -30);
	
	return rectWorldLoc;
}*/

void EnemyAdvancedGeneticMonster2::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_AGM_ANIM_DEATH2, 0, true, true, 4, false);
}

HPTRect &EnemyAdvancedGeneticMonster2::GetWeaponWorldLoc()
{
	if(ipFlags.S_VISIBLE)
	{
		if((player_spr->GetFrameSet() == ENEMY_AGM_ANIM_ATTACK_CLAW2))
		{
			if(player_spr->GetFrame() == 7)
				SetRectangle(rectWeaponWorldLoc, 40, 4, 0, -15);
			else if(player_spr->GetFrame() == 8)
				SetRectangle(rectWeaponWorldLoc, 40, 4, 0, -15);
			else if(player_spr->GetFrame() == 9)
				SetRectangle(rectWeaponWorldLoc, 40, 4, 0, -15);
		}	

		else
			SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);
	}
	else
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);

	return rectWeaponWorldLoc;
}

void EnemyAdvancedGeneticMonster2::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)	SetAnimation(ENEMY_AGM_ANIM_MOVE2, 0, true, false, 15, true);
	else SetAnimation(ENEMY_AGM_ANIM_MOVE2, 0, true, false, 15, false);

	//Accelerate Left Velocity
	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyAdvancedGeneticMonster2::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right) SetAnimation(ENEMY_AGM_ANIM_MOVE2, 0, true, false, 15, true);
	else SetAnimation(ENEMY_AGM_ANIM_MOVE2, 0, true, false, 15, false);

	//Accelerate Right Velocity
	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}

void EnemyAdvancedGeneticMonster2::stop()
{
	if(!ipFlags.S_JUMP)
	{

	//Stop All Movement
	StopMovement();

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)	SetAnimation(ENEMY_AGM_ANIM_STAND2, 0, false, false, 15, true);
	else SetAnimation(ENEMY_AGM_ANIM_STAND2, 0, false, false, 15, false);

	}
}

void EnemyAdvancedGeneticMonster2::processDamage()
{
}

void EnemyAdvancedGeneticMonster2::processAttack()
{
	if(!ipFlags.S_ATTACK)
	{
	//	ipFlags.S_ATTACK = true;

		switch(ipFlags.nCurrAttack)
		{	
		case 0: /* CLAW ATTACK */
			{
//				sound_processor->PlaySound(game_sounds->growl00);
//				sound_processor->PlaySound(game_sounds->swoosh);
				SetWeaponDamage(15);
				SetAnimation(ENEMY_AGM_ANIM_ATTACK_CLAW2, 0, true, true, 25, true);
				StopMovement();
				ipFlags.S_ATTACK = true;
			}
			break;	
		default:
			ipFlags.S_ATTACK = false;
			break;
		}
	}
		SetRectangle(rectWorldLoc, 30, 60, -15, -30);
}

// Mr Thomas Taunt Action
//void EnemyAdvancedGeneticMonster::processSpecial1()
//{
//	velMovement = 0;
//	SetAnimation(ENEMY_MR_THOMAS_ANIM_TAUNT, 0, true, true, 10, false);
//}



void EnemyAdvancedGeneticMonster2::processUpdate()
{
	BelowFeetLadderCheck();

	if(!ipFlags.S_DEAD)
		ipFlags.S_ACTIVE = true;

	if(ipFlags.S_JUMP)
	{
		/* check for noncollidable ground tile */
		if(level_class != 0)
		{
			if((level_class->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBLADDER) ||
			   (level_class->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBROPE) ||
			   (level_class->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBBLOCKRIGHT) ||
			   (level_class->GetLevelData(GetXTilePos(), GetYTilePos()) == CLIMBBLOCKLEFT))
			{
				StopMovement();
				velYModifier = 0;
				velYJumpModifier = 0;

				ipFlags.S_NO_GRAVITY = true;
			}
			/* reset gravity if BACK on the 'collidable' ground */
			else
			{
				ipFlags.S_NO_GRAVITY = false;
			}
		}
	}

	if((player_spr->GetFrameSet() == ENEMY_AGM_ANIM_DEATH2) && !player_spr->IsAnimating())
	{
		deathtimer -= time;

		if(deathtimer < 0)
		{
			deathtimer = 2.5;
			Die();
		}
	}
		
	if(ipFlags.S_ON_GROUND)
	{
		ipFlags.S_NO_GRAVITY = false;
		velModifier = 0;
		velYModifier = 0;
		ipFlags.S_JUMP = false;
	}
	else if(!ipFlags.S_NO_GRAVITY)
		ApplyGravity();

	if(ipFlags.S_ATTACK)
	{
		if(!player_spr->IsAnimating())
		{
			ipFlags.nCurrAttack = 0;
			ipFlags.S_ATTACK = false;
		}
	}

	// Apply Velocity Modifier
	if(/*!ipFlags.S_DAMAGED && */!ipFlags.S_ATTACK)
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

	{
		rectDX = 30;
		rectDY = 60;
		rectXOffset = -15;
		rectYOffset = -30;
	}
}
