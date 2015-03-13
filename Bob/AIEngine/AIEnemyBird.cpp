// EnemyBird.cpp: implementation of the EnemyBird class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyBird.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyBird::AIEnemyBird()
{
	attack_range = 6*16;
	y_range = 6*16;
	current_state = AIS_ATTACK;

}

AIEnemyBird::~AIEnemyBird()
{

}

void AIEnemyBird::Attack()
{
	if(fabs(xpos - aio->player_input->GetXLoc()) <= attack_range)
	{
		if(fabs(ypos - aio->player_input->GetYLoc()) <= y_range)
		{
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				aioutput->SetAttack(0);
				aioutput->moveButton4();
			}
		}
	}
}
