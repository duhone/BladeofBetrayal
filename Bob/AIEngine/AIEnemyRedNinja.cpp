// EnemyRedNinja.cpp: implementation of the EnemyRedNinja class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyRedNinja.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyRedNinja::AIEnemyRedNinja()
{
	SetAttackRange(10*16);
	SetChaseRange(0);
//	ChangeState(AIS_ATTACK);
	time_star = 3.5;
	throw_star =0;
	high_star = true;
	low_star =false;
	high_count=0;
	current_state = AIS_ATTACK;
	prev_state = AIS_ATTACK;
}

AIEnemyRedNinja::~AIEnemyRedNinja()
{

}

void AIEnemyRedNinja::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = ytile - pyt;
//	int temp;

	FacePlayer();

	if((th >= 0 ) && (th <= tileheight) && (fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)))
	{
/*#ifdef _DEBUG
				char temp[512];
				sprintf(temp, "{AI}[RedNinja] (throw_star:%f) (time_star:%f) (time:%f)", throw_star, time_star, time);
				OutputDebugString(temp);
#endif*/	
	
		if(throw_star <= 0)
		{
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				throw_star = time_star;

				if(high_star)
				{
					if(high_count == 1) 
					{
						high_count=0;
						high_star =false;
						low_star=true;
					}
					else high_count++;
					
					low_star=true;
/*	#ifdef _DEBUG
					char temp[512];
					sprintf(temp, "{AI}[RedNinja] (attack=1)");
					OutputDebugString(temp);
	#endif*/
					aioutput->SetAttack(1);
					aioutput->moveButton4();
				}
				else if(low_star)
				{
					low_star=false;
					high_star=true;
/*	#ifdef _DEBUG
					char temp[512];
					sprintf(temp, "{AI}[RedNinja] (attack=2)");
					OutputDebugString(temp);
	#endif*/

					aioutput->SetAttack(2);
					aioutput->moveButton4();
				}
			}
			
		}
		else throw_star -= time;
	}
	else ChangeState(AIS_WAIT);

}

void AIEnemyRedNinja::Chase()
{

}

void AIEnemyRedNinja::Patrol()
{

}

void AIEnemyRedNinja::Wait()
{
	FacePlayer();

	if(fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)) 
	{
		ChangeState(AIS_ATTACK);
	}
}
