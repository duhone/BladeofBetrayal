// EnemyPrisonerRock1.cpp: implementation of the EnemyPrisonerRock class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyPrisonerRock1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyPrisonerRock::AIEnemyPrisonerRock()
{
	SetAttackRange(9*16);
	SetChaseRange(0);
	current_state = AIS_ATTACK;
	rock_time = 2.5;
	throw_rock =0;
	
}

AIEnemyPrisonerRock::~AIEnemyPrisonerRock()
{

}

void AIEnemyPrisonerRock::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = pyt-ytile;
//	int temp;

	FacePlayer();
/*
#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[PrisonerRock] (th:%d)", th);
	OutputDebugString(temp);
#endif*/

	if((th >= 0 ) && (th <= (((rand()%2)+1)*10)) && (fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)))
	{
		if(throw_rock <= 0)
		{
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				throw_rock = rock_time;
				aioutput->SetAttack(1);
				aioutput->moveButton4();
			}
		}	
		else throw_rock -= time;
	}
	else ChangeState(AIS_WAIT);
}

void AIEnemyPrisonerRock::Wait()
{
	FacePlayer();

	if(fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)) 
	{
		ChangeState(AIS_ATTACK);
	}
}
