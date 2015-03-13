// EnemyGMonsterSpit.cpp: implementation of the EnemyGMonsterSpit class.
//
//////////////////////////////////////////////////////////////////////

#include "AIEnemyGMonsterSpit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIEnemyGMonsterSpit::AIEnemyGMonsterSpit()
{
//	SetAttackRange(10*16);
//	SetChaseRange(0);
//	ChangeState(AIS_ATTACK);
	current_state = AIS_ATTACK;
	float temp = ((float)(rand()%500)/500)-.25f;
	fire_time = 2.0f + temp;
	fire = 0;
}

AIEnemyGMonsterSpit::~AIEnemyGMonsterSpit()
{

}
