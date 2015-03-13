// BaseEnemy.cpp: implementation of the BaseEnemy class.
//
//////////////////////////////////////////////////////////////////////

#include "BaseEnemy.h"
#include "../AILevel.h"
//#include "windows.h"

extern void AINEW(void *arg);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BaseEnemy::BaseEnemy():
current_state(AIS_PATROL),
cblocks(0),
attack_range(0),
chase_range(0),
use_patrol_bounds(false)
{
	cblocks = new bool[36];
	AINEW(cblocks);
	

	//if(cblocks == NULL) MessageBox(NULL, _T("cblocks - Out Of Memory"), _T("AI ENGINE"), MB_OK);

	for( int count=1; count<36; count++)
	{
		cblocks[count]=1;
	}

	cblocks[0]=0;
	cblocks[NONSIDEBASICBLOCK]=0;
	cblocks[CLIMBBLOCKLEFT]=0;
	cblocks[CLIMBBLOCKRIGHT]=0;
	cblocks[CLIMBLADDER]=0;
	cblocks[CLIMBROPE]=0;
	cblocks[WATERBLOCK]=0;
	cblocks[SPAWNFLAG]=0;
	cblocks[ENDLEVEL]=0;
	cblocks[WATERBLOCK]=0;
	cblocks[SPAWNFLAG]=0;
	cblocks[GASBLOCK]=0;

	ignore_player = false;

	use_patrol_bounds = false;
	
}

BaseEnemy::~BaseEnemy()
{
	delete[] cblocks;	
}

int BaseEnemy::GetState()
{
	return current_state;
}

void BaseEnemy::ChangeState(int state)
{
	//if(state == AIS_ATTACK) attackstate = (rand()%2)+201;
	aioutput->moveStop();
	prev_state = current_state;
	current_state = state;

	
}


bool BaseEnemy::FacePlayer()
{
	//int playerx = aio->player_input->GetXTilePos();
	bool dir = aiinput->GetDirection();
	int aix = aiinput->GetXLoc();
	
	if(!aiinput->GetStateFlags()->S_ATTACK)
	{
		
		/*if(playerx < xtile) aioutput->SetDirection(false);
		 else if(playerx > xtile) aioutput->SetDirection(true);
		 else //players xtile and ais xtile are the same base on cord
		 {*/
		float playerfx = aio->player_input->GetXLoc();
		if(playerfx < aix) aioutput->FaceLeft();
		else if(playerfx > aix) aioutput->FaceRight();
		else aioutput->SetDirection(!aio->player_input->GetDirection());
		//}
		
		if(dir == aiinput->GetDirection()) return false;
		else return true;
	}
	return false;
}

bool BaseEnemy::IsStopBlock()
{

	int count=0;
	unsigned char blk;//= GetAIMapCord(xtile, ytile);
	unsigned char blkl;
	
	if(aiinput->GetDirection())
	{
		blk= GetAIMapCord(xtile+1, ytile);
		//check ai coding
		if( (blk == BLK_STOP) || (blk == BLK_STOPRIGHT)) return true;	
	
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
				(blk < ENEMYFIRST || blk > ENEMYLAST)) return true;
		}
		
		/*
		for(count=0; count<aiinput->GetTileHeight(); count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile+1, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}*/
		
	}
	else
	{
		blk= GetAIMapCord(xtile-1, ytile);
		if( (blk == BLK_STOP) || (blk == BLK_STOPLEFT)) return true;

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
		
		/*
		for(count=0; count<aiinput->GetTileHeight(); count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile-1, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}*/

	}

	return false;
}

/*unsigned char BaseEnemy::GetAIMapCord(int &x, int&y)
{
	if( ((unsigned int)x < (unsigned int)aio->aimap_width) && ((unsigned int)y < (unsigned int)aio->aimap_height)) return aio->ai_map[y*aio->aimap_width+x];
	else return 0;
}*/

void BaseEnemy::StateManager()
{
	int th;
	
	

	if( abs(xtile - aio->player_input->GetXTilePos())  <= chase_range)
	{
		th = ytile - aio->player_input->GetYTilePos();

		if( (th >=0) && (th <= tileheight))
		{
			if(fabs( xpos  - aio->player_input->GetXLoc()) <= attack_range)
			{
				ChangeState(AIS_ATTACK);
			//	if(prev_state != AIS_ATTACK) 
				
			}	
			else ChangeState(AIS_CHASE);
		}	
	}
	else ChangeState(AIS_PATROL);
					
}

void BaseEnemy::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();
//	_ftprintf(debug, _T("%i %i\n"), xtile, ytile);
//	_ftprintf(debug, _T("%i\n"), GetAIMapCord(xtile, ytile));

//	aioutput->moveButton4();
	
/*	FILE *temp  = _tfopen(_T("greenninja.txt"), _T("a"));
	_ftprintf(temp, _T("th%d xt%d yt%d xp%f yp%f\n"), aiinput->GetTileHeight(), xtile, ytile, xpos, ypos);
	fclose(temp);*/

	
//	StateManager();

/*	FILE *fp;
	fp = fopen("ailog.txt", "w");
	fprintf(fp, "%i %i %i %i", aiinput->lower_patrol_x, aiinput->lower_patrol_y, aiinput->upper_patrol_x, aiinput->upper_patrol_y);
	fclose(fp);*/
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
/*	case AIS_NAVIGATE_DOWN:
		break;
	case AIS_NAVIGATE_UP:
		break;*/
	}
}

void BaseEnemy::SetAttackRange(float num_pix)
{
	attack_range = num_pix;
}

void BaseEnemy::SetChaseRange(int num_tiles)
{
	chase_range = num_tiles;
}

void BaseEnemy::MoveToXTile(int xtile)
{
		
	//if(IsStopBlock()){aioutput->moveStop(); ChangeState(AIS_WAIT); }

	//FacePlayer();

	if(aiinput->GetXTilePos() < movetoxtile) 
	{
		if(!IsStopBlock()) aioutput->moveRight();
		else 
		{
			aioutput->moveStop();
			ChangeState(AIS_WAIT);
		}
	}
	else if(aiinput->GetXTilePos() > movetoxtile) 
	{
		if(!IsStopBlock()) aioutput->moveLeft();
		else 
		{
			aioutput->moveStop();
			ChangeState(AIS_WAIT);
		}
	}
	else
	{
		aioutput->moveStop();
		ChangeState(AIS_WAIT);
	}

}

void BaseEnemy::Wait()
{
	aioutput->moveStop();
	FacePlayer();
}

void BaseEnemy::ChangeAttackState(int arg)
{
	prevattackstate= attackstate;
	attackstate = arg;
}

bool BaseEnemy::CheckObstruct()
{
	int pxt = aio->player_input->GetXTilePos();
	unsigned char blkl;
	unsigned char blk;
	
	if(pxt < xtile)
	{
		for(int i=pxt; i <=xtile; i++)
		{
			blkl=aio->level_interface->GetLevelData(i, ytile-1);
			if(*(cblocks+blkl)) return true;
			blk = GetAIMapCord(i, ytile);
			if( blk == BLK_STOP || blk == BLK_STOPLEFT || blk == BLK_STOPRIGHT) return true;
		}
	}
	else
	{
		for(int i=xtile; i <=pxt; i++)
		{
			blkl=aio->level_interface->GetLevelData(i, ytile-1);
			if(*(cblocks+blkl)) return true;
			blk = GetAIMapCord(i, ytile);
			if( blk == BLK_STOP || blk == BLK_STOPLEFT || blk == BLK_STOPRIGHT) return true;
		}
	}

	return false;



}
