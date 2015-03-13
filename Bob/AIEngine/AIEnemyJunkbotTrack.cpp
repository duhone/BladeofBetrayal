// EnemyJunkbotTrack.cpp: implementation of the EnemyJunkbotTrack class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyJunkbotTrack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyJunkbotTrack::AIEnemyJunkbotTrack()
{
	chase_range = 4; //tiles
	attack_range = 0; //pix
	current_state = AIS_PATROL;
	prev_state = AIS_PATROL;
}

AIEnemyJunkbotTrack::~AIEnemyJunkbotTrack()
{

}

void AIEnemyJunkbotTrack::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));


	if( ((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 2)) )
	{
		
		FacePlayer();

		if(fabs(aio->player_input->GetXLoc()-xpos) > attack_range)
		{
			ChangeState(AIS_CHASE);
		}
		else
		{	
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				aioutput->SetAttack(0);
				aioutput->moveButton4();
			}
		}
	}
	else ChangeState(AIS_PATROL);

}

void AIEnemyJunkbotTrack::Chase()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));
	
    FacePlayer();



	if( (((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 2)))  && (abs(aio->player_input->GetXTilePos()-xtile) <= chase_range))
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

void AIEnemyJunkbotTrack::Patrol()
{
int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));
	
/*	if( (th <= tileheight) && (fabs(aio->player_input->GetXLoc()-xpos) <= attack_range))
	{
		ChangeState(AIS_ATTACK);
		swing_sword=0;
		throw_star=time_star;
	}*/


	
	
/*	if( (((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 2)))  && (abs(aio->player_input->GetXTilePos()-xtile) <= chase_range))
	{
		ChangeState(AIS_CHASE);
		
	}*/

	

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

bool AIEnemyJunkbotTrack::IsStopBlock()
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

void AIEnemyJunkbotTrack::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();

/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[JunkbotTrack] (xt:%d) (yt%d) (stopblock:%d)", xtile, ytile, IsStopBlock());
	OutputDebugString(temp);
#endif*/


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

