// EnemyBaseballPunk.h: interface for the EnemyBaseballPunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYBASEBALLPUNK_H__3E078460_EFA9_49D0_8937_069557D0C0E4__INCLUDED_)
#define AFX_ENEMYBASEBALLPUNK_H__3E078460_EFA9_49D0_8937_069557D0C0E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyBaseballPunk : public BaseEnemy  
{
public:
	AIEnemyBaseballPunk();
	virtual ~AIEnemyBaseballPunk();
	void UseBrain();
	bool IsStopBlock();
	float punch_time;
	float punch;
	void Patrol();
	void Chase();
	void Attack();
	


};

#endif // !defined(AFX_ENEMYBASEBALLPUNK_H__3E078460_EFA9_49D0_8937_069557D0C0E4__INCLUDED_)
