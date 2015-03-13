// EnemyBaseEliteGaurd.cpp: implementation of the EnemyBaseEliteGaurd class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyBaseEliteGaurd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyBaseEliteGaurd::AIEnemyBaseEliteGaurd()
{
	fire = 0;
}

AIEnemyBaseEliteGaurd::~AIEnemyBaseEliteGaurd()
{

}

void AIEnemyBaseEliteGaurd::UseBrain()
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

bool AIEnemyBaseEliteGaurd::IsStopBlock()
{
	int count=0;
	unsigned char blk;//= GetAIMapCord(xtile, ytile);
	unsigned char blkl;
	
	if(aiinput->GetDirection())
	{
		blk= GetAIMapCord(xtile + 1, ytile);
		
		//check ai coding
		if( (blk == BLK_STOP) || (blk == BLK_STOPRIGHT)) return true;	
		if(use_patrol_bounds) if(xtile == aiinput->upper_patrol_x) return true;
		//check for blocks in the level in front of us
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
		/*
		for(count=0; count<aiinput->GetTileHeight(); count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile+1, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}
		*/
	}
	else
	{
		blk= GetAIMapCord(xtile - 1, ytile);
		if( (blk == BLK_STOP) || (blk == BLK_STOPLEFT)) return true;
		if(use_patrol_bounds) if(xtile == aiinput->lower_patrol_x) return true;
		
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
		for(count=0; count<aiinput->GetTileHeight(); count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile-1, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}
		 */

	}

	return false;
}

