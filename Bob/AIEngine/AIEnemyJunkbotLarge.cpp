// EnemyJunkbotLarge.cpp: implementation of the EnemyJunkbotLarge class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyJunkbotLarge.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



AIEnemyJunkbotLarge::AIEnemyJunkbotLarge()
{
	attack_range=10*16;
	SetChaseRange(0);
	current_state = AIS_ATTACK;
	rock_time = 2.5;
	rock =0;
	
}

AIEnemyJunkbotLarge::~AIEnemyJunkbotLarge()
{

}

void AIEnemyJunkbotLarge::Attack()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = pyt-ytile;
//	int temp;

//	FacePlayer();
/*
#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[JunkbotLarge]-Attack-(yt:%d)(playeryt:%d)(th:%d)", ytile, aio->player_input->GetYTilePos(), th);
	OutputDebugString(temp);
#endif*/

	if((th >= -1 ) && (th <= 15) && (fabs(aio->player_input->GetXLoc()-xpos) < attack_range))
	{
		if(rock <= 0)
		{
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				rock = rock_time;
				aioutput->SetAttack(1);
				aioutput->moveButton4();
			}
		}	
		else rock -= time;
	}
	else ChangeState(AIS_WAIT);
}

void AIEnemyJunkbotLarge::Wait()
{
//	FacePlayer();
/**#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[JunkbotLarge]-Wait-(xt:%d)(yt:%d)(playerxt:%d)(attack_range:%f)", xtile, ytile, aio->player_input->GetXTilePos(), attack_range);
	OutputDebugString(temp);
#endif*/

	if(fabs(aio->player_input->GetXLoc()-xpos) < (attack_range)) 
	{
		ChangeState(AIS_ATTACK);
	}
}
