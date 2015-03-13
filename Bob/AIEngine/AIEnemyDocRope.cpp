// EnemyDockRope.cpp: implementation of the EnemyDockRope class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyDocRope.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyDocRope::AIEnemyDocRope()
{
	SetAttackRange(5*16);
	SetChaseRange(0);
//	ChangeState(AIS_ATTACK);
	time_star = 4.5;
	throw_star =0;
//	high_star = true;
//	low_star =false;
//	high_count=0;
	current_state = AIS_ATTACK;
	prev_state = AIS_ATTACK;
}

AIEnemyDocRope::~AIEnemyDocRope()
{

}

void AIEnemyDocRope::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = ytile - pyt;
//	int temp;

	FacePlayer();

	if((th >= 0 ) && (th <= tileheight) && (fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)))
	{

		if(throw_star <= 0)
		{
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				aioutput->SetAttack(2);
				aioutput->moveButton4();
			}
		}
		else throw_star -= time;
	}
	else ChangeState(AIS_WAIT);
}

void AIEnemyDocRope::Chase()
{

}

void AIEnemyDocRope::Patrol()
{

}

void AIEnemyDocRope::Wait()
{
	FacePlayer();
	aioutput->moveStop();
	if(fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)) 
	{
		ChangeState(AIS_ATTACK);
	}
}
