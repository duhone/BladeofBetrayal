// EnemyFlyingSentryA.cpp: implementation of the EnemyFlyingSentryA class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyFlyingSentryA.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyFlyingSentryA::AIEnemyFlyingSentryA()
{
	float temp = ((float)(rand()%1000)/1000.0f)-.5f;
	attack_time = 2 + temp;
	//	ChangeState(AIS_PATROL);
	time_bullet=0;
	time_flydown=0;
	time_stopflydown=2;

	range_patrol = 4;
	time_attack = 2;

	turret = rand()%2;

//	if(aiinput->lower_

//	temp = _tfopen(_T("sentry.txt"), _T("w"));
}

AIEnemyFlyingSentryA::~AIEnemyFlyingSentryA()
{
//	fclose(temp);
}

bool AIEnemyFlyingSentryA::IsStopBlock()
{
	unsigned char blk;
	unsigned char  tile;
	float vx, vy;
	
	
/*	if(aiinput->GetDirection())
		tile = aio->level_interface->GetLevelData(xtile+1, ytile);
	else
		tile = aio->level_interface->GetLevelData(xtile-1, ytile);*/


	
	
	aiinput->GetVelocityVector(&vx, &vy);
	if(vy < 0) 
	{

/*#ifdef _DEBUG
		char temp[512];
		sprintf(temp, "{AI}[sentryA] (vy:%f) (lyb:%d) (uyb:%d) (xt:%d) (yt:%d)", vy, aiinput->lower_patrol_y, aiinput->upper_patrol_y, xtile, ytile);
		OutputDebugString(temp);
#endif*/
		blk = GetAIMapCord(xtile, ytile - 1);
		if(blk == BLK_STOP) 
			return true;
		
		//if(use_patrol_bounds) if(ytile <= aiinput->upper_patrol_y) return true;
		
		//tile = aio->level_interface->GetLevelData(xtile, ytile-1);
	}
	else 
	{
		blk = GetAIMapCord(xtile, ytile + 1);
		if(blk == BLK_STOP) 
			return true;
		
		//if(use_patrol_bounds) if(ytile >= aiinput->lower_patrol_y) return true;
		//tile = aio->level_interface->GetLevelData(xtile, ytile+1);
	}

	//if(tile >= 1) return true;
	//else return false;
	return false;
//	unsigned char  tile;
	
//	float dx, dy;
//	aiinput->GetVelocityVector(&dx, &dy);

//	if(dy >= 0) tile = aio->level_interface->GetLevelData(xtile, ytile+1);
///	else tile = aio->level_interface->GetLevelData(xtile, ytile-1);
	
//	if(tile >= 1) return true;
//	else if(aiinput->GetYTilePos() >= aiinput->right_patrol_loc.y) return true;
//	else if(aiinput->GetYTilePos() <= aiinput->left_patrol_loc.y) return true;
//	else return false;
			
}


void AIEnemyFlyingSentryA::Patrol()
{
//	if(abs(aio->player_input->GetXTilePos()-xtile) <= MAX_ENEMY_DIST) ChangeState(AIS_ATTACK);
	
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
//	else /*check for attack */
//		ChangeState(AIS_PATROL);

	time_attack -= time;

	if(time_attack < 0)
	{
		Attack();
		time_attack = attack_time;
	}
//	else
//	{
//		float dx, dy;
//		aiinput->GetVelocityVector(&dx, &dy);

//		if(dy <= 0) aioutput->moveDown();
//		else aioutput->moveUp();
//	}

/*
	if(abs(aio->player_input->GetXTilePos()-xtile) <= MAX_ENEMY_DIST) ChangeState(AIS_ATTACK);
	
	else if(IsStopBlock())
	{
		if(aiinput->GetDirection()) aioutput->moveLeft();
		else aioutput->moveRight();
	}

	else
	{
		if(aiinput->GetDirection()) aioutput->moveRight();
		else aioutput->moveLeft();
	}
*/
}

void AIEnemyFlyingSentryA::Chase()
{
	
	
	
}

void AIEnemyFlyingSentryA::Attack()
{
//	int disty = aio->player_input->GetYTilePos() - ytile;
//	int distx = aio->player_input->GetXTilePos() - xtile;
//	int dist = abs(aio->player_input->GetXTilePos() - xtile);

	//_ftprintf(temp, _T("xt%d yt%d pxt%d pyt%d distx%d disty%d\n"), xtile, ytile, aio->player_input->GetXTilePos(), aio->player_input->GetYLoc, distx, disty);

//	if(distx > 2) aioutput->moveRight();
//	else if(distx < 2) aioutput->moveLeft();
//	else aioutput->moveStop();

//	if(disty > 4) aioutput->moveDown();
//	else if(disty < 4) aioutput->moveUp();
//	else aioutput->moveStop();
	
//	ChangeState(AIS_PATROL);

//	if((distx == 2) && (disty == 4)) aioutput->moveStop();
	
	


	/*	if(time_flydown<=0)
	{
		if(time_stopflydown <=0)
		{
			time_flydown =2;
			time_stopflydown =2;
		}
		else
		{
			time_stopflydown -= time;
			
			if(disty < 1) aioutput->moveUp();
			else if(disty > 1) aioutput->moveDown();
			else aioutput->moveStop();

			if(distx > 0) aioutput->moveRight();
			else if(distx < 0) aioutput->moveLeft();
			else aioutput->moveStop();
		}
	}
	else
	{*/
//		time_flydown -= time;
/*		if(disty < 4 ) aioutput->moveUp();
		else if(disty > 4) aioutput->moveDown();
		else aioutput->moveStop();

		if(distx > 2) aioutput->moveRight();
		else if(distx < 2) aioutput->moveLeft();
		else aioutput->moveStop();
//	}*/

//	if((time_bullet <= 0) && (dist <= 3))
//	{
//		time_bullet = 2.0;
//		if(distx < 0)
//		{
	if(turret)
	{
		turret = !turret;
		aioutput->SetAttack(0);
		aioutput->moveButton4();
	}
	else
	{	
		turret = !turret;
		aioutput->SetAttack(1);
		aioutput->moveButton4();
	}
//		}
//		else if(distx > 0)
//		{
		
//		}
//	}
//	else time_bullet -= time;*/
	
}

void AIEnemyFlyingSentryA::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();

	if(new_enemy){
		new_enemy=false;
		//use_patrol_bounds=true;
		//if( (aiinput->lower_patrol_y  == 0) && (aiinput->upper_patrol_y  == 0))
		//{/*no bounds were set -- make some*/
		//	aiinput->lower_patrol_y = aiinput->GetYTilePos()+6;
		//	aiinput->upper_patrol_y = aiinput->GetYTilePos()-6;
		//}

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
