// EnemyBullDozer.cpp: implementation of the EnemyBullDozer class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyBullDozer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyBullDozer::AIEnemyBullDozer()
{
	first_move = true;
}

AIEnemyBullDozer::~AIEnemyBullDozer()
{

}

void AIEnemyBullDozer::UseBrain()
{
	int pxt = aio->player_input->GetXTilePos();
	int xtile = aiinput->GetXTilePos();
	
	if(new_enemy) 
	{
		/*fixes moveStop bug*/
		new_enemy = false;
		aioutput->moveRight();
	}

/*	char temp[256];
	sprintf(temp, "[BULL](pxt:%d)(xt:%d)", pxt, xtile);
	OutputDebugString(temp);*/

/*	if(xtile < pxt)
	{
		aioutput->moveRight();
		aioutput->SetAttack(0);
		aioutput->moveButton4();
	}
	else aioutput->moveStop();*/
	
	if(xtile == 246)
	{
		aioutput->moveStop();
		return;
	}

	if(first_move)
	{
		
		if( (xtile+2) < (pxt-6))
		{
			aioutput->moveRight();
			first_move = false;
			aioutput->SetAttack(0);
			aioutput->moveButton4();

		}
		else aioutput->moveStop();
	}
	else
	{
		if( (xtile+2) < pxt)
		{
			aioutput->moveRight();
			aioutput->SetAttack(0);
			aioutput->moveButton4();
		}
		else aioutput->moveStop();
	}

}
