// EnemyWaterMine.cpp: implementation of the EnemyWaterMine class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyWaterMine.h"
#include "../point.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyWaterMine::AIEnemyWaterMine()
{

}

AIEnemyWaterMine::~AIEnemyWaterMine()
{

}

void AIEnemyWaterMine::UseBrain()
{
	HPTRect lm = aiinput->GetWorldLoc();
	HPTRect p = aio->player_input->GetWorldLoc();

	if(aiinput->GetStateFlags()->S_ACTIVE)
	{
		if( ((p.p1.x >= lm.p1.x) && (p.p1.x <= lm.p2.x)) || ((p.p2.x <= lm.p2.x) && (p.p2.x >= lm.p1.x)) )
		{
			if( ((p.p1.y >= lm.p1.y) && (p.p1.y <= lm.p2.y)) || ((p.p2.y <= lm.p2.y) && (p.p2.y >= lm.p1.y)) )
			{
				aioutput->SetAttack(0);
				aioutput->moveButton4();
			}
		}
	}

}
