// EnemyJunkbotFlying2.cpp: implementation of the EnemyJunkbotFlying2 class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyJunkbotFlying2.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyJunkbotFlying2::AIEnemyJunkbotFlying2()
{
	
	float temp = ((float)(rand()%1000)/1000.0f)-.5f;
	current_state = AIS_PATROL;
	attack_timer = 4.5f + temp;
	attack_time = 4.5f + temp;
}

AIEnemyJunkbotFlying2::~AIEnemyJunkbotFlying2()
{

}

void AIEnemyJunkbotFlying2::Patrol()
{
		if(!IsStopBlock())
		{
			if(aiinput->GetDirection()) aioutput->moveRight();
			else aioutput->moveLeft();
		}
		else
		{
			if(aiinput->GetDirection()) aioutput->moveLeft();
			else aioutput->moveRight();
		}

		if(attack_timer <=0)
		{
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				attack_timer = attack_time;
				aioutput->SetAttack(0);
				aioutput->moveButton4();
			}
		}
		else attack_timer -= time;
		
}

bool AIEnemyJunkbotFlying2::IsStopBlock()
{
/*	unsigned char  tile;
	
	if(aiinput->GetDirection())
		tile = aio->level_interface->GetLevelData(xtile+1, ytile);
	else
		tile = aio->level_interface->GetLevelData(xtile-1, ytile);
	
	
	if(tile >= 1) return true;
	else return false;*/

	unsigned char  tile;
	unsigned char  blk = GetAIMapCord(xtile, ytile);
	
//	float dx, dy;
//	aiinput->GetVelocityVector(&dx, &dy);

	if(aiinput->GetDirection()) 
	{
		if(use_patrol_bounds) if(xtile == aiinput->upper_patrol_x) return true;
		tile = aio->level_interface->GetLevelData(xtile+1, ytile-1);
	}
	else
	{
		if(use_patrol_bounds) if(xtile == aiinput->lower_patrol_x) return true;	
		tile = aio->level_interface->GetLevelData(xtile-1, ytile-1);
	}
	
	if(tile == 1) return true;
	
	if( aiinput->GetDirection()) if( (blk == BLK_STOP) || (blk == BLK_STOPRIGHT)) return true;
    if(!aiinput->GetDirection()) if( (blk == BLK_STOP) || (blk == BLK_STOPLEFT) ) return true;
	
	
	return false;
			
}

void AIEnemyJunkbotFlying2::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();

	if(new_enemy){
		new_enemy=false;
		
		if( (aiinput->lower_patrol_x  != 0) && (aiinput->upper_patrol_x  != 0))
		{
			use_patrol_bounds=true;
		}

	}
	
	switch(GetState())
	{
	case AIS_CHASE:
		Chase();
		break;
	case AIS_ATTACK:
		Attack();
		break;
	case AIS_PATROL:
		Patrol();
		break;
	case AIS_MOVE:
		MoveToXTile(movetoxtile);
		break;
	case AIS_WAIT:
		Wait();
		break;

	}
}

