// EnemyGMonster.h: interface for the EnemyGMonster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYGMONSTER_H__EFF3E850_94AF_4D46_AD3C_B99C286183D6__INCLUDED_)
#define AFX_ENEMYGMONSTER_H__EFF3E850_94AF_4D46_AD3C_B99C286183D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyGMonster : public BaseEnemy  
{
public:
	int attack_count;
	
	bool IsStopBlock();
	float wait_timer;
	float wait_time;
	void Patrol();
	float run_time;
	float run_timer;
	void Chase();
	void Wait();
	void Attack();
	AIEnemyGMonster();
	virtual ~AIEnemyGMonster();
	

};

#endif // !defined(AFX_ENEMYGMONSTER_H__EFF3E850_94AF_4D46_AD3C_B99C286183D6__INCLUDED_)
