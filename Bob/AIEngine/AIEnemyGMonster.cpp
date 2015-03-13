// EnemyGMonster.cpp: implementation of the EnemyGMonster class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyGMonster.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyGMonster::AIEnemyGMonster()
{
	SetAttackRange(4*16);
	SetChaseRange(9);
	//ChangeState(AIS_PATROL);
	current_state = AIS_PATROL;
	ChangeAttackState(0);
	run_time = 4;
	run_timer = 4;
	wait_time = .25;
	wait_timer =.25;
	
}

AIEnemyGMonster::~AIEnemyGMonster()
{

}

void AIEnemyGMonster::Attack()
{
/*#ifdef _DEBUG
	char temp[512];
	sprintf(temp, "{AI}[GM] (state:%d)", current_state);
	OutputDebugString(temp);
#endif*/
	
	/*if(aiinput->GetDirection())
	{
		if(GetAIMapCord(xtile, ytile) == BLK_STOPRIGHT ) 
		{
			aioutput->moveStop();
			ChangeAttackState((attackstate++)%2);
		}
	}
	else
	{
		if(GetAIMapCord(xtile, ytile) == BLK_STOPLEFT)
		{
			aioutput->moveStop();
			ChangeAttackState((attackstate++)%2);
		}
	}*/
	
	int	pxt = aio->player_input->GetXTilePos();
	int pyt = aio->player_input->GetYTilePos();
	float pxl = aio->player_input->GetXLoc();
	
	if( (abs(pyt - ytile) <=1) && (fabs(pxl - xpos) >= attack_range) ) 
	{
		aioutput->moveStop();
		ChangeState(AIS_CHASE);
		return;
	}
	if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
	{
		switch(attackstate)
		{
		case 0:
			FacePlayer();
			aioutput->SetAttack(0);
			aioutput->moveButton4();
			ChangeAttackState(1);
			break;
		case 1:
			aioutput->SetDirection(!aiinput->GetDirection());
			aioutput->SetAttack(0);
			aioutput->moveButton4();
			ChangeAttackState(0);
			break;
		}
	}

}

void AIEnemyGMonster::Chase()
{
	int	pxt = aio->player_input->GetXTilePos();
	int pyt = aio->player_input->GetYTilePos();
	float pxl = aio->player_input->GetXLoc();
/*#ifdef _DEBUG
	char temp[512];
	sprintf(temp, "{AI}[GM] (state:%d)(tileheight:%d)", current_state, aiinput->GetTileHeight());
	OutputDebugString(temp);
#endif*/
	if(abs(pxt - xtile) > chase_range ) 
	{
		aioutput->moveStop();
		ChangeState(AIS_PATROL);
	}
	if(IsStopBlock()) 
	{
//		was_stop_block = true;
//		xstoploc = xtile;
		ignore_player = true;
		aioutput->moveStop();
		ChangeState(AIS_PATROL);
	}
	else if( (abs(pyt - ytile) <=1) && (fabs(pxl - xpos) <= attack_range) )
	{
		aioutput->moveStop();
		ChangeAttackState(0);
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
	}
	else
	{
		FacePlayer();
		if(aiinput->GetDirection()) aioutput->moveRight();
		else aioutput->moveLeft();
	}
}

void AIEnemyGMonster::Wait()
{
	int pyt = aio->player_input->GetYTilePos();
	int pxt = aio->player_input->GetXTilePos();
/*#ifdef _DEBUG
	char temp[512];
	sprintf(temp, "{AI}[GM] (state:%d)(waittime%f)", current_state, wait_timer);
	OutputDebugString(temp);
#endif*/
	aioutput->moveStop();

	if( (abs(pyt - ytile) <=1) && (abs(pxt - xtile) <= chase_range) )
	{
		if(!CheckObstruct())
		{
			aioutput->moveStop();
			ChangeState(AIS_CHASE);
			return;
		}
		
	}
	if(wait_timer <=0) {run_timer = run_time; aioutput->moveStop(); ChangeState(AIS_PATROL);}
	else
	{
		wait_timer -= time;
		aioutput->moveStop();
	}
	
	

}

void AIEnemyGMonster::Patrol()
{
	int pyt = aio->player_input->GetYTilePos();
	int pxt = aio->player_input->GetXTilePos();
/*#ifdef _DEBUG
	char temp[512];
	sprintf(temp, "{AI}[GM] (state:%d)", current_state);
	OutputDebugString(temp);
#endif*/
	if(ignore_player)
	{
		if( (abs(pyt - ytile) <=1) && (fabs(aio->player_input->GetXLoc() - xpos) <= attack_range) )
		{
			ignore_player = false;
			aioutput->moveStop();
			ChangeAttackState(0);
			ChangeState(AIS_ATTACK);
			return;
		}
	}
	else
	{
		if( (abs(pyt - ytile) <=1) && (abs(pxt - xtile) <= chase_range) )
		{
			if(!CheckObstruct()) 
			{
				aioutput->moveStop();
				ChangeState(AIS_CHASE);
				return;
			}
			
		}
	}
	
	if(run_timer <=0 ) { wait_timer = wait_time; aioutput->moveStop(); ChangeState(AIS_WAIT);}
	else
	{
		run_timer -= time;
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
	}
	
}

bool AIEnemyGMonster::IsStopBlock()
{

	int count=0;
	unsigned char blk;//= GetAIMapCord(xtile, ytile);
	unsigned char blkl;
	


	if(aiinput->GetDirection())
	{
		blk = GetAIMapCord(xtile + 1, ytile);
		//check ai coding
		if( (blk == BLK_STOP) || (blk == BLK_STOPRIGHT)) return true;	
	
		//check for blocks in the level in front of us
		
		/*
		for(count=0; count<aiinput->GetTileHeight(); count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile+2, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}
		*/
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
				(blk < ENEMYFIRST || blk > ENEMYLAST)) return
				true;
		}
	}
	else
	{
		blk = GetAIMapCord(xtile - 1, ytile);
		if( (blk == BLK_STOP) || (blk == BLK_STOPLEFT)) return true;

		/*
		for(count=0; count<aiinput->GetTileHeight(); count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile-2, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}*/
		
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
				(blk < ENEMYFIRST || blk > ENEMYLAST)) return true;
		}

	}

	return false;
}

	
