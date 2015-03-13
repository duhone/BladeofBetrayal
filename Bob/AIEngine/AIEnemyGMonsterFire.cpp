// EnemyGMonsterFire.cpp: implementation of the EnemyGMonsterFire class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyGMonsterFire.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyGMonsterFire::AIEnemyGMonsterFire()
{
 //   SetAttackRange(7*16);
//	SetChaseRange(0);
//	ChangeState(AIS_ATTACK);
	current_state = AIS_ATTACK;
	float temp = ((float)(rand()%1000)/1000.0f)-.5f;
	fire_time = 1.75f+temp;
	fire = 0;
}

AIEnemyGMonsterFire::~AIEnemyGMonsterFire()
{

}

void AIEnemyGMonsterFire::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = ytile - pyt;
//	int temp;

	FacePlayer();

	if(!aiinput->GetStateFlags()->S_DAMAGED)
	{
			if(fire <=0)
			{

				fire = fire_time;
				aioutput->SetAttack(1);
				aioutput->moveButton4();
			}
			else fire -= time;
	}
	

}

void AIEnemyGMonsterFire::Wait()
{
	FacePlayer();

	if(fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)) 
	{
		fire=0;
		ChangeState(AIS_ATTACK);
	}
}
