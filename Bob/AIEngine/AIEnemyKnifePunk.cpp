// EnemyKnifePunk.cpp: implementation of the EnemyKnifePunk class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyKnifePunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


AIEnemyKnifePunk::AIEnemyKnifePunk()
{
	SetAttackRange(12*16);
	SetChaseRange(0);
//	ChangeState(AIS_ATTACK);
	time_star = 3.5;
	throw_star =0;
	current_state = AIS_ATTACK;
	prev_state = AIS_ATTACK;
}

AIEnemyKnifePunk::~AIEnemyKnifePunk()
{

}

void AIEnemyKnifePunk::Attack()
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
				throw_star = time_star;

				aioutput->SetAttack(2);
				aioutput->moveButton4();
			}
			
		}
		else throw_star -= time;
	}
	else ChangeState(AIS_WAIT);

}

void AIEnemyKnifePunk::Chase()
{

}

void AIEnemyKnifePunk::Patrol()
{

}

void AIEnemyKnifePunk::Wait()
{
	
	if(throw_star <= 0)
	{
		throw_star = time_star;
		aioutput->SetAttack(1);
		aioutput->moveButton4();
	}
	else throw_star -= time;

	if(fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)) 
	{
		ChangeState(AIS_ATTACK);
	}
}