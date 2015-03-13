// EnemyElitePistolGaurd.cpp: implementation of the EnemyElitePistolGaurd class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyElitePistolGaurd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyElitePistolGaurd::AIEnemyElitePistolGaurd()
{
//	ChangeState(AIS_PATROL);
	fire=0;
	fire_time=2.25;
//	swing_sword=0;
//	throw_star =0;
//	time_star=5;
//	time_sword=.60f;
	chase_range = 5; //tiles
	attack_range = 6*16; //pix
	current_state = AIS_PATROL;
	prev_state = AIS_PATROL;
	//attackstate=AIS_ATTACK_WAIT;
}

AIEnemyElitePistolGaurd::~AIEnemyElitePistolGaurd()
{

}

void AIEnemyElitePistolGaurd::Attack()
{
/*#ifdef _DEBUG
	char temp[512];
	sprintf(temp, "{AI}[ElitePistol] (fire:%f) (fire_time:%f) (time:%f)", fire, fire_time, time);
	OutputDebugString(temp);
#endif*/
	
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);

	if(aiinput->GetStateFlags()->S_DAMAGED || aiinput->GetStateFlags()->S_INVULNERABLE) fire = fire_time;

	FacePlayer();

	if( (fabs(aio->player_input->GetXLoc() - xpos) <= attack_range ) && (th <= tileheight))
	{
		if(fire <= 0)
		{
			if(!aiinput->GetStateFlags()->S_DAMAGED)
			{
				fire = fire_time;
				aioutput->moveButton4();
			}
		}
		else fire -= time;
	
	}
	else ChangeState(AIS_PATROL);
}

void AIEnemyElitePistolGaurd::Chase()
{

	if(IsStopBlock()){
		/*face the player and take a final shot for fun :) */
		
		aioutput->moveStop();
		//FacePlayer();
		//aioutput->moveButton4();
	    ChangeState(AIS_PATROL); 
	}

	else if(aio->player_input->GetXLoc() <= (xpos-chase_range*16)) aioutput->moveLeft();
	else if(aio->player_input->GetXLoc() >= (xpos+chase_range*16)) aioutput->moveRight();
	else
	{
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
	}	
}

void AIEnemyElitePistolGaurd::Patrol()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);
	
	
	
	if( (th <= tileheight) && (fabs(aio->player_input->GetXLoc()-xpos) <= attack_range))
	{
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
		fire=0;
	}
	
	else if(IsStopBlock())
	{
		if(aiinput->GetDirection()) aioutput->moveLeft();
		else aioutput->moveRight();
	}

	else
	{
		if(aiinput->GetDirection()) aioutput->moveRight();
		else aioutput->moveLeft();
	}
}


