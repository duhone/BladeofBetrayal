// EnemyBaseNinja.cpp: implementation of the EnemyBaseNinja class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyBaseNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyBaseNinja::AIEnemyBaseNinja()
{
	wait_time = .6f;
	wait_timer = wait_time;
	
}

AIEnemyBaseNinja::~AIEnemyBaseNinja()
{

}

void AIEnemyBaseNinja::ChangeState(int state)
{
	aioutput->moveStop();
/*	if(state == AIS_PATROL)
	{
		if( (aiinput->lower_patrol_x > 0) && (aiinput->upper_patrol_x > 0)) use_patrol_bounds = true;
	}
	else use_patrol_bounds = false;*/
	
	if(state == AIS_ATTACK)	attackstate = (rand()%2)+201;
	
	prev_state = current_state;
	current_state = state;


	
}



bool AIEnemyBaseNinja::IsStopBlock()
{
	int count=0;
	unsigned char blk;// = GetAIMapCord(xtile, ytile);
	unsigned char blkl;
	
	if(aiinput->GetDirection())
	{
		blk = GetAIMapCord(xtile + 1, ytile);
		//check ai coding
		if( (blk == BLK_STOP) || (blk == BLK_STOPRIGHT)) 
			return true;	
		if(use_patrol_bounds) if(xtile == aiinput->upper_patrol_x) 
			return true;
		//check for blocks in the level in front of us
		/*
		for(count=0; count<=aiinput->GetTileHeight(); count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile+1, ytile-count-1);
			if(*(cblocks+blkl))
				return true;

//			if(count >=10) break;
		}*/
		for (int i = 1; i <= 3; i++)
		{
			blk = aio->level_interface->GetLevelData(xtile + 1, ytile - i);
			if (blk != 0 &&
				blk != NONSIDEBASICBLOCK &&
				blk != CLIMBBLOCKLEFT &&
				blk != CLIMBBLOCKRIGHT &&
				blk != CLIMBLADDER &&
				blk != CLIMBROPE &&
				blk != SPAWNFLAG &&
				blk != LANDMINE &&
				blk != GASBLOCK &&
				(blk < ENEMYFIRST || blk > ENEMYLAST)) return true;
		}

	}
	else
	{
		blk = GetAIMapCord(xtile - 1, ytile);
		if( (blk == BLK_STOP) || (blk == BLK_STOPLEFT)) 
			return true;
		if(use_patrol_bounds) if(xtile == aiinput->lower_patrol_x) 
			return true;
		
		for (int i = 1; i <= 3; i++)
		{
			blk = aio->level_interface->GetLevelData(xtile - 1, ytile - i);
			if (blk != 0 &&
				blk != NONSIDEBASICBLOCK &&
				blk != CLIMBBLOCKLEFT &&
				blk != CLIMBBLOCKRIGHT &&
				blk != CLIMBLADDER &&
				blk != CLIMBROPE &&
				blk != SPAWNFLAG &&
				blk != LANDMINE &&
				blk != GASBLOCK &&
				(blk < ENEMYFIRST || blk > ENEMYLAST)) return true;
		}
		/*
		for(count=0; count<=3;aiinput->GetTileHeight(); count++)
		{
			
			blkl=aio->level_interface->GetLevelData(xtile-1, ytile-count-1);
			if(*(cblocks+blkl)) 
				return true;


//			if(count >=10) break;
		}*/

	}

	return false;
}

void AIEnemyBaseNinja::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();

	if(new_enemy){
		new_enemy=false;
		//if( (aiinput->lower_patrol_x > 0) && (aiinput->upper_patrol_x > 0)) use_patrol_bounds = true;
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

