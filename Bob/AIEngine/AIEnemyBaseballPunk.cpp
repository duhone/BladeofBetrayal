// EnemyBaseballPunk.cpp: implementation of the EnemyBaseballPunk class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyBaseballPunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyBaseballPunk::AIEnemyBaseballPunk()
{
	//time_sword=.60f;
	//swing_sword=0;
	punch_time = .25f;
	punch = 0;
	chase_range = 5; //tiles
	attack_range = 32; //pix
	current_state = AIS_PATROL;
	prev_state = AIS_PATROL;
}

AIEnemyBaseballPunk::~AIEnemyBaseballPunk()
{

}


void AIEnemyBaseballPunk::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);

	if(th <= tileheight )
	{
		
		if(FacePlayer())
		{
			punch = 0;
//				throw_star=0;
		}

		if(fabs(aio->player_input->GetXLoc()-xpos) > attack_range)
		{
			ChangeState(AIS_CHASE);
		}
		else
		{	
			if(punch <=0)
			{
				if(!aiinput->GetStateFlags()->S_DAMAGED)
				{
					punch = punch_time;
					aioutput->SetAttack(0);
					aioutput->moveButton4();
				}

			}
			else punch-=time;
		}
	}
	else ChangeState(AIS_PATROL);
	
	

}

void AIEnemyBaseballPunk::Chase()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);

	
	if(FacePlayer())
	{
		punch=0;
	}
	if(IsStopBlock())
	{
		ignore_player = true;
		aioutput->moveStop();
		ChangeState(AIS_PATROL);
	}
	if((th <= tileheight) && (abs(aio->player_input->GetXTilePos()-xtile) <= chase_range))
	{
		if(xpos < (aio->player_input->GetXLoc()-attack_range)) 
		{
			if(!IsStopBlock()) aioutput->moveRight();
			else aioutput->moveStop();
		}
		else if(xpos > (aio->player_input->GetXLoc()+attack_range)) 
		{
			if(!IsStopBlock()) aioutput->moveLeft();
			else aioutput->moveStop();
		}
		else
		{
			aioutput->moveStop();
			ChangeState(AIS_ATTACK);
		}
	}
	else ChangeState(AIS_PATROL);
}

void AIEnemyBaseballPunk::Patrol()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));
	
	
/*	if( (th <= tileheight) && (fabs(aio->player_input->GetXLoc()-xpos) <= attack_range))
	{
		ChangeState(AIS_ATTACK);
		swing_sword=0;
		throw_star=time_star;
	}*/

	if(ignore_player)
	{
		if( (((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 4)))  && (fabs(aio->player_input->GetXLoc()-xpos) <= attack_range))
		{
			ignore_player = false;
			ChangeState(AIS_ATTACK);
		}
	}
	
	else
	{
		if( (((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 4)))  && (abs(aio->player_input->GetXTilePos()-xtile) <= chase_range))
		{
			
			punch=0;
			ChangeState(AIS_CHASE);
			
		}
	}

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

bool AIEnemyBaseballPunk::IsStopBlock()
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
			blkl=aio->level_interface->GetLevelData(xtile+1, ytile-count-1);
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
			
			blkl=aio->level_interface->GetLevelData(xtile-1, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}

	}

	return false;
}

void AIEnemyBaseballPunk::UseBrain()
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
