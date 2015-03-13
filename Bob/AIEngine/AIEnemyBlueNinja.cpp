// EnemyBlueNinja.cpp: implementation of the EnemyBlueNinja class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyBlueNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyBlueNinja::AIEnemyBlueNinja()
{
	swing_sword=0;
	throw_star =0;
	time_star=5;
	time_sword=.60f;
	chase_range = 5; //tiles
	attack_range = 40; //pix
	current_state = AIS_PATROL;
	prev_state = AIS_PATROL;
	//attackstate=AIS_ATTACK_WAIT;
}

AIEnemyBlueNinja::~AIEnemyBlueNinja()
{

}

void AIEnemyBlueNinja::Patrol()
{
/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[BlueNinja} (state:%i)", current_state);
	OutputDebugString(temp);
#endif*/
	
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
			ChangeState(AIS_CHASE);
			FacePlayer();
			aioutput->SetAttack(1);
			aioutput->moveButton4();
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



void AIEnemyBlueNinja::Attack()
{
/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[BlueNinja} (state:%i)", current_state);
	OutputDebugString(temp);
#endif*/
	
	int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));

	switch(attackstate)
	{
	case AIS_ATTACK_ATTACK:
	

		if( ((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 4)) )
		{
			
			if(FacePlayer())
			{
				swing_sword = 0;
				throw_star=0;
			}

			if(fabs(aio->player_input->GetXLoc()-xpos) > attack_range)
			{
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

				if(throw_star <=0)
				{
					if(!aiinput->GetStateFlags()->S_DAMAGED)
					{
						throw_star = time_star;
						aioutput->SetAttack(1);
						aioutput->moveButton4();
					}
				
				}
				else time_star -= time;

			}
		}
		else ChangeState(AIS_PATROL);
		
		break;
	case AIS_ATTACK_WAIT:
		//attackstate = AIS_ATTACK_ATTACK;
		if( ((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 4)) )
		{
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
					movetoxtile = aio->player_input->GetXTilePos() + (int)pow(-1, (rand()%2)+1)*5;
					ChangeState(AIS_MOVE);
				}

			}
		}
		else ChangeState(AIS_PATROL);
		break;
	}


}
void AIEnemyBlueNinja::Chase()
{
/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[BlueNinja} (state:%i)", current_state);
	OutputDebugString(temp);
#endif*/
	
	//	xtileloc = aiinput->GetXTilePos();
//	ytileloc = aiinput->GetYTilePos();
	
	
//	if(IsStopBlock()){aioutput->moveStop(); /*ChangeState(AIS_PATROL);*/ }

	int pyt = aio->player_input->GetYTilePos();
	int th = abs((pyt+aio->player_input->GetTileHeight()) - (ytile + aiinput->GetTileHeight()));

	
	if(FacePlayer())
	{
	//	swing_sword=0;
		throw_star=0;
		/*aioutput->SetAttack(1);
		aioutput->moveButton4();*/
	}
	if(IsStopBlock())
	{
		ignore_player = true;
		aioutput->moveStop();
		ChangeState(AIS_PATROL);
	}
	if( (((pyt > ytile) && (th < 1)) || ((pyt <= ytile) && (th <= 4)))  && (abs(aio->player_input->GetXTilePos()-xtile) <= chase_range))
	{
		if(fabs(aio->player_input->GetXLoc() - xpos) <= attack_range)
		{
			aioutput->moveStop();
			ChangeState(AIS_ATTACK);
			Attack();
		}
		else
		{
			if(!IsStopBlock())
			{
				if(aio->player_input->GetXTilePos() < xtile) aioutput->moveLeft();
				else aioutput->moveRight();
			}
		}
		
	/*	if(xpos < (aio->player_input->GetXLoc()-attack_range)) 
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
		}*/
	}
	else ChangeState(AIS_PATROL);

}

void AIEnemyBlueNinja::Wait()
{
/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[BlueNinja} (state:%i)", current_state);
	OutputDebugString(temp);
#endif*/
	
	FacePlayer();

	if( (abs(aio->player_input->GetXTilePos()-xtile) < chase_range) || (wait_timer <= 0))
	{
		wait_timer = wait_time;
		ChangeState(AIS_CHASE);
		//throw_star=0;
		//swing_sword=0;
	}
	else wait_timer -= time;
}
