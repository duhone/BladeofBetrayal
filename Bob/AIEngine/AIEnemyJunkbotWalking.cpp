// EnemyJunkbotWalking.cpp: implementation of the EnemyJunkbotWalking class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyJunkbotWalking.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
AIEnemyJunkbotWalking::AIEnemyJunkbotWalking()
{
	chase_range = 10; //tiles
	attack_range = 7*16; //pix
	current_state = AIS_PATROL;
	prev_state = AIS_PATROL;
	shoot =0;
	shoot_time = .75;
	no_move =false;
	xwalk = 0;
}

AIEnemyJunkbotWalking::~AIEnemyJunkbotWalking()
{

}

void AIEnemyJunkbotWalking::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));


	if( ((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 4)) )
	{
		
		if(shoot <=0)
		{
			if(no_move)
			{
				
				if(!aiinput->GetStateFlags()->S_DAMAGED)
				{
					FacePlayer();
					shoot = shoot_time;
					aioutput->SetAttack(1);
					aioutput->moveButton4();
				}
			}
			else
			{
				if(!aiinput->GetStateFlags()->S_DAMAGED)
				{
					FacePlayer();
					shoot = shoot_time;
					aioutput->SetAttack(0);
					aioutput->moveButton4();
					if(aiinput->GetDirection()) xwalk = xtile - 3;
					else xwalk = xtile + 3;
					aioutput->moveStop();
					ChangeState(AIS_CHASE); 
				}
			}


		}
		else shoot-=time;
	
	}
	else 
	{
		aioutput->moveStop();
		ChangeState(AIS_PATROL);
	}
		
	

}

void AIEnemyJunkbotWalking::Chase()
{
	/*not really a chase -- enemy turns and runs a few tiles then turns and shoots agian.*/
	
	int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));

	if(no_move)
	{
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
		return;
	}

	
	if(xwalk < xtile) aioutput->moveLeft();
	else if(xwalk > xtile) aioutput->moveRight();
	else
	{
		shoot=0;
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
	}

	
	if(IsStopBlock())
	{
		no_move = true;
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
	}

	
	
}

void AIEnemyJunkbotWalking::Patrol()
{
		int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));
	
	


	if( (((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 4)))  && (fabs(aio->player_input->GetXLoc()-xpos) <= attack_range))
	{
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
		
	}

	else
	{

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
}

bool AIEnemyJunkbotWalking::IsStopBlock()
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

void AIEnemyJunkbotWalking::UseBrain()
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
