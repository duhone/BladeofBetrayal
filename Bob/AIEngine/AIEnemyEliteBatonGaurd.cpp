// EnemyEliteBatonGaurd.cpp: implementation of the EnemyEliteBatonGaurd class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyEliteBatonGaurd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyEliteBatonGaurd::AIEnemyEliteBatonGaurd()
{
	time_sword=.60f;
	swing_sword=0;
	chase_range = 5; //tiles
	attack_range = 20; //pix
	current_state = AIS_PATROL;
	prev_state = AIS_PATROL;
}

AIEnemyEliteBatonGaurd::~AIEnemyEliteBatonGaurd()
{
}

void AIEnemyEliteBatonGaurd::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);

/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "[EBG](xt:%d)(yt:%d)(stop:%d)(state:attack)", xtile, ytile, IsStopBlock()); 
	OutputDebugString(temp);
#endif*/

	switch(attackstate)
	{
	case AIS_ATTACK_ATTACK:
	

		if(th <= tileheight )
		{
			
			if(FacePlayer())
			{
				swing_sword = 0;
//				throw_star=0;
			}

			if(fabs(aio->player_input->GetXLoc()-xpos) > attack_range)
			{
				aioutput->moveStop();
				ChangeState(AIS_CHASE);
			}
			else
			{	
				if(swing_sword <=0)
				{
					if(!aiinput->GetStateFlags()->S_DAMAGED)
					{
						swing_sword = time_sword;
						aioutput->SetAttack(0);
						aioutput->moveButton4();
					}

				}
				else swing_sword-=time;
			}
		}
		else
		{
			aioutput->moveStop();
			ChangeState(AIS_PATROL);
		}
		
		break;
	case AIS_ATTACK_WAIT:
		//attackstate = AIS_ATTACK_ATTACK;
		if(th <= tileheight )
		{
			if(fabs(aio->player_input->GetXLoc()-xpos) > attack_range)
			{
				aioutput->moveStop();
				ChangeState(AIS_CHASE);
			}
			else
			{	
				if(!aiinput->GetStateFlags()->S_DAMAGED)
				{
					aioutput->SetAttack(0);
					aioutput->moveButton4();
					movetoxtile = aio->player_input->GetXTilePos() + (int)pow(-1, (rand()%2)+1)*5;
					aioutput->moveStop();
					ChangeState(AIS_MOVE);
				}

			}
		}
		else 
		{
			aioutput->moveStop();
			ChangeState(AIS_PATROL);
		}
		break;
	}
}

void AIEnemyEliteBatonGaurd::Patrol()
{
		int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);

/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "[EBG](xt:%d)(yt:%d)(stop:%d)(state:attack)", xtile, ytile, IsStopBlock()); 
	OutputDebugString(temp);
#endif*/	
	
/*	if( (th <= tileheight) && (fabs(aio->player_input->GetXLoc()-xpos) <= attack_range))
	{
		ChangeState(AIS_ATTACK);
		swing_sword=0;
		throw_star=time_star;
	}*/

	if(ignore_player)
	{
		if((th <= tileheight) && (fabs(aio->player_input->GetXLoc()-xpos) <= attack_range))
		{
			ignore_player = false;
			aioutput->moveStop();
			ChangeState(AIS_ATTACK);
		}
	}
	else
	{
	
		if((th <= tileheight) && (abs(aio->player_input->GetXTilePos()-xtile) <= chase_range))
		{
			aioutput->moveStop();
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

void AIEnemyEliteBatonGaurd::Chase()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);
/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "[EBG](xt:%d)(yt:%d)(stop:%d)(state:chase)", xtile, ytile, IsStopBlock()); 
	OutputDebugString(temp);
#endif*/
	
	if(FacePlayer())
	{
		swing_sword=0;
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
	else
	{
		aioutput->moveStop();
		ChangeState(AIS_PATROL);
	}

}

void AIEnemyEliteBatonGaurd::Wait()
{
	FacePlayer();

	if(abs(aio->player_input->GetXTilePos()-xtile) < chase_range) 
	{
		aioutput->moveStop();
		ChangeState(AIS_CHASE);
//		throw_star=0;
		swing_sword=0;
	}
}
