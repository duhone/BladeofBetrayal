// EnemyLandMine.cpp: implementation of the EnemyLandMine class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyLandMine.h"
#include "../point.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyLandMine::AIEnemyLandMine()
{

}

AIEnemyLandMine::~AIEnemyLandMine()
{

}

void AIEnemyLandMine::UseBrain()
{
	HPTRect lm = aiinput->GetWorldLoc();
	HPTRect p = aio->player_input->GetWorldLoc();

	if(aiinput->GetStateFlags()->S_ACTIVE)
	{
		if( ((p.p1.x >= lm.p1.x) && (p.p1.x <= lm.p2.x)) || ((p.p2.x <= lm.p2.x) && (p.p2.x >= lm.p1.x)) )
		{
			if( aio->player_input->GetYTilePos() == aiinput->GetYTilePos())
				aioutput->moveButton4();
		}
	}

	
	/*
	xtile = aiinput->GetXTilePos();
	
	ytile = aiinput->GetYTilePos();

	if(xtile == aio->player_input->GetXTilePos() && ytile == aio->player_input->GetYTilePos()) 
		aioutput->moveButton4();*/
}

