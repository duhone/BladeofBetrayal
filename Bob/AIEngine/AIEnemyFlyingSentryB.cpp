// EnemyFlyingSentryB.cpp: implementation of the EnemyFlyingSentryB class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyFlyingSentryB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyFlyingSentryB::AIEnemyFlyingSentryB()
{
//	ChangeState(AIS_PATROL);
	float temp = ((float)(rand()%1000)/1000.0f)-.5f;

	
	range_patrol = 10;
	time_attack = 0;
	attack_time = 3+temp;
}

AIEnemyFlyingSentryB::~AIEnemyFlyingSentryB()
{

}


bool AIEnemyFlyingSentryB::IsStopBlock()
{
/*	unsigned char  tile;
	
	if(aiinput->GetDirection())
		tile = aio->level_interface->GetLevelData(xtile+1, ytile);
	else
		tile = aio->level_interface->GetLevelData(xtile-1, ytile);
	
	
	if(tile >= 1) return true;
	else return false;*/

	unsigned char  tile;
	unsigned char  blk;// = GetAIMapCord(xtile, ytile);
	
//	float dx, dy;
//	aiinput->GetVelocityVector(&dx, &dy);

	if(aiinput->GetDirection()) 
	{
		if(use_patrol_bounds) if(xtile == aiinput->upper_patrol_x) return true;
		tile = aio->level_interface->GetLevelData(xtile+1, ytile-1);
		blk = GetAIMapCord(xtile+1, ytile);
	}
	else
	{
		if(use_patrol_bounds) if(xtile == aiinput->lower_patrol_x) return true;	
		tile = aio->level_interface->GetLevelData(xtile-1, ytile-1);
		blk = GetAIMapCord(xtile-1, ytile);
	}
	
	if(tile == 1) return true;
	
	if( aiinput->GetDirection()) if( (blk == BLK_STOP) || (blk == BLK_STOPRIGHT)) return true;
    if(!aiinput->GetDirection()) if( (blk == BLK_STOP) || (blk == BLK_STOPLEFT) ) return true;
	
	
	return false;
			
}


void AIEnemyFlyingSentryB::Attack()
{
	aioutput->moveButton4();

/*	int dist = aio->player_input->GetYTilePos() - ytile;
	int distx;

	if(dist < 1) aioutput->moveUp();
	else if(dist > 1) aioutput->moveDown();
	else aioutput->moveStop();

	
	FacePlayer();
	
	if(aiinput->GetDirection()) //facing right
	{
		distx = aio->player_input->GetXTilePos() - xtile;
		if(distx > 2 ) aioutput->moveRight();
		else if(distx <2) aioutput->moveLeft();
		else aioutput->moveStop();

	}
	else //facing left
	{
		distx = xtile - aio->player_input->GetXTilePos();
		if(distx > 2) aioutput->moveLeft();
		else if(distx <2) aioutput->moveRight();
		else aioutput->moveStop();
	}
*/
	
	
}

void AIEnemyFlyingSentryB::Chase()
{

}

void AIEnemyFlyingSentryB::Patrol()
{
//	if(abs(aio->player_input->GetXTilePos()-xtile) <= MAX_ENEMY_DIST) ChangeState(AIS_ATTACK);
	
	
/*#ifdef _DEBUG
	char temp[512];
	sprintf(temp, "{AI}[sentryB] (uxb:%d) (lxb:%d) (xt:%d) (yt:%d) (dir:%d)", aiinput->upper_patrol_x, aiinput->lower_patrol_x, xtile, ytile, aiinput->GetDirection());
	OutputDebugString(temp);
#endif*/
	
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
	
	

	float pxl = aio->player_input->GetXLoc();
	
	if(time_attack <= 0)
	{
		if(!aiinput->GetStateFlags()->S_DAMAGED)
		{
			time_attack = attack_time;
			if( ((pxl > xpos) && aiinput->GetDirection()) || ((pxl < xpos) && !aiinput->GetDirection()) )
			{
				aioutput->moveButton4();
			
			}
		}
	}else time_attack -= time;

}

void AIEnemyFlyingSentryB::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();

	if(new_enemy){
		new_enemy=false;
		//if( (aiinput->lower_patrol_x  > 0) && (aiinput->upper_patrol_x  > 0)) use_patrol_bounds=true;
	}

/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[SentryB] (cstate:%d)(use_patrol_bounds:%d)(lxb:%d)(uxb:%d)", current_state, use_patrol_bounds, aiinput->lower_patrol_x, aiinput->upper_patrol_x);
	OutputDebugString(temp);
#endif*/
	
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
