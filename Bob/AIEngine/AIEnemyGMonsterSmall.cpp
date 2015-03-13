// EnemyGMonsterSmall.cpp: implementation of the EnemyGMonsterSmall class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyGMonsterSmall.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyGMonsterSmall::AIEnemyGMonsterSmall()
{
    SetAttackRange(10*16);
	SetChaseRange(0);
	current_state = AIS_ATTACK;
	jump_attack = 0;
	jump_attack_time = .5;
	hop = 0;
	hop_time = .75;

	
}

AIEnemyGMonsterSmall::~AIEnemyGMonsterSmall()
{

}

void AIEnemyGMonsterSmall::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);
//	int temp;

	if(!aiinput->GetStateFlags()->S_ATTACK) FacePlayer();

	if( (th <= 3) && (fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)))
	{
		if(abs(aio->player_input->GetXTilePos() - xtile) <=2)
		{
			if(jump_attack <= 0)
			{
				if(!aiinput->GetStateFlags()->S_DAMAGED)
				{
					jump_attack = jump_attack_time;
					aioutput->SetAttack(2);
					aioutput->moveButton4();
				}
			}
			else jump_attack -= time;
		}
		else
		{
			if(hop <= 0)
			{
				if(!aiinput->GetStateFlags()->S_DAMAGED)
				{
					hop = hop_time;
					aioutput->SetAttack(0);
					aioutput->moveButton4();
				}
			}
			else hop -= time;
		}
	}
	else ChangeState(AIS_WAIT);
}

void AIEnemyGMonsterSmall::Wait()
{
	if(!aiinput->GetStateFlags()->S_ATTACK) FacePlayer();

	if(fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)) 
	{
		jump_attack = 0;
		hop =0;
		ChangeState(AIS_ATTACK);
	}
}
