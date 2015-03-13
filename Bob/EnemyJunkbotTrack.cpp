// EnemyJunkbotTrack.cpp: implementation of the EnemyJunkbotTrack class.
//
//////////////////////////////////////////////////////////////////////


#include "EnemyJunkbotTrack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


EnemyJunkbotTrack::EnemyJunkbotTrack(Level *curLevel)
{
	InitEnemy(base_enemy_type_3, 
		      base_x_velocity,
			  base_y_velocity,
			  0,
			  .5,
			  0,
			  true);

	SetRenderOffset(enemy_junkbot_walking_render_offset);

	SetMaxWalkVelocity(WALK_MAX);

	level_class = curLevel;
	SetDamageTimer(.5);

	SetWeaponDamage(5);
	
		rectDX = 40;
	rectDY = 45;
	rectXOffset = -20;
	rectYOffset = -15;

}

EnemyJunkbotTrack::~EnemyJunkbotTrack()
{
}

/*HPTRect &EnemyJunkbotTrack::GetWorldLoc()
{


	return rectWorldLoc;
}*/

HPTRect &EnemyJunkbotTrack::GetWeaponWorldLoc()
{
	if((player_spr->GetFrameSet() == ENEMY_JUNKBOT_TRACK_MOVE) && (player_spr->GetFrame() == 4))
	{
		ipFlags.S_ATTACK = true;
		SetRectangle(rectWeaponWorldLoc, 15, 15, 17, -5);
	}
	else
	{
		ipFlags.S_ATTACK = false;
		SetRectangle(rectWeaponWorldLoc, 0, 0, 0, 0);
	}

	return rectWeaponWorldLoc;
}

void EnemyJunkbotTrack::processLeft()
{
	//If Not Previously Moving Left - Reset Animation
	if(ipFlags.PrevMState != move_left)
		SetAnimation(ENEMY_JUNKBOT_TRACK_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_JUNKBOT_TRACK_MOVE, 0, true, false, 22, false);

	velMovement = -maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = false;
}

void EnemyJunkbotTrack::processRight()
{
	//If Not Previously Moving Right - Reset Animation
	if(ipFlags.PrevMState != move_right)
		SetAnimation(ENEMY_JUNKBOT_TRACK_MOVE, 0, true, false, 22, true);
	else
		SetAnimation(ENEMY_JUNKBOT_TRACK_MOVE, 0, true, false, 22, false);

	velMovement = maxWalkSpeed;

	//Set Sprite Direction
	ipFlags.S_DIRECTION = true;
}


void EnemyJunkbotTrack::processDeath()
{
	//Stop All Directional Movement
	velMovement = 0;
	velModifier = 0;

	SetAnimation(ENEMY_JUNKBOT_TRACK_DEATH, 0, true, true, 10, true);
}

void EnemyJunkbotTrack::processDamage()
{

	//if (ipFlags.S_ACTIVE) soundPlayer->PlaySound(laser02);
	ipFlags.S_ATTACK = false;

	velYModifier = -100;
	
	if(	ipFlags.S_DAMAGED_DIRECTION)
		velMovement = 80;
	else
		velMovement = -80;
}

void EnemyJunkbotTrack::stop()
{
	//Stop All Movement
	velMovement = 0;

	//Reset Animation
	if(ipFlags.PrevMState != move_stop)
		SetAnimation(ENEMY_JUNKBOT_TRACK_MOVE, 0, false, false, 22, true);
	else
		SetAnimation(ENEMY_JUNKBOT_TRACK_MOVE, 0, false, false, 22, false);
}

void EnemyJunkbotTrack::processUpdate()
{
//	BelowFeetLadderCheck();

	if(!ipFlags.S_DEAD)
	{
		if((player_spr->GetFrameSet() == ENEMY_JUNKBOT_TRACK_DEATH) && !player_spr->IsAnimating())
			Die();

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

//	SetRectangle(rectWorldLoc, 40, 45, -20, -15);
}