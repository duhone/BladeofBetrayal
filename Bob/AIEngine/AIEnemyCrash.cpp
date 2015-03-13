// EnemyCrash.cpp: implementation of the EnemyCrash class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyCrash.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyCrash::AIEnemyCrash()
{
	current_state = AIS_ATTACK;
	attackstate = AIS_CRASH_INTRO;
	hilow_attack = true;
	hilow_timer = 1;
	hilow_time =1;
	hilow_count=0;
	damaged=false;
	attack_range = 4*16;
	rapidfire_count = 0;
	step6_count = 0;
	rbound = 16;
	lbound = 0;
	mode = 0;
	pause_timer = 3;
	pause_time = 3;
	mode3_count = 0;
}

AIEnemyCrash::~AIEnemyCrash()
{

}

void AIEnemyCrash::Attack()
{
	if((aiinput->GetCurLife() <= 80) && (mode < 1))
	{
		aioutput->moveStop();
		ChangeAttackState(AIS_CRASH_ROCKETJUMP1);
		mode++;
	}
	if((aiinput->GetCurLife() <= 32) && (mode <2))
	{
		aioutput->moveStop();
		ChangeAttackState(AIS_CRASH_GRENADE1);
		mode++;
	}

/*	if( (abs(aio->player_input->GetYTilePos() - ytile) > 2) || (xtile < 2) || (xtile > 13)) 
	{
		
		FacePlayer();
		ChangeState(AIS_PATROL);
		return;
		
	}*/

	if(mode == 0)
	{
		switch(attackstate)
		{
		case AIS_CRASH_INTRO:
			if(!aiinput->GetStateFlags()->S_ATTACK)
			{
				aioutput->SetAttack(9);
				aioutput->moveButton4();
				ChangeAttackState(AIS_CRASH_HILOW);
			}
			break;
		case AIS_CRASH_HILOW:
			if(aiinput->GetStateFlags()->S_ON_GROUND && !aiinput->GetStateFlags()->S_ATTACK)
			{
				FacePlayer();
				if(hilow_timer <= 0)
				{
					hilow_timer = hilow_time;
					if(hilow_attack)
					{
						hilow_attack = false;
						aioutput->SetAttack(0);
						aioutput->moveButton4();
					}
					else
					{
						hilow_attack = true;
						aioutput->SetAttack(1);
						aioutput->moveButton4();
					}
				}else hilow_timer -= time;
				
			}
			if(aiinput->GetStateFlags()->S_ON_GROUND && damaged) ChangeAttackState(AIS_CRASH_ROCKETJUMP1);
			break;
		case AIS_CRASH_ROCKETJUMP1:
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				aioutput->SetAttack(7);
				aioutput->moveButton4();
				hilow_count++;
				if(hilow_count == 2)
				{
					hilow_count = 0;
					ChangeAttackState(AIS_CRASH_GRENADE1);

				}
				else ChangeAttackState(AIS_CRASH_HILOW);
			}
			break;
		case AIS_CRASH_GRENADE1:
			if(aiinput->GetStateFlags()->S_ON_GROUND && (!aiinput->GetStateFlags()->S_ATTACK) && (!aiinput->GetStateFlags()->S_JUMP))
			{
				FacePlayer();
				aioutput->SetAttack(2);
				aioutput->moveButton4();
				//ChangeAttackState(AIS_CRASH_HILOW);
				ChangeState(AIS_CHASE);
			}
			break;
		case AIS_CRASH_GRENADE2:
			if(aiinput->GetStateFlags()->S_ON_GROUND && (!aiinput->GetStateFlags()->S_ATTACK) && (!aiinput->GetStateFlags()->S_JUMP))
			{
				FacePlayer();
				aioutput->SetAttack(3);
				aioutput->moveButton4();
				if(aiinput->GetDirection()) walk_x = xtile - 3;
				else walk_x = xtile +3;
				
				ChangeAttackState(AIS_CRASH_WALKAWAY);
			}
			break;
		case AIS_CRASH_RAPIDFIRE:
			if(!aiinput->GetStateFlags()->S_ATTACK)
			{
				FacePlayer();
				rapidfire_count++;
				if(rapidfire_count == 6)
				{
					rapidfire_count =0;
					ChangeAttackState(AIS_CRASH_GRENADE2);
				}
				else
				{
					aioutput->SetAttack(4);
					aioutput->moveButton4();
				}
			}
			break;
		case AIS_CRASH_WALKAWAY:
			if(!IsStopBlock())
			{
				if(xtile < walk_x) aioutput->moveRight();
				else if(xtile > walk_x) aioutput->moveLeft();
				else
				{
					step6_count++;
					aioutput->moveStop();
					ChangeAttackState(AIS_CRASH_RAPIDFIRE);
				}
			}
			else
			{
				step6_count++;
				aioutput->moveStop();
				ChangeAttackState(AIS_CRASH_RAPIDFIRE);
			}

			if(step6_count == 2)
			{
				if(xtile > (rbound - xtile)) aioutput->SetDirection(false);
				else aioutput->SetDirection(true);

				step6_count =0;
				aioutput->SetAttack(7);
				aioutput->moveButton4();
				ChangeAttackState(AIS_CRASH_HILOW);
			}
			break;
		}
	}
	else if(mode == 2)
	{
		switch(attackstate)
		{
		case AIS_CRASH_ROCKETJUMP1:
			if(xtile != 7)
			{
				if(xtile > 7) aioutput->moveLeft();
				else aioutput->moveRight();
			}
			else if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				aioutput->moveStop();
				aioutput->SetAttack(8);
				aioutput->moveButton4();
				ChangeAttackState(AIS_CRASH_GRENADE1);
			}
			break;
		case AIS_CRASH_GRENADE1:
			if(aiinput->GetStateFlags()->S_ON_GROUND && (!aiinput->GetStateFlags()->S_ATTACK) && (!aiinput->GetStateFlags()->S_JUMP))
			{
				FacePlayer();
				aioutput->SetAttack(2);
				aioutput->moveButton4();
				ChangeAttackState(AIS_CRASH_GRENADE2);
				//ChangeAttackState(AIS_CRASH_HILOW);
			}
			break;
		case AIS_CRASH_GRENADE2:
			if(aiinput->GetStateFlags()->S_ON_GROUND && (!aiinput->GetStateFlags()->S_ATTACK) && (!aiinput->GetStateFlags()->S_JUMP))
			{
				FacePlayer();
				aioutput->SetAttack(3);
				aioutput->moveButton4();
				ChangeAttackState(AIS_CRASH_HIGHSPREAD);
			}
			break;
		case AIS_CRASH_HIGHSPREAD:
			if(aiinput->GetStateFlags()->S_ON_GROUND && (!aiinput->GetStateFlags()->S_ATTACK) && (!aiinput->GetStateFlags()->S_JUMP))
			{
				FacePlayer();
				aioutput->SetAttack(5);
				aioutput->moveButton4();
				ChangeAttackState(AIS_CRASH_LOWSPREAD);
			}
			break;
		case AIS_CRASH_LOWSPREAD:
			if(aiinput->GetStateFlags()->S_ON_GROUND && (!aiinput->GetStateFlags()->S_ATTACK) && (!aiinput->GetStateFlags()->S_JUMP))
			{
				FacePlayer();
				aioutput->SetAttack(6);
				aioutput->moveButton4();
				ChangeAttackState(AIS_CRASH_PAUSE);
			}
			break;
		case AIS_CRASH_PAUSE:
			if(pause_timer <= 0)
			{
				pause_timer = pause_time;
				ChangeAttackState(AIS_CRASH_GRENADE1);
			}
			else pause_timer -= time;
			break;
		}
	}
	else
	{
		if(xtile != 10)
		{
			if(xtile > 10) aioutput->moveLeft();
			else aioutput->moveRight();
			return;
		}

		switch(attackstate)
		{
		case AIS_CRASH_ROCKETJUMP1:
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				aioutput->moveStop();
				aioutput->SetAttack(8);
				aioutput->moveButton4();
				ChangeAttackState(AIS_CRASH_GRENADE1);
			}
			break;
		case AIS_CRASH_GRENADE1:
			if(aiinput->GetStateFlags()->S_ON_GROUND && (!aiinput->GetStateFlags()->S_ATTACK) && (!aiinput->GetStateFlags()->S_JUMP))
			{
				FacePlayer();
				aioutput->SetAttack(2);
				aioutput->moveButton4();
				mode3_count++;
				if(mode3_count == 3)
				{
					mode3_count = 0;
					ChangeAttackState(AIS_CRASH_GRENADE2);
				}
				//ChangeAttackState(AIS_CRASH_HILOW);
			}
			break;
		case AIS_CRASH_GRENADE2:
			if(aiinput->GetStateFlags()->S_ON_GROUND && (!aiinput->GetStateFlags()->S_ATTACK) && (!aiinput->GetStateFlags()->S_JUMP))
			{
				FacePlayer();
				aioutput->SetAttack(3);
				aioutput->moveButton4();
				mode3_count++;
				if(mode3_count == 3)
				{
					mode3_count = 0;
					ChangeAttackState(AIS_CRASH_PAUSE);
				}

			}
			break;
		case AIS_CRASH_PAUSE:
			if(pause_timer <= 0)
			{
				pause_timer = pause_time;
				mode3_count = 0;
				ChangeAttackState(AIS_CRASH_GRENADE1);
			}
			else pause_timer -= time;
			break;
		}
	}

}

void AIEnemyCrash::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos();
	xpos = aiinput->GetXLoc();
	ypos = aiinput->GetYLoc();

	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);

	if(aiinput->GetStateFlags()->S_DEAD) return;

	if(new_enemy)
	{
		new_enemy = false;
		cur_health = aiinput->GetCurLife();
	}

	prev_health = cur_health;
	cur_health = aiinput->GetCurLife();

	
	
	if( (prev_health - cur_health) >0 ) damaged = true;
	else damaged = false;



	switch(GetState())
	{
	case AIS_CHASE:
		Chase();
		break;
	case AIS_ATTACK:
		Attack();
		break;
	case AIS_PATROL:
		Patrol();
		break;
	case AIS_MOVE:
		MoveToXTile(movetoxtile);
		break;
	case AIS_WAIT:
		Wait();
		break;
/*	case AIS_NAVIGATE_DOWN:
		break;
	case AIS_NAVIGATE_UP:
		break;*/
	}
}

void AIEnemyCrash::Chase()
{
	if(fabs(xpos - aio->player_input->GetXLoc()) <= attack_range)
	{
		aioutput->moveStop();
		rapidfire_count = 0;
		ChangeAttackState(AIS_CRASH_RAPIDFIRE);
		ChangeState(AIS_ATTACK);
	}
	else
	{
		FacePlayer();
		if(aio->player_input->GetXTilePos() < xtile ) aioutput->moveLeft();
		else aioutput->moveRight();
	}
}

void AIEnemyCrash::Patrol()
{
	if( (abs(aio->player_input->GetYTilePos() - ytile) <= 2) && (xtile > 1) && (xtile < 14)) 
	{
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
		return;
	}

	if(!IsStopBlock())
	{
		if(aiinput->GetDirection()) aioutput->moveRight();
		else aioutput->moveLeft();
	}
	else
	{
		if(aiinput->GetDirection()) aioutput->moveLeft();
		else aioutput->moveRight();
	}



}
