// EnemyAdvancedGeneticMonster2.cpp: implementation of the EnemyAdvancedGeneticMonster2 class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyAdvancedGeneticMonster2.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyAdvancedGeneticMonster2::AIEnemyAdvancedGeneticMonster2()
{

	was_damaged = false;
	damage_count =0;
	attackstate=AIS_AGM_SLASH;
	prevattackstate=AIS_AGM_SLASH;
	attack_range = 50;
	ignore_player = false;
	current_state = AIS_ATTACK;
	attack_height = 4;
	damaged = false;
	temp = true;
//	cur_health = aiinput->GetCurLife();
}

AIEnemyAdvancedGeneticMonster2::~AIEnemyAdvancedGeneticMonster2()
{

}

void AIEnemyAdvancedGeneticMonster2::Attack()
{
/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "[AGM] attackstate (xtile:%d)(ytile:%d)(stop:%d)(direction:%d)", xtile, ytile, IsStopBlock(), aiinput->GetDirection());
	OutputDebugString(temp);
#endif*/
	
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);

	//if(th > attack_height) ChangeState(AIS_PATROL);

	if(IsStopBlock())
	{
		ignore_player = true;
		ChangeState(AIS_PATROL);
		return;
	}
	
	switch(attackstate)
	{
/*	case AIS_AGM_INTRO:
		if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
		{
			FacePlayer();
			aioutput->SetAttack(1);
			aioutput->moveButton4();
			ChangeAttackState(AIS_AGM_SLASH);
		}
		break;*/
	case AIS_AGM_SLASH:	
		if(aiinput->GetStateFlags()->S_ON_GROUND && !aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
		{
			if(fabs(aio->player_input->GetXLoc()-xpos) <= attack_range) 
			{
				
				FacePlayer();
				aioutput->SetAttack(0);
				aioutput->moveButton4();
				ChangeAttackState(AIS_AGM_JUMP);

			}
			else ChangeState(AIS_CHASE);
		}
		break;	
	case AIS_AGM_JUMP:
		if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
		{
			FacePlayer();
			aioutput->moveButton3();
			ChangeAttackState(AIS_AGM_SLASH2);
		}
		break;
	case AIS_AGM_SLASH2:
		if(aiinput->GetStateFlags()->S_ON_GROUND && !aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
		{
			if(fabs(aio->player_input->GetXLoc()-xpos) <= attack_range) 
			{
				
				FacePlayer();
				aioutput->SetAttack(0);
				aioutput->moveButton4();
				ChangeAttackState(AIS_AGM_RUN);

			}
			else ChangeState(AIS_CHASE);
		}
		break;

	/*case AIS_AGM_SPIKE:
		if(aiinput->GetStateFlags()->S_ON_GROUND && !aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
		{
			FacePlayer();
			aioutput->SetAttack(2);
			aioutput->moveButton4();
			ChangeAttackState(AIS_AGM_RUN);
			run_direction = aiinput->GetDirection();
		}
		break;*/
	case AIS_AGM_RUN:
		if(!aiinput->GetStateFlags()->S_ATTACK)
		{
			if(!IsStopBlock())
			{
				if(run_direction) aioutput->moveRight();
				else aioutput->moveLeft();
				
			}
			else 
			{
				aioutput->moveStop();
				ChangeAttackState(AIS_AGM_SLASH);
			}
		}
		
	default:
		break;
	}



	
/*	switch(attackstate)
	{
	case AIS_AGM_INTRO:
		if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
		{
			FacePlayer();
			aioutput->SetAttack(1);
			aioutput->moveButton4();
			ChangeAttackState(AIS_AGM_SLASH);
		}
		break;
	case AIS_AGM_SLASH:
		if((th < attack_height) && (fabs(aio->player_input->GetXLoc()-xpos) <= attack_range)) 
		{
			if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_JUMP && !aiinput->GetStateFlags()->S_DAMAGED)
			{
				FacePlayer();
				aioutput->SetAttack(0);
				aioutput->moveButton4();
				
			}
			if(damaged)
			{
				damaged = false;
				if(damage_count == 2) 
				{
					ChangeAttackState(AIS_AGM_SPIKE);
				}
				else
				{
					damage_count++;
					ChangeAttackState(AIS_AGM_JUMP);
				}
			}
		}
		else if(th > attack_height) ChangeState(AIS_PATROL);
		else ChangeState(AIS_CHASE);
		
		break;
	case AIS_AGM_JUMP:
		if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
		{
			aioutput->moveButton3();
			ChangeAttackState(AIS_AGM_SLASH);
		}
		break;
	case AIS_AGM_SPIKE:
		if(!aiinput->GetStateFlags()->S_ATTACK && !aiinput->GetStateFlags()->S_DAMAGED)
		{
			aioutput->SetAttack(2);
			aioutput->moveButton4();
			ChangeAttackState(AIS_AGM_SLASH);
			damage_count = 0;
		}
		break;
	default:
		break;
	}*/
}

void AIEnemyAdvancedGeneticMonster2::Patrol()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);
	
	
/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "[AGM] patrolstate (xtile:%d)(ytile:%d)(stop:%d)", xtile, ytile, IsStopBlock());
	OutputDebugString(temp);
#endif*/
	
	
	if(fabs(aio->player_input->GetXLoc() - xpos) <= 8)
	{
		ignore_player = false;
		ChangeState(AIS_ATTACK);
	}
	
	if(th > attack_height || ignore_player) 
	{
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
	ChangeState(AIS_CHASE);

}

void AIEnemyAdvancedGeneticMonster2::Chase()
{
	int pyt = aio->player_input->GetYTilePos();
	int th = abs(ytile - pyt);
	int pxt = aio->player_input->GetXTilePos();

/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "[AGM] chasestate (xtile:%d)(ytile:%d)(stop:%d)", xtile, ytile, IsStopBlock());
	OutputDebugString(temp);
#endif*/
	if(IsStopBlock())
	{
		ignore_player = true;
		ChangeState(AIS_PATROL);
		return;
	}
	
	if(fabs(aio->player_input->GetXLoc()-xpos) <= attack_range) 
	{
		aioutput->moveStop();
		ChangeState(AIS_ATTACK);
		//ChangeAttackState(AIS_AGM_SLASH);
	
	}
	else if(th <=1)
	{
		if(xtile < pxt ) aioutput->moveRight();
		else aioutput->moveLeft();
	}
	else ChangeState(AIS_PATROL);
	
}

void AIEnemyAdvancedGeneticMonster2::UseBrain()
{
	xtile = aiinput->GetXTilePos();
	ytile = aiinput->GetYTilePos()-1;
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

/*#ifdef _DEBUG
	char temp[256];
	sprintf(temp, "{AI}[AGM] (th:%d)", th);
	OutputDebugString(temp);
#endif*/

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

bool AIEnemyAdvancedGeneticMonster2::IsStopBlock()
{
	int count=0;
	unsigned char blk= GetAIMapCord(xtile, ytile);
	unsigned char blkl;
	
	if(aiinput->GetDirection())
	{
		//check ai coding
		if( (blk == BLK_STOP) || (blk == BLK_STOPRIGHT)) return true;	
		if(use_patrol_bounds) if(xtile == aiinput->upper_patrol_x) return true;
		//check for blocks in the level in front of us
		
		for(count=0; count<=aiinput->GetTileHeight()+6; count++)
		{
			blkl=aio->level_interface->GetLevelData(xtile+3, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}
		
	}
	else
	{
		if( (blk == BLK_STOP) || (blk == BLK_STOPLEFT)) return true;
		if(use_patrol_bounds) if(xtile == aiinput->lower_patrol_x) return true;
		
		for(count=0; count<=aiinput->GetTileHeight()+6; count++)
		{
			
			blkl=aio->level_interface->GetLevelData(xtile-3, ytile-count-1);
			if(*(cblocks+blkl)) return true;

//			if(count >=10) break;
		}

	}

	return false;
}

