// EnemyBrownNinja.cpp: implementation of the EnemyBrownNinja class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyBrownNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyBrownNinja::AIEnemyBrownNinja()
{
//	ChangeState(AIS_CHASE);
}

AIEnemyBrownNinja::~AIEnemyBrownNinja()
{

}

void AIEnemyBrownNinja::Chase()
{
	//if(IsStopBlock()) {aioutput->moveStop(); ChangeState(AIS_PATROL); }

	if(IsStopBlock()) {aioutput->moveStop(); ChangeState(AIS_PATROL); }

	
	if(aio->player_input->GetXLoc() < xpos) aioutput->moveRight();
	else if(aio->player_input->GetXLoc() > xpos) aioutput->moveLeft();
	else
	{
		if(aiinput->GetDirection()) aioutput->moveRight();
		else aioutput->moveLeft();
	}
	
	
	
}

void AIEnemyBrownNinja::Patrol()
{
	/*if(aio->player_input->GetYTilePos() == ytile && abs(aio->player_input->GetXTilePos()-xtile) <= MAX_ENEMY_DIST) ChangeState(AIS_CHASE);
	
	else if(IsStopBlock())
	{
		if(aiinput->GetDirection()) aioutput->moveLeft();
		else aioutput->moveRight();
	}

	else
	{
		if(aiinput->GetDirection()) aioutput->moveRight();
		else aioutput->moveLeft();
	}*/
}



void AIEnemyBrownNinja::Attack()
{

}
