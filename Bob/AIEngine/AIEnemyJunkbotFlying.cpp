// EnemyJunkbotFlying.cpp: implementation of the EnemyJunkbotFlying class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyJunkbotFlying.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


AIEnemyJunkbotFlying::AIEnemyJunkbotFlying()
{

	float temp = ((float)(rand()%1000)/1000.0f)-.5f;
	time_bullet= 4.5f + temp; 
	time_attack = 4.5f + temp;

	

}

AIEnemyJunkbotFlying::~AIEnemyJunkbotFlying()
{

}

bool AIEnemyJunkbotFlying::IsStopBlock()
{
	unsigned char  tile;
	float vx, vy;
	

	aiinput->GetVelocityVector(&vx, &vy);
	if(vy < 0) 
	{


	
		if(use_patrol_bounds) if(ytile <= aiinput->upper_patrol_y) return true;
		tile = aio->level_interface->GetLevelData(xtile, ytile-1);
	}
	else 
	{
		if(use_patrol_bounds) if(ytile >= aiinput->lower_patrol_y) return true;
		tile = aio->level_interface->GetLevelData(xtile, ytile+1);
	}

	if(tile >= 1) return true;
	else return false;

			
}


void AIEnemyJunkbotFlying::Patrol()
{

	if(aio->player_input->GetXTilePos() != xtile) FacePlayer();
	if(IsStopBlock())
	{
		float dx, dy;
		aiinput->GetVelocityVector(&dx, &dy);

		if(dy >= 0)
		{
			aioutput->moveUp();
			yLocPrev = aiinput->GetYLoc();
		}
		else 
		{
			aioutput->moveDown();
			yLocPrev = aiinput->GetYLoc();
		}
	}
	else 
	{
		float dx, dy;
		aiinput->GetVelocityVector(&dx, &dy);

		if(dy >= 0) 
		{
			aioutput->moveDown();
			yLocPrev = aiinput->GetYLoc();
		}
		else if(dy < 0)
		{
			aioutput->moveUp();
			yLocPrev = aiinput->GetYLoc();
		}
		else
		{
			unsigned int i = rand()%2;

			if(i) aioutput->moveDown();
			else aioutput->moveUp();
		}
	}

	

	if(time_attack <= 0)
	{
		Attack();
		time_attack = time_bullet;
	}
	else time_attack -= time;



}



void AIEnemyJunkbotFlying::Attack()
{

	if(!aiinput->GetStateFlags()->S_DAMAGED)
	{
		aioutput->SetAttack(0);
		aioutput->moveButton4();
	}
	
	
}

void AIEnemyJunkbotFlying::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();

	if(new_enemy){
		new_enemy=false;
		use_patrol_bounds=true;
		if( (aiinput->lower_patrol_y  == 0) && (aiinput->upper_patrol_y  == 0))
		{/*no bounds were set -- make some*/
			aiinput->lower_patrol_y = aiinput->GetYTilePos()+6;
			aiinput->upper_patrol_y = aiinput->GetYTilePos()-6;
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
