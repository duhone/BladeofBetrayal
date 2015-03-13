// EnemyGawain.cpp: implementation of the EnemyGawain class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyGawain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyGawain::AIEnemyGawain()
{
	attackstate=AIS_GAW_INTRO;
	prevattackstate=AIS_GAW_SLASH;
	attack_range = 44;
	current_state = AIS_ATTACK;
	teleport_range = 2;
	teleport_distance = 3;
	temp = 100;
	slash_time = .75;
	slash_timer = .75;
	teleport_rx = 20;
	teleport_lx = 3;
	jump = false;
	jump_count =0;
	shock_count = 0;
	second_stage = false;
	animal_attack_count =0;
	above_head_timer = 0;
	above_head_time = 3;
	berzerk_timer =0;
	berzerk_time =.5;
	

}

AIEnemyGawain::~AIEnemyGawain()
{

}

void AIEnemyGawain::Attack()
{
	if(aiinput->GetStateFlags()->S_DEAD) return;

/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[GAWAIN] (direction:%d)", aiinput->GetDirection());
	OutputDebugString(temp);
#endif*/

	int pxt = aio->player_input->GetXTilePos();
	float pxloc = aio->player_input->GetXLoc();

	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);


	if((aiinput->GetCurLife() <= 10) && !second_stage)
	{
		second_stage = true;
		ChangeAttackState(AIS_GAW_ANIMAL_START);
	}

	if(th >= 3)
	{
		float tempx, tempy;
		
		
		if(above_head_timer <= 0)
		{
			aiinput->GetDisplacementVector(&tempx , &tempy);
			above_head_timer = above_head_time;
			FacePlayer();
			if(tempx != 0)
			{
				if(aiinput->GetStateFlags()->nCurrAttack == 4)
				{
					aioutput->SetAttack(5);
					aioutput->moveButton4();
				}
				else aioutput->moveStop();
			}
			else
			{
				
				aioutput->SetAttack(6);
				aioutput->moveButton4();
			}
		}
		else above_head_timer -= time;

		return;
	}

	if(!second_stage)
	{
		switch(attackstate)
		{
		case AIS_GAW_INTRO:
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				FacePlayer();
				aioutput->SetAttack(0);
				aioutput->moveButton4();
				ChangeAttackState(AIS_GAW_TELEPORT);
			}
			break;
		case AIS_GAW_SLASH:
			FacePlayer();
			if(fabs(xpos - aio->player_input->GetXLoc()) >= attack_range)
			{
				if(pxt > xtile) aioutput->moveRight();
				else aioutput->moveLeft();
			}
			if(slash_timer<=0)
			{
				if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
				{
					
					slash_timer = slash_time;
					
					aioutput->SetAttack(1);
					aioutput->moveButton4();
					ChangeAttackState(AIS_GAW_ANIMAL_START);
				}
			}
			else slash_timer -= time;
			break;
		case AIS_GAW_TELEPORT:
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				if(abs(pxt - xtile) <= teleport_range)
				{
					aioutput->SetAttack(4);
					aioutput->moveButton4();
					if(aio->player_input->GetDirection()) teleport_x = pxt - teleport_distance;
					else teleport_x = pxt + teleport_distance;
					ChangeAttackState(AIS_GAW_TELEPORT_FINISH);
				}
				else
				{
					if(pxt < xtile) aioutput->moveLeft();
					else aioutput->moveRight();
				}
			}
			break;
		case AIS_GAW_TELEPORT_FINISH:
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
			
				if(!IsStopBlock())
				{
					if(aiinput->GetDirection())
					{
						if(xtile >= teleport_x)
						{
							aioutput->moveStop();
							aioutput->SetAttack(5);
							aioutput->moveButton4();
							ChangeAttackState(AIS_GAW_SLASH);
						}
						else aioutput->moveRight();
					}
					else
					{
						if(xtile <= teleport_x)
						{
							aioutput->moveStop();
							aioutput->SetAttack(5);
							aioutput->moveButton4();
							ChangeAttackState(AIS_GAW_SLASH);
						}
						else aioutput->moveLeft();
					}
				}
				else
				{
					aioutput->moveStop();
					aioutput->SetAttack(5);
					aioutput->moveButton4();
					ChangeAttackState(AIS_GAW_SLASH);
				}
			}
			break;
		case AIS_GAW_ANIMAL_START:
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				if( (xtile - teleport_lx) < (teleport_rx - xtile)) teleport_x = teleport_rx;
				else teleport_x = teleport_lx;
				aioutput->SetAttack(4);
				aioutput->moveButton4();
				ChangeAttackState(AIS_GAW_ANIMAL_MOVE);
			}	
			break;
		case AIS_GAW_ANIMAL_MOVE:
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
			
				if(xtile != teleport_x)
				{
					if(teleport_x < xtile) aioutput->moveLeft();
					else aioutput->moveRight();
				}
				else
				{

					aioutput->moveStop();
					aioutput->SetAttack(5);
					aioutput->moveButton4();
					ChangeAttackState(AIS_GAW_ANIMAL_FINISH);

				}
			}
			break;
		case AIS_GAW_ANIMAL_FINISH:
			FacePlayer();
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				aioutput->SetAttack(3);
				aioutput->moveButton4();
				ChangeState(AIS_CHASE);
			}
			break;
		case AIS_GAW_SLASH_JUMP:
			FacePlayer();
			if(!aiinput->GetStateFlags()->S_ATTACK)
			{
				
				if(jump_count == 3)
				{
				//	aioutput->moveStop();
					
					if(!aiinput->GetStateFlags()->S_JUMP)
					{
						shock_count++;
						aioutput->SetAttack(2);
						aioutput->moveButton4();
					}
					if(shock_count == 3)
					{
						shock_count = 0;
						jump_count = 0;
						jump = false;
						ChangeAttackState(AIS_GAW_TELEPORT);
					}
					break;
				}
				if(jump)
				{
					jump_count++;
					jump = false;
					aioutput->moveButton3();
					if(jump_count != 3) ChangeState(AIS_CHASE);
				
				}
				else 
				{
					jump = true;
					aioutput->SetAttack(1);
					aioutput->moveButton4();
				
				}

			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch(attackstate)
		{
		case AIS_GAW_ANIMAL_START:
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				if( (xtile - teleport_lx) < (teleport_rx - xtile)) teleport_x = teleport_rx;
				else teleport_x = teleport_lx;
				aioutput->SetAttack(4);
				aioutput->moveButton4();
				ChangeAttackState(AIS_GAW_ANIMAL_MOVE);

			}	
			break;
		case AIS_GAW_ANIMAL_MOVE:

			if(!aiinput->GetStateFlags()->S_ATTACK  && !aiinput->GetStateFlags()->S_DAMAGED)
			{
			
				if(xtile != teleport_x)
				{
					if(teleport_x < xtile) aioutput->moveLeft();
					else aioutput->moveRight();
				}
				else
				{

					aioutput->moveStop();
					aioutput->SetAttack(5);
					aioutput->moveButton4();
					ChangeAttackState(AIS_GAW_ANIMAL_FINISH);

				}
			}
			break;
		case AIS_GAW_ANIMAL_FINISH:
	
			FacePlayer();
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				
				
				if(berzerk_timer <= 0)
				{
					berzerk_timer = berzerk_time;
					aioutput->SetAttack(3);
					aioutput->moveButton4();
					animal_attack_count++;
				}
				else berzerk_timer -= time;
				
				if(animal_attack_count >= 5)
				{
					animal_attack_count = 0;
					ChangeState(AIS_CHASE);
				}
				
				
			}
			break;
		case AIS_GAW_SLASH_JUMP:
			FacePlayer();

			if(fabs(xpos - aio->player_input->GetXLoc()) >= attack_range)
			{
				if(pxt > xtile) aioutput->moveRight();
				else aioutput->moveLeft();
			}
			else aioutput->moveStop();

			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				
				if(jump_count == 1)
				{
				//	aioutput->moveStop();
					
					if(!aiinput->GetStateFlags()->S_JUMP)
					{
						shock_count++;
						aioutput->SetAttack(2);
						aioutput->moveButton4();
					}
					if(shock_count == 3)
					{
						shock_count = 0;
						jump_count = 0;
						jump = false;
						ChangeAttackState(AIS_GAW_ANIMAL_START);
					}
					break;
				}
				if(jump)
				{
					jump_count++;
					jump = false;
					aioutput->moveButton3();
					if(jump_count != 1) ChangeState(AIS_CHASE);
				
				}
				else 
				{
					jump = true;
					aioutput->SetAttack(1);
					aioutput->moveButton4();
				
				}

			}
			break;
		default: break;
		}
	}
}

void AIEnemyGawain::Chase()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - aio->player_input->GetYTilePos());

	if(aiinput->GetStateFlags()->S_DEAD) return;
	
	if(th >= 3)
	{
		float tempx, tempy;
		
		
		if(above_head_timer <= 0)
		{
			aiinput->GetDisplacementVector(&tempx , &tempy);
			above_head_timer = above_head_time;
			FacePlayer();
			if(tempx != 0)
			{
				if(aiinput->GetStateFlags()->nCurrAttack == 4)
				{
					aioutput->SetAttack(5);
					aioutput->moveButton4();
				}
				else aioutput->moveStop();
			}
			else
			{
				
				aioutput->SetAttack(6);
				aioutput->moveButton4();
			}
		}
		else above_head_timer -= time;

		return;
	}
	else{
	
		if(!aiinput->GetStateFlags()->S_JUMP)
		{
			
			if(fabs(xpos - aio->player_input->GetXLoc()) <= attack_range)
			{
				aioutput->moveStop();
				ChangeState(AIS_ATTACK);
				jump = false;
				ChangeAttackState(AIS_GAW_SLASH_JUMP);
				return;
			}
			
			if(xtile > aio->player_input->GetXTilePos()) aioutput->moveLeft();
			else aioutput->moveRight();
		}
	}
}
