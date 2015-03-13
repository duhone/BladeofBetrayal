// EnemyDockWrench.h: interface for the EnemyDockWrench class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENEMYDOCKWRENCH_H__50CEE572_2C09_4C3B_9FEE_CF649844F92F__INCLUDED_)
#define AFX_ENEMYDOCKWRENCH_H__50CEE572_2C09_4C3B_9FEE_CF649844F92F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseEnemy.h"

class AIEnemyDocWrench : public BaseEnemy  
{
public:

	AIEnemyDocWrench();
	virtual ~AIEnemyDocWrench();
void UseBrain();
	bool IsStopBlock();
	float punch_time;
	float punch;
	void Patrol();
	void Chase();
	void Attack();

};

#endif // !defined(AFX_ENEMYDOCKWRENCH_H__50CEE572_2C09_4C3B_9FEE_CF649844F92F__INCLUDED_)
