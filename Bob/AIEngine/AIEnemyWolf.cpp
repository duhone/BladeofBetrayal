// EnemyWolf.cpp: implementation of the EnemyWolf class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyWolf.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyWolf::AIEnemyWolf()
{
	current_state = AIS_PATROL;
}

AIEnemyWolf::~AIEnemyWolf()
{

}

void AIEnemyWolf::Patrol()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));
	

	if(IsStopBlock())
	{

		if(aiinput->GetDirection()) aioutput->moveLeft();
		else aioutput->moveRight();
	}

	else
	{
		if(aiinput->GetDirection()) aioutput->moveRight();
		else aioutput->moveLeft();
	}

}

bool AIEnemyWolf::IsStopBlock()
{
	int count=0;
	unsigned char blk= GetAIMapCord(xtile, ytile);
	unsigned char blkl;
	
	if(aiinput->GetDirection())
	{
		//check ai coding
		if( (blk == BLK_STOP) || (blk == BLK_STOPRIGHT)) return true;	
		if(use_patrol_bounds) if(xtile == aiinput->upper_patrol_x) return true;
		//check for blocks in the level in front of us
		
		for(count=0; count<=aiinput->GetTileHeight(); count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile+2, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}
		
	}
	else
	{
		if( (blk == BLK_STOP) || (blk == BLK_STOPLEFT)) return true;
		if(use_patrol_bounds) if(xtile == aiinput->lower_patrol_x) return true;
		
		for(count=0; count<=aiinput->GetTileHeight(); count++)
		{
			
			blkl=aio->level_interface->GetLevelData(xtile-2, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}

	}

	return false;
}

void AIEnemyWolf::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();

	if(new_enemy){
		new_enemy=false;
		if( (aiinput->lower_patrol_x > 0) && (aiinput->upper_patrol_x > 0)) use_patrol_bounds = true;
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





