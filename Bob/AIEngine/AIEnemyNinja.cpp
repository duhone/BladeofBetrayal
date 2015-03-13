// EnemyNinja.cpp: implementation of the EnemyNinja class.
//
//////////////////////////////////////////////////////////////////////
//#include "windows.h"
#include "AIEnemyNinja.h"
//#include "math.h"
//#include "tchar.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyNinja::AIEnemyNinja()
{
//	ChangeState(AIS_ATTACK);	
}

AIEnemyNinja::~AIEnemyNinja()
{
	
}

void AIEnemyNinja::Attack()
{
	
	FacePlayer();
	if((fabs(aio->player_input->GetXLoc() - xpos) < MAX_ENEMY_DIST_PIX ) && (aio->player_input->GetYTilePos() != ytile))
	{
		if(swing_sword <= 0)
		{
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				swing_sword = 1;
				aioutput->moveButton4();
			}
		}
		else swing_sword -= time;
	}
	
}


void AIEnemyNinja::UseBrain()
{
	//MoveRight();

	//aioutput->moveRight();	
	xpos=aiinput->GetXLoc();
	ypos=aiinput->GetYLoc();
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
//	_ftprintf(debug, _T("%i %i\n"), xtile, ytile);
//	_ftprintf(debug, _T("%i\n"), GetAIMapCord(xtile, ytile));

	switch(GetState())
	{
	case AIS_ATTACK:
		Attack();
		break;
	}
}




void AIEnemyNinja::Chase()
{

}
